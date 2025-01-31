#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);
    float glow = 1.0; // Adjust this value for more or less glow
    vec4 glowColor = vec4(1.0, 1.0, 0.0, 1.0); // Yellow glow

    // Increase the intensity of the glow
    vec4 emission = glowColor * glow * 20.0; // Adjust the multiplier for more intensity
    finalColor = mix(texelColor, emission, glow) * colDiffuse * fragColor;
}
