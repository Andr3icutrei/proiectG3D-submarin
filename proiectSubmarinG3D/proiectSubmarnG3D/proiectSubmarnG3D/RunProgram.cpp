﻿#include "RunProgram.h"

RunProgram::RunProgram() {
}

RunProgram* RunProgram::getInstance()
{
	if (instance == nullptr) 
	{
		instance = new RunProgram();
	}
	return instance;
}

void RunProgram::run()
{
	initializeGL();
	initializeCameras();
	initializePaths();
	generateShadowMapTexture();
	createLightSource();
	createSubmarine();
	createWater();
	createFishes();
	createSkybox();
	render();
}

void RunProgram::initializeCameras()
{
	m_submarinePosition = glm::vec3(0.0, 0.0, 3.0);
	m_submarineCamera =std::make_shared<SubmarineCamera>(m_SCR_HEIGHT, m_SCR_WIDTH,m_submarinePosition);

	m_sideCameraPosition = glm::vec3(9.0f, 3.0f, -2.0f);
	m_sideCameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	m_sideCameraWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	m_sideCamera =std::make_shared<SideviewCamera>(m_sideCameraPosition,m_sideCameraTarget, m_sideCameraWorldUp,
		m_SCR_WIDTH, m_SCR_HEIGHT);

	m_camera = m_submarineCamera;
}

void RunProgram::render()
{
	while (!glfwWindowShouldClose(window)) {
		glm::vec3 lightDir=  glm::normalize(-m_lightSource->getPosition());
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		generateShadowMap();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);

		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(37.0f, 15.0f, 37.0f)); // Scale with a smaller value for Y
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 7.0f, 0.0f));
		glm::mat4 modelMatrix = translateMatrix * scaleMatrix;
		m_skyboxShader->use();
		m_skyboxShader->SetVec3("lightColor", m_lightSource->getLightColor());
		m_skyboxShader->SetVec3("lightDir", lightDir);
		m_skyboxShader->setMat4("view", m_camera->getViewMatrix());
		m_skyboxShader->setMat4("projection",m_camera->getProjectionMatrix());
		m_skyboxShader->setMat4("model", modelMatrix);
		m_skybox->draw(*m_skyboxShader);

		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		m_lightSourceShader->use();
		m_lightSourceShader->setFloat("shininess", 0.8f);
		m_lightSourceShader->setMat4("model", m_lightSource->getModelMatrix());
		m_lightSourceShader->setMat4("view", m_camera->getViewMatrix());
		m_lightSourceShader->setMat4("projection", m_camera->getProjectionMatrix());
		m_lightSourceShader->SetVec3("lightColor", m_lightSource->getLightColor());
		m_lightSourceShader->setInt("texture_diffuse1", 0);
		m_lightSource->rotate(deltaTime, m_lightSourceShader, m_camera->getViewMatrix());
		m_lightSource->draw(m_lightSourceShader);

		m_submarineShader->use();
		m_submarineShader->SetVec3("lightDir", lightDir);
		m_submarineShader->SetVec3("lightColor", m_lightSource->getLightColor());
		m_submarineShader->SetVec3("viewPos", m_camera->getPosition()); 
		m_submarineShader->setMat4("projection", m_camera->getProjectionMatrix());
		m_submarineShader->setMat4("view", m_camera->getViewMatrix());
		m_submarineShader->setMat4("model", m_submarine->getModel());
		m_submarineShader->setInt("texture_diffuse1", 0);
		// Use the shadow map in the main rendering pass
		glActiveTexture(GL_TEXTURE1);  // Use texture unit 1 for shadow map
		glBindTexture(GL_TEXTURE_2D, m_shadowMap); // Bind the shadow map texture
		m_submarineShader->setInt("shadowMap", 1); // Tell the shader to use texture unit 1 for the shadow map
		m_submarine->draw(*m_submarineShader);

		for (auto& fish : m_fishes)
		{
			fish->update(deltaTime); 
			fish->draw(m_submarineShader);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		m_waterShader->use();
		m_waterShader->SetVec3("lightDir", lightDir);
		m_waterShader->setFloat("time", glfwGetTime());
		m_waterShader->SetVec3("lightColor", m_lightSource->getLightColor());
		m_waterShader->setMat4("view", m_camera->getViewMatrix());
		m_waterShader->setMat4("projection", m_camera->getProjectionMatrix());
		m_waterShader->SetVec3("lightColor", m_lightSource->getLightColor());
		m_waterShader->setMat4("lightSpaceMatrix", m_lightSpaceMatrix); // Pass the light space matrix
		m_waterShader->setFloat("nearPlane", 1.f);  // Pass near plane
		m_waterShader->setFloat("farPlane", 50.f);
		m_waterShader->setInt("shadowMap", 2);
		glActiveTexture(GL_TEXTURE2);  // Use texture unit 1 for shadow map
		glBindTexture(GL_TEXTURE_2D, m_shadowMap); // Bind the shadow map texture

		m_water->draw(*m_waterShader);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources
	glfwTerminate();
}

