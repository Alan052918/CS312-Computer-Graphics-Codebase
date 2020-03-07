// A simple C++ program that illustrate 3 basic matrix-vector manipulations
// provided in GLM

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

int main() {
  glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);  // 4x1, w=1
  glm::mat4 trans;                        // manipulation matrix

  // 1. Scaling
  trans = glm::mat4(1.0f);           // initialize to 4x4 identity matrix
  trans = glm::scale(                // scales the given matrix
      trans,                         // glm::mat4 matrix
      glm::vec3(0.5f, 0.5f, 0.5f));  // glm::vec3 scale vector
  std::cout << vec.x << vec.y << vec.z << std::endl;

  // 2. Translation
  trans = glm::mat4(1.0f);           // initialize to 4x4 identity matrix
  trans = glm::translate(            // translate the given matrix
      trans,                         // glm::mat4 matrix
      glm::vec3(1.0f, 0.0f, 1.0f));  // glm::vec3 translation
  vec = trans * vec;                 // translate
  std::cout << vec.x << vec.y << vec.z << std::endl;

  // 3. Rotation
  trans = glm::mat4(1.0f);           // initialize to 4x4 identity matrix
  trans = glm::rotate(               // make the given matrix rotation matrix
      trans,                         // glm::mat4 matrix
      glm::radians(90.0f),           // GLfloat angle in radians
      glm::vec3(0.0f, 0.0f, 1.0f));  // glm::vec3 rotation_axis
  std::cout << vec.x << vec.y << vec.z << std::endl;
}
