#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormals;

layout(location = 0) out vec3 fragPosition;
layout(location = 1) out vec3 fragColor;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec3 fragNormals;

out gl_PerVertex
{
  vec4 gl_Position;
};

void main()
{
  fragPosition = vec4(inPosition, 1.0).xyz;
  fragColor = inColor;
  fragTexCoord = inTexCoord;
  fragNormals = (ubo.proj * ubo.view * ubo.model * vec4(inNormals, 0.0)).xyz;
}
