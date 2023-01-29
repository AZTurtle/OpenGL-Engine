#ifndef RESOURCE_CLASS_H
#define RESOURCE_CLASS_H

#include "assets/shaders.h"
#include "assets/model.h"
#include "assets/textures.h"

namespace shaders{
	extern ShaderBase<uniforms<glm::mat4*, float*,Texture*>,staticUniforms<>> diffuse2D;
	extern ShaderBase<uniforms<glm::mat4*>,staticUniforms<>> diffuse;
	extern ShaderBase<uniforms<glm::mat4*>,staticUniforms<>> letterShader;
	extern ShaderBase<uniforms<glm::mat4*, Texture*>,staticUniforms<glm::mat4*>> textured;
	extern ShaderBase<uniforms<float*>,staticUniforms<>> fadeShader;
};

namespace models{
	extern Model_def_N letters[26];
	extern Model_def_NT l1;
	extern Model_def_NT table;
};

#endif