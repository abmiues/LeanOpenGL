#include<stdio.h>
#include<glad/glad.h>//需要先包含
#include<GLFW/glfw3.h>//才能包含这个
#include<math.h>
#include"shader.h"
#include"stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{

}
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	
}
int main()
{
	glfwInit();//初始化gifw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//定义opengl大版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//定义opengl小版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//glfw使用核心模式，不能向下兼容
	// for macOS X glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	GLFWwindow * window = glfwCreateWindow(1920, 1080, "LeanOpenGL", NULL, NULL);//创建窗口
	
	if (window == NULL)
	{
		printf("创建窗口失败\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("加载GLAD失败\n");
		return -1;
	}
	//是否支持垂直同步，垂直同步必须在绑定窗后后执行
	if (glfwExtensionSupported("WGL_EXT_swap_control_tear") || glfwExtensionSupported("GLX_EXT_swap_control_tear "))
		glfwSwapInterval(1);//在glfwSwapBuffers交换缓冲区之前等待的最小屏幕更新次数。==0关闭垂直同步，>0开启
	//glViewport(0, 0, 800, 600);//设置视口
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//绑定窗口变化的监听，用于更新视口
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// 限制光标在窗口内并且隐藏
	glfwSetCursorPosCallback(window, mouse_callback);
	
	float vertices[] = { 0.5f, 0.5f,0.5f,  1.0f,0.0f,0.0f,   1.0f,1.0f,
						 0.5f,-0.5f,0.5f,  0.0f,1.0f,0.0f,   1.0f,0.0f,
						-0.5f,-0.5f,0.5f,  0.0f,0.0f,1.0f,   0.0f,0.0f,
						-0.5f, 0.5f,0.5f,  1.0f,0.0f,0.0f,   0.0f,1.0f,

						 0.5f, 0.5f,-0.5f,  0.0f,1.0f,0.0f,   0.0f,1.0f,
						 0.5f,-0.5f,-0.5f,  0.0f,0.0f,1.0f,   1.0f,1.0f,
						-0.5f,-0.5f,-0.5f,  1.0f,0.0f,0.0f,   1.0f,0.0f,
						-0.5f, 0.5f,-0.5f,  0.0f,1.0f,0.0f,   0.0f,0.0f,};
	unsigned int indices[] = {0,1,3,1,2,3,0,5,1,0,4,5,4,6,5,4,7,6,7,3,2,7,2,6,0,4,3,3,4,7,1,5,2,2,5,6};

	unsigned int VAO, VBO, EBO;//定义一个顶点数组对象
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);//创建vbo
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//给vbo传递数据
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定EBO,索引数组
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//传递索引数组
	
	//顶点位置属性
	//顶点属性id,对应着色器中loaction；
	//属性值大小，顶点由3个值组成，相当于取几个值；
	//数据类型；
	//是否标准化；
	//步长，下次从什么位置取值；
	//数据起始位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//设置顶点属性指针
	glEnableVertexAttribArray(0);
	
	//顶点颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//uv坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);线框模式


	//glm::mat4 trans = glm::mat4(1.0f);
	//glm::mat4 trans;//定义变换矩阵
	
//	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));//变换矩阵绕z轴旋转90度
	
	//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));//设置变换矩阵平移。
	//实际要先缩放，再平移。代码里是先设置平移，再设置旋转，矩阵和向量相乘的时候是反过来的
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));//缩放到原来的0.5
	glEnable(GL_DEPTH_TEST);//开启深度测试，应该写在shader里
	Shader *shader = new Shader("VertexShader.glsl","FragmentShader.glsl");
	shader->use();
	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);
	shader->setTexture("container.jpg",0,false);
	shader->setTexture("awesomeface.png", 1,true);

	glm::mat4 view;//定义观察矩阵
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f,1.0f,0.0f)
		);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float cameraSpeed = 0.05f;
	
	glm::mat4 projection;//定义投影矩阵
	projection = glm::perspective(glm::radians(45.0f), 16.0f / 9, 0.1f, 100.0f);

	double time = glfwGetTime();
	unsigned int frames = 0;
	float deltaTime = 0;
	float lastFrameTime = time;
	while (!glfwWindowShouldClose(window))//主循环体
	{
		processInput(window);//按键操作监听
		cameraSpeed = 2.5f*deltaTime;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			cameraPos += cameraSpeed * cameraFront;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			cameraPos -= cameraSpeed * cameraFront;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp))* cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp))* cameraSpeed;
		}
		
		glClearColor(.2f, .2f, .3f, 1.0f);//定义清理颜色
		glClear(GL_COLOR_BUFFER_BIT);//清理颜色

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.05f;
		//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));//缩放到原来的0.5
		
		shader->use();
		shader->setFloat4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
		
		view = glm::lookAt(cameraPos, cameraFront+cameraPos, cameraUp);
		shader->SetMatrix4("view", view);
		shader->SetMatrix4("projection", projection);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除缓冲，应该写在相机里
		for (unsigned int i = 0;i < 10;i++)
		{
			glm::mat4 model;//定义个模型矩阵，这个后面要创建成一个单独的类，每个模型都有这么个矩阵
			float angle = 20 * i;
			model = glm::translate(model, glm::vec3(i*glm::cos(glm::radians(i * 90.0f)) / 5.0f, i*glm::sin(glm::radians(i * 90.0f) ) / 5.0f, i / -5.0f));
			model = glm::rotate(model, angle+(float)glfwGetTime()*glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			shader->SetMatrix4("model", model);
			//glBindVertexArray(VAO);//绘制其他时需绑定其他的VAO
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
		glfwSwapBuffers(window);//输出缓冲
		glfwPollEvents();//检查键盘输入，鼠标移动等,不可少
		//glBindVertexArray(0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
		
		frames++;
		if (currentTime - time >=1)
		{
			printf("fps:%d", frames);
			frames = 0;
			time = currentTime;
		}
	}
	delete shader;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}