#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(vertices = 3) out;

layout (binding = 0) uniform UniformBufferObject{
  mat4 model;
  mat4 view;
  mat4 proj;
} ubo;

layout(location = 0) in vec3 tescPosition[];
layout(location = 1) in vec3 tescColor[];
layout(location = 2) in vec2 tescTexCoord[];
layout(location = 3) in vec3 tescNormals[];

layout(location = 0) out vec3 tesePosition[];
layout(location = 1) out vec3 teseColor[];
layout(location = 2) out vec2 teseTexCoord[];
layout(location = 3) out vec3 teseNormals[];

void main()
{
  if(gl_InvocationID == 0)
  {
    gl_TessLevelInner[0] = 1.0;
    gl_TessLevelOuter[0] = 1.0;
    gl_TessLevelOuter[1] = 1.0;
    gl_TessLevelOuter[2] = 1.0;
  }

  tesePosition[gl_InvocationID] = tescPosition[gl_InvocationID];
  teseColor[gl_InvocationID] = tescColor[gl_InvocationID];
  teseTexCoord[gl_InvocationID] = tescTexCoord[gl_InvocationID];
  teseNormals[gl_InvocationID] = tescNormals[gl_InvocationID];
}
