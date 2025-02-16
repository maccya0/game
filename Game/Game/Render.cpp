#include "Render.h"
#include<iostream>
/**********************************/
/*関数名 : Render                 */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : コンストラクタ         */
/*備考   : 無し                   */
/**********************************/
Render::Render()
{
}

/**********************************/
/*関数名 : ~Render                */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : デストラクタ           */
/*備考   : 無し                   */
/**********************************/
Render::~Render()
{
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

/**************************************************/
/*関数名 : Initialize                             */
/*戻り値 : 初期化の成否                           */
/*引数   : width(ウィンドウの幅)                  */
/*       : hright(ウィンドウの高さ)               */
/*処理   : 初期化                                 */
/*備考   : 無し                                   */
/**************************************************/
bool Render::Initialize(S16 width, S16 height)
{
	if (SDL_Init((SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0))
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("Game", 100, 100, width, height, 0);
	//nullの時は失敗
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	return true;
}
