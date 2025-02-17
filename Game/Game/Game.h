#pragma once
#ifndef GAME_H
#define GAME_H
#include "Lib.h"
#include "Render.h"

class Game
{
	public:
		/* コンストラクタ */
		Game();
		/* デストラクタ */
		~Game();

		bool Initialize();
		void MainLoop();
		void ShotDown();
	private:

		/* メインループ関連 */
		void Input();
		void Update();
		void Output();

		/* 入力関連 */
		/* 更新関連 */
		/* 出力関連 */

		/* メンバー変数 */
		/* ヒープ領域にメモリを確保したいのでポインタ */
		class Render *mRender;
	
		/* スタック領域 */
		bool mRunFlag;
		U32 mTicksCount;


};
#endif
