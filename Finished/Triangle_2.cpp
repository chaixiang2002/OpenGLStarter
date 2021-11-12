/*

    顶点数组对象：Vertex Array Object，VAO
    顶点缓冲对象：Vertex Buffer Object，VBO
    索引缓冲对象：Element Buffer Object，EBO或Index Buffer Object，IBO

*/
//  传递3个3D坐标作为图形渲染管线的输入，表示一个三角形，这数组叫做顶点数据VertexData

//  1,顶点输入

// x,y,z
/* -0.5,  -0.5f, 0.0f, //
0.5f,  -0.5f, 0.0f, //
0.0f,  0.5f,  0.0f, //
0.5f,  -0.5f, 0.0f, // 右下角
-0.5f, -0.5f, 0.0f, // 左下角
-0.5f, 0.5f,  0.0f  // 左上角
*/

//索引缓冲对象(Element Buffer Object
float vertices[] = {
    0.5f,  0.5f,  0.0f,  //
    0.5f,  -0.5f, 0.0f,  //
    -0.5f, -0.5f, -0.5f, //
    -0.5f, 0.5f,  0.0f   //
};

unsigned int inddices[] = {
    // 注意索引从0开始!
    0, 1, 3, //
    1, 2, 3  //

};

//创建索引缓冲对象：
unsigned int EBO;
glad_glGenBuffers(1, &EBO);

glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //先绑定EBO
// glBufferData把索引复制到缓冲
glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), GL_STATIC_DRAW);

//  2,使用glGenBuffers函数和一个缓冲ID生成一个VBO对象
unsigned int VBO;
glGenBuffers(1, &VBO);

// OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
// 使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
glBindBuffer(GL_ARRAY_BUFFER, sizeof(vertics), vertices, GL_STATTC_DRAW);
//第一个参数是目标缓冲的类型
//第二个参数指定传输数据的大小(以字节为单位)
//第三个参数是我们希望发送的实际数据
//第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：

// GL_STATIC_DRAW ：数据不会或几乎不会改变。
// GL_DYNAMIC_DRAW：数据会被改变很多。
// GL_STREAM_DRAW ：数据每次绘制时都会改变

//  2,顶点着色器(Vertex Shader)
//第一件事是用着色器语言GLSL(OpenGL Shading
// Language)编写顶点着色器，然后编译这个GLSL着色器
#verson 330 core
layout(location = 0) in ves3 apos;

void main() { gl_Postion = vec4(apos.x, apos.y, apos.z, 1.0); }

//  3,编译着色器
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location =0) in vec3 apos;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = vec4(aPos.x,apos.y,apos.z,1.0);\n"
    "}\n";

//做的是创建一个着色器对象
//储存这个顶点着色器为unsigned int
//用glCreateShader创建这个着色器
unsigned int vertexShader;
vertexShader = glCreateSHader(Gl_VERTEX_SHADER);
//把需要创建的着色器类型以参数(GL_VERTEX_SHADER)形式提供给glCreateShader
//把这个着色器源码附加到着色器对象上，然后编译它
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader); //编译它

//检测glCompileShader编译是否成功
int success;       //一变量来表示是否成功
char infoLog[512]; //储存错误消息的容器
glGetShaderiv(vertexShader, Gl_COMILE_STATUS,
              &success); // glGetShaderiv检查是否编译成功

if (!success) {
  glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
  std::cout << "ERROR::SHADER::VERYEX::COMPLATION_FAILED\n"
            << infoLog << std::endl;
}
