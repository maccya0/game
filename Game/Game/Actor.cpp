#include "Actor.h"
#include "Component.h"

/**********************************/
/*関数名 : Actor                  */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : コンストラクタ         */
/*備考   : 無し                   */
/**********************************/
Actor::Actor(class Game* game)
	:mGame(game),
	 mState(EActive)
{
	//アクターの生成時にGameクラスで管理するActorに自身のポインタを追加する
	mGame->AddActor(this);
}

/**********************************/
/*関数名 : ~Actor                 */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : デストラクタ           */
/*備考   : 無し                   */
/**********************************/
Actor::~Actor()
{
	mGame->RemoveActor(this);
	while (mComponents.empty())
	{
		delete mComponents.back();
	}
}

/**********************************/
/*関数名 : AcotrUpdate            */
/*戻り値 : 無し                   */
/*引数   : deltaTime(ゲーム内時間)*/
/*処理   : 更新処理               */
/*備考   : 無し                   */
/**********************************/
void Actor::AcotrUpdate(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateComponents(deltaTime);
	}
}
/******************************************************/
/*関数名 : UpdateComponents                           */
/*戻り値 : 無し                                       */
/*引数   : deltaTime(ゲーム内時間)                    */
/*処理   : 追加処理                                   */
/*備考   : 無し                                       */
/******************************************************/
void Actor::UpdateComponents(float deltaTime)
{

	for (auto iter = mComponents.begin(); iter < mComponents.end(); iter++)
	{
		(*iter)->ComponentUpdate(deltaTime);
	}

}

/**********************************/
/*関数名 : ActorInput             */
/*戻り値 : 無し                   */
/*引数   : 無し                   */
/*処理   : 入力処理               */
/*備考   : 無し                   */
/**********************************/
void Actor::ActorInput()
{
	if (mState == EActive)
	{
		for (auto iter = mComponents.begin(); iter < mComponents.end(); iter++)
		{
			//サブクラスが継承したComponentProcessInputを呼び出す
			(*iter)->ComponentProcessInput();
		}
	}
}





/******************************************************/
/*関数名 : AddComponent                               */
/*戻り値 : 無し                                       */
/*引数   : component(依存性を注入したいコンポーネント)*/
/*処理   : 追加処理                                   */
/*備考   : 無し                                       */
/******************************************************/
void Actor::AddComponent(class Component* component)
{
	U8 order = component->GetUpdateOrder();
	//最終的にmComponentに挿入したいのでスコープを関数全体にしておく
	auto iter = mComponents.begin();
	for (; iter < mComponents.end(); iter++)
	{
		//ダブルポインターになるのでポインターとして参照する
		if (order < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter,component);

}
/******************************************************/
/*関数名 : RemoveComponent                            */
/*戻り値 : 無し                                       */
/*引数   : component(削除したいコンポーネント)        */
/*処理   : 削除処理                                   */
/*備考   : 無し                                       */
/******************************************************/
void Actor::RemoveComponent(class Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
