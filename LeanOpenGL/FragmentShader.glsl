#version 330 core
out vec4 FragColor;
in  vec3 vectColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec4 ourColor;
void main()
{
	//FragColor=vec4(ourColor.rgb/2+vectColor,1);
	//FragColor=texture(texture1,TexCoord)*vec4(ourColor.rgb/2+vectColor,1);;
	FragColor=mix(texture(texture1,TexCoord),texture(texture2,TexCoord),0.2)*vec4(ourColor.rgb/2+vectColor,1);
}