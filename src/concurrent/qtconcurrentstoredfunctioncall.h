/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtConcurrent module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QTCONCURRENT_STOREDFUNCTIONCALL_H
#define QTCONCURRENT_STOREDFUNCTIONCALL_H

#include <QtConcurrent/qtconcurrent_global.h>

#ifndef QT_NO_CONCURRENT
#include <QtConcurrent/qtconcurrentrunbase.h>
#include <type_traits>

QT_BEGIN_NAMESPACE


#ifndef Q_QDOC

namespace QtConcurrent {

template <class Function, class ...Args>
struct InvokeResult
{
    static_assert(std::is_invocable_v<std::decay_t<Function>, std::decay_t<Args>...>,
                  "It's not possible to invoke the function with passed arguments.");

    using Type = std::invoke_result_t<std::decay_t<Function>, std::decay_t<Args>...>;
};

template <class Function, class ...Args>
using InvokeResultType = typename InvokeResult<Function, Args...>::Type;

template <class Function, class ...Args>
struct StoredFunctionCall : public RunFunctionTask<InvokeResultType<Function, Args...>>
{
    template <class ...Types>
    using DecayedTuple = std::tuple<std::decay_t<Types>...>;

    StoredFunctionCall(Function &&f, Args &&...args)
        : data{std::forward<Function>(f), std::forward<Args>(args)...}
    {}

    void runFunctor() override
    {
        using Indexes =
            std::make_index_sequence<
                std::tuple_size<DecayedTuple<Function, Args...>>::value>;

        invoke(Indexes());
    }

    template <std::size_t... I>
    void invoke(std::index_sequence<I...>)
    {
        if constexpr (std::is_void_v<InvokeResultType<Function, Args...>>)
            std::invoke(std::get<I>(std::move(data))...);
        else
            this->result = std::invoke(std::get<I>(std::move(data))...);
    }

    DecayedTuple<Function, Args...> data;
};

} //namespace QtConcurrent

#endif // Q_QDOC

QT_END_NAMESPACE

#endif // QT_NO_CONCURRENT

#endif
