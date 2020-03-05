/*
 * This is a course assignment program for SUSTech CS312 Computer Graphics.
 *
 * Author: 艾君达
 * Student ID: 11711310
 *
 * Website references:
 * https://www.glfw.org
 * https://learnopengl.com/Getting-started/Hello-Window
 * https://stackoverflow.com/questions/2898503/background-colour-in-opengl
 *
 * Updated on 2020.2.18
 */

#define GLFW_INCLUDE_GLCOREARB
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

int main() {
  GLFWwindow* window;
  if (!glfwInit()) return -1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Online tutorial said the line below is needed for initialization on macOS.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  window = glfwCreateWindow(720, 540, "Hello OpenGL", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Uncomment the line below to make the window's background color blue.
    // glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
}
