#pragma once
#include "Game.h"
#include "Lib.h"

class Actor
{
	public:
		//�R���X�g���N�^
		Actor(class Game* game);
		~Actor();

		//�A�N�^�[�̏�Ԑݒ�֘A
		enum ActorState
		{
			EActive,
			EIdle,
			Edead
		};
		ActorState GetActorState() { return mState; };
		void SetActorState(ActorState state) { mState = state; };


		void Update(float deltaTime);

	private:

		//�q�[�v�̈�

		//�X�^�b�N�̈�
		ActorState mState; //�A�N�^�[�̏��
		Game* mGame;       //�ˑ����̒����ɂ��Game�I�u�W�F�N�g�̃f�[�^�ɃA�N�Z�X����
};