precision mediump float;
varying vec3 v_color;
varying vec2 v_uv;
uniform float u_time;
uniform float u_dispMax;
uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;
uniform sampler2D u_texture_2;


void main()
{
vec4 color = texture2D(u_texture_2,vec2(v_uv.x,v_uv.y+u_time));
vec2 disp = texture2D(u_texture_2, vec2(v_uv.x, v_uv.y + u_time)).rg; 
vec2 offset = (disp*float(2)-vec2(1,1))*u_dispMax;
vec2 v_uv_displaced=v_uv+offset; 
vec4 c_fire=texture2D(u_texture_1,v_uv_displaced);
vec4 c_alpha=texture2D(u_texture_0,v_uv);
c_fire.a=c_fire.a*c_alpha.r;
gl_FragColor = c_fire;
}
