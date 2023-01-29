#include"assets/assets.h"


void Assets::load(){


	for(std::filesystem::directory_entry path : std::filesystem::recursive_directory_iterator(texturePath)){
		if(!path.is_regular_file()) continue;
		std::string path_string = path.path().generic_string();
		textures[path_string.c_str() + strlen(CWD) + 20] = loadTexture(path_string.c_str());
	}
	for(std::filesystem::path path : std::filesystem::recursive_directory_iterator(shaderPath)){
		if(!path.has_extension()) continue;
		std::string path_string = path.generic_string();
		const char* path_char = path_string.c_str();
		if(path.extension() == ".vs"){
			vertexShaders[path_char + strlen(CWD) + 19] = loadShader(path_char, GL_VERTEX_SHADER);
		} else if(path.extension() == ".fs"){
			fragmentShaders[path_char + strlen(CWD) + 19] = loadShader(path_char, GL_FRAGMENT_SHADER);
		}
	}
	printf("%i",Model_::models.size());
	for(auto model : Model_::models){
		model->loadModel();
	}
	printf("%i",ShaderBase_::shaders.size());
	for(auto shader : ShaderBase_::shaders){
		shader->load(getVertexShader(shader->vert), getFragmentShader(shader->frag));
	}
}

Texture* Assets::getTexture(const char* filename){
	return &textures[filename];
}

GLuint Assets::getVertexShader(const char* shader){
	return vertexShaders[shader];
}

GLuint Assets::getFragmentShader(const char* shader){
	return fragmentShaders[shader];
}