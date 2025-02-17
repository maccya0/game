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
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
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
	//OPENGLウィンドウの作成の前にSDL_GLattrの属性を設定する
	//コアでプロファイルを固定したいのでCOREでMASKする
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_PROFILE_MASK, 
		SDL_GL_CONTEXT_PROFILE_CORE
	);

	//ver3.3を指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//RGBAの各チャンネルを8bit指定→1ピクセルあたりRGBA32bitに設定
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	//画面切り替えのためにダブルバッファの有効化
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//ハードウェアアクセラレーション(GPU)使用を設定
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//OpenGL使用なのでSDL_WINDOW_OPENGLを指定する
	mWindow = SDL_CreateWindow("Game", 100, 100, width, height, SDL_WINDOW_OPENGL);
	//nullの時は失敗
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	/* 勉強用：コンテクスト　＝　OpenGL内での”世界”カラーバッファ,画像,etcはコンテクストに含まれる　 */
	//ウィンドウに関連付けたコンテクストの生成
	mContext = SDL_GL_CreateContext(mWindow);

	if (!mContext)
	{
		SDL_Log("Failed to initialize Context.");
		return false;
	}

	/* 勉強用：GLEW　＝　OpenGLを拡張するためのライブラリ　 */
	//GLEWの初期化
	//Initする前にTrueにしないと失敗する
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}


	return true;
}
