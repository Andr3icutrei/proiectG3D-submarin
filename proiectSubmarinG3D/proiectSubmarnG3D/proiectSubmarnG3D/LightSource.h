#pragma once
#include "Model.h"
#include "glm.hpp"
#include "Shader.h"
#include "IObject.h"

class LightSource : public IObject
{
private:
	Model m_model;
	glm::mat4 m_mat;
	std::string m_path;
	float m_rotateAngle;
	float m_rotateSpeed;
	glm::vec3 m_position;
	glm::vec3 m_scale;
public:
	LightSource(std::string& fileName,Shader& Shader,glm::vec3 scale);

	void rotate(double deltaTime, Shader& Shader, const glm::mat4& viewMatrix);

	void appear(Shader& Shader);

	void draw(Shader& shader);

	void SetModelMatrix(glm::mat4 modelMatrix) override;

	glm::mat4& GetModelMatrix() override;

	void SetPosition(glm::vec3 pos) { m_position = pos; }

	Model& getModel(){return m_model;}

	void setModel(const Model& model){m_model = model;}

	glm::mat4& getModelMatrix(){return m_mat;}

	void setModelMatrix(const glm::mat4& modelMatrix){m_mat = modelMatrix;}

	std::string getPath() const{return m_path;}

	void setPath(const std::string& path){m_path = path;}

	float getRotateAngle() const{return m_rotateAngle;}

	void setRotateAngle(float rotateAngle){m_rotateAngle = rotateAngle;}

	float getRotateSpeed() const{return m_rotateSpeed;}

	void setRotateSpeed(float rotateSpeed){m_rotateSpeed = rotateSpeed;}

	glm::vec3 getPosition() const{return m_position;}

	void setPosition(const glm::vec3& position){	m_position = position;}

	glm::vec3 getScale() const{	return m_scale;}

	void setScale(const glm::vec3& scale){	m_scale = scale;}

};
