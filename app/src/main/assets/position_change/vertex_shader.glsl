#version 300 es

layout (location=0) in vec3 vPosition;
layout (location=1) in vec3 vColors;

out vec3 ourColor;
float offset = 0.5f;


// 将顶点作为颜色传到片段着色器，片段着色器取每个顶点的第一个值为颜色值
out vec3 ourPosition;

void main() {

// 顛倒三角形
//gl_Position=vec4(vPosition.x,-vPosition.y,vPosition.z,1.0f);
// 偏移三角形
//gl_Position=vec4(vPosition.x+offset,vPosition.y,vPosition.z,1.0f);

gl_Position=vec4(vPosition.x,vPosition.y,vPosition.z,1.0f);

ourColor=vColors;
ourPosition=vPosition;
}
