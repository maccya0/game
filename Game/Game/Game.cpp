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
	mRunFlag(true)
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
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
	{
		;
	}

	//���^�C�� = (���ݎ��� - �O��o�ߎ���)ms��b�ɕϊ�����
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f ;

	//�ő�o�ߎ��Ԃ𒴂���p�Ȃ�΃K�[�h����
	if (deltaTime > MAX_DELTA_TIME)
	{
		deltaTime = MAX_DELTA_TIME;
	}

	//���Ԍo�ߎ��Ԃׂ̈Ƀ��b�`����
	mTicksCount = SDL_GetTicks();
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


