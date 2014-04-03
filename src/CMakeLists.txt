# Auto generate the Qt's moc files
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(libews_qt_SRCS
    wsdl_Services.cpp
    ESoapNamespaces.cpp
    ESoapElement.cpp
    ESoapMessage.cpp
    EwsEmailAddress.cpp
    EwsPermission.cpp
    EwsFolder.cpp
    EwsFolder_p.h
    EwsEffectiveRights.cpp
    EwsMessage.cpp
    EwsReply.cpp
    EwsReply_p.h
    EwsSyncFolderItemsReply.cpp
    EwsSyncFolderItemsReply_p.h
    EwsSyncFolderHierarchyReply.cpp
    EwsSyncFolderHierarchyReply_p.h
    EwsRequest.cpp
    EwsAutoDiscover.cpp
    EwsAutoDiscoverReply.cpp
    EwsConnection.cpp
)

set(ewsqt_HEADERS
    ewsexport.h
    ESoapMessage.h
    EwsEmailAddress.h
    EwsPermission.h
    EwsFolder.h
    EwsEffectiveRights.h
    EwsMessage.h
    EwsReply.h
    EwsSyncFolderItemsReply.h
    EwsSyncFolderHierarchyReply.h
    EwsRequest.h
    EwsAutoDiscover.h
    EwsAutoDiscoverReply.h
    EwsConnection.h
)

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
