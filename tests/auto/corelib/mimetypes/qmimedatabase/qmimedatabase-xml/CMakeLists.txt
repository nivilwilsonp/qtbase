# Generated from qmimedatabase-xml.pro.

if(NOT QT_FEATURE_private_tests)
    return()
endif()

#####################################################################
## tst_qmimedatabase-xml Test:
#####################################################################

add_qt_test(tst_qmimedatabase-xml
    SOURCES
        ../tst_qmimedatabase.h
        tst_qmimedatabase-xml.cpp
    PUBLIC_LIBRARIES
        Qt::Concurrent
)

# Resources:
# special case begin
# the freedesktop resources are handled manually below via mimetypes_resources.cmake
#set(mimetypes_resource_files
    #"mime/packages/freedesktop.org.xml"
#)
# special case end
set_source_files_properties("../invalid-magic1.xml"
    PROPERTIES QT_RESOURCE_ALIAS "invalid-magic1.xml"
)
set_source_files_properties("../invalid-magic2.xml"
    PROPERTIES QT_RESOURCE_ALIAS "invalid-magic2.xml"
)
set_source_files_properties("../invalid-magic3.xml"
    PROPERTIES QT_RESOURCE_ALIAS "invalid-magic3.xml"
)
set_source_files_properties("../magic-and-hierarchy.foo"
    PROPERTIES QT_RESOURCE_ALIAS "magic-and-hierarchy.foo"
)
set_source_files_properties("../magic-and-hierarchy.xml"
    PROPERTIES QT_RESOURCE_ALIAS "magic-and-hierarchy.xml"
)
set_source_files_properties("../magic-and-hierarchy2.foo"
    PROPERTIES QT_RESOURCE_ALIAS "magic-and-hierarchy2.foo"
)
set_source_files_properties("../qml-again.xml"
    PROPERTIES QT_RESOURCE_ALIAS "qml-again.xml"
)
set_source_files_properties("../test.qml"
    PROPERTIES QT_RESOURCE_ALIAS "test.qml"
)
set_source_files_properties("../text-x-objcsrc.xml"
    PROPERTIES QT_RESOURCE_ALIAS "text-x-objcsrc.xml"
)
set_source_files_properties("../yast2-metapackage-handler-mimetypes.xml"
    PROPERTIES QT_RESOURCE_ALIAS "yast2-metapackage-handler-mimetypes.xml"
)
set(testdata_resource_files
    "invalid-magic1.xml"
    "invalid-magic2.xml"
    "invalid-magic3.xml"
    "magic-and-hierarchy.foo"
    "magic-and-hierarchy.xml"
    "magic-and-hierarchy2.foo"
    "qml-again.xml"
    "test.qml"
    "text-x-objcsrc.xml"
    "yast2-metapackage-handler-mimetypes.xml"
)

add_qt_resource(tst_qmimedatabase-xml "testdata"
    PREFIX
        "/qt-project.org/qmime"
    BASE
        ".."
    FILES
        ${testdata_resource_files}
)

# special case begin
set(corelib_source_dir ../../../../../../src/corelib)
include(${corelib_source_dir}/mimetypes/mimetypes_resources.cmake)
corelib_add_mimetypes_resources(tst_qmimedatabase-xml)
# special case end

#### Keys ignored in scope 1:.:.:qmimedatabase-xml.pro:<TRUE>:
# _REQUIREMENTS = "qtConfig(private_tests)"

## Scopes:
#####################################################################

extend_target(tst_qmimedatabase-xml CONDITION GCC
    COMPILE_OPTIONS
        -W
        -Wall
        -Wextra
        -Wno-long-long
        -Wnon-virtual-dtor
        -Wshadow
)

extend_target(tst_qmimedatabase-xml CONDITION UNIX AND NOT APPLE AND NOT QNX
    DEFINES
        USE_XDG_DATA_DIRS
)
