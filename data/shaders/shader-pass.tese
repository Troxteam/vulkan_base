#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (triangles, equal_spacing, cw) in;

layout (binding = 0) uniform UniformBufferObject{
  mat4 model;
  mat4 view;
  mat4 proj;
} ubo;

layout(location = 0) in vec3 tesePosition[];
layout(location = 1) in vec3 teseColor[];
layout(location = 2) in vec2 teseTexCoord[];
layout(location = 3) in vec3 teseNormals[];

layout(location = 0) out vec3 fragPosition;
layout(location = 1) out vec3 fragColor;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec3 fragNormals;

void main ()
{
  gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +
                (gl_TessCoord.y * gl_in[1].gl_Position) +
                (gl_TessCoord.z * gl_in[2].gl_Position);
  gl_Position = ubo.proj * ubo.view * ubo.model * gl_Position;

  fragPosition = gl_Position.xyz;
  fragColor = teseColor[0];
  fragTexCoord = gl_TessCoord.x * teseTexCoord[0] + gl_TessCoord.y * teseTexCoord[1] + gl_TessCoord.z * teseTexCoord[2];
  fragNormals = teseNormals[0];
}
