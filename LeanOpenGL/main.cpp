#include<stdio.h>
#include<glad/glad.h>//��Ҫ�Ȱ���
#include<GLFW/glfw3.h>//���ܰ������
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
	glfwInit();//��ʼ��gifw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//����opengl��汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//����openglС�汾
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//glfwʹ�ú���ģʽ���������¼���
	// for macOS X glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	GLFWwindow * window = glfwCreateWindow(1920, 1080, "LeanOpenGL", NULL, NULL);//��������
	
	if (window == NULL)
	{
		printf("��������ʧ��\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("����GLADʧ��\n");
		return -1;
	}
	//�Ƿ�֧�ִ�ֱͬ������ֱͬ�������ڰ󶨴����ִ��
	if (glfwExtensionSupported("WGL_EXT_swap_control_tear") || glfwExtensionSupported("GLX_EXT_swap_control_tear "))
		glfwSwapInterval(1);//��glfwSwapBuffers����������֮ǰ�ȴ�����С��Ļ���´�����==0�رմ�ֱͬ����>0����
	//glViewport(0, 0, 800, 600);//�����ӿ�
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//�󶨴��ڱ仯�ļ��������ڸ����ӿ�
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// ���ƹ���ڴ����ڲ�������
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

	unsigned int VAO, VBO, EBO;//����һ�������������
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);//����vbo
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//��vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//��vbo��������
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//��EBO,��������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//������������
	
	//����λ������
	//��������id,��Ӧ��ɫ����loaction��
	//����ֵ��С��������3��ֵ��ɣ��൱��ȡ����ֵ��
	//�������ͣ�
	//�Ƿ��׼����
	//�������´δ�ʲôλ��ȡֵ��
	//������ʼλ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//���ö�������ָ��
	glEnableVertexAttribArray(0);
	
	//������ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//uv����
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);�߿�ģʽ


	//glm::mat4 trans = glm::mat4(1.0f);
	//glm::mat4 trans;//����任����
	
//	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));//�任������z����ת90��
	
	//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));//���ñ任����ƽ�ơ�
	//ʵ��Ҫ�����ţ���ƽ�ơ���������������ƽ�ƣ���������ת�������������˵�ʱ���Ƿ�������
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));//���ŵ�ԭ����0.5
	glEnable(GL_DEPTH_TEST);//������Ȳ��ԣ�Ӧ��д��shader��
	Shader *shader = new Shader("VertexShader.glsl","FragmentShader.glsl");
	shader->use();
	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);
	shader->setTexture("container.jpg",0,false);
	shader->setTexture("awesomeface.png", 1,true);

	glm::mat4 view;//����۲����
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f,1.0f,0.0f)
		);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float cameraSpeed = 0.05f;
	
	glm::mat4 projection;//����ͶӰ����
	projection = glm::perspective(glm::radians(45.0f), 16.0f / 9, 0.1f, 100.0f);

	double time = glfwGetTime();
	unsigned int frames = 0;
	float deltaTime = 0;
	float lastFrameTime = time;
	while (!glfwWindowShouldClose(window))//��ѭ����
	{
		processInput(window);//������������
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
		
		glClearColor(.2f, .2f, .3f, 1.0f);//����������ɫ
		glClear(GL_COLOR_BUFFER_BIT);//������ɫ

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.05f;
		//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));//���ŵ�ԭ����0.5
		
		shader->use();
		shader->setFloat4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
		
		view = glm::lookAt(cameraPos, cameraFront+cameraPos, cameraUp);
		shader->SetMatrix4("view", view);
		shader->SetMatrix4("projection", projection);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//������壬Ӧ��д�������
		for (unsigned int i = 0;i < 10;i++)
		{
			glm::mat4 model;//�����ģ�;����������Ҫ������һ���������࣬ÿ��ģ�Ͷ�����ô������
			float angle = 20 * i;
			model = glm::translate(model, glm::vec3(i*glm::cos(glm::radians(i * 90.0f)) / 5.0f, i*glm::sin(glm::radians(i * 90.0f) ) / 5.0f, i / -5.0f));
			model = glm::rotate(model, angle+(float)glfwGetTime()*glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			shader->SetMatrix4("model", model);
			//glBindVertexArray(VAO);//��������ʱ���������VAO
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
		glfwSwapBuffers(window);//�������
		glfwPollEvents();//���������룬����ƶ���,������
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