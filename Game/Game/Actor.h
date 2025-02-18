#pragma once
#include "Game.h"
#include "Lib.h"

class Actor
{
	public:

		//アクターの状態設定関連
		enum ActorState
		{
			EActive,
			EIdle,
			Edead
		};
		ActorState GetActorState() { return mState; };
		//コンストラクタ
		Actor(class Game* game);
		//デストラクタ
		~Actor();

		//アクター関連
		void AcotrUpdate(float deltaTime);
		void ActorInput();
		//セッター
		void SetActorState(ActorState state) { mState = state; };


		//コンポーネント関連
		//コンポーネントの追加
		void AddComponent(class Component* component);
		//コンポーネントの削除
		void RemoveComponent(class Component* component);

private:
		//コンポーネントの更新
		void UpdateComponents(float deltaTime);

		//ヒープ領域
		std::vector<class Component*> mComponents;

		//スタック領域
		ActorState mState; //アクターの状態
		Game* mGame;       //依存性の注入によりGameオブジェクトのデータにアクセスする
};