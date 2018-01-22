#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D videoFrame;
uniform sampler2D overlayImage;

void main() {
	FragColor = mix(texture(videoFrame, TexCoord), texture(overlayImage, TexCoord), 0.2);
}