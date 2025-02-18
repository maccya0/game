#include"Component.h"
#include"Actor.h"


/***************************************************/
/*関数名 : Component                               */
/*戻り値 : 無し                                    */
/*引数   : owner(コンポネントを所持するアクター)   */
/*       : updateorder(描画順)                     */
/*処理   : コンストラクタ                          */
/*備考   : 無し                                    */
/***************************************************/
Component::Component(class Actor* owner, int updateOrder = MAX_UPDATE_ORDER)
	:mOwner(owner),
	mUpdataOrder(updateOrder)
{
	//自身をアクターに返す
	owner->AddComponent(this);
}

/***************************************************/
/*関数名 : ~Component                              */
/*戻り値 : 無し                                    */
/*引数   : 無し                                    */
/*処理   : デストラクタ                            */
/*備考   : 無し                                    */
/***************************************************/
Component::~Component()
{

}


