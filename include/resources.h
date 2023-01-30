#ifndef RESOURCE_CLASS_H
#define RESOURCE_CLASS_H

#include "assets/shaders.h"
#include "assets/model.h"
#include "assets/textures.h"

namespace shaders{
	extern ShaderBase<uniforms<glm::mat4*, float*,Texture*>,staticUniforms<>> diffuse2D;
};

namespace models{

};

#endif