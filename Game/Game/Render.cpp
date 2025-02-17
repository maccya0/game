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
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
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
	//OPENGL�E�B���h�E�̍쐬�̑O��SDL_GLattr�̑�����ݒ肷��
	//�R�A�Ńv���t�@�C�����Œ肵�����̂�CORE��MASK����
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_PROFILE_MASK, 
		SDL_GL_CONTEXT_PROFILE_CORE
	);

	//ver3.3���w��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//RGBA�̊e�`�����l����8bit�w�聨1�s�N�Z��������RGBA32bit�ɐݒ�
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	//��ʐ؂�ւ��̂��߂Ƀ_�u���o�b�t�@�̗L����
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//�n�[�h�E�F�A�A�N�Z�����[�V����(GPU)�g�p��ݒ�
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//OpenGL�g�p�Ȃ̂�SDL_WINDOW_OPENGL���w�肷��
	mWindow = SDL_CreateWindow("Game", 100, 100, width, height, SDL_WINDOW_OPENGL);
	//null�̎��͎��s
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	/* �׋��p�F�R���e�N�X�g�@���@OpenGL���ł́h���E�h�J���[�o�b�t�@,�摜,etc�̓R���e�N�X�g�Ɋ܂܂��@ */
	//�E�B���h�E�Ɋ֘A�t�����R���e�N�X�g�̐���
	mContext = SDL_GL_CreateContext(mWindow);

	if (!mContext)
	{
		SDL_Log("Failed to initialize Context.");
		return false;
	}

	/* �׋��p�FGLEW�@���@OpenGL���g�����邽�߂̃��C�u�����@ */
	//GLEW�̏�����
	//Init����O��True�ɂ��Ȃ��Ǝ��s����
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}


	return true;
}
