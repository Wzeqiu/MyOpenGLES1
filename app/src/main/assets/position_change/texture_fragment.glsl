#version 300 es

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord; // 纹理坐标

 //纹理采样器
uniform sampler2D texture1;
uniform sampler2D texture2;
void main() {

//FragColor=texture(texture1,TexCoord); // 输出纹理上的颜色

//FragColor=vec4(1.0,0.0,0.5,1.0);

//FragColor=texture(ourTexture1,TexCoord)*vec4(ourColor,1.0);

 FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.3);

//图片旋转方向
// FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0-TexCoord.x, TexCoord.y)), 0.5);

}
