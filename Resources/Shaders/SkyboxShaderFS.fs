precision mediump float;
varying vec3 v_color;
varying vec3 v_coord;
uniform samplerCube u_texture_0;
void main()
{

gl_FragColor = textureCube(u_texture_0,v_coord);
}
