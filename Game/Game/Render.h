#pragma once
#ifndef RENDER_H
#define RENDER_H
#include "Lib.h"
#include "Config.h"

class Render
{
	public:
		// コンストラクタ
		Render();
		// デストラクタ
		~Render();

		bool Initialize(S16 width, S16 height);
	private:

		SDL_Window* mWindow;  //ウィンドウ用のポインタ
};
#endif