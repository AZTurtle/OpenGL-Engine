#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<vector>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<tuple>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include"assets/textures.h"

inline char shaderPath[MAX_CWD + 20];

template<typename... T>
struct uniforms{
    std::tuple<T...> vals;
    GLuint* locs;
    uniforms(T... u){
        vals = std::make_tuple(u...);
    }
};

template<typename... T>
struct staticUniforms{
    std::tuple<T...> vals;
    GLuint* locs;
    staticUniforms(T... u){
        vals = std::make_tuple(u...);
    }
};

class ShaderBase_{
    public:
        static std::vector<ShaderBase_*> shaders;
        virtual void load(GLuint, GLuint);
        virtual void bind();
        const char* vert;
        const char* frag;
};

template<class T, class S>
class ShaderBase : ShaderBase_{
    public:
        ShaderBase(const char* vert, const char* frag, std::vector<const char*> uniformNames, std::vector<const char*> staticUniformNames){
            this->uniformNames = uniformNames;
            this->staticUniformNames = staticUniformNames;
            this->vert = vert;
            this->frag = frag;
            shaders.push_back(this);
        }
        void load(GLuint vert, GLuint frag){
            GLint link = 0;
            char log[512];
            id = glCreateProgram();
            glAttachShader(id, vert);
            glAttachShader(id, frag);
            glLinkProgram(id);

            glGetProgramiv(id, GL_LINK_STATUS, &link);
            if(!link){
                glGetProgramInfoLog(id, 512, NULL, log);
                printf(log);
            }

            uniformLocs = new GLuint[uniformNames.size()];
            staticUniformLocs = new GLuint[staticUniformNames.size()];

            for(int i = 0; i < uniformNames.size(); i++){
                uniformLocs[i] = glGetUniformLocation(id, uniformNames[i]);
            }

            for(int i = 0; i < staticUniformNames.size(); i++){
                staticUniformLocs[i] = glGetUniformLocation(id, staticUniformNames[i]);
            }
        }
        void bind(){
            glUseProgram(id);
        }

        void setUniform(GLuint loc, float u) {glUniform1f(loc, u);}
        void setUniform(GLuint loc, glm::vec2 u) {glUniform2fv(loc, 1, glm::value_ptr(u));}
        void setUniform(GLuint loc, glm::vec3 u) {glUniform3fv(loc, 1, glm::value_ptr(u));}
        void setUniform(GLuint loc, glm::mat4 u) {glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(u));}
        void setUniform(GLuint loc, Texture u) {glBindTexture(GL_TEXTURE_2D, u.id);}

        std::vector<const char*> uniformNames;
        std::vector<const char*> staticUniformNames;
        GLuint* uniformLocs;
        GLuint* staticUniformLocs;
        GLuint id;
};

class Shader_{
    public:
        virtual void bind() = 0;
};


template<class Tu, class Su>
class Shader : public Shader_{
    public:
        Shader(ShaderBase<Tu,Su>& shader, Tu uniforms, Su staticUniforms) : 
        shader(shader), 
        uniforms(uniforms), 
        staticUniforms(staticUniforms)
        {
            shader.bind();
            setStaticUniforms(std::make_index_sequence<std::tuple_size_v<decltype(staticUniforms.vals)>>{});
            glUseProgram(0);
        }

        Shader(ShaderBase<Tu,Su>& shader) : 
        shader(shader)
        {
        }

        void bind(){
	        shader.bind();
            setUniforms(std::make_index_sequence<std::tuple_size_v<decltype(uniforms.vals)>>{});
        }

        void bind(Tu uniforms_){
            shader.bind();
            setUniforms(std::make_index_sequence<std::tuple_size_v<decltype(uniforms.vals_)>>{});
        }
    private:
        ShaderBase<Tu,Su>& shader;
        Tu uniforms;
        Su staticUniforms;
        template<std::size_t... i>
        void setUniforms(std::index_sequence<i...>){
            (shader.setUniform(shader.uniformLocs[i], *std::get<i>(uniforms.vals)), ...);
        }
        template<std::size_t... i>
        void setStaticUniforms(std::index_sequence<i...>){
            (shader.setUniform(shader.staticUniformLocs[i], *std::get<i>(staticUniforms.vals)), ...);
        }
};

GLuint loadShader(const char*, GLenum);

#endif