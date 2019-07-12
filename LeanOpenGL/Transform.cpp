#include "Transform.h"



Transform::Transform()
{
}
void Transform::SetPosition(glm::vec3 position)
{
	_position = position;
}

void Transform::SetRotation(glm::vec3 rotation)
{
	_rotation = rotation;
}

void Transform::SetScale(glm::vec3 scale)
{
	_scale = scale;
}

glm::vec3 Transform::Position()
{
	return _position;
}

glm::vec3 Transform::Rotation()
{
	return _rotation;
}

glm::vec3 Transform::Scale()
{
	return _scale;
}


Transform::~Transform()
{
}
