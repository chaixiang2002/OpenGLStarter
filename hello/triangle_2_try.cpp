#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <ostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location=0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = vec4(aPos.x,aPos.y,aPos.z ,1.0);\n"
    "}\n";
const char *framgmentShaderSource = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "  FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
                                    "}\n\0";

/* glfwGetKey函数，它需要一个窗口以及一个按键作为输入 */
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  /* glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
这个函数将会返回Esc这个按键是否正在被按下 */
}

/* void framebuffer_size_callback(GLFWwindow* window, int width, int height);
回调函数(Callback Function)，用户改变窗口的大小的时候，视口也被调整
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  // glfw: init and config
  //----------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // (GLFW_OPENGL_CORE_PROFILE)告诉GLFW我们使用的是核心模式(Core-profile)
  /* if Mac OS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
 */

  // glfw window creation
  //---------------------
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Snow_WINDOW", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate(); //释放/删除之前的分配的所有资源
    return -1;
  }
  glfwMakeContextCurrent(window); //??????????**********???????********???
  //通知GLFW将我们窗口的上下文设置为当前线程的主上下文了。----------------
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  //告诉GLFW我们希望每当窗口调整大小的时候调用这个函数

  // glad: load all opengl function pointers
  /* GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
   */
  //-----------------------------------------------------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to init GLAD" << std::endl;
    return -1;
  }

  // build and compile shaderprogram
  //----------------------------------------------------------------------------------------------
  // vertex shader
  unsigned int vertexShader = glad_glCreateShader(GL_VERTEX_SHADER);
  /* 创建一个顶点着色器对象，注意还是用ID来引用的。
     传递的参数是GL_VERTEX_SHADER(顶点着色器) */
  glad_glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glad_glCompileShader(vertexShader);
  //把这个(顶点)着色器源码附加到着色器对象上，然后编译它

  // check for shader compile errors
  int success;       //定义变量表示是否成功编译
  char infoLog[512]; //储存错误消息的容器
  glad_glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  // glGetShaderiv检查是否编译成功
  if (!success) {
    glad_glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    // glGetShaderInfoLog获取错误消息，然后打印它
    std::cout << "ERROR::SHADER::VERTEX::COMPILATTION_FAILED\n"
              << infoLog << std::endl;
  }

  // fragment shader
  unsigned int framgmentShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
  glad_glShaderSource(framgmentShader, 1, &framgmentShaderSource, NULL);
  glad_glCompileShader(framgmentShader);
  // check for shader compile errors
  glad_glGetShaderiv(framgmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glad_glGetShaderInfoLog(framgmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPLATION_FAILED\n"
              << infoLog << std::endl;
  } //-------------------------------------------------------------------------------------------

  // link shades
  // -----------
  //着色器程序(Shader Program)
  unsigned int shaderProgram = glad_glCreateProgram();
  // glCreateProgram创建一个程序对象
  glad_glAttachShader(shaderProgram, vertexShader);
  //顶点把着色器附加到了程序上
  glad_glAttachShader(shaderProgram, framgmentShader);
  //片段把着色器附加到了程序上
  glad_glLinkProgram(shaderProgram); //然后用glLinkProgram链接它们
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramPipelineInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glad_glDeleteShader(vertexShader);
  glad_glDeleteShader(framgmentShader);
  //把着色器对象链接到程序对象以后,删除着色器对象

  // set up vertex date (and buffer(s)) and configure vertex attributes
  // (顶点属性)vertex attributes
  //-------------------------------------------------------------------
  float vertices[] = {
      0.7f,  0.0f,
      0.0f, // 1
      0.5f,  0.5f,
      0.0f, // 2
      0.0f,  0.7f,
      0.0f, // 3
      -0.5f, 0.5f,
      0.0f, // 4
      -0.7f, 0.0f,
      0.0f, // 5
      -0.5f, -0.5f,
      0.0f, // 6
      0.0f,  -0.7f,
      0.0f, // 7
      0.5f,  -0.5f,
      0.0f, // 8
  };

  unsigned int VBO, VAO;
  glad_glGenVertexArrays(1, &VAO); //创建一个VAO
  glad_glGenBuffers(1, &VBO);      //创建一个VBO
  //使用glGenBuffers函数和一个缓冲ID生成一个VBO对象
  /* bind the Vertex Array Object first ,then bind and vertex buffer(s),and then
 configure vertex attributes(s)配置顶点属性 */

  // ..:: 初始化代码（只运行一次 (除非你的物体频繁改变)） :: ..
  glad_glBindVertexArray(VAO); // 1. 绑定VAO
                               //
  // 2. 把顶点数组复制到缓冲中供OpenGL使用
  glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上：
  glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                    GL_STREAM_DRAW);
  // glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
  // OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
  // GL_STATIC_DRAW ：数据不会或几乎不会改变。

  // glVertexAttribPointer函数告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上）
  glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                             (void *)0); //----------------------????????****CX
  glad_glEnableVertexAttribArray(0);

  //
  glad_glBindBuffer(GL_ARRAY_BUFFER, 0);

  glad_glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {
    // input
    //------
    processInput(window);

    // render
    //-------
    glad_glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glad_glClear(GL_COLOR_BUFFER_BIT); // glClear函数来清空屏幕的颜色缓冲

    /*
  它接受一个缓冲位(BufferBit)来指定要清空的缓冲，可能的缓冲位有GL_COLOR_BUFFER_BIT，
  GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT。
  由于现在我们只关心颜色值，所以我们只清空颜色缓冲。
  */
    glad_glUseProgram(shaderProgram);
    glad_glBindVertexArray(VAO);
    glad_glDrawArrays(GL_TRIANGLES, 0, 3);
    /* glDrawArrays函数，它使用当前激活的着色器he之前定义的顶点属性配置，
      和VBO的顶点数据（通过VAO间接绑定）来绘制图元。
     */
    //第一个参数是我们打算绘制的OpenGL图元的类型TRIANGLES
    //第二个参数指定了顶点数组的起始索引，我们这里填0
    //最后一个参数指定我们打算绘制多少个顶点，这里是3
    glfwSwapBuffers(window);
    glfwPollEvents();
    /*glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、
      更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。*/
    /* glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲，
    它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
     */
  }
  glad_glDeleteVertexArrays(1, &VAO);
  glad_glDeleteBuffers(1, &VBO);
  glad_glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}

/*
我们通过顶点缓冲对象(Vertex Buffer Objects,
VBO)管理这个内存，它会在GPU内存（通常被称为显存）中储存大量顶点。
使用这些缓冲对象的好处是我们可以一次性的发送一大批数据到显卡上，而不是每个顶点发送一次。
从CPU把数据发送到显卡相对较慢，所以只要可能我们都要尝试尽量一次性发送尽可能多的数据。
当数据发送至显卡的内存中后，顶点着色器几乎能立即访问顶点，这是个非常快的过程。
*/