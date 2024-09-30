cmake_minimum_required(VERSION 3.14)
project(wheels_driver)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra)
endif()

include(ExternalProject)

ExternalProject_Add(
    SOEM
    GIT_REPOSITORY  https://github.com/OpenEtherCATsociety/SOEM.git 
    GIT_TAG         master
    SOURCE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/soem"
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)

add_executable(demo src/main.cpp)
add_dependencies(demo SOEM)
include_directories("${CMAKE_INSTALL_PREFIX}/include")

find_package(ament_cmake REQUIRED)

set(SOEM_LIBRARY ${CMAKE_INSTALL_PREFIX}/lib/libsoem.a)
target_link_libraries(demo ${SOEM_LIBRARY})

install(TARGETS
  demo
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
    find_package(ament_lint_auto REQUIRED)
    # the following line skips the linter which checks for copyrights
    # comment the line when a copyright and license is added to all source files
    set(ament_cmake_copyright_FOUND TRUE)
    # the following line skips cpplint (only works in a git repo)
    # comment the line when this package is in a git repo and when
    # a copyright and license is added to all source files
    set(ament_cmake_cpplint_FOUND TRUE)
    ament_lint_auto_find_test_dependencies()
endif()

ament_package()
