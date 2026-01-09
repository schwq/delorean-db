add_executable(deloreandb-tests db_tests.cc)

target_link_libraries(deloreandb-tests PRIVATE deloreandb gtest_main)

target_compile_features(deloreandb-tests PRIVATE cxx_std_23)

include(GoogleTest)
gtest_discover_tests(deloreandb-tests)