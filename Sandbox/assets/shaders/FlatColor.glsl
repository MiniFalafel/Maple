// Flat Color Shader

#type vertex
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 uViewProjectionMatrix;
uniform mat4 uModelMatrix;

void main() {
	vec3 Pos = vec3(uModelMatrix * vec4(aPos, 1.0));
	gl_Position = uViewProjectionMatrix * vec4(Pos, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

uniform vec4 uColor;

void main() {
	FragColor = uColor;
}