#include "SubmarineCamera.h"

SubmarineCamera::SubmarineCamera(int newHeight, int newWidth, glm::vec3 position) :
	height(newHeight),
	width(newWidth),
	cameraPosition(position),
	cameraOffset(0.0f, 0.3f, 1.2f),
	worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	yaw(YAW),
	pitch(PITCH),
	rotationSpeed(10000.0f),
	movementSpeed(100.0f),
	fov(FOV),
	znear(zNEAR),
	zfar(zFAR),
	cameraFront(glm::vec3(0.0f, 0.0f, -1.0f))
{
	updateCameraVectors();
}

void SubmarineCamera::updateCamera(glm::vec3 position, glm::vec3 forwardDirection, float newYaw, float newPitch)
{
	cameraPosition = position - forwardDirection * cameraOffset.z + glm::vec3(0.0f, cameraOffset.y, 0.0f);

	yaw = newYaw;
	pitch = newPitch;

	updateCameraVectors();
}

void SubmarineCamera::resetCamera(int newHeight, int newWidth, glm::vec3 position)
{
	height = newHeight;
	width = newWidth;
	cameraPosition = position;
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = YAW;
	pitch = PITCH;
	rotationSpeed = 1.0f;
	movementSpeed = 1.0f;
	fov = FOV;
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	updateCameraVectors();
}

glm::mat4 SubmarineCamera::getViewMatrix() const 
{
	return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

glm::mat4 SubmarineCamera::getProjectionMatrix() const 
{
	glm::mat4 Proj = glm::mat4(1);

	float aspectRatio = ((float)(width)) / height;
	Proj = glm::perspective(glm::radians(fov), aspectRatio, znear, zfar);

	return Proj;
}

glm::vec3 SubmarineCamera::getDirectionVector()
{
	glm::vec3 direction;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	return direction;
}

glm::vec3 SubmarineCamera::getPosition() const
{
	return cameraPosition;
}

void SubmarineCamera::updateCameraVectors()
{
	glm::vec3 direction;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(direction);
	cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

void SubmarineCamera::Reshape(int windowWidth, int windowHeight)
{
	width = windowWidth;
	height = windowHeight;

	// define the viewport transformation
	glViewport(0, 0, windowWidth, windowHeight);
}

float SubmarineCamera::getYaw()
{
	return yaw;
}

float SubmarineCamera::getPitch()
{
	return pitch;
}