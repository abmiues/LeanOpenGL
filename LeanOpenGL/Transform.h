#pragma once 
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
class Transform
{

protected:
	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;
public:
	Transform();
	~Transform();
	virtual void SetPosition(glm::vec3 position);
	virtual void SetRotation(glm::vec3 rotation);
	virtual void SetScale(glm::vec3 scale);
	virtual glm::vec3 Position();
	virtual glm::vec3 Rotation();
	virtual glm::vec3 Scale();
};

