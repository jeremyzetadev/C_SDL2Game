// #version 420 core
// #extension GL_ARB_explicit_uniform_location : require
#version 330 core

out vec4 frag_color;

in vec2 uvs;

uniform vec4 color;
uniform sampler2D texture_id;

void main(){
    frag_color = texture(texture_id, uvs) * color;
}
