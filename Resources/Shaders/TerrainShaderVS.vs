attribute vec3 a_posL;
attribute vec3 a_color;
attribute vec2 a_uv;

varying vec3 v_color;
varying vec2 v_uv;
varying vec2 v_uv2;
varying vec3 v_pos;

uniform mat4 u_rotation;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform int u_nrCells;
uniform vec3 u_height;
uniform sampler2D u_texture_3;


void main()
{
vec4 c_blend = texture2D(u_texture_3,a_uv/float(u_nrCells));

vec4 pos_nou = vec4(a_posL,1.0);

pos_nou.w = 1.0;
pos_nou.y += c_blend.r*u_height.r+c_blend.g*u_height.g+c_blend.b*u_height.b;
gl_Position =  u_proj*u_view *u_rotation* pos_nou;
v_uv = a_uv;

v_uv2 = vec2(a_uv.x / float(u_nrCells),a_uv.y /  float(u_nrCells));
vec4 temp=u_rotation* pos_nou;
v_pos=vec3(temp.x,temp.y,temp.z);
}
   