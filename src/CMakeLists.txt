# CMakeLists for UDisks-Qt library
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(-fPIC)

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

set(ewsqt_HEADERS
    ESoapNamespaces.h
    ESoapMessage.h
    ESoapElement.h
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

add_library(libews-qt5 SHARED ${libews_qt_SRCS})
set_target_properties(libews-qt5 PROPERTIES VERSION ${EWSQT_VERSION} SOVERSION ${EWSQT_API_LEVEL})
target_link_libraries(libews-qt5
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Quick_LIBRARIES}
    ${Qt5Network_LIBRARIES}
    ${Qt5Xml_LIBRARIES}
    ${Qt5Core_LIBRARIES}
    KDSoap::kdsoap
    -lresolv
)

set_property(TARGET libews-qt5 PROPERTY COMPILE_DEFINITIONS UDISKS_STATIC)

install(TARGETS libews-qt5 DESTINATION ${CMAKE_INSTALL_LIBDIR})
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libews-qt5.pc
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
#)
install(FILES ${ewsqt_HEADERS}
        DESTINATION include/EwsQt5
)

set_property(TARGET libews-qt5 PROPERTY COMPILE_DEFINITIONS MAKE_EWS_LIB)

add_subdirectory(modules)
