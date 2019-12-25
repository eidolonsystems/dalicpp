include_directories(SYSTEM ${DOCTEST_INCLUDE_PATH})
file(GLOB source_files ${DALI_SOURCE_PATH}/Tests/*.cpp)
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()
add_executable(dali_tester ${source_files})
if(UNIX)
  target_link_libraries(dali_tester pthread)
endif()
add_custom_command(TARGET dali_tester POST_BUILD COMMAND dali_tester)
install(TARGETS dali_tester CONFIGURATIONS Debug
  DESTINATION ${TEST_INSTALL_DIRECTORY}/Debug)
install(TARGETS dali_tester CONFIGURATIONS Release RelWithDebInfo
  DESTINATION ${TEST_INSTALL_DIRECTORY}/Release)
