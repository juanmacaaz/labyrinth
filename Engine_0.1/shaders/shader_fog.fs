#version 330

in vec2 TexCoord0;
in vec3 mVertex;

out vec4 FragColor;

uniform int fog;
uniform sampler2D tex;
uniform vec3 CameraEye;

float getFogFactor(float d)
{
    const float FogMax = 13.5;
    const float FogMin = 1;

    if (d>=FogMax) return 1;
    if (d<=FogMin) return 0;

    return 1 - (FogMax - d) / (FogMax - FogMin);
}

void main()
{
    vec4 V = vec4(mVertex, 1.0);
    float d = distance(vec4(CameraEye, 1.0), V);
    float alpha = getFogFactor(d);

    if (fog == 1){
        FragColor = mix(texture(tex, TexCoord0), vec4(0.792, 0.478, 0.070, 0.5), alpha); 
    }else {
        FragColor = texture(tex, TexCoord0);
    } 
}
