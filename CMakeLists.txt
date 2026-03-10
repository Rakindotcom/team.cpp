cmake_minimum_required(VERSION 3.10)
project(GarmentFactory)

set(CMAKE_CXX_STANDARD 17)

# --- Raylib Integration ---
# Try to find installed package
find_package(raylib 4.0 QUIET)

# If not found, use FetchContent or expect user to provide paths
if (NOT raylib_FOUND)
    message(STATUS "Raylib package not found standardly. Checking headers...")
    # This is a simplified fallback. Ideally we use FetchContent.
endif()

# Define Sources
set(SOURCES_GUI
    src/GuiApp.cpp
    src/GuiComponents.cpp
)

set(SOURCES_CONSOLE
    src/main.cpp
)

# --- Executables ---

# GUI Version
add_executable(GarmentFactoryGUI ${SOURCES_GUI})
if(raylib_FOUND)
    target_link_libraries(GarmentFactoryGUI PRIVATE raylib)
else()
    # Link explicitly if passed via command line or generic system link
    target_link_libraries(GarmentFactoryGUI PRIVATE raylib gdi32 winmm) 
endif()

# Console Version
add_executable(GarmentFactoryConsole ${SOURCES_CONSOLE})

# Include Directories
target_include_directories(GarmentFactoryGUI PRIVATE src)
target_include_directories(GarmentFactoryConsole PRIVATE src)
