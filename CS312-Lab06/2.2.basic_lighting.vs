/**
 * Title: 2.2.basic_lighting.vs
 * Author: Joey de Vries (twitter handle https://twitter.com/JoeyDeVriez)
 * Source: https://learnopengl.com
 * https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.2.basic_lighting_specular/2.2.basic_lighting.vs
 * License: CC BY-NC 4.0 (https://creativecommons.org/licenses/by-nc/4.0/)
 */
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
