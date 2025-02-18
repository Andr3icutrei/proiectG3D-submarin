#include "SideviewCamera.h"

SideviewCamera::SideviewCamera(glm::vec3 pos, glm::vec3 target, glm::vec3 worldUp, const int width, const int height) :
	m_position{pos},
	m_target{target},
	m_worldUp{worldUp},
	m_fov{ 75.0f },
	m_nearPlane{0.1f},
	m_farPlane{500.f},
	m_aspectRatio{(float)width/(float)height}
{
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}

SideviewCamera& SideviewCamera::operator=(const SideviewCamera& other)
{
    if (this != &other)
	{
        m_position = other.m_position;
        m_target = other.m_target;
        m_worldUp = other.m_worldUp;

        m_projectionMatrix = other.m_projectionMatrix;
        m_width = other.m_width;
        m_height = other.m_height;
    }
    return *this;
}

void SideviewCamera::Reshape(int windowWidth, int windowHeight)
{
	m_width = windowWidth;
	m_height = windowHeight;

	glViewport(0, 0, windowWidth, windowHeight);
}