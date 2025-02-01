#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 vertPos;

out vec4 finalColor;

void main()
{
    float dcurve = 1.0-abs((fragTexCoord.y)-(sin(fragTexCoord.x)/10.0));
    float fromcentre = length(fragTexCoord-0.5); 
    float alpha = (1.0/(fromcentre*50.0))-0.07;
    finalColor = vec4(fragColor.r, fragColor.g, fragColor.b, alpha);
}