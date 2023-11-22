#include "../include/Camera.h"

#include <iostream>
#ifdef WIN32
#include <ext/matrix_projection.hpp>
#else
#include <glm/ext/matrix_projection.hpp>
#endif

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::normalize(glm::vec3(-0.0f, -1.0f, 0.0f));

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;
  glm::vec3 front_static_y = glm::normalize(glm::vec3(front.x, 0.0, front.z));
  glm::vec3 right_static_y = glm::normalize(glm::vec3(right.x, 0.0, right.z));

	if (keys[GLFW_KEY_W])
	{
		position += front_static_y * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front_static_y * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right_static_y * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right_static_y * velocity;
	}
}

void Camera::setDirection(float yaw, float pitch)
{
	this->yaw = yaw;
	this->pitch = pitch;
  update();
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

void Camera::setCameraPosition(float x, float y, float z)
{
  position.x = x;
  position.y = y;
  position.z = z;
}

glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera() {}
