#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <GL/glew.h>

#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glfw3.h>

#include "shader.h"

enum Dir
{
	NONE,
	FORWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	FORWARD_LEFT,
	FORWARD_RIGHT
};

class Camera
{
public:
	//default camera values
	const float zNEAR = 0.1f;
	const float zFAR = 500.f;
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float FOV = 75.0f;


	glm::vec3 cameraPosition;
	glm::vec3 cameraOffset;

	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	glm::vec3 worldUp;

	float yaw;
	float pitch;
	float rotationSpeed;
	float movementSpeed;
	float fov;
	float znear;
	float zfar;

	int height;
	int width;

	Camera(int newHeight, int newWidth, glm::vec3 position);

	void updateCamera(glm::vec3 position, glm::vec3 forwardDirection, float newYaw, float newPitch);
	void resetCamera(int newHeight, int newWidth, glm::vec3 position);
	void Reshape(int windowWidth, int windowHeight);

	float getYaw();
	float getPitch();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getDirectionVector();

private:
	void updateCameraVectors();
};

#endif