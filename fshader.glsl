uniform sampler2D texture;

varying vec2 v_texcoord;

void main()
{
    // Set fragment color from texture
    gl_FragColor = texture2D(texture, v_texcoord);
}










/*#version 330 core

#define FRAG_OUTPUT0 0

// параметры точеченого источника освещения
uniform struct PointLight
{
  vec4 position;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec3 attenuation;
} light;

// параметры материала
uniform struct Material
{
  sampler2D texture;

  vec4  ambient;
  vec4  diffuse;
  vec4  specular;
  vec4  emission;
  float shininess;
} material;

// параметры полученные из вершинного шейдера
in Vertex {
  vec2  texcoord;
  vec3  normal;
  vec3  lightDir;
  vec3  viewDir;
  float distance;
} Vert;

layout(location = FRAG_OUTPUT0) out vec4 color;

void main(void)
{
  // нормализуем полученные данные для коррекции интерполяции
  vec3 normal   = normalize(Vert.normal);
  vec3 lightDir = normalize(Vert.lightDir);
  vec3 viewDir  = normalize(Vert.viewDir);

  // коэффициент затухания
  float attenuation = 1.0 / (light.attenuation[0] +
    light.attenuation[1] * Vert.distance +
    light.attenuation[2] * Vert.distance * Vert.distance);

  // добавим собственное свечение материала
  color = material.emission;

  // добавим фоновое освещение
  color += material.ambient * light.ambient * attenuation;

  // добавим рассеянный свет
  float NdotL = max(dot(normal, lightDir), 0.0);
  color += material.diffuse * light.diffuse * NdotL * attenuation;

  // добавим отраженный свет
  float RdotVpow = max(pow(dot(reflect(-lightDir, normal), viewDir), material.shininess), 0.0);
  color += material.specular * light.specular * RdotVpow * attenuation;

  // вычислим итоговый цвет пикселя на экране с учетом текстуры
  //color *= texture(material.texture, Vert.texcoord);
}*/
/*void main()
{

    float y = 1.0;
    gl_FragColor = vec4(y,y,y,1.0);

}*/

