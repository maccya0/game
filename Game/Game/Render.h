#pragma once
#ifndef RENDER_H
#define RENDER_H
#include "Lib.h"

class Render
{
	public:
		// コンストラクタ
		Render();
		// デストラクタ
		~Render();

		bool Initialize(S16 width, S16 height);
		void Draw();
	private:

		SDL_Window* mWindow;     //ウィンドウ用のポインタ
		SDL_GLContext mContext;  //コンテクスト用の変数
};
#endif