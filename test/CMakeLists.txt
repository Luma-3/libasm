cmake_minimum_required(VERSION 3.22)
project(asm_test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(asm_test
	ft_strlen.cpp
)

target_link_libraries(asm_test PRIVATE
	gtest_main
	${CMAKE_SOURCE_DIR}/../libasm.a
)

enable_testing()

include(GoogleTest)
gtest_discover_tests(asm_test)
