cmake_minimum_required(VERSION 3.28)

project(Lead)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(../vcpkg/scripts/buildsystems/vcpkg.cmake)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(LEAD_FILES 
    # Headers
    include/lead/boundingbox.h
    include/lead/camera.h
    include/lead/color.h
    include/lead/common.h
    include/lead/euclidean.h
    include/lead/integrator.h
    include/lead/leadexception.h
    include/lead/object.h
    include/lead/parser.h
    include/lead/proplist.h
    include/lead/render.h
    include/lead/sampler.h
    include/lead/scene.h
    include/lead/shape.h

    #Files
    src/main.cpp
    
    src/camera.cpp
    src/common.cpp
    src/direct.cpp
    src/object.cpp
    src/scene.cpp
    src/sphere.cpp
    src/independent.cpp
)

find_package(OpenVDB CONFIG REQUIRED)
find_package(OpenEXR CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_path(RAPIDXML_INCLUDE_DIRS "rapidxml/rapidxml.hpp")

add_executable(Lead ${LEAD_FILES})

target_link_libraries(Lead PRIVATE OpenVDB::openvdb OpenEXR::OpenEXR glm::glm)
target_include_directories(Lead PRIVATE ${CMAKE_SOURCE_DIR}/include ${RAPIDXML_INCLUDE_DIRS})
