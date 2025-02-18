#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "Lib.h"

/* �׋��p�F�R���|�[�l���g�I�u�W�F�N�g���f�����O�ׂ̈ɗp����N���X�@                                 */
/* �@�@�@�F���̃N���X���X�[�p�[�N���X�ɂ��ăT�u�N���X�̃R���|�[�l���g�𐶐����A�A�N�^�[�ɕR�Â���@ */
class Component
{
	public:
		//�R���X�g���N�^
		Component(class Actor* owner, int updateOrder);
		//�f�X�g���N�^
		virtual~Component();
		
		//�X�V����
		virtual void ComponentUpdate(float deltatime) {};
		//����
		virtual void ComponentProcessInput() {};

		//�Q�b�^�[
		int GetUpdateOrder()const { return mUpdataOrder; };

	private:

		//�X�^�b�N�̈�
		class Actor* mOwner;   //�R���|�[�l���g�̏����A�N�^�[
		U8 mUpdataOrder;       //�A�b�v�f�[�g��
};

#endif