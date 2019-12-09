add_executable(unit_tests
    main.cpp
    parser_test.cpp
)

catch_discover_tests(unit_tests)
