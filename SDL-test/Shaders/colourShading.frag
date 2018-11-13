#version 130

in vec4 fragmentColour;

out vec4 colour;

uniform float time;

void main() {
	colour = fragmentColour + vec4(1.0 * (cos(time) + 1.0) * 0.5, 
								 1.0 * (cos(time + 2.0) + 1.0) * 0.5,
								 1.0 * (sin(time + 2.0) + 1.0) * 0.5, 0.0);
}