float RunProgram::generateRandom(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Define a uniform distribution for integers
	std::uniform_int_distribution<> uniformDist(min, max);

	float rand = uniformDist(gen);
	return rand;
}

void RunProgram::generateShadowMap()
{
	m_shadowShader->use();

	glViewport(0, 0, 2048,2048);
	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	// Compute light space matrix
	// Step 1: Set the position of the light
	glm::vec3 lightPos = glm::normalize(glm::vec3(-6.0f, 2.0f, -6.0f));

	// Step 2: Define the target point for the light (center of the scene)
	glm::vec3 lightTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Light points at the origin

	// Step 3: Compute the light direction (from light position to target)
	glm::vec3 lightDir = glm::normalize(lightPos - lightTarget); // Direction from light to the target

	// Step 4: Set up orthogonal projection (for directional light)
	glm::mat4 lightProjection = glm::ortho(-100.f, 100.0f, -100.0f, 100.0f, 0.1f, 500.0f);

	// Step 5: Create the light view matrix using the light position and direction
	glm::mat4 lightView = glm::lookAt(lightPos, lightTarget, glm::vec3(0.0f, 1.0f, 0.0f));

	m_lightSpaceMatrix = lightProjection * lightView;
	m_shadowShader->setMat4("lightSpaceMatrix", m_lightSpaceMatrix);

	// Render scene objects to depth map
	m_shadowShader->setMat4("model", m_submarine->getModelMatrix());
	m_submarine->draw(*m_shadowShader);

	for (auto& fish : m_fishes) {
		m_shadowShader->setMat4("model", fish->getModelMatrix());
		fish->draw(m_shadowShader);
	}

	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_water->getPosition());
	m_shadowShader->setMat4("model",model);
	m_water->draw(*m_shadowShader);

	// Unbind framebuffer and reset viewport
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_SCR_WIDTH, m_SCR_HEIGHT);  // Reset to screen dimensions
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDepthFunc(GL_LEQUAL);
}


void RunProgram::generateShadowMapTexture()
{
	// Create and configure the FBO
	glGenFramebuffers(1, &m_shadowFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);

	// Create the shadow map texture
	glGenTextures(1, &m_shadowMap);
	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 2048, 2048, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// Attach the texture to the FBO as a depth attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap, 0);

	// Disable color output for the shadow FBO
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Check if the framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Shadow map framebuffer is not complete!" << std::endl;
	}

	// Unbind the framebuffer
	glViewport(0, 0, m_SCR_WIDTH,m_SCR_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	RunProgram* instance = RunProgram::getInstance();
	instance->getCamera()->Reshape(width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	RunProgram* instance = RunProgram::getInstance();
	float deltaTime = instance->getDeltaTime();
	std::shared_ptr<Submarine> submarine = instance->getSubmarine();
	std::shared_ptr<Water> water = instance->getWater();

	bool surface = false;

	if (submarine->getPosition().y >= 0.0f)
		surface = true;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		RunProgram::getInstance()->getSubmarine()->updateSubmarine(Dir::LEFT, deltaTime, RunProgram::getInstance()->getSubmarineShader(), surface);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::RIGHT, deltaTime, RunProgram::getInstance()->getSubmarineShader(), surface);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::UP, deltaTime, RunProgram::getInstance()->getSubmarineShader(), surface);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::DOWN, deltaTime, RunProgram::getInstance()->getSubmarineShader(), surface);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::FORWARD, deltaTime, RunProgram::getInstance()->getSubmarineShader(), surface);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	std::shared_ptr<ICamera> camera = instance->getCamera();
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)//O - camera submarinului
	{
		instance->setCamera( instance->getSubmarineCamera());
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)//P- side view camera
	{
		instance->setCamera(instance->getSideCamera());
	}

	if (std::shared_ptr<SubmarineCamera> currentCamera = std::dynamic_pointer_cast<SubmarineCamera>(camera))
	{
		currentCamera->updateCamera(submarine->getPosition(), submarine->getForwardDirection(), submarine->getYaw(), submarine->getPitch());
	}
}

