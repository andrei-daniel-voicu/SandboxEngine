precision mediump float;
varying vec3 v_color;
varying vec2 v_uv;
varying vec3 v_norm;
varying vec3 frag_pos;

uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;


uniform float u_r;
uniform float u_R;
uniform vec3 u_color;
uniform vec3 u_cameraPos;
uniform bool u_selected;
varying vec3 v_pos;
void main()
{
vec4 objColor=texture2D(u_texture_0,v_uv);
if(objColor.a<0.1)
discard;
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
if(!u_selected)
{
   vec4 outline=vec4(1.0,0.0,0.0,1.0);
   vec3 dir= normalize(u_cameraPos-frag_pos);
   float cameraFacing=dot(dir,v_norm);
   gl_FragColor = outline*cameraFacing+color*(1.0-cameraFacing);
}
else
{
     gl_FragColor=color;
}


}
