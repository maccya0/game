#include "./Game.h"
#include <iostream>
/**********************************/
/*関数名 : Game                   */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : コンストラクタ         */
/*備考   : 無し                   */
/**********************************/
Game::Game()
	:mRender(nullptr),
	mRunFlag(true)
{
}

/**********************************/
/*関数名 : ~Game                  */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : デストラクタ           */
/*備考   : 無し                   */
/**********************************/
Game::~Game()
{
	delete mRender;
}
/**********************************/
/*関数名 : Initialize             */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : 初期化                 */
/*備考   : 無し                   */
/**********************************/
bool Game::Initialize()
{

	mRender = new Render();

	bool result = mRender->Initialize(WINDOW_WIDE,WINDOW_HEIGHT);

	if (!result)
	{
		return false;
	}

	return true;
}
/**********************************/
/*関数名 : MainLoop               */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : メイン処理             */
/*備考   : 無し                   */
/**********************************/
void Game::MainLoop()
{
	/* メイン処理は入力→変換→出力 */
	while (mRunFlag)
	{
		Input();
		Update();
		Output();
	};

}

/**********************************/
/*関数名 : ShotDown               */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : シャットダウン処理     */
/*備考   : 無し                   */
/**********************************/
void Game::ShotDown()
{

}

/**********************************/
/*関数名 : Inout                  */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : メインループ入力処理   */
/*備考   : 無し                   */
/**********************************/
void Game::Input()
{
	SDL_Event event;

	//キューにイベントが入っている限り続ける
	while (SDL_PollEvent(&event))
	{
		//Windowを閉じるイベントが起こったか
		switch (event.type)
		{
			case SDL_QUIT:
				mRunFlag = false;
		}
	}

	//ESCキーが入力された場合
	//SDL_GetKeyboardStateはキーボード全体の入力を見る
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mRunFlag = false;
	}

}

/**********************************/
/*関数名 : Update                 */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : メインループ更新処理   */
/*備考   : 無し                   */
/**********************************/
void Game::Update()
{

}

/**********************************/
/*関数名 : Output                 */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : メインループ出力処理   */
/*備考   : 無し                   */
/**********************************/
void Game::Output()
{

}


