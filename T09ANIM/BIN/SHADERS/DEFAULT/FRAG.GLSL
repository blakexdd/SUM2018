#version 330

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;


uniform float GlobalTime;

void main( void )
{
  OutColor = DrawColor;
  OutColor = vec4(1, 8, 0, 1);

  vec3 L = normalize(vec3(1, 0.1, 1));
  OutColor = vec4(L, 1);

}
