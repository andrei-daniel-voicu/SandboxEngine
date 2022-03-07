attribute vec3 a_posL;
attribute vec3 a_color;
attribute vec2 a_uv;

varying vec3 v_color;
varying vec3 v_coord;


uniform mat4 u_rotation;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
vec4 posL=vec4(a_posL,1.0);
gl_Position =  u_proj*u_view *u_rotation* posL;
v_coord=a_posL;

}
   