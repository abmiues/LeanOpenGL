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
		printf("着色器文件加载失败\n");
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	ComplileShaderAndLink(vShaderCode, fShaderCode);
}
void Shader::ComplileShaderAndLink(const char* vShaderCode, const char* fShaderCode)
{
	int success;//定义着色器编译结果
	char infoLog[512];//定义着色器编译日志
	unsigned int vertex, fragment;//定义顶点着色器

	vertex = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器
	glShaderSource(vertex, 1, &vShaderCode, NULL);//加载顶点着色器代码
	glCompileShader(vertex);//编译顶点着色器代码

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);//检查着色器编译结果
	if (!success)//如果编译失败
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);//获取错误消息
		printf("顶点着色器编译错误：%s\n", infoLog);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);//检查着色器编译结果
	if (!success)//如果编译失败
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);//获取错误消息
		printf("片段着色器编译错误：%s\n", infoLog);
	}

	ID= glCreateProgram();//创建着色器程序,返回着色器程序的ID
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);//链接着色器

	glGetProgramiv(ID, GL_LINK_STATUS, &success);//检查着色器链接结果
	if (!success)//如果链接失败
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);//获取错误消息
		printf("着色器链接错误：%s\n", infoLog);
	}
	glDeleteShader(vertex);//激活后删除着色器对象
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
	// 变量位置值，传递几个矩阵，是否对矩阵进行置换（交换行列）
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
}
//贴图名，贴图id（最多支持16张贴图），贴图是否开启alpha通道
void Shader::setTexture(const std::string &path,int textureID,bool alpha) 
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + textureID);//激活指定纹理单元
	glBindTexture(GL_TEXTURE_2D, texture);//绑定纹理单元
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//设置环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//设置纹理过滤，GL_LINEAR平滑，GL_NEAREST 颗粒
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
		printf("贴图加载失败\n");
	stbi_image_free(data);
}
