#ifndef LEVEL_DEF_CLASS_H
#define LEVEL_DEF_CLASS_H

#include"level.h"
#include"resources.h"

namespace levels{
	struct l1 : level{
		Model levelModel = Model(&models::l1);
		Shader_* levelShader = new Shader(shaders::textured, uniforms(&cam->matrix,assets.getTexture("paperl1.png")), staticUniforms(&lTransform));
		void draw(){
			level::draw();
			levelShader->bind();
			levelModel.render();
		}
		void drawTransparent(){

		}
		void update(){
			level::update();
		}
		void restart(){
			level::restart();
			player.prepModel("at", glm::vec3(3.0f, 0.0f, 7.0f));
			for(int i = 0; i < player.body.size(); i++){
				letters.push_back(player.body[i]);
			}
			addLetter('c', glm::vec3(12.0f, 0.0f, 6.0f));
			checkWords();
		}
		l1(Camera* cam, bool* levelComplete): level(40.0f, cam, 16, 16, 1, {
			"cat","act"
		},levelComplete)
		{
			restart();
		}
	};
	struct l2 : level{
		Model levelModel = Model(&models::l1);
		Shader_* levelShader = new Shader(shaders::textured, uniforms(&cam->matrix,assets.getTexture("paperl2.png")), staticUniforms(&lTransform));
		void draw(){
			level::draw();
			levelShader->bind();
			levelModel.render();
		}
		void drawTransparent(){

		}
		void update(){
			level::update();
		}
		void restart(){
			level::restart();
			player.prepModel("cart", glm::vec3(4.0f, 0.0f, 7.0f));
			for(int i = 0; i < player.body.size(); i++){
				letters.push_back(player.body[i]);
			}
			addLetter('l', glm::vec3(7.0f, 0.0f, 4.0f));
			addLetter('e', glm::vec3(5.0f, 0.0f, 0.0f));
			addTile(glm::ivec3(6.0f, 0.0f, 6.0f));
			addTile(glm::ivec3(5.0f, 0.0f, 6.0f));
			addTile(glm::ivec3(6.0f, 0.0f, 5.0f));
			addTile(glm::ivec3(5.0f, 0.0f, 5.0f));
			addTile(glm::ivec3(6.0f, 0.0f, 4.0f));
			addTile(glm::ivec3(5.0f, 0.0f, 4.0f));
			addTile(glm::ivec3(4.0f, 0.0f, 4.0f));
			addTile(glm::ivec3(4.0f, 0.0f, 6.0f));
			addTile(glm::ivec3(4.0f, 0.0f, 5.0f));
			checkWords();
		}
		l2(Camera* cam, bool* levelComplete): level(45.0f, cam, 8, 8, 1, {
			"cartle","car","cart","alert","alter","clear","lent","let","arc","ear","eat","react","trace","cater","crate"
		},levelComplete)
		{
			restart();
		}
	};
	struct l3 : level{
		Model levelModel = Model(&models::l1);
		Shader_* levelShader = new Shader(shaders::textured, uniforms(&cam->matrix,assets.getTexture("paperl3.png")), staticUniforms(&lTransform));
		void draw(){
			level::draw();
			levelShader->bind();
			levelModel.render();
		}
		void drawTransparent(){

		}
		void update(){
			level::update();
		}
		void restart(){
			level::restart();
			player.prepModel("ploint", glm::vec3(5.0f, 0.0f, 5.0f));
			for(int i = 0; i < player.body.size(); i++){
				letters.push_back(player.body[i]);
			}
			addLetter('t', glm::vec3(0.0f, 0.0f, 0.0f));
			checkWords();
		}
		l3(Camera* cam, bool* levelComplete): level(45.0f, cam, 6, 6, 1, {
			"point","pint","lot","plot","alter","clear","lent","let","arc","ear","eat","react","trace","cater","crate"
		},levelComplete)
		{
			restart();
		}
	};
};

#endif