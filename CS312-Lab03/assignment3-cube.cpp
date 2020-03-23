#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 400;

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
    "layout(location = 1) in vec3 vertexColor;\n"
    "out vec3 fragmentColor;\n"
    "uniform mat4 MVP;\n"
    "void main() {\n"
    "  gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n"
    "  fragmentColor = vertexColor;\n"
    "}\0";
const char *fragmentShaderSource =
    "#version 330 core\n"
    "in vec3 fragmentColor;\n"
    "out vec3 color;\n"
    "void main() {\n"
    "  color = fragmentColor;\n"
    "}\0";

void FramebufferSizeCallback(GLFWwindow *, int, int);

void ProcessInput(GLFWwindow *);

int main() {
  // initialize and configure GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // create window
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cube", NULL, NULL);
  if (!window) {
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

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  GLint success;
  GLchar infoLog[512];

  // create vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // create fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // create shader program
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

  GLuint matrix = glGetUniformLocation(shaderProgram, "MVP");
  glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
  glm::mat4 View = glm::lookAt(
      glm::vec3(4, 3, -3),  // Camera is at (4,3,-3), in World Space
      glm::vec3(0, 0, 0),   // and looks at the origin
      glm::vec3(0, 1, 0)    // Head is up (set to 0,-1,0 to look upside-down)
  );
  glm::mat4 Model = glm::mat4(1.0f);
  glm::mat4 MVP = projection * View * Model;

  GLfloat positions[] = {
      -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f,
      1.0f,  -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f,
      1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
      1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,
      1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,
      1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,
      1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f};
  GLfloat colors[] = {
      0.583f, 0.771f, 0.014f, 0.609f, 0.115f, 0.436f, 0.327f, 0.483f, 0.844f,
      0.822f, 0.569f, 0.201f, 0.435f, 0.602f, 0.223f, 0.310f, 0.747f, 0.185f,
      0.597f, 0.770f, 0.761f, 0.559f, 0.436f, 0.730f, 0.359f, 0.583f, 0.152f,
      0.483f, 0.596f, 0.789f, 0.559f, 0.861f, 0.639f, 0.195f, 0.548f, 0.859f,
      0.014f, 0.184f, 0.576f, 0.771f, 0.328f, 0.970f, 0.406f, 0.615f, 0.116f,
      0.676f, 0.977f, 0.133f, 0.971f, 0.572f, 0.833f, 0.140f, 0.616f, 0.489f,
      0.997f, 0.513f, 0.064f, 0.945f, 0.719f, 0.592f, 0.543f, 0.021f, 0.978f,
      0.279f, 0.317f, 0.505f, 0.167f, 0.620f, 0.077f, 0.347f, 0.857f, 0.137f,
      0.055f, 0.953f, 0.042f, 0.714f, 0.505f, 0.345f, 0.783f, 0.290f, 0.734f,
      0.722f, 0.645f, 0.174f, 0.302f, 0.455f, 0.848f, 0.225f, 0.587f, 0.040f,
      0.517f, 0.713f, 0.338f, 0.053f, 0.959f, 0.120f, 0.393f, 0.621f, 0.362f,
      0.673f, 0.211f, 0.457f, 0.820f, 0.883f, 0.371f, 0.982f, 0.099f, 0.879f};

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &MVP[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
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
