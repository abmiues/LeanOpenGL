#include "Camera.h"



Camera::Camera()
{
}
 void Camera::SetPosition(glm::vec3 position)
{
	 __super::SetPosition(position);
}
 void Camera::SetRotation(glm::vec3 rotation)
 {
	 __super::SetRotation(rotation);
 }
 void Camera::SetScale(glm::vec3 scale)
 {
	 __super::SetScale(scale);
 }


Camera::~Camera()
{
}
