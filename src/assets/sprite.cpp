#include"assets/sprite.h"

Assets& assets = Assets::getAssets();

Sprite::Sprite(const char* file, glm::mat4* transform, Camera* cam, float* color){
    img = assets.getTexture(file);
    shader = new Shader(shaders::diffuse2D, uniforms{transform, color, img}, staticUniforms{});
    float w = img->w / 2.0f, h = img->h / 2.0f;
    if(w > h){
        h /= w;
        w = 1.0f;
    } else {
        w /= h;
        h = 1.0f;
    }
    verts[0] = Vert_T_2D{glm::vec2(-w,-h),glm::vec2(0.0f,0.0f)};
    verts[1] = Vert_T_2D{glm::vec2(-w,h),glm::vec2(0.0f,1.0f)};
    verts[2] = Vert_T_2D{glm::vec2(w,h),glm::vec2(1.0f,1.0f)};
    verts[3] = Vert_T_2D{glm::vec2(w,-h),glm::vec2(1.0f,0.0f)};
    vao.bindVertexBuffer(verts, 4, GL_STATIC_DRAW);
    vao.bindIndexBuffer(INDS, 6, GL_STATIC_DRAW);
    vao.addAttribute<Vert_T_2D>(0, 2, GL_FLOAT, 0);
    vao.addAttribute<Vert_T_2D>(1, 2, GL_FLOAT, (void*)(2*sizeof(float)));
}

void Sprite::draw(){
    shader->bind();
	vao.bind();
    glDrawElements(GL_TRIANGLES, vao.indNum, GL_UNSIGNED_SHORT, 0);
}