include_directories(${CMAKE_BINARY_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(libews_qt_SRCS
    wsdl_Services.cpp
    ESoapNamespaces.cpp
    ESoapMessage.cpp
    ESoapElement.cpp
    EwsEmailAddress.cpp
    EwsPermission.cpp
    EwsFolder.cpp
    EwsEffectiveRights.cpp
    EwsMessage.cpp
    EwsReply.cpp
    EwsSyncFolderItemsReply.cpp
    EwsSyncFolderHierarchyReply.cpp
    EwsSyncFolderHierarchyReply_p.h
    EwsRequest.cpp
    EwsAutoDiscover.cpp
    EwsAutoDiscoverReply.cpp
    EwsConnection.cpp
)

add_library(libews-qt SHARED ${libews_qt_SRCS})
target_link_libraries(libews-qt
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Quick_LIBRARIES}
    ${Qt5Network_LIBRARIES}
    ${Qt5Xml_LIBRARIES}
    ${Qt5Core_LIBRARIES}
    KDSoap::kdsoap
    -lresolv
)

set_property(TARGET libews-qt PROPERTY COMPILE_DEFINITIONS MAKE_EWS_LIB)

#install(TARGETS libews-qt DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
