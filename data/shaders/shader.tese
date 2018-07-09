#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (triangles, equal_spacing, cw) in;

layout (binding = 0) uniform UniformBufferObject{
  mat4 model;
  mat4 view;
  mat4 proj;
} ubo;

layout (binding = 1) uniform sampler2D displacementSampler;

layout(location = 0) in vec3 tesePosition[];
layout(location = 1) in vec3 teseColor[];
layout(location = 2) in vec2 teseTexCoord[];
layout(location = 3) in vec3 teseNormals[];

layout(location = 0) out vec3 fragPosition;
layout(location = 1) out vec3 fragColor;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec3 fragNormals;

float displacementFactor = 0.5;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main ()
{
  fragTexCoord = interpolate2D(teseTexCoord[0], teseTexCoord[1], teseTexCoord[2]);
  fragNormals = interpolate3D(teseNormals[0], teseNormals[1], teseNormals[2]);
  fragNormals = normalize(fragNormals);
  fragPosition = interpolate3D(tesePosition[0], tesePosition[1], tesePosition[2]);

  float Displacement = textureLod(displacementSampler, fragTexCoord, 0.0).r;
  fragPosition += fragNormals * (Displacement * displacementFactor);
  gl_Position = ubo.proj * ubo.view * ubo.model * vec4(fragPosition, 1.0f);

  fragColor = teseColor[0];
}
