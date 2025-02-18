#pragma once
#include "Game.h"
#include "Lib.h"

class Actor
{
	public:

		//�A�N�^�[�̏�Ԑݒ�֘A
		enum ActorState
		{
			EActive,
			EIdle,
			Edead
		};
		ActorState GetActorState() { return mState; };
		//�R���X�g���N�^
		Actor(class Game* game);
		//�f�X�g���N�^
		~Actor();

		//�A�N�^�[�֘A
		void AcotrUpdate(float deltaTime);
		void ActorInput();
		//�Z�b�^�[
		void SetActorState(ActorState state) { mState = state; };


		//�R���|�[�l���g�֘A
		//�R���|�[�l���g�̒ǉ�
		void AddComponent(class Component* component);
		//�R���|�[�l���g�̍폜
		void RemoveComponent(class Component* component);

private:
		//�R���|�[�l���g�̍X�V
		void UpdateComponents(float deltaTime);

		//�q�[�v�̈�
		std::vector<class Component*> mComponents;

		//�X�^�b�N�̈�
		ActorState mState; //�A�N�^�[�̏��
		Game* mGame;       //�ˑ����̒����ɂ��Game�I�u�W�F�N�g�̃f�[�^�ɃA�N�Z�X����
};