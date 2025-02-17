#pragma once
#include "Game.h"
#include "Lib.h"

class Actor
{
	public:
		//コンストラクタ
		Actor(class Game* game);
		~Actor();

		//アクターの状態設定関連
		enum ActorState
		{
			EActive,
			EIdle,
			Edead
		};
		ActorState GetActorState() { return mState; };
		void SetActorState(ActorState state) { mState = state; };


		void Update(float deltaTime);

	private:

		//ヒープ領域

		//スタック領域
		ActorState mState; //アクターの状態
		Game* mGame;       //依存性の注入によりGameオブジェクトのデータにアクセスする
};