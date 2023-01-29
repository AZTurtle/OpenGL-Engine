#include "resources.h"

namespace shaders{
	ShaderBase<uniforms<glm::mat4*, float*,Texture*>,staticUniforms<>> diffuse2D("2D_diffuse.vs","2D_diffuse.fs", {"matrix","color","tex"},{});
	ShaderBase<uniforms<glm::mat4*>,staticUniforms<>> diffuse("diffuse.vs","diffuse.fs",{"camMatrix"},{});
	ShaderBase<uniforms<glm::mat4*>,staticUniforms<>> letterShader("letter.vs","letter.fs",{"camMatrix"},{});
	ShaderBase<uniforms<glm::mat4*, Texture*>,staticUniforms<glm::mat4*>> textured("textured.vs","textured.fs",{"camMatrix","tex"},{"objMatrix"});
	ShaderBase<uniforms<float*>,staticUniforms<>> fadeShader("fade.vs","fade.fs",{"fade"},{});
}

namespace models{
	Model_def_N letters[] = {
		Model_def_N("letters\\A.obj"),
		Model_def_N("letters\\B.obj"),
		Model_def_N("letters\\C.obj"),
		Model_def_N("letters\\D.obj"),
		Model_def_N("letters\\E.obj"),
		Model_def_N("letters\\F.obj"),
		Model_def_N("letters\\G.obj"),
		Model_def_N("letters\\H.obj"),
		Model_def_N("letters\\I.obj"),
		Model_def_N("letters\\J.obj"),
		Model_def_N("letters\\K.obj"),
		Model_def_N("letters\\L.obj"),
		Model_def_N("letters\\M.obj"),
		Model_def_N("letters\\N.obj"),
		Model_def_N("letters\\O.obj"),
		Model_def_N("letters\\P.obj"),
		Model_def_N("letters\\Q.obj"),
		Model_def_N("letters\\R.obj"),
		Model_def_N("letters\\S.obj"),
		Model_def_N("letters\\T.obj"),
		Model_def_N("letters\\U.obj"),
		Model_def_N("letters\\V.obj"),
		Model_def_N("letters\\W.obj"),
		Model_def_N("letters\\X.obj"),
		Model_def_N("letters\\Y.obj"),
		Model_def_N("letters\\Z.obj")
	};
	Model_def_NT l1("l1.obj");
	Model_def_NT table("table.obj");
}