precision mediump float;
varying vec3 v_color;
varying vec2 v_uv;
varying vec3 v_norm;
uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;
uniform samplerCube u_texture_2;


uniform float u_r;
uniform float u_R;
uniform vec3 u_color;
uniform vec3 u_cameraPos;
varying vec3 v_pos;
void main()
{
vec4 objColor=texture2D(u_texture_0,v_uv);
vec4 fogColor=texture2D(u_texture_1,v_uv);

float dist=distance(u_cameraPos,v_pos);
float alpha;
if(dist<=u_r)
   alpha=0.0;
if(dist>=u_R)
   alpha=1.0;
if(u_r<dist && dist<u_R)
   alpha=(dist-u_r)/(u_R-u_r);
vec4 color=alpha*fogColor+(1.0-alpha)*objColor;
vec4 c_refl;
vec3 vectCam=u_cameraPos-v_pos;
vec3 dirReflect=reflect(normalize(vectCam),normalize(v_norm));
vec4 c_sky=textureCube(u_texture_2,dirReflect);

gl_FragColor = 0.5*color+0.5*c_sky;
}
