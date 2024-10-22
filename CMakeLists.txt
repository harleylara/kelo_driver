cmake_minimum_required(VERSION 3.14)
project(kelo_driver)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra)
endif()

include(ExternalProject)

ExternalProject_Add(
    SOEM
    GIT_REPOSITORY  https://github.com/OpenEtherCATsociety/SOEM.git 
    GIT_TAG         master
    GIT_SHALLOW     1
    UPDATE_DISCONNECTED 1
    SOURCE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/soem"
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
                    -DCMAKE_C_FLAGS="-fPIC"
)

include_directories("${CMAKE_INSTALL_PREFIX}/include")
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(ament_cmake QUIET)

if (ament_cmake_FOUND)
    message("ament_cmake found. Enabling ROS 2 specific parts.")
else()
    message("ament_cmake not found. Building without ROS 2 support.")
endif()


set(SOEM_LIBRARY ${CMAKE_INSTALL_PREFIX}/lib/libsoem.a)

# Create the shared library
add_library(kelo_driver SHARED src/EthercatBus.cpp)
add_dependencies(kelo_driver SOEM)
target_link_libraries(kelo_driver PRIVATE ${SOEM_LIBRARY})

# Install the library and headers
install(TARGETS kelo_driver
  EXPORT export_kelo_driver
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install header files
install(DIRECTORY include/
  DESTINATION include
)

# Test executable linking to the shared library
add_executable(kelo src/kelo.cpp)
target_link_libraries(kelo PRIVATE kelo_driver)

install(TARGETS
  kelo
  DESTINATION lib/${PROJECT_NAME})

# Export package
ament_export_include_directories(include)
ament_export_libraries(kelo_driver)

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
