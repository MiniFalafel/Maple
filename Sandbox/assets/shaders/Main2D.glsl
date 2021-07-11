// Basic Texture shader

#type vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

uniform mat4 uViewProjectionMatrix;
uniform mat4 uModelMatrix;

out vec2 TexCoords;

void main() {
	vec3 Pos = vec3(uModelMatrix * vec4(aPos, 1.0));
	TexCoords = vec2(aTexCoords.xy);
	gl_Position = uViewProjectionMatrix * vec4(Pos, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

uniform sampler2D uTexImage;
uniform vec4 uColor;

uniform float uTextureScale = 1.0;

in vec2 TexCoords;

void main() {
	FragColor = texture(uTexImage, TexCoords * uTextureScale) * uColor;
}
