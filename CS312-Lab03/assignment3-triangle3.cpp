#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 400;

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderCyanSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";
const char *fragmentShaderClementineSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.7f, 0.3f, 0.2f, 1.0f);\n"
    "}\n\0";

void FramebufferSizeCallback(GLFWwindow *, int, int);

void ProcessInput(GLFWwindow *);

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // create GLFW window
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                        "Colored dual triangle", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    exit(EXIT_FAILURE);
  }

  // define and compile vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // define and compile cyan fragment shader
  GLuint fragmentShaderCyan = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderCyan, 1, &fragmentShaderCyanSource, NULL);
  glCompileShader(fragmentShaderCyan);

  // define and compile clementine fragment shader
  GLuint fragmentShaderClementine = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderClementine, 1, &fragmentShaderClementineSource,
                 NULL);
  glCompileShader(fragmentShaderClementine);

  // create cyan shader program
  GLuint shaderProgramCyan = glCreateProgram();
  glAttachShader(shaderProgramCyan, vertexShader);
  glAttachShader(shaderProgramCyan, fragmentShaderCyan);
  glLinkProgram(shaderProgramCyan);

  // create clementine shader
  GLuint shaderProgramClementine = glCreateProgram();
  glAttachShader(shaderProgramClementine, vertexShader);
  glAttachShader(shaderProgramClementine, fragmentShaderClementine);
  glLinkProgram(shaderProgramClementine);

  GLfloat triangleCyan[] = {
      -0.9f,  -0.5f, 0.0f,  // left
      -0.0f,  -0.5f, 0.0f,  // right
      -0.45f, 0.5f,  0.0f,  // top
  };
  GLfloat triangleClementine[] = {
      0.0f,  -0.5f, 0.0f,  // left
      0.9f,  -0.5f, 0.0f,  // right
      0.45f, 0.5f,  0.0f   // top
  };

  GLuint VBOs[2], VAOs[2];
  glGenBuffers(2, VBOs);
  glGenVertexArrays(2, VAOs);

  // create cyan vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangleCyan), triangleCyan,
               GL_STATIC_DRAW);

  // create cyan vertex array object corresponding with the cyan VBO
  glBindVertexArray(VAOs[0]);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(0);

  // create clementine vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangleClementine), triangleClementine,
               GL_STATIC_DRAW);

  // create clementine vertex array object
  glBindVertexArray(VAOs[1]);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    ProcessInput(window);

    // draw cyan triangle
    glUseProgram(shaderProgramCyan);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // draw clementine triangle
    glUseProgram(shaderProgramClementine);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // poll I/O events and swap buffer
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glfwDestroyWindow(window);
  glfwTerminate();
}

void ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
