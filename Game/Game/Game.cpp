#include "./Game.h"
#include <iostream>
/**********************************/
/*�֐��� : Game                   */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : �R���X�g���N�^         */
/*���l   : ����                   */
/**********************************/
Game::Game()
	:mRender(nullptr),
	mRunFlag(true),
	mUpdataingActors(false)
{
}

/**********************************/
/*�֐��� : ~Game                  */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : �f�X�g���N�^           */
/*���l   : ����                   */
/**********************************/
Game::~Game()
{
	delete mRender;
}
/**********************************/
/*�֐��� : Initialize             */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : ������                 */
/*���l   : ����                   */
/**********************************/
bool Game::Initialize()
{

	mRender = new Render();

	bool result = mRender->Initialize(WINDOW_WIDE,WINDOW_HEIGHT);

	if (!result)
	{
		return false;
	}

	//�����o�ߎ��Ԃ�ݒ肷��
	mTicksCount = SDL_GetTicks();

	return true;
}
/**********************************/
/*�֐��� : MainLoop               */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : ���C������             */
/*���l   : ����                   */
/**********************************/
void Game::MainLoop()
{
	/* ���C�������͓��́��ϊ����o�� */
	while (mRunFlag)
	{
		Input();
		Update();
		Output();
	};

}

/**********************************/
/*�֐��� : ShotDown               */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : �V���b�g�_�E������     */
/*���l   : ����                   */
/**********************************/
void Game::ShotDown()
{

}

/**********************************/
/*�֐��� : Inout                  */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : ���C�����[�v���͏���   */
/*���l   : ����                   */
/**********************************/
void Game::Input()
{
	SDL_Event event;

	//�L���[�ɃC�x���g�������Ă�����葱����
	while (SDL_PollEvent(&event))
	{
		//Window�����C�x���g���N��������
		switch (event.type)
		{
			case SDL_QUIT:
				mRunFlag = false;
			default:
				break;
		}
	}

	//ESC�L�[�����͂��ꂽ�ꍇ
	//SDL_GetKeyboardState�̓L�[�{�[�h�S�̂̓��͂�����
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mRunFlag = false;
	}

	for (auto iter = mActiveActors.begin() ;  iter< mActiveActors.end() ; iter++)
	{
		(*iter)->ActorInput();
	}

}

/**********************************/
/*�֐��� : Update                 */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : ���C�����[�v�X�V����   */
/*���l   : ����                   */
/**********************************/
void Game::Update()
{
	//�Q�[�������Ԃ̌o�߂�҂�
	//���ݎ��Ԃ��O��o�ߎ���+16ms(60fps�����Ȃ̂�1/60)�܂ő҂�
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + FLAME_TIME ))
	{
		;
	}

	//���^�C�� = (���ݎ��� - �O��o�ߎ���)ms��b�ɕϊ�����
	float deltaTime = (SDL_GetTicks() - mTicksCount) / SECOND;

	//�ő�o�ߎ��Ԃ𒴂���p�Ȃ�΃K�[�h����
	if (deltaTime > MAX_DELTA_TIME)
	{
		deltaTime = MAX_DELTA_TIME;
	}

	//���Ԍo�ߎ��Ԃׂ̈Ƀ��b�`����
	mTicksCount = SDL_GetTicks();

	//�A�N�^�[�̍X�V
	UpdateActors(deltaTime);
}

/**********************************/
/*�֐��� : UpdateActors           */
/*�߂�l : ����                   */
/*����   : deltaTime(�Q�[��������)*/
/*����   : �A�N�^�[�̍X�V����     */
/*���l   : ����                   */
/**********************************/
void Game::UpdateActors(float deltaTime)
{
	//�A�N�^�[�̍X�V����mActiveActors�𑀍삳���Ƃ܂����̂�
	//�X�V����mActiveActors�̍X�V�������Ȃ�
	mUpdataingActors = true;
	for (auto actor : mActiveActors)
	{
		actor->AcotrUpdate(deltaTime);
	}
	mUpdataingActors = false;

	for (auto actor : mIdleActors)
	{
		//����X�V�Ɍ����đ҂���Ԃ̃A�N�^�[���A�N�e�B�u�ɂ���
		mActiveActors.emplace_back(actor);
	}
	//�҂���Ԃ̃A�N�^�[����ɂ���
	mIdleActors.clear();


	//���S�����A�N�^�[�̃��������J������
	//mActiveActors�𒼐ڑ��삵�����Ȃ��̂Ő�p�̔z���p�ӂ��č폜����
	std::vector<class Actor*> deadActors;
	for (auto actor : mActiveActors)
	{
		if (actor->GetActorState() == Actor::Edead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor;
	}

}
/**********************************/
/*�֐��� : Output                 */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : ���C�����[�v�o�͏���   */
/*���l   : ����                   */
/**********************************/
void Game::Output()
{

}


/**************************************/
/*�֐��� : AddActor                   */
/*�߂�l : ����                       */
/*����   : Actor(�Q�[�����I�u�W�F�N�g)*/
/*����   : �A�N�^�[�̒ǉ�����         */
/*���l   : ����                       */
/**************************************/
void Game::AddActor(Actor* actor)
{

	//�X�V���̒ǉ���h��
	if (mUpdataingActors == true)
	{
		mActiveActors.emplace_back(actor);
	}
	else
	{
		mIdleActors.emplace_back(actor);
	}
}
/**************************************/
/*�֐��� : RemoveActor                */
/*�߂�l : ����                       */
/*����   : Actor(�Q�[�����I�u�W�F�N�g)*/
/*����   : �A�N�^�[�̍폜����         */
/*���l   : �ʏ�X�V�ȊO�ł̍폜       */
/**************************************/
void Game::RemoveActor(Actor* actor)
{
	/* �Ώۃf�[�^���X�^�b�N�����Ɉړ����ă|�b�v���� */
	auto iter = std::find(mIdleActors.begin(), mIdleActors.end(), actor);
	if (iter != mIdleActors.end())
	{

		std::iter_swap(iter, mIdleActors.end() - 1);
		mIdleActors.pop_back();
	}
	iter = std::find(mActiveActors.begin(), mActiveActors.end(), actor);
	if (iter != mActiveActors.end())
	{

		std::iter_swap(iter, mActiveActors.end() - 1);
		mActiveActors.pop_back();
	}

}
