#include "Shader.h"
#include <fstream>
#include <sstream>
/*************************************************/
/*�֐��� : LoadShader                            */
/*�߂�l : ����                                  */
/*����   : vertName(���_�V�F�[�_�[��)            */
/*����   : flagName(�t���O�����g�V�F�[�_�[��)    */
/*����   : �V�F�[�_�[�̃��[�h                    */
/*���l   : ����                                  */
/*************************************************/
bool Shader::LoadShader(const std::string& vertName, const std::string& flagName)
{
	if ((!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShaderID)) ||
		(!CompileShader(flagName, GL_FRAGMENT_SHADER, mFragShaderID)))
	{
		return false;
	}


	//���_/�t���O�����g�V�F�[�_�[�������N���ăV�F�[�_�[�v���O�������쐬����
	mShaderProgramID = glCreateProgram();
	glAttachShader(mShaderProgramID, mVertexShaderID);
	glAttachShader(mShaderProgramID, mFragShaderID);
	glLinkProgram(mShaderProgramID);

	if (!IsValidProgram())
	{
		return false;
	}

	return true;
}

/*************************************************/
/*�֐��� : UnloadShader                          */
/*�߂�l : ����                                  */
/*����   : �Ȃ�                                  */
/*����   : �V�F�[�_�[�̃A�����[�h                */
/*���l   : ����                                  */
/*************************************************/
void Shader::UnloadShader()
{
	//�v���O�������V�F�[�_�[�̏��ō폜����
	glDeleteProgram(mShaderProgramID);
	glDeleteShader(mVertexShaderID);
	glDeleteShader(mFragShaderID);
}

/*************************************************/
/*�֐��� : CompileShader                         */
/*�߂�l : ����                                  */
/*����   : fileName(�V�F�[�_�[�̃t�@�C����)      */
/*����   : shaderType(�V�F�[�_�[�̎��)          */
/*����   : outShader(�V�F�[�_�[�̃R���p�C������) */
/*����   : �V�F�[�_�[�̃R���p�C��                */
/*���l   : ����                                  */
/*************************************************/
bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	std::ifstream shaderFile(fileName);

	if (shaderFile.is_open())
	{
		std::stringstream sstream;

		//�S�e�L�X�g��1�̕�����Ƃ��ēǂݏo��
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		//�w�肳�ꂽ�V�F�[�_�[�^�C�v�̃V�F�[�_�[���쐬
		/* �׋��p�F�V�F�[�_�[�^�C�v�͈ȉ��̎�ނ�����                                                                 �@�@�@�@*/
		/* GL_VERTEX_SHADER    : ���_�������Ă���������Z����                                                       �@�@�@�@*/
		/* GL_FRAGMENT_SHADER  : �e�s�N�Z���̐F�̉��Z���s��                                                          �@�@�@�@ */
		/* GL_GEOMETRY_SHADER  : �v���~�e�B�u���Ƃ̏������s���C���C�V�����v���~�e�B�u�����o�����Ƃ��ł���V�F�[�_�@�@�@�@ */
		/* ���������肢���ƃo�[�e�b�N�X�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[�������ƍގ��\���ł��Ȃ����璆�Ԃ̃V�F�[�_�[��p���� */
		outShader = glCreateShader(shaderType);
		
		//�R���p�C���̎��s
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}
	return true;
}

/*************************************************/
/*�֐��� : IsCompiled                            */
/*�߂�l : ����                                  */
/*����   : shader(�V�F�[�_�[ID)                  */
/*����   : �V�F�[�_�[�̃R���p�C�������m�F        */
/*���l   : ����                                  */
/*************************************************/
bool Shader::IsCompiled(GLuint shader)
{
	GLint status;

	//�R���p�C���̗L����₢���킹��
	glGetShaderiv(shader,GL_COMPILE_STATUS,&status);

	if (status != GL_TRUE)
	{
		//�R���p�C���G���[�̌������o�͂���
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	return true;
}

/*************************************************/
/*�֐��� : SetShaderActive                       */
/*�߂�l : ����                                  */
/*����   : �Ȃ��@�@�@�@�@�@�@�@                  */
/*����   : �V�F�[�_�[�v���O�����̗L����          */
/*���l   : ����                                  */
/*************************************************/
void Shader::SetShaderActive()
{
	glUseProgram(mShaderProgramID);
}


/*************************************************/
/*�֐��� : IsValidProgram                        */
/*�߂�l : ����                                  */
/*����   : �Ȃ��@�@�@�@�@�@�@�@                  */
/*����   : �����N�̊����m�F�@�@�@�@�@�@�@        */
/*���l   : ����                                  */
/*************************************************/
bool Shader::IsValidProgram()
{
	GLint status;

	//�����N�̗L����₢���킹��
	glGetProgramiv(mShaderProgramID, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		//�R���p�C���G���[�̌������o�͂���
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgramID, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	return true;
}
