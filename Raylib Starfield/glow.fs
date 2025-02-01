#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

const vec2 size = vec2(800, 450); // Framebuffer size
const float samples = 5.0;        // Pixels per axis; higher = bigger glow, worse performance
const float quality = 2.5;        // Lower = smaller glow, better quality

void main()
{
    vec4 sum = vec4(0.0);
    vec2 sizeFactor = vec2(1.0) / size * quality;
    vec4 source = texture(texture0, fragTexCoord);

    int range = int((samples - 1.0) / 2.0);
    for (int x = -range; x <= range; x++)
    {
        for (int y = -range; y <= range; y++)
        {
            sum += texture(texture0, fragTexCoord + vec2(float(x), float(y)) * sizeFactor);
        }
    }

    finalColor = ((sum / (samples * samples)) + source) * colDiffuse;
}
