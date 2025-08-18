#version 460 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main() {

   vec4 texColor;
   
   texColor = texture(tex0, texCoord);
   FragColor = vec4(color, 1.0); // texColor *
}
