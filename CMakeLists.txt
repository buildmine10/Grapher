cmake_minimum_required(VERSION 3.20)
project(Grapher)

set(CMAKE_CXX_STANDARD 14)


find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_directories(${OPENGL_LIBRARIES})

find_package(GLUT REQUIRED VERBOSE)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARIES})


find_package(GLEW REQUIRED)
#message(${GLEW_FOUND})
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARIES})



add_executable(Grapher main.cpp Pipelines/Pipeline.cpp Pipelines/Pipeline.h Math/Matrix4.cpp Math/Matrix4.h Math/TransformationMatrix.cpp Math/TransformationMatrix.h Math/Vector3.cpp Math/Vector3.h Pipelines/MeshPipeline.cpp Pipelines/MeshPipeline.h Renderables/Mesh.cpp Renderables/Mesh.h Plots/Surface.cpp Plots/Surface.h Camera.cpp Camera.h Renderables/Line.cpp Renderables/Line.h Pipelines/LinePipeline.cpp Pipelines/LinePipeline.h Plots/Curve.cpp Plots/Curve.h Renderables/Volume.cpp Renderables/Volume.h Pipelines/VolumePipeline.cpp Pipelines/VolumePipeline.h Plots/ColorField.cpp Plots/ColorField.h Plots/IsoSurface.cpp Plots/IsoSurface.h)
target_link_libraries(Grapher opengl32)
target_link_libraries(Grapher ${GLUT_LIBRARIES})
target_link_libraries(Grapher ${GLEW_LIBRARIES})
