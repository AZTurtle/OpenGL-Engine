#include"assets/shaders.h"

std::vector<ShaderBase_*> ShaderBase_::shaders;

std::string getFileContents(const char* filepath){
	std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string fileData;
    try{
        file.open(filepath, std::ios::binary);
        std::stringstream dataStream;
        dataStream << file.rdbuf();
        fileData = dataStream.str();
        file.close();   
    } catch(std::ifstream::failure err){
        std::cout << filepath << " failed to open" << std::endl;
    }
	return fileData;
}

GLuint loadShader(const char* filepath, GLenum type){
	GLuint id = glCreateShader(type);
	std::string fileString = getFileContents(filepath);
	const char* fileData = fileString.c_str();
	glShaderSource(id, 1, &fileData, NULL);
	glCompileShader(id);
	GLint compiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
	char log[218];
	if(compiled == GL_FALSE){
		glGetShaderInfoLog(id, 218, NULL, log);
		printf("Shader %s failed to compile : %s", filepath, log);
	}
	return id;
}

void ShaderBase_::load(GLuint vert, GLuint frag){};
void ShaderBase_::bind(){};