#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 400;

// shader source code in GLSL
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

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

  // create glfw window
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Window", NULL, NULL);
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

  // Create vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // Attach shader source code to shader object and compile shader
  // replace the source code of a given shader object
  glShaderSource(
      vertexShader,         // shader object
      1,                    // string count
      &vertexShaderSource,  // array of pointers to strings of source code
      NULL);                // array of string lengths
  glCompileShader(vertexShader);

  // Check whether compilation is successful
  GLint success;
  GLchar infoLog[512];

  // query shader object information: compile status
  glGetShaderiv(vertexShader,       // shader object
                GL_COMPILE_STATUS,  // queried object parameter
                &success);          // returned object parameter
  if (!success) {
    glGetShaderInfoLog(vertexShader,  // shader object
                       512,           // max buffer size
                       NULL,          // info log length
                       infoLog);      // info log (char array)
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Create fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // check for compilation failure
  glGetShaderiv(fragmentShader,     // shader object
                GL_COMPILE_STATUS,  // queried object parameter
                &success);          // returned object parameter
  if (!success) {
    glGetShaderInfoLog(fragmentShader,  // shader object
                       512,             // max buffer size
                       NULL,            // info log length
                       infoLog);        // info log (char array)
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Create shader program and link shaders
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // check for link failure
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  GLfloat positions[] = {
      -0.5f, -0.5f, 0.0f,  // left
      0.5f,  -0.5f, 0.0f,  // right
      0.0f,  0.5f,  0.0f   // top
  };

  GLuint VAO;  // describe how vertex attributes are stored in VBO
  GLuint VBO;  // source for vertex array data
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

  // define an array of generic vertex attribute data
  glVertexAttribPointer(
      0,         // index of the generic vertex attribute to be modified
      3,         // number of components per generic vertex attribute
      GL_FLOAT,  // data type of each component
      GL_FALSE,  // specifies whether fixed-point data should be normalized
      sizeof(float) * 3,  // byte offset between consecutive attributes
      (void *)0);  // offset of the first component of the first attribute
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  while (!glfwWindowShouldClose(window)) {
    ProcessInput(window);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
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
