#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

int main() {
  std::cout << "Exercise 2" << std::endl;
  glm::vec4 v(6.0f, 6.0f, 3.0f, 1.0f);
  glm::vec3 u(9.0f, 8.0f, 5.0f);
  glm::mat4 trans(1.0f);
  glm::vec4 result;

  trans = glm::translate(trans, u);
  trans = glm::scale(trans, glm::vec3(-1.0f, -1.0f, -1.0f));
  result = trans * v;
  std::cout << "(a) u - v = [" << result.x << ", " << result.y << ", "
            << result.z << "]" << std::endl;

  trans = glm::translate(trans, u);
  trans = glm::scale(trans, glm::vec3(5.0f, 5.0f, 5.0f));
  result = trans * v;
  std::cout << "(b) u + 5v = [" << result.x << ", " << result.y << ", "
            << result.z << "]" << std::endl;

  std::cout << "\nExercise 5" << std::endl;
  u = glm::vec3(7.0f, 3.0f, 8.0f);
  std::cout << "|u| = " << glm::length(u) << std::endl;

  std::cout << "\nExercise 11" << std::endl;
  float proj =
      glm::dot(glm::vec2(9.0f, 4.0f), glm::vec2(1 / sqrt(2), 1 / sqrt(2)));
  std::cout << "Projection a = " << proj << std::endl;

  std::cout << "\nExercise 11" << std::endl;
  std::cout << "(c)" << std::endl;
  std::cout << "\nExercise 12" << std::endl;
  std::cout << "(a)" << std::endl;
  std::cout << "\nExercise 16" << std::endl;
  std::cout << "\nExercise 20" << std::endl;
  std::cout << "\nExercise 22" << std::endl;
  std::cout << "(a)" << std::endl;
}
