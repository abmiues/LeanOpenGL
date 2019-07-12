#ifndef SHADER_H
#define SHADER_H
#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
class Shader {
public:
	unsigned int ID;
	unsigned int textureUnit[16];//opengl至少支持16个纹理单元
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setFloat4(const std::string &name, float v1, float v2, float v3, float v4) const;
	void setTexture(const std::string &path, int textureID, bool alpha) ;
	void SetMatrix4(const std::string &name, glm::mat4 trans) const;
	private:
		void ComplileShaderAndLink(const char* vShaderCode, const char* fShaderCode);
};
#endif // ! SHADER_H