#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "Lib.h"

/* 勉強用：コンポーネントオブジェクトモデリングの為に用いるクラス　                                 */
/* 　　　：このクラスをスーパークラスにしてサブクラスのコンポーネントを生成し、アクターに紐づける　 */
class Component
{
	public:
		//コンストラクタ
		Component(class Actor* owner, int updateOrder);
		//デストラクタ
		virtual~Component();
		
		//更新処理
		virtual void ComponentUpdate(float deltatime) {};
		//入力
		virtual void ComponentProcessInput() {};

		//ゲッター
		int GetUpdateOrder()const { return mUpdataOrder; };

	private:

		//スタック領域
		class Actor* mOwner;   //コンポーネントの所持アクター
		U8 mUpdataOrder;       //アップデート順
};

#endif