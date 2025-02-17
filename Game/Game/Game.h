#pragma once
#ifndef GAME_H
#define GAME_H
#include "Lib.h"
#include "Render.h"

class Game
{
	public:
		/* �R���X�g���N�^ */
		Game();
		/* �f�X�g���N�^ */
		~Game();

		bool Initialize();
		void MainLoop();
		void ShotDown();
	private:

		/* ���C�����[�v�֘A */
		void Input();
		void Update();
		void Output();

		/* ���͊֘A */
		/* �X�V�֘A */
		/* �o�͊֘A */

		/* �����o�[�ϐ� */
		/* �q�[�v�̈�Ƀ��������m�ۂ������̂Ń|�C���^ */
		class Render *mRender;
	
		/* �X�^�b�N�̈� */
		bool mRunFlag;
		U32 mTicksCount;


};
#endif
