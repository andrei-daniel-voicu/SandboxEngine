attribute vec3 a_posL;

uniform mat4 u_view;
uniform mat4 u_proj;
uniform mat4 u_rotation;

void main()
{

vec4 posL = vec4(a_posL, 1.0);
gl_Position =  u_proj*u_view *u_rotation* posL;
}