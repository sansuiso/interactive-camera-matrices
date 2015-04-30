#version 150

uniform mat4 extrinsic;
uniform mat4 projection;
uniform mat4 model;

in vec3 vertex;

void main()
{
    gl_Position = projection * extrinsic * model * vec4(vertex, 1);
}

