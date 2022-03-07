attribute vec3 a_posL;
attribute vec3 a_color;
attribute vec2 a_uv;
attribute vec3 a_norm;

varying vec3 v_color;
varying vec2 v_uv;
varying vec3 v_pos;
varying vec3 frag_pos;
varying vec3 v_norm;


uniform mat4 u_rotation;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position =  u_proj*u_view *u_rotation* posL;
vec4 temp = u_rotation* posL;
v_pos = vec3(temp.x,temp.y,temp.z);
frag_pos=vec3(gl_Position.x,gl_Position.y,gl_Position.z);
v_uv=a_uv;
v_norm=a_norm;
}
   