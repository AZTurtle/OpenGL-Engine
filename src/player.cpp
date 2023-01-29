#include"player.h"

bool hasLetters = true;

Player::Player(Camera* cam):
letterShader(new Shader(shaders::diffuse, uniforms(&cam->matrix), staticUniforms())),
pos_u(glGetUniformLocation(shaders::diffuse.id, "objMatrix"))
{
    
}

void Player::prepModel(const char* word, glm::ivec3 startPos){
	hasLetters = true;
	this->word = word;
	wordLen = strlen(word);
	for(unsigned short i = 0; i < wordLen; i++){
		body.push_back(new letterTile(startPos,glm::vec3(0.6f, 0.6f, 0.6f),word[i],false,true));
		startPos.x -= 1;
	}
}

void Player::move(glm::ivec3 shift){
	if(hasLetters){
		update();
		body[0]->pos += shift;
		body[0]->transform = glm::translate(glm::mat4(1.0f), glm::vec3(-body[0]->pos.x, body[0]->pos.y, -body[0]->pos.z));
	}
	if(body.size() == 0){
		hasLetters = false;
	}
}

void Player::update(){
	for(unsigned short i = wordLen - 1; i > 0; i--){
		body[i]->pos = body[i - 1]->pos;
	}
}

void Player::clearWords(){
	int num = 0;
	for(int i = 0; i < body.size(); i++){
		if(body[i]->chained){
			num++;
		}
	}
	for(int i = 0; i < body.size(); i++){
		if(body[i]->chained){
			if(i + num < body.size()){
				body[i + num]->pos = body[i]->pos;
			}
		}
	}
	for(int i = 0; i < body.size(); i++){
		if(body[i]->chained){
			body.erase(body.begin() + i);
			i--;
		}
	}
	if(body.size() == 0){
		hasLetters = false;
	}
}




/*
glm::vec2* generateUnitCircle(){
	glm::vec2* circle = new glm::vec2[RING_RES];
	const float angle_diff = 360.0f / RING_RES;
	for(int i = 0; i < RING_RES; i++){
		float angle = angle_diff * i;
		circle[i] = glm::vec2(glm::sin(glm::radians(angle)),glm::cos(glm::radians(angle)));
	}
	return circle;
}

const glm::vec2* unitCircle = generateUnitCircle();

void Player::prepModel(int segments){
    
	const unsigned short VERT_NUM = (2 * END_VERTS) + (SEG_VERTS * (segments + 2)) + RING_RES;
	verts = new Vert_N[VERT_NUM];
	verts[0] = Vert_N{glm::vec3(0.0f, 0.0f, -1.0f),glm::vec3(0.0f, 0.0f, -1.0f)};

	//FACE VERTS

	for(int x = 1; x < RING_RES + 1; x++){
		glm::vec3 pos = glm::vec3(unitCircle[x - 1] * 0.3826834324f, -0.9238795325f);
		glm::vec3 norm = glm::vec3(unitCircle[x - 1], -0.9238795325f);
		verts[x] = Vert_N{pos, norm}; 
		inds.push_back(0);
		inds.push_back(x);
		if(x+1 < 17){
			inds.push_back(x+1);
		} else {
			inds.push_back(1);
		}
	}

	//SEGMENT VERTS

	for(int segment = 0; segment < segments + 2; segment++){
		for(int ring = 0; ring < RING_NUM; ring++){
			unsigned short offset = END_VERTS + (SEG_VERTS * segment) + (RING_RES * ring);
			float z_offset = (SEG_OFFSET * (segment)) + unitCircle[ring + 10].y;
			for(int x = 0; x < RING_RES; x++){
				glm::vec3 pos = glm::vec3(unitCircle[x] * glm::abs(unitCircle[ring + 2].x), z_offset);
				if(segment > 0 && ring > 0){
					glm::vec3 norm = glm::vec3(unitCircle[x], SEG_NORMS[ring]);
					verts[x + offset] = Vert_N{pos, norm}; 
				} else {
					glm::vec3 norm = glm::vec3(unitCircle[x], -0.7071067812f);
					verts[x + offset] = Vert_N{pos, norm}; 
				}
				inds.push_back(x + offset);
				if(x+1 < 16){
					inds.push_back(x + 1 + offset);
					inds.push_back(x - 15 + offset);
					inds.push_back(x - 15 + offset);
					inds.push_back(x - 16 + offset);
					inds.push_back(x + offset);
				} else {
					inds.push_back(offset);
					inds.push_back(-1 + offset);
					inds.push_back(offset);
					inds.push_back(-16 + offset);
					inds.push_back(-1 + offset);
				}
			}
		}
	}

	//TAIL VERTS
	
	const float TAIL_Z_OFFSET = SEG_OFFSET * (segments + 1);
	verts[VERT_NUM - 1] = Vert_N{glm::vec3(0.0f, 0.0f, TAIL_Z_OFFSET + 1.0f),glm::vec3(0.0f, 0.0f, 1.0f)};

	for(int segment = 0; segment < 2; segment++){
		unsigned short offset = VERT_NUM - END_VERTS - ((1 - segment) * RING_RES);
		for(int x = 0; x < RING_RES; x++){
			glm::vec3 pos = glm::vec3(unitCircle[x] * unitCircle[segment + 2].y, TAIL_Z_OFFSET + unitCircle[segment + 2].x);
			glm::vec3 norm = glm::vec3(unitCircle[x], unitCircle[segment + 2].x);
			verts[x + offset] = Vert_N{pos, norm}; 
			inds.push_back(x + offset);
			if(x+1 < 16){
				inds.push_back(x + 1 + offset);
				inds.push_back(x - 15 + offset);
				inds.push_back(x - 15 + offset);
				inds.push_back(x - 16 + offset);
				inds.push_back(x + offset);
			} else {
				inds.push_back(offset);
				inds.push_back(-1 + offset);
				inds.push_back(offset);
				inds.push_back(-16 + offset);
				inds.push_back(-1 + offset);
			}
		}
	}

	unsigned short offset = VERT_NUM - END_VERTS;
	for(int x = 0; x < RING_RES; x++){
		if(x+1 < 16){
			inds.push_back(x + 1 + offset);
			inds.push_back(x + offset);
			inds.push_back(VERT_NUM - 1);
		} else {
			inds.push_back(offset);
			inds.push_back(x + offset);
			inds.push_back(x + 1 + offset);
		}
	}
	
	vao.bindVertexBuffer(verts, VERT_NUM, GL_STATIC_DRAW);
	vao.bindIndexBuffer(inds, GL_STATIC_DRAW);

	vao.addAttribute<Vert_N>(0, 3, GL_FLOAT, 0);
	vao.addAttribute<Vert_N>(1, 3, GL_FLOAT, (void*)(3 * sizeof(float)));
}
*/