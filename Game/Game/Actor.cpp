#include "Actor.h"
#include "Component.h"

/**********************************/
/*�֐��� : Actor                  */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : �R���X�g���N�^         */
/*���l   : ����                   */
/**********************************/
Actor::Actor(class Game* game)
	:mGame(game),
	 mState(EActive)
{
	//�A�N�^�[�̐�������Game�N���X�ŊǗ�����Actor�Ɏ��g�̃|�C���^��ǉ�����
	mGame->AddActor(this);
}

/**********************************/
/*�֐��� : ~Actor                 */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : �f�X�g���N�^           */
/*���l   : ����                   */
/**********************************/
Actor::~Actor()
{
	mGame->RemoveActor(this);
	while (mComponents.empty())
	{
		delete mComponents.back();
	}
}

/**********************************/
/*�֐��� : AcotrUpdate            */
/*�߂�l : ����                   */
/*����   : deltaTime(�Q�[��������)*/
/*����   : �X�V����               */
/*���l   : ����                   */
/**********************************/
void Actor::AcotrUpdate(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateComponents(deltaTime);
	}
}
/******************************************************/
/*�֐��� : UpdateComponents                           */
/*�߂�l : ����                                       */
/*����   : deltaTime(�Q�[��������)                    */
/*����   : �ǉ�����                                   */
/*���l   : ����                                       */
/******************************************************/
void Actor::UpdateComponents(float deltaTime)
{

	for (auto iter = mComponents.begin(); iter < mComponents.end(); iter++)
	{
		(*iter)->ComponentUpdate(deltaTime);
	}

}

/**********************************/
/*�֐��� : ActorInput             */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : ���͏���               */
/*���l   : ����                   */
/**********************************/
void Actor::ActorInput()
{
	if (mState == EActive)
	{
		for (auto iter = mComponents.begin(); iter < mComponents.end(); iter++)
		{
			//�T�u�N���X���p������ComponentProcessInput���Ăяo��
			(*iter)->ComponentProcessInput();
		}
	}
}





/******************************************************/
/*�֐��� : AddComponent                               */
/*�߂�l : ����                                       */
/*����   : component(�ˑ����𒍓��������R���|�[�l���g)*/
/*����   : �ǉ�����                                   */
/*���l   : ����                                       */
/******************************************************/
void Actor::AddComponent(class Component* component)
{
	U8 order = component->GetUpdateOrder();
	//�ŏI�I��mComponent�ɑ}���������̂ŃX�R�[�v���֐��S�̂ɂ��Ă���
	auto iter = mComponents.begin();
	for (; iter < mComponents.end(); iter++)
	{
		//�_�u���|�C���^�[�ɂȂ�̂Ń|�C���^�[�Ƃ��ĎQ�Ƃ���
		if (order < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter,component);

}
/******************************************************/
/*�֐��� : RemoveComponent                            */
/*�߂�l : ����                                       */
/*����   : component(�폜�������R���|�[�l���g)        */
/*����   : �폜����                                   */
/*���l   : ����                                       */
/******************************************************/
void Actor::RemoveComponent(class Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
