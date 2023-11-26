# Project settings
cmake_minimum_required(VERSION 3.5)
project(pinball)


# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)


# Required libraries installed in the system

## OpenGL
set(OpenGL_GL_PREFERENCE GLVND) # Set OpenGL version
find_package(OpenGL REQUIRED)

## GLFW3
find_package(glfw3 3.3 REQUIRED)

## GLEW
find_package(GLEW REQUIRED)

## GLM
find_package(glm REQUIRED)

## Assimp
find_package(assimp REQUIRED)

## OpenAL
find_package(OpenAL REQUIRED)
#find_package(audio REQUIRED)


# Source files
add_executable(
  ${PROJECT_NAME} src/main.cpp
  src/helpers/Mesh.cpp
  src/helpers/Window.cpp
  src/helpers/Shader.cpp
  src/helpers/Camera.cpp
  src/helpers/Model.cpp
  src/helpers/Material.cpp
  src/helpers/Texture.cpp
  src/helpers/Skybox.cpp
  src/helpers/Light.cpp
  src/helpers/DirectionalLight.cpp
  src/helpers/PointLight.cpp
  src/helpers/SpotLight.cpp
  src/components/Inador.cpp
  src/components/Flipper.cpp
  src/components/FlipperKeyController.cpp
  src/components/CameraToggleController.cpp
  src/components/Spring.cpp
  src/components/SpringMouseController.cpp
  src/components/Earth.cpp
  src/components/Perry.cpp
  src/components/LightManager.cpp
  src/components/SkyboxManager.cpp
  src/components/Bouncer.cpp
  src/components/Ball.cpp
  src/components/Bumper.cpp
  src/components/Rocket.cpp
  src/animations/InadorAnimation.cpp
  src/animations/PerryAnimation.cpp
  src/animations/BallAnimation.cpp
  src/animations/BallKeyframeAnimation.cpp
  src/audio/Buffer.cpp
  src/audio/Device.cpp
  src/audio/Source.cpp
  src/audio/SpringAudioController.cpp
  src/audio/EnvironmentAudioController.cpp
  src/audio/Listener.cpp
  src/textures/BangTexture.cpp
)


# Include files
include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
)


# Linked libraries settings
target_link_libraries(${PROJECT_NAME}
  OpenGL::GL
  GLEW
  glfw
  glm::glm
  assimp
  openal
  Xrandr
  Xi
  Xinerama
  Xcursor
  audio
)
