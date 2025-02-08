#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 vertPos;

out vec4 finalColor;

uniform float myAlpha;

void main()
{
    float dcurve = 1.0-abs((fragTexCoord.y)-(sin(fragTexCoord.x)/10.0));
    float fromcentre = length(fragTexCoord-0.5); 
    float alpha = (myAlpha/(fromcentre*50.0))-0.1;
    finalColor = vec4(fragColor.r, fragColor.g, fragColor.b, alpha);
}


