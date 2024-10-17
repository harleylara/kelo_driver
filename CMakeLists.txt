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
)

add_executable(demo src/main.cpp)
add_executable(slaves src/slaves.cpp)

add_dependencies(demo SOEM)
add_dependencies(slaves SOEM)

include_directories("${CMAKE_INSTALL_PREFIX}/include")
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(ament_cmake REQUIRED)

set(SOEM_LIBRARY ${CMAKE_INSTALL_PREFIX}/lib/libsoem.a)

target_link_libraries(demo ${SOEM_LIBRARY})
target_link_libraries(slaves ${SOEM_LIBRARY})

# Create the shared library
add_library(kelo_driver SHARED src/EthercatBus.cpp)

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
  demo
  slaves
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
