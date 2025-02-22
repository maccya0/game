#pragma once
#ifndef VERTEXARRY_H
#define VERTEXARRY_H
#include "Lib.h"

class VertexArray
{
public:
	//コンストラクタ
	VertexArray(const F32* verts, U16 numVerts,
		const U16* indices,U16 numIndices );
	//デストラクタ
	~VertexArray();

	//セッター
	void SetVertexActive();

	//ゲッター
	U16 GetNumIndices() const { return mNumIndices; };
	U16 GetNumVerts() const { return mNumVerts; };


private:

	U32 mNumVerts;            //頂点バッファにある頂点の数
	U32 mNumIndices;          //インデックスバッファにあるインデックスの数
	U32 mVertexBufferID;      //頂点バッファのOpenGL ID
	U32 mIndexBufferID;       //インデックスバッファのOpenGL ID
	U32 mVertexArrayID;       //頂点配列オブジェクトのOpenGL ID

};

#endif