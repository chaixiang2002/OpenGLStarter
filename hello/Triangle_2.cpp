/*

    顶点数组对象：Vertex Array Object，VAO
    顶点缓冲对象：Vertex Buffer Object，VBO
    索引缓冲对象：Element Buffer Object，EBO或Index Buffer Object，IBO

*/
//  传递3个3D坐标作为图形渲染管线的输入，表示一个三角形，这数组叫做顶点数据VertexData

//  1,顶点输入
float vertices[] = { // x,y,z
    -0.5, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
//  2,使用glGenBuffers函数和一个缓冲ID生成一个VBO对象
unsigned int VBO;
glGenBuffers(1, &VBO);

// OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
// 使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
glBindBuffer(GL_ARRAY_BUFFER, VBO);