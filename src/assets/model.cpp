#include "assets/model.h"

Model_::Model_(const char* filepath) : filepath(filepath){
	models.push_back(this);
	printf("%i", models.size());
}

void Model_::load(){}
void Model_::loadModel(){}

Model_def::Model_def(const char* filepath) : Model_(filepath){}

void Model_def::load(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)0);
    glEnableVertexAttribArray(0);
}

void Model_def::loadModel(){
	char path[128];
	strcpy(path, modelPath);
	strcat(path, filepath);
    std::ifstream file(path);

	std::vector<glm::vec3> verts;
	std::vector<unsigned int> order;
	std::string line;
	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::string type = line.substr(0, 2);
			if (type == "v ") {
				std::stringstream line_s;
				line_s << line.substr(2, line.length());
				float vert[3];
				for (unsigned int i = 0; i < 3; i++) {
					line_s >> vert[i];
				}
				verts.push_back(glm::vec3(vert[0], vert[1], vert[2]));
			}
			else if (type == "f ") {
				line = line.substr(2, line.length());
				for (int i = 0; i < line.length(); i++) {
					if (line[i] == '/') {
						line[i] = ' ';
					}
				}
				std::stringstream line_s;
				line_s << line;
				for (unsigned int i = 0; i < 9; i++) {
					int x;
					line_s >> x;
					order.push_back(x);
				}
			}
		}
		file.close();
	} else {
		printf("Failed to open %s", path);
	}
    std::vector<Vert> vertData;
    std::vector<unsigned int> indData;
	for (unsigned int i = 0; i < order.size(); i++) {
		vertData.push_back(Vert{verts[order[i] - 1]});
		indData.push_back(i);
	}

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertData.size() * sizeof(Vert), vertData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indData.size() * sizeof(GLuint), indData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	indNum = indData.size();
}

Model_def_NT::Model_def_NT(const char* filepath) : Model_(filepath){
}

void Model_def_NT::load(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_NT), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_NT), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_NT), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Model_def_NT::loadModel(){
	char path[128];
	strcpy(path, modelPath);
	strcat(path, filepath);
    std::ifstream file(path);

	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> norms;
	std::vector<glm::vec2> texs;
	std::vector<unsigned int> order;
	std::string line;
	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::string type = line.substr(0, 2);
			if (type == "v ") {
				std::stringstream line_s;
				line_s << line.substr(2, line.length());
				float vert[3];
				for (unsigned int i = 0; i < 3; i++) {
					line_s >> vert[i];
				}
				verts.push_back(glm::vec3(vert[0], vert[1], vert[2]));
			}
			else if (type == "vn") {
				std::stringstream line_s;
				line_s << line.substr(2, line.length());
				float norm[3];
				for (unsigned int i = 0; i < 3; i++) {
					line_s >> norm[i];
				}
				norms.push_back(glm::vec3(norm[0], norm[1], norm[2]));
			}
			else if (type == "f ") {
				line = line.substr(2, line.length());
				for (int i = 0; i < line.length(); i++) {
					if (line[i] == '/') {
						line[i] = ' ';
					}
				}
				std::stringstream line_s;
				line_s << line;
				for (unsigned int i = 0; i < 9; i++) {
					int x;
					line_s >> x;
					order.push_back(x);
				}
			} 
            else if (type=="vt"){
				std::stringstream line_s;
				line_s << line.substr(2, line.length());
				float tex[2];
				for (unsigned int i = 0; i < 2; i++) {
					line_s >> tex[i];
				}
				texs.push_back(glm::vec2(tex[0], tex[1]));
            }
		}
		file.close();
	} else {
		printf("Failed to open %s", path);
	}
    std::vector<Vert_NT> vertData;
    std::vector<unsigned int> indData;
	for (unsigned int i = 0; i < order.size() / 3; i++) {
		unsigned int at = i * 3;
		bool found = false;
		for(int x = 0; x < vertData.size(); x++){
			if(vertData[x].pos == verts[order[at] - 1] && vertData[x].uv == texs[order[at + 1] - 1] && vertData[x].norm == norms[order[at + 2] - 1]){
				indData.push_back(x);
				found = true;
				break;
			}
		}
		if(!found){
			vertData.push_back(Vert_NT{verts[order[at] - 1], norms[order[at + 2] - 1], texs[order[at + 1] - 1] });
			indData.push_back(vertData.size() - 1);
		}
	}

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertData.size() * sizeof(Vert_NT), vertData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indData.size() * sizeof(GLuint), indData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	indNum = indData.size();
}

Model_def_N::Model_def_N(const char* filepath) : Model_(filepath){}

