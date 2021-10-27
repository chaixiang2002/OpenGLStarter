#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // major version is 3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor version is 3
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    macOS needed

  /*  1.creat A window object   */
  GLFWwindow *window = glfwCreateWindow(
      800, 600, "CX's_window", NULL,
      NULL); // width ,height,window's name,Don't worry the rest parameters

  if (window == NULL) {
    std::cout << "Failed to create GLfw window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  /*  2.Init GlAD ,GLAD is used to manage OpenGl pointer functions  */
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to init GLAD" << std::endl;
    return -1;
  }
  /*我们给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数。
  GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。*/
  //  I don't know what he tell

  /*  VIEWport  */
  //  3.tell OpenGL the date and coordinates of window,configure the Dimension
  //  of window
  glViewport(0, 0, 800, 600); //  (0,0) set the coordinates in the lower right
                              //  corner of the window
}