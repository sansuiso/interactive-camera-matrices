#version 150

uniform mat4 extrinsic;
uniform mat4 projection;
in vec3 vertex;

void main()
{
    gl_Position = projection * extrinsic * vec4(vertex, 1);
}

