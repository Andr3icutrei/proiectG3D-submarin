#pragma once
#include "Model.h"
#include "glm.hpp"
#include "Shader.h"
#include "IObject.h"
#include "stb_image.h"
#include <string>
#include "memory"

class Water {
private:
    unsigned int VAO, VBO, EBO;
    unsigned int textureID;// Water texture
    unsigned int sandTextureID;   // Sand texture for the bottom
    glm::vec3 position;
    glm::vec3 scale;

    float distanceFromCenter;

    void setupWater();
    void loadTexture(const char* waterTexturePath, const char* sandTexturePath);

public:
    Water(const glm::vec3& position, const glm::vec3& scale, const char* texturePath, const char* sandTexturePath);
    ~Water();

    glm::vec3 getPosition();
    glm::vec3 getScale();

    void draw(Shader& shader);
    float getSurface();
    float getBottom();
    float getDistanceFromCenter();
};

