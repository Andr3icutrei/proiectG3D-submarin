#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <locale>
#include <codecvt>

#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h> 

#include <GL/glew.h>

#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glfw3.h>

#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include "Shader.h"
#include "Model.h"
#include "FlyingCube.h"
#include "LightSource.h"
#include "Submarine.h"
#include "SubmarineCamera.h"
#include "SideviewCamera.h"
#include "Water.h"

class RunProgram
{
private:
    static RunProgram* instance;

    RunProgram();
    RunProgram(const RunProgram&) = delete;
    RunProgram& operator=(const RunProgram&) = delete;


    const unsigned int m_SCR_WIDTH=1200;
    const unsigned int m_SCR_HEIGHT=800;

    GLFWwindow* window;

    glm::vec3 m_submarinePosition;

    glm::vec3 m_sideCameraPosition;
    glm::vec3 m_sideCameraTarget;
    glm::vec3 m_sideCameraWorldUp;

    GLuint ProjMatrixLocation, ViewMatrixLocation, WorldMatrixLocation;

    std::string m_currentPath;

    std::shared_ptr<Submarine> submarine;
    std::shared_ptr<SubmarineCamera> submarineCamera;
    std::shared_ptr<SideviewCamera> sideCamera;
    std::shared_ptr<ICamera> camera;
    std::shared_ptr<Water> water;
    std::shared_ptr<LightSource> lightSource;

    std::shared_ptr<Shader> lightingShader;

    std::shared_ptr<Shader> lightingWithTextureShader;

    std::shared_ptr < Shader> lampShader;

    std::shared_ptr < Shader> waterShader;

    double deltaTime = 0.0f;
    double lastFrame = 0.0f;

    void initializeGL();
    void initializePaths();

    void createWater();
    void createSubmarine();
    void createLightSource();
    void initializeCameras();
    void render();
public:
    // Static method to get the instance of the class
    static RunProgram* getInstance();

    void run();


    //getters
    unsigned int getSCRWidth() const { return m_SCR_WIDTH; }
    unsigned int getSCRHeight() const { return m_SCR_HEIGHT; }

    GLuint getProjMatrixLocation() const { return ProjMatrixLocation; }
    GLuint getViewMatrixLocation() const { return ViewMatrixLocation; }
    GLuint getWorldMatrixLocation() const { return WorldMatrixLocation; }

    std::shared_ptr<Submarine> getSubmarine() { return submarine; }
    std::shared_ptr<SubmarineCamera> getSubmarineCamera() { return submarineCamera; }
    std::shared_ptr<SideviewCamera> getSideCamera() { return sideCamera; }
    std::shared_ptr<ICamera> getCamera() const { return camera; }

    double getDeltaTime() const { return deltaTime; }
    double getLastFrame() const { return lastFrame; }

    // Setters
    void setProjMatrixLocation(GLuint value) { ProjMatrixLocation = value; }
    void setViewMatrixLocation(GLuint value) { ViewMatrixLocation = value; }
    void setWorldMatrixLocation(GLuint value) { WorldMatrixLocation = value; }

    void setSubmarine(std::shared_ptr<Submarine> sub) { submarine = std::move(sub); }
    void setSubmarineCamera(std::shared_ptr<SubmarineCamera> cam) { submarineCamera = cam; }
    void setSideCamera(std::shared_ptr<SideviewCamera> cam) { sideCamera = cam; }
    void setCamera(std::shared_ptr<ICamera> cam) { camera = std::move(cam); }

    void setDeltaTime(double time) { deltaTime = time; }
    void setLastFrame(double time) { lastFrame = time; }
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);