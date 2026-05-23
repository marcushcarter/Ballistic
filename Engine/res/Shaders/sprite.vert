#version 450

layout(location = 0) out vec2 outUV;

layout(push_constant) uniform PushConstants {
    vec2 screenSize;
    vec2 imageSize;
} pc;

void main()
{
    vec2 positions[6] = vec2[](
        vec2(0.0, 0.0),
        vec2(1.0, 0.0),
        vec2(1.0, 1.0),
        vec2(0.0, 0.0),
        vec2(1.0, 1.0),
        vec2(0.0, 1.0)
    );

    vec2 uv = positions[gl_VertexIndex];
    outUV = uv;

    float screenAspect = pc.screenSize.x / pc.screenSize.y;
    float imageAspect  = pc.imageSize.x  / pc.imageSize.y;

    vec2 scale;
    if (screenAspect > imageAspect)
        scale = vec2(imageAspect / screenAspect, 1.0);
    else
        scale = vec2(1.0, screenAspect / imageAspect);

    vec2 ndc = (uv * 2.0 - 1.0) * scale;
    gl_Position = vec4(ndc, 0.0, 1.0);
}