#include"shader.h"
#include"stb_image.h"
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		printf("��ɫ���ļ�����ʧ��\n");
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	ComplileShaderAndLink(vShaderCode, fShaderCode);
}
void Shader::ComplileShaderAndLink(const char* vShaderCode, const char* fShaderCode)
{
	int success;//������ɫ��������
	char infoLog[512];//������ɫ��������־
	unsigned int vertex, fragment;//���嶥����ɫ��

	vertex = glCreateShader(GL_VERTEX_SHADER);//����������ɫ��
	glShaderSource(vertex, 1, &vShaderCode, NULL);//���ض�����ɫ������
	glCompileShader(vertex);//���붥����ɫ������

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);//�����ɫ��������
	if (!success)//�������ʧ��
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);//��ȡ������Ϣ
		printf("������ɫ���������%s\n", infoLog);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);//�����ɫ��������
	if (!success)//�������ʧ��
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);//��ȡ������Ϣ
		printf("Ƭ����ɫ���������%s\n", infoLog);
	}

	ID= glCreateProgram();//������ɫ������,������ɫ�������ID
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);//������ɫ��

	glGetProgramiv(ID, GL_LINK_STATUS, &success);//�����ɫ�����ӽ��
	if (!success)//�������ʧ��
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);//��ȡ������Ϣ
		printf("��ɫ�����Ӵ���%s\n", infoLog);
	}
	glDeleteShader(vertex);//�����ɾ����ɫ������
	glDeleteShader(fragment);
}
void Shader::use()
{
	glUseProgram(ID);
}
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat4(const std::string &name, float v1, float v2, float v3, float v4) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), v1,v2,v3,v4);
}
void Shader::SetMatrix4(const std::string &name,glm::mat4 trans) const
{
	// ����λ��ֵ�����ݼ��������Ƿ�Ծ�������û����������У�
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
}
//��ͼ������ͼid�����֧��16����ͼ������ͼ�Ƿ���alphaͨ��
void Shader::setTexture(const std::string &path,int textureID,bool alpha) 
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + textureID);//����ָ������Ԫ
	glBindTexture(GL_TEXTURE_2D, texture);//������Ԫ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//���û��Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//����������ˣ�GL_LINEARƽ����GL_NEAREST ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	int GLCOLOR = alpha ? GL_RGBA : GL_RGB;
	if (data)
	{
		textureUnit[textureID] = texture;
		glTexImage2D(GL_TEXTURE_2D, 0, GLCOLOR, width, height, 0, GLCOLOR, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		printf("��ͼ����ʧ��\n");
	stbi_image_free(data);
}
