#pragma once
#ifndef VERTEXARRY_H
#define VERTEXARRY_H
#include "Lib.h"

class VertexArray
{
public:
	//�R���X�g���N�^
	VertexArray(const F32* verts, U16 numVerts,
		const U16* indices,U16 numIndices );
	//�f�X�g���N�^
	~VertexArray();

	//�Z�b�^�[
	void SetVertexActive();

	//�Q�b�^�[
	U16 GetNumIndices() const { return mNumIndices; };
	U16 GetNumVerts() const { return mNumVerts; };


private:

	U32 mNumVerts;            //���_�o�b�t�@�ɂ��钸�_�̐�
	U32 mNumIndices;          //�C���f�b�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐�
	U32 mVertexBufferID;      //���_�o�b�t�@��OpenGL ID
	U32 mIndexBufferID;       //�C���f�b�N�X�o�b�t�@��OpenGL ID
	U32 mVertexArrayID;       //���_�z��I�u�W�F�N�g��OpenGL ID

};

#endif