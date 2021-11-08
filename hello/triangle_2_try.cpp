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
  // vertex shaderv
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
}