void Model_def_N::load(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_N), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_N), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Model_def_N::loadModel(){
	char path[128];
	strcpy(path, modelPath);
	strcat(path, filepath);
    std::ifstream file(path);

	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> norms;
	std::vector<unsigned int> order;
	std::string line;
	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::string type = line.substr(0, 2);
			if (type == "v ") {
				std::stringstream line_s;
				line_s << line.substr(2, line.length());
				float vert[3];
				for (unsigned int i = 0; i < 3; i++) {
					line_s >> vert[i];
				}
				verts.push_back(glm::vec3(vert[0], vert[1], vert[2]));
			}
			else if (type == "vn") {
				std::stringstream line_s;
				line_s << line.substr(2, line.length());
				float norm[3];
				for (unsigned int i = 0; i < 3; i++) {
					line_s >> norm[i];
				}
				norms.push_back(glm::vec3(norm[0], norm[1], norm[2]));
			}
			else if (type == "f ") {
				line = line.substr(2, line.length());
				for (int i = 0; i < line.length(); i++) {
					if (line[i] == '/') {
						line[i] = ' ';
					}
				}
				std::stringstream line_s;
				line_s << line;
				for (unsigned int i = 0; i < 6; i++) {
					int x;
					line_s >> x;
					order.push_back(x);
				}
			}
		}
		file.close();
	} else {
		printf("Failed to open %s", path);
	}
    std::vector<Vert_N> vertData;
    std::vector<unsigned int> indData;
	for (unsigned int i = 0; i < order.size() / 2; i++) {
		unsigned int at = i * 2;
		bool found = false;
		for(int x = 0; x < vertData.size(); x++){
			if(vertData[x].pos == verts[order[at] - 1] && vertData[x].norm == norms[order[at + 1] - 1]){
				indData.push_back(x);
				found = true;
				break;
			}
		}
		if(!found){
			vertData.push_back(Vert_N{verts[order[at] - 1], norms[order[at + 1] - 1]});
			indData.push_back(vertData.size() - 1);
		}
	}

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertData.size() * sizeof(Vert_N), vertData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indData.size() * sizeof(GLuint), indData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	indNum = indData.size();
}

Model_def_T::Model_def_T(const char* filepath) : Model_(filepath){}

void Model_def_T::load(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_T), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_T), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Model_def_T::loadModel(){
	char path[128];
	strcpy(path, modelPath);
	strcat(path, filepath);
    std::ifstream file(path);

	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> texs;
	std::vector<unsigned int> order;
	std::string line;
	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::string type = line.substr(0, 2);
			if (type == "v ") {
				std::stringstream line_s;
				line_s << line.substr(2, line.length());
				float vert[3];
				for (unsigned int i = 0; i < 3; i++) {
					line_s >> vert[i];
				}
				verts.push_back(glm::vec3(vert[0], vert[1], vert[2]));
			}
			else if (type == "f ") {
				line = line.substr(2, line.length());
				for (int i = 0; i < line.length(); i++) {
					if (line[i] == '/') {
						line[i] = ' ';
					}
				}
				std::stringstream line_s;
				line_s << line;
				for (unsigned int i = 0; i < 9; i++) {
					int x;
					line_s >> x;
					order.push_back(x);
				}
			} 
            else if (type=="vt"){
				std::stringstream line_s;
				line_s << line.substr(2, line.length());
				float tex[2];
				for (unsigned int i = 0; i < 2; i++) {
					line_s >> tex[i];
				}
				texs.push_back(glm::vec2(tex[0], tex[1]));
            }
		}
		file.close();
	} else {
		printf("Failed to open %s", path);
	}
    std::vector<Vert_T> vertData;
    std::vector<unsigned int> indData;
	for (unsigned int i = 0; i < order.size() / 2; i++) {
		unsigned int at = i * 2;
		for(int x = 0; x < indData.size(); x++){
			if(vertData[x].pos == verts[order[at] - 1 && vertData[x].uv == texs[order[at + 1] - 1]]){
				indData.push_back(x);
				continue;
			}
		}
		vertData.push_back(Vert_T{verts[order[at] - 1], texs[order[at + 1] - 1] });
		indData.push_back(vertData.size());
	}

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertData.size() * sizeof(Vert_T), vertData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indData.size() * sizeof(GLuint), indData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	indNum = indData.size();
}

Model::Model(Model_* model){
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
    model->load();
	indNum = model->indNum;
}

void Model::render(){
    glBindVertexArray(id);
	glDrawElements(GL_TRIANGLES, indNum, GL_UNSIGNED_INT, 0);
}