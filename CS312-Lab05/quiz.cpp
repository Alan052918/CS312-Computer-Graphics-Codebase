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
const char *fragmentShaderSource =
    "#version 330 core\n"
    "in vec3 fragmentColor;\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "   color = fragmentColor;\n"
    "}\0";

void FramebufferSizeCallback(GLFWwindow *, int, int);

void ProcessInput(GLFWwindow *);

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Colored Rectangle", NULL, NULL);
  if (!window) {
    std::cout << "Failed ot create GLFW window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    exit(EXIT_FAILURE);
  }

  GLint success;
  GLchar infoLog[512];

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  GLfloat positions[] = {
      0.5f,  -0.5f, 0.0f,  // bottom right
      0.5f,  0.5f,  0.0f,  // top right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f, 0.5f,  0.0f   // top right
  };
  GLfloat colors[] = {
      0.5f, 0.5f, 0.5f,  // first color
      0.3f, 0.5f, 0.7f,  // second color
      0.1f, 0.5f, 0.9f,  // thrid color
      0.0f, 0.5f, 0.5f   // fourth color
  };

  GLuint posBuffer;
  glGenBuffers(1, &posBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

  GLuint posArray;
  glGenVertexArrays(1, &posArray);
  glBindVertexArray(posArray);

  GLuint colorBuffer;
  glGenBuffers(1, &colorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

  GLuint colorArray;
  glGenVertexArrays(1, &colorArray);
  glBindVertexArray(colorArray);

  while (!glfwWindowShouldClose(window)) {
    ProcessInput(window);
    glUseProgram(shaderProgram);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glDrawArrays(GL_TRIANGLES, 0, 4 * 3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  glDeleteProgram(shaderProgram);
  glDeleteVertexArrays(1, &colorArray);
  glDeleteVertexArrays(1, &posArray);
  glDeleteBuffers(1, &colorBuffer);
  glDeleteBuffers(1, &posBuffer);
  glfwDestroyWindow(window);
  glfwTerminate();
}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}
