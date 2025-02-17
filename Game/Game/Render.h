#pragma once
#ifndef RENDER_H
#define RENDER_H
#include "Lib.h"
#include "Config.h"

class Render
{
	public:
		// �R���X�g���N�^
		Render();
		// �f�X�g���N�^
		~Render();

		bool Initialize(S16 width, S16 height);
	private:

		SDL_Window* mWindow;     //�E�B���h�E�p�̃|�C���^
		SDL_GLContext mContext;  //�R���e�N�X�g�p�̕ϐ�
};
#endif