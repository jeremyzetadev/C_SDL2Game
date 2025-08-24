#version 330 core
// #version 420 core
// #extension GL_ARB_explicit_uniform_location : require

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_uvs;

out vec2 uvs;

uniform mat4 projection;
uniform mat4 model;

void main() {
    uvs = a_uvs;
    gl_Position = projection * model * vec4(a_pos, 1.0);
}
