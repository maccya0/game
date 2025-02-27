#pragma once
#ifndef GAME_H
#define GAME_H
#include "Lib.h"
#include "Render.h"
#include "Actor.h"
#include "Shader.h"

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

		/* アクター関連 */
		/* アクターの追加 */
		void AddActor(class Actor* actor);
		/* アクターの削除 */
		void RemoveActor(class Actor* actor);

	private:

		/* 初期化関連 */
		bool LoadShaders();

		/* メインループ関連 */
		void Input();
		void Update();
		void Output();

		/* 入力関連 */
		/* 更新関連 */
		void UpdateActors(float deltaTime);
		/* 出力関連 */

		/* メンバー変数 */
		/* ヒープ領域に */
		class Render        *mRender;             //レンダラー操作用(メモリを確保したいのでポインタ)
		std::vector<class Actor*> mActiveActors;  //アクティブなアクター(アクターとゲームクラスは相互にデータを参照したいのでポインタ)
		std::vector<class Actor*> mIdleActors;    //待ち状態なアクター
		class Shader* mSpriteShader;              //シェーダーオブジェクト

		/* スタック領域 */
		bool  mRunFlag;         //実行フラグ
		U32   mTicksCount;      //実行経過時間
		bool  mUpdataingActors; //Actor更新中フラグ


};
#endif
