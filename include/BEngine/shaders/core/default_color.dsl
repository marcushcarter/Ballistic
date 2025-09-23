@vs vertex_shader

#version 460 core
layout(location = 0) in vec3 aPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 TexCoord;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}

@end

@fs fragment_shader

#version 460 core

out vec4 FragColor;

uniform vec4 diffuseColor;

void main() {
    FragColor = vec4(diffuseColor.xyz, 1.0);
}

@end

@program default_color vertex_shader fragment_shader