void RunProgram::initializeGL()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(m_SCR_WIDTH, m_SCR_HEIGHT, "Submarine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RunProgram::initializePaths()
{
	wchar_t buffer[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, buffer);

	std::wstring executablePath(buffer);
	std::wstring wscurrentPath = executablePath.substr(0, executablePath.find_last_of(L"\\/"));

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	m_currentPath = converter.to_bytes(wscurrentPath);

	m_submarineShader = std::make_unique<Shader>((m_currentPath + "\\Shaders\\Object.vs").c_str(), (m_currentPath + "\\Shaders\\Object.fs").c_str());
	m_lightSourceShader = std::make_unique<Shader>((m_currentPath + "\\Shaders\\LightSource.vs").c_str(), (m_currentPath + "\\Shaders\\LightSource.fs").c_str());
	m_waterShader = std::make_unique<Shader>((m_currentPath + "\\Shaders\\Water.vs").c_str(), (m_currentPath + "\\Shaders\\Water.fs").c_str());
	m_skyboxShader = std::make_unique<Shader>((m_currentPath + "\\Shaders\\Skybox.vs").c_str(), (m_currentPath + "\\Shaders\\Skybox.fs").c_str());

	m_shadowShader = std::make_unique<Shader>((m_currentPath + "\\Shaders\\Shadow.vs").c_str(), (m_currentPath + "\\Shaders\\Shadow.fs").c_str());
}

void RunProgram::createWater()
{
	std::string strWaterJpgPath = m_currentPath + "\\x64\\Debug\\water.jpg";
	const char* waterPath{ strWaterJpgPath.c_str() };

	std::string strSandJpgPath = m_currentPath + "\\x64\\Debug\\sand.jpg";
	const char* sandPath{ strSandJpgPath.c_str() };

	m_water = std::make_shared<Water>(glm::vec3(0.0f, -4.0f, 3.0f), glm::vec3(80.0f, 8.0f, 80.0f), waterPath, sandPath);
}

void RunProgram::createSubmarine()
{
	std::string submarineFileName = (m_currentPath + "\\Models\\Submarin\\submarin.obj");
	m_submarine = std::make_shared<Submarine>(submarineFileName);
}

void RunProgram::createLightSource()
{
	std::string lightSourcePath = m_currentPath;

	std::time_t currentTime = std::time(nullptr);
	std::tm* localTime = std::localtime(&currentTime);
	int hour = localTime->tm_hour;

	glm::vec3 lightSourceScale=glm::vec3(1.0f);
	glm::vec3 lightColor;
	std::string mtlPath;
	if (hour >= 6 && hour <= 18)
	{
		lightColor = (glm::vec3(1.0f, 0.95f, 1.f));//sun light color
		lightSourcePath += "\\Models\\Sun\\sun.obj";
		lightSourceScale = (glm::vec3(5.0f, 5.0f, 1.0f));
	}
	else
	{
		lightColor=(glm::vec3(0.6f, 0.6f, 1.0f));//moon light color
		lightSourcePath += "\\Models\\Moon\\Moon.obj";
		lightSourceScale=(glm::vec3(0.2f, 0.2f, 0.2f));
	}

	m_lightSource=std::make_shared<LightSource>(lightSourcePath,m_lightSourceShader, lightSourceScale);
	m_lightSource->setPosition(glm::vec3(-3.0f, 4.0f, -8.0f));
	m_lightSource->setLightColor(lightColor);
}

void RunProgram::createSkybox()
{
	std::string skyPath = m_currentPath + "\\x64\\Debug\\sky.jpg";
	m_skybox = std::make_shared<Skybox>(skyPath.c_str());
}

void RunProgram::createFishes()
{
    std::string fishPath = m_currentPath + "\\Models\\Fish\\fish.obj";

    const int FishCount = 7;
    std::vector<float> linearFishSpeeds(FishCount, 6.f);
    std::vector<float> linearFishHeights(FishCount);
    std::vector<float> movementLimitsX(FishCount); // Radius on X axis (ellipse)
    std::vector<float> movementLimitsZ(FishCount); // Radius on Z axis (ellipse)
	std::vector<float> angles(FishCount);

    const int waterSurface = m_water->getSurface(); // water max
    const int waterBottom = m_water->getBottom(); // water min
    float maxRadius = m_water->getDistanceFromCenter(); // max radius to spawn
    float startPositionToSpawn = 0.f;

    for (int i = 0; i < FishCount; ++i)
    {
		angles[i] = generateRandom(0.f, 360.f);
        movementLimitsX[i] = generateRandom(1.0f, maxRadius); 
        movementLimitsZ[i] = generateRandom(1.0f, maxRadius);
    }

	linearFishHeights[0]=-6.f;
	for (int i = 1; i < FishCount; ++i)
	{
		if (i % 2)
			linearFishHeights[i] = -7.f;
		else
			linearFishHeights[i] = -6.f;
	}

    for (int i = 0; i < FishCount; ++i)
    {
        float randomX = generateRandom(-movementLimitsX[i], movementLimitsX[i]);
        float randomZ = generateRandom(-movementLimitsZ[i], movementLimitsZ[i]);

        std::cout << "Fish " << i << " position: X=" << randomX << ", Y=" << linearFishHeights[i] << ", Z=" << randomZ << '\n';

        glm::vec3 startPosition(randomX, linearFishHeights[i], randomZ);
        glm::vec3 scale(22.f);
		
        m_fishes.push_back(std::make_shared<Fish>(fishPath, startPosition, scale, linearFishSpeeds[i], movementLimitsX[i], movementLimitsZ[i],angles[i]));
    }
}

