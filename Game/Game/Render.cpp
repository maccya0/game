#include "Render.h"
#include<iostream>
/**********************************/
/*�֐��� : Render                 */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : �R���X�g���N�^         */
/*���l   : ����                   */
/**********************************/
Render::Render()
{
}

/**********************************/
/*�֐��� : ~Render                */
/*�߂�l : ����                   */
/*����   : ����                   */
/*����   : �f�X�g���N�^           */
/*���l   : ����                   */
/**********************************/
Render::~Render()
{
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

/**************************************************/
/*�֐��� : Initialize                             */
/*�߂�l : �������̐���                           */
/*����   : width(�E�B���h�E�̕�)                  */
/*       : hright(�E�B���h�E�̍���)               */
/*����   : ������                                 */
/*���l   : ����                                   */
/**************************************************/
bool Render::Initialize(S16 width, S16 height)
{
	if (SDL_Init((SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0))
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("Game", 100, 100, width, height, 0);
	//null�̎��͎��s
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	return true;
}
