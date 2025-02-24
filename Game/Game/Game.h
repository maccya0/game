#pragma once
#ifndef GAME_H
#define GAME_H
#include "Lib.h"
#include "Render.h"
#include "Actor.h"
#include "Shader.h"

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

		/* �A�N�^�[�֘A */
		/* �A�N�^�[�̒ǉ� */
		void AddActor(class Actor* actor);
		/* �A�N�^�[�̍폜 */
		void RemoveActor(class Actor* actor);

	private:

		/* �������֘A */
		bool LoadShaders();

		/* ���C�����[�v�֘A */
		void Input();
		void Update();
		void Output();

		/* ���͊֘A */
		/* �X�V�֘A */
		void UpdateActors(float deltaTime);
		/* �o�͊֘A */

		/* �����o�[�ϐ� */
		/* �q�[�v�̈�� */
		class Render        *mRender;             //�����_���[����p(���������m�ۂ������̂Ń|�C���^)
		std::vector<class Actor*> mActiveActors;  //�A�N�e�B�u�ȃA�N�^�[(�A�N�^�[�ƃQ�[���N���X�͑��݂Ƀf�[�^���Q�Ƃ������̂Ń|�C���^)
		std::vector<class Actor*> mIdleActors;    //�҂���ԂȃA�N�^�[
		class Shader* mSpriteShader;              //�V�F�[�_�[�I�u�W�F�N�g

		/* �X�^�b�N�̈� */
		bool  mRunFlag;         //���s�t���O
		U32   mTicksCount;      //���s�o�ߎ���
		bool  mUpdataingActors; //Actor�X�V���t���O


};
#endif
