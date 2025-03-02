#pragma once
#ifndef SHADER_H
#define SHADER_H
#include "Lib.h"

class Shader
{
public:
	//コンストラクタ
	Shader() {};
	//デストラクタ
	~Shader() {};

	bool LoadShader(const std::string& vertName, const std::string& flagName);
	void UnloadShader();
	//セッター
	void SetShaderActive();
private:

	bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram();

	GLuint mVertexShaderID;  
	GLuint mFragShaderID;
	GLuint mShaderProgramID;
};

#endif#pragma once
