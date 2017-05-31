//uniform mat4 mvp_matrix;

attribute highp vec4 a_position;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position =  a_position; //mvp_matrix *

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
}
//! [0]



//attribute highp vec4 posAtr;
//uniform highp int time;
/*
#version 330 core
#define VERT_POSITION 0
#define VERT_TEXCOORD 1
#define VERT_NORMAL   2

layout(location = VERT_POSITION) in vec3 position;
layout(location = VERT_TEXCOORD) in vec2 texcoord;
layout(location = VERT_NORMAL)   in vec3 normal;

// параметры преобразований
uniform struct Transform
{
  mat4 model;
  mat4 viewProjection;
  mat3 normal;
  vec3 viewPosition;
} transform;

// параметры точеченого источника освещения
uniform struct PointLight
{
  vec4 position;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec3 attenuation;
} light;

// параметры для фрагментного шейдера
out Vertex {
  vec2  texcoord;
  vec3  normal;
  vec3  lightDir;
  vec3  viewDir;
  float distance;
} Vert;

void main(void)
{
  // переведем координаты вершины в мировую систему координат
  vec4 vertex   =  vec4(position, 1.0);

  // направление от вершины на источник освещения в мировой системе координат
  vec4 lightDir = light.position - vertex;

  // передадим во фрагментный шейдер некоторые параметры
  // передаем текстурные координаты
  Vert.texcoord = texcoord;
  // передаем нормаль в мировой системе координат
  Vert.normal   =  normal;
  // передаем направление на источник освещения
  Vert.lightDir = vec3(lightDir);
  // передаем направление от вершины к наблюдателю в мировой системе координат
  Vert.viewDir  =  vec3(vertex);
  // передаем рассятоние от вершины до источника освещения
  Vert.distance = length(lightDir);

  // переводим координаты вершины в однородные
  gl_Position =  vertex;
}
*/
/*void main()
{
    gl_Position = vec4(posAtr.x + cos(posAtr.y*10.0 + time*0.05)*0.1,
                       posAtr.y + sin(posAtr.x*5.0 + time*0.05)*0.1,
                       posAtr.z,
                       1);
}*/
