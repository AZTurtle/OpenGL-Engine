#include "resources.h"

namespace shaders{
	ShaderBase<uniforms<glm::mat4*, float*,Texture*>,staticUniforms<>> diffuse2D("2D_diffuse.vs","2D_diffuse.fs", {"matrix","color","tex"},{});
}

namespace models{
	
}