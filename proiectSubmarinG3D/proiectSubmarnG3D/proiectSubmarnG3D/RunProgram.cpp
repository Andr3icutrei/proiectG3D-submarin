#include "RunProgram.h"

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
	createLightSource();
	createSubmarine();
	createWater();
	render();
}

void RunProgram::initializeCameras()
{
	m_submarinePosition = glm::vec3(0.0, 0.0, 3.0);
	submarineCamera=std::make_shared<SubmarineCamera>(m_SCR_HEIGHT, m_SCR_WIDTH,m_submarinePosition);

	m_sideCameraPosition = glm::vec3(7.0f, 3.0f, 0.0f);
	m_sideCameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	m_sideCameraWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	sideCamera=std::make_shared<SideviewCamera>(m_sideCameraPosition,m_sideCameraTarget, m_sideCameraWorldUp,
		m_SCR_WIDTH, m_SCR_HEIGHT);

	camera =submarineCamera;
}

void RunProgram::render()
{
	while (!glfwWindowShouldClose(window)) {
		// per-frame time logic
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);

		lightingWithTextureShader->use();
		lightingWithTextureShader->SetVec3("objectColor", 0.5f, 1.0f, 0.31f);
		lightingWithTextureShader->SetVec3("lightColor", lightSource->getLightColor());

		lightingWithTextureShader->SetVec3("viewPos", camera->getPosition());
		lightingWithTextureShader->setInt("texture_diffuse1", 0);

		lightSource->rotate(deltaTime, lightingWithTextureShader, camera->getViewMatrix());
		lightSource->draw(lightingWithTextureShader);

		if (std::shared_ptr<SubmarineCamera> subCam = std::dynamic_pointer_cast<SubmarineCamera>(camera))
		{
			lightingWithTextureShader->setMat4("projection", subCam->getProjectionMatrix());
			lightingWithTextureShader->setMat4("view", subCam->getViewMatrix());
			lightingWithTextureShader->setMat4("model", submarine->getModel());
		}
		else if (std::shared_ptr<SideviewCamera> sideCam = std::dynamic_pointer_cast<SideviewCamera>(camera))
		{
			glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float)m_SCR_WIDTH / m_SCR_HEIGHT, 0.1f, 100.0f);
			lightingWithTextureShader->setMat4("projection", projection);
			lightingWithTextureShader->setMat4("view", sideCam->getViewMatrix());
			lightingWithTextureShader->setMat4("model", submarine->getModel());
		}

		//submarine.draw();
		submarine->draw();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		waterShader->use();
		waterShader->setMat4("view", camera->getViewMatrix());
		waterShader->setMat4("projection", camera->getProjectionMatrix());
		waterShader->SetVec3("lightColor", lightSource->getLightColor());
		water->draw(waterShader);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources
	glfwTerminate();
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

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		RunProgram::getInstance()->getSubmarine()->updateSubmarine(Dir::LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::UP, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::DOWN, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::FORWARD_LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::FORWARD_RIGHT, deltaTime);

	std::shared_ptr<ICamera> camera = instance->getCamera();
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)//O - camera submarinului
	{
		if (std::shared_ptr<SideviewCamera> currentCamera = std::dynamic_pointer_cast<SideviewCamera>(camera))
		{
			instance->setCamera( instance->getSubmarineCamera());
		}
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)//P- side view camera
	{
		if (std::shared_ptr<SubmarineCamera> currentCamera = std::dynamic_pointer_cast<SubmarineCamera>(camera))
		{
			instance->setCamera(instance->getSideCamera());
		}
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

	lightingShader= std::make_shared<Shader>((m_currentPath + "\\Shaders\\PhongLight.vs").c_str(), (m_currentPath + "\\Shaders\\PhongLight.fs").c_str());

	lightingWithTextureShader= std::make_shared<Shader>((m_currentPath + "\\Shaders\\PhongLightWithTexture.vs").c_str(), (m_currentPath + "\\Shaders\\PhongLightWithTexture.fs").c_str());

	lampShader= std::make_shared<Shader>((m_currentPath + "\\Shaders\\Lamp.vs").c_str(), (m_currentPath + "\\Shaders\\Lamp.fs").c_str());

	waterShader= std::make_shared<Shader>((m_currentPath + "\\Shaders\\Water.vs").c_str(), (m_currentPath + "\\Shaders\\Water.fs").c_str());;

}

void RunProgram::createWater()
{
	std::string strWaterJpgPath = m_currentPath + "\\x64\\Debug\\water.jpg";
	const char* waterPath{ strWaterJpgPath.c_str() };

	std::string strSandJpgPath = m_currentPath + "\\x64\\Debug\\sand.jpg";
	const char* sandPath{ strSandJpgPath.c_str() };

	water = std::make_shared<Water>(glm::vec3(0.0f, -4.0f, 3.0f), glm::vec3(50.0f, 8.0f, 50.0f), waterPath, sandPath);
}

void RunProgram::createSubmarine()
{
	std::string submarineFileName = (m_currentPath + "\\Models\\Submarin\\submarin.obj");
	submarine = std::make_shared<Submarine>(submarineFileName, lightingWithTextureShader);
}

void RunProgram::createLightSource()
{
	std::string lightSourcePath = m_currentPath;

	std::time_t currentTime = std::time(nullptr);
	std::tm* localTime = std::localtime(&currentTime);
	int hour = localTime->tm_hour;

	glm::vec3 lightSourceScale=glm::vec3(1.0f);
	glm::vec3 lightColor;
	if (hour >= 6 && hour <= 18)
	{
		lightColor=(glm::vec3(1.0f, 0.95f, 0.6f));//sun light color
		lightSourcePath += "\\Models\\Sun\\sun.obj";
		lightSourceScale=(glm::vec3(5.0f, 5.0f, 1.0f));
	}
	else
	{
		lightColor=( glm::vec3(0.7f, 0.8f, 1.0f));//moon light color
		lightSourcePath += "\\Models\\Moon\\Moon.obj";
		lightSourceScale=(glm::vec3(0.2f, 0.2f, 0.2f));
	}
	lightSource=std::make_shared<LightSource>(lightSourcePath, lightingWithTextureShader, lightSourceScale);
	lightSource->setPosition(glm::vec3(-3.0f, 3.0f, -8.0f));
	lightSource->setLightColor(lightColor);
}