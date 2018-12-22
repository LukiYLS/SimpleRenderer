#version 330                                                                        
                                                                                    
uniform sampler2D texture;                                                        
                                                                                    
in vec2 TexCoord;                                                                   
out vec4 FragColor;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    FragColor = texture2D(texture, TexCoord);                                     
                                                                                    
    if (FragColor.r == 0 && FragColor.g == 0 && FragColor.b == 0) {
        discard;                                                                    
    }                                                                               
}