cmake_minimum_required(VERSION 3.16)
project(epidemic VERSION 0.1.0)

# to enable the support for tests 
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Require the use of C++17, without non-standard compiler extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Require SFML, version 2.5
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Enable warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# Enable address sanitizer and undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

# Add executable epidemic_graph to the build directory to rappresent the graph of the epidemic 
add_executable(epidemic_graph main_graph.cpp epidemic/epidemic.cpp graph/draw.cpp graph/curve/curve.cpp graph/text/text.cpp graph/grid/grid.cpp graph/key/key.cpp)
# Add executable cellular_automaton to the build directory to rappresent the cellular automaton of the epidemic 
add_executable(cellular_automaton cellular_automaton.cpp epidemic/epidemic.cpp simulation/simulation.cpp )
# Adding SFML library required by epidemic_graph and cellular_automaton
target_link_libraries(epidemic_graph PRIVATE sfml-graphics)
target_link_libraries(cellular_automaton PRIVATE sfml-graphics)

# Activate if testing is enabled
if (BUILD_TESTING)

  # Add executable epidemic.t for testing the Epidemic class
  add_executable(epidemic.t epidemic/epidemic.test.cpp epidemic/epidemic.cpp)
  add_test(NAME epidemic.t COMMAND epidemic.t)
  # Add executable graph.t for testing the Draw and Text classes
  add_executable(graph.t graph/graph.test.cpp epidemic/epidemic.cpp graph/draw.cpp graph/curve/curve.cpp graph/text/text.cpp graph/grid/grid.cpp graph/key/key.cpp)
  add_test(NAME graph.t COMMAND graph.t)
  # Add executable simulation.t for testing the Simulation class
  add_executable(simulation.t epidemic/epidemic.cpp simulation/simulation.cpp simulation/simulation.test.cpp)
  add_test(NAME simulation.t COMMAND simulation.t)
  # Adding SFML library required by graph.t and simulation.t
  target_link_libraries(graph.t PRIVATE sfml-graphics)
  target_link_libraries(simulation.t PRIVATE sfml-graphics)

endif()

# Automatize code formatting using clang-format
find_program(CLANG_FORMAT_EXECUTABLE clang-format)
if (CLANG_FORMAT_EXECUTABLE)
    
  file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)
  add_custom_target(format COMMAND ${CLANG_FORMAT_EXECUTABLE} -i ${ALL_SOURCE_FILES} COMMENT "Formatting code using clang-format")

endif()
