# Auto generate the Qt's moc files
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(libews_qt_SRCS
    esoapnamespaces.cpp
    esoapelement.cpp
    esoapmessage.cpp
    emailaddress.cpp
    permission.cpp
    folder.cpp
    folder_p.h
    effectiverights.cpp
    message.cpp
    reply.cpp
    reply_p.h
    syncfolderitemsreply.cpp
    syncfolderitemsreply_p.h
    syncfolderhierarchyreply.cpp
    syncfolderhierarchyreply_p.h
    request.cpp
    autodiscover.cpp
    autodiscoverreply.cpp
    connection.cpp
)

set(ewsqt_HEADERS
    export.h
    esoapmessage.h
    esoapelement.h
    esoapnamespaces.h
    emailaddress.h
    permission.h
    folder.h
    effectiverights.h
    message.h
    reply.h
    syncfolderitemsreply.h
    syncfolderhierarchyreply.h
    request.h
    autodiscover.h
    autodiscoverreply.h
    connection.h
)

KDSOAP_GENERATE_WSDL(libews_qt_SRCS Services.wsdl)

add_library(ews-qt5 SHARED ${libews_qt_SRCS})
set_target_properties(ews-qt5 PROPERTIES VERSION ${EWSQT_VERSION} SOVERSION ${EWSQT_API_LEVEL})
set_property(TARGET ews-qt5 PROPERTY COMPILE_DEFINITIONS MAKE_EWS_LIB)

qt5_use_modules(ews-qt5 Network Xml)
target_link_libraries(ews-qt5
    KDSoap::kdsoap
)


install(TARGETS ews-qt5 DESTINATION ${CMAKE_INSTALL_LIBDIR})
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libews-qt5.pc
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
#)
install(FILES ${ewsqt_HEADERS}
        DESTINATION include/EwsQt5
)

add_subdirectory(modules)
