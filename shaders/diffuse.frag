//
//   Fragment Shader
//

#version 330 core

out vec4 FragColor;

in vec3 outNormal;
in vec3 outNonDistortedPos;

uniform vec4 color;
uniform vec3 mainLight;

void main()
{
  vec3 normal = normalize(outNormal);
  vec3 lightDir = normalize(mainLight - outNonDistortedPos);

  float diffuse = max(dot(normal, lightDir), 0.0);
  vec4 colorDiffuse = diffuse * color;

  FragColor = colorDiffuse;
}