precision mediump float;
varying vec3 v_color;
varying vec2 v_uv;
varying vec2 v_uv2;

uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;
uniform sampler2D u_texture_2;
uniform sampler2D u_texture_3;
uniform sampler2D u_texture_4;

uniform float u_r;
uniform float u_R;
uniform vec3 u_color;
uniform vec3 u_cameraPos;
varying vec3 v_pos;
void main()
{

vec4 c_blend = texture2D(u_texture_3,v_uv2);
vec4 c_rock = texture2D(u_texture_2,v_uv);
vec4 c_grass = texture2D(u_texture_1,v_uv);
vec4 c_dirt = texture2D(u_texture_0,v_uv);
vec4 c_final = c_blend.r*c_rock+c_blend.g*c_grass+c_blend.b*c_dirt;
c_final.a = 1.0;

vec4 fogColor=texture2D(u_texture_4,v_uv);
float dist=distance(u_cameraPos,v_pos);
float alpha;
if(dist<=u_r)
   alpha=0.0;
if(dist>=u_R)
   alpha=1.0;
if(u_r<dist && dist<u_R)
   alpha=(dist-u_r)/(u_R-u_r);
vec4 color=alpha*fogColor+(1.0-alpha)*c_final;
gl_FragColor = color;
}
