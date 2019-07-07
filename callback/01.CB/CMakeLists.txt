CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CALLBACK)
# Path to `motor` directory for OpenSceneGraph.
SET(MOTOR_DIR ${CMAKE_SOURCE_DIR}/../../../motor)
SET(STAGE_ID "01")
SET(STAGE ${STAGE_ID}.CB)
SET(BINARY_NAME "callback-${STAGE_ID}")
# Create and link executable.
ADD_EXECUTABLE(${BINARY_NAME} callback.cpp)
# Use C++14.
TARGET_COMPILE_OPTIONS(${BINARY_NAME} PUBLIC "-std=c++14")
# Include cross-platform headers.
INCLUDE_DIRECTORIES(${MOTOR_DIR}/../OpenSceneGraph)
INCLUDE_DIRECTORIES(${MOTOR_DIR}/../OpenSceneGraph/include)

# Build OpenSceneGraph for Mac.
IF (APPLE)
    MESSAGE("Build OpenSceneGraph for Mac")
# Build OpenSceneGraph for Web.
ELSEIF(EMSCRIPTEN)
    MESSAGE("Build OpenSceneGraph for Web")
    # Include Web specific headers.
    INCLUDE_DIRECTORIES(${MOTOR_DIR}/motor/OpenSceneGraph/include/web)
    ADD_LIBRARY(
        OpenSceneGraph
        STATIC
        OpenSceneGraph-01.cpp
        OpenSceneGraph-02.cpp
        OpenSceneGraph-03.cpp
        OpenSceneGraph-04.cpp
    )
    TARGET_LINK_LIBRARIES(
        OpenSceneGraph
        # For OpenThreads:
        pthread 
        # For osgViewer:
        EGL
    )
# Build OpenSceneGraph for Linux.
ELSE()
    MESSAGE("Build OpenSceneGraph for Linux")
ENDIF ()

TARGET_LINK_LIBRARIES(
    ${BINARY_NAME}
    OpenSceneGraph
)

# Make Emscripten generate ready-to-open HTML page.
SET(CMAKE_EXECUTABLE_SUFFIX ".html")
# Construct build flags for web.
SET(BUILD_FLAGS "")
# Make compact binary.
LIST(APPEND BUILD_FLAGS "-O3")
# Use SDL2 as OpenGL provider.
LIST(APPEND BUILD_FLAGS "-s USE_SDL=2")
# Disable web assembly to support old (2010+) browsers.
LIST(APPEND BUILD_FLAGS "-s WASM=0")
# Generate single HTML file.
LIST(APPEND BUILD_FLAGS "-s SINGLE_FILE=1")
# Allow undefined symbols.
LIST(APPEND BUILD_FLAGS "-s ERROR_ON_UNDEFINED_SYMBOLS=0")
# Use Bind.
LIST(APPEND BUILD_FLAGS "--bind")
# Convert build flags into a string.
STRING(REPLACE ";" " " BUILD_FLAGS "${BUILD_FLAGS}")
# Use build flags for compilation and linking.
ADD_DEFINITIONS(${BUILD_FLAGS})
SET_TARGET_PROPERTIES(${BINARY_NAME} PROPERTIES LINK_FLAGS ${BUILD_FLAGS})
