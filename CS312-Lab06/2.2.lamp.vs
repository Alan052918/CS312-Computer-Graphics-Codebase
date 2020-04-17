/**
 * Title: 2.2.lamp.vs
 * Author: Joey de Vries (twitter handle https://twitter.com/JoeyDeVriez)
 * Source: https://learnopengl.com
 * https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.2.basic_lighting_specular/2.2.lamp.vs
 * License: CC BY-NC 4.0 (https://creativecommons.org/licenses/by-nc/4.0/)
 */
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}
