#version 150

uniform mat4 extrinsic;
in vec3 vertex;

void main()
{
    gl_Position = extrinsic * vec4(vertex, 1);
}

