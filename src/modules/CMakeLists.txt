# CMakeLists for EwsQt5 lib extra modules

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ewsqt5-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/ewsqt5-config.cmake
  @ONLY
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ewsqt5-config-version.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/ewsqt5-config-version.cmake
  @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ewsqt5-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/ewsqt5-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ewsqt5/
)
