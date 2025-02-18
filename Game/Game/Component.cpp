#include"Component.h"
#include"Actor.h"


/***************************************************/
/*�֐��� : Component                               */
/*�߂�l : ����                                    */
/*����   : owner(�R���|�l���g����������A�N�^�[)   */
/*       : updateorder(�`�揇)                     */
/*����   : �R���X�g���N�^                          */
/*���l   : ����                                    */
/***************************************************/
Component::Component(class Actor* owner, int updateOrder = MAX_UPDATE_ORDER)
	:mOwner(owner),
	mUpdataOrder(updateOrder)
{
	//���g���A�N�^�[�ɕԂ�
	owner->AddComponent(this);
}

/***************************************************/
/*�֐��� : ~Component                              */
/*�߂�l : ����                                    */
/*����   : ����                                    */
/*����   : �f�X�g���N�^                            */
/*���l   : ����                                    */
/***************************************************/
Component::~Component()
{

}


