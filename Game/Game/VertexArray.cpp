#include"VertexArray.h"

/*************************************************/
/*�֐��� : VertexArray                           */
/*�߂�l : ����                                  */
/*����   : verts(���_�o�b�t�@)                   */
/*����   : numVerts(���_�̐�)                    */
/*����   : indices(�C���f�b�N�X�o�b�t�@)         */
/*����   : numIndices(�C���f�b�N�X�̐�)          */
/*����   : ���_,�C���f�b�N�X���̏�����         */
/*���l   : ����                                  */
/*************************************************/
VertexArray::VertexArray(const F32* verts, U16 numVerts, const U16* indices, U16 numIndices)
	:mNumIndices(numIndices),
	mNumVerts(numVerts)
{
	/*�׋��p�F���_�z��.���_�o�b�t�@,�C���f�b�N�X�o�b�t�@�̈Ⴂ  �@          �@�@                           */
	/*      �F���_�z��                 �� ���_����z��Ɋi�[���Ă����A�`�掞��CPU����GPU�Ɍ����ē]������ */
	/*      �F���_�o�b�t�@             �� ���_�����i�[���郁�����o�b�t�@�@�@�@�@�@                       */
	/*      �F�C���f�b�N�X�o�b�t�@     �� �C���f�b�N�X�����i�[���郁�����o�b�t�@�@                       */
	
	
	//���_�z��I�u�W�F�N�g���쐬���ăo�C���h(�g�p�̎w��)����
	/* �׋��p�FglGenVertexArrays�̑�1�����͒��_�z��I�u�W�F�N�g�̐� */
    glGenVertexArrays(1, &mVertexArrayID);
	/* �׋��p�FglBindVertexArray�̈����Ŏw�肳�ꂽ�I�u�W�F�N�g���̒��_�z��I�u�W�F�N�g���������� */
	glBindVertexArray(mVertexArrayID);

	//���l�ɒ��_�o�b�t�@���쐬���ăo�C���h����
	glGenBuffers(1,&mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER,mVertexBufferID);
	glBufferData(
		GL_ARRAY_BUFFER,                          //�o�b�t�@�̎��
		numVerts * TOTAL_VERTS_NUM * sizeof(F32), //�m�ۂ���o�C�g��
		verts,                                    //�R�s�[��
		GL_STATIC_DRAW                            //�f�[�^�̗��p���@
	);

	//���l�ɃC���f�b�N�X�o�b�t�@���쐬���ăo�C���h����
	glGenBuffers(1, &mIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,                  //�o�b�t�@�̎��
		numIndices * sizeof(U32),                 //�m�ۂ���o�C�g��
		indices,                                  //�R�s�[��
		GL_STATIC_DRAW                            //�f�[�^�̗��p���@
	);

	glEnableVertexAttribArray(0);
	/* �׋��p�F�����_�����O���� index �Ɏw�肳�ꂽ�ʒu�ɂ��� attribute �ϐ����󂯎��f�[�^�̏ꏊ�Ə������w�肷��  */
	/* �׋��p�F�F�X�Ɖ��̂�������ɂȂ��Ă���̂Ő���
	         : attribute�Ƃ̓f�[�^�̉�(�C���[�W��TLS�Ƃ��̃y�C���[�h)
			 : �f�[�^�� �F | attribute0 | attribute1 | attribute2 | attribute0 | attribute1 | attribute2 |�c
			 :��L�̂悤�Ƀf�[�^�̉�ɂȂ��Ă��邽�ߑ�1�����ł͂��̎g������"attribute"�̔ԍ����w�肷��
			 :��4�����̗v�f�Ԃ̊Ԋu�Ƃ͂܂�attribute�̒����ɂȂ�
			 :"attribute0"��xyz���W���w�肵�Ă���̂�"attribute1"�܂ł̒�����float�̃f�[�^�T�C�Y*���W���ɂȂ�
			 :�I�t�Z�b�g�͎w�肵��"attribute"���擪����ǂꂾ������Ă��邩�ɂȂ�
			 :"attribute1"���1�����Ɏw�肷��Ȃ�΃I�t�Z�b�g��"attribute0"����sizeof(F32)* COODINATE_NUM�ɂȂ�(���|�C���^�[�^�Ȃ̂Œ���)	
	*/
	//attribute0��xyz���W���L������
	glVertexAttribPointer(
		COODINATE_ATRIBUTE_POS,     //attribute�ϐ��̈ʒu
		COODINATE_NUM,              //�f�[�^�T�C�Y
		GL_FLOAT,                   //�f�[�^�̌^
		GL_FALSE,                   //���K���̗L��
		sizeof(F32)* COODINATE_NUM, //�v�f�Ԃ̊Ԋu
		0                           //�I�t�Z�b�g
	);
	glEnableVertexAttribArray(1);


}

/*************************************************/
/*�֐��� : ~VertexArray                          */
/*�߂�l : ����                                  */
/*����   : �Ȃ�                                  */
/*����   : ���_,�C���f�b�N�X���̍폜           */
/*���l   : ����                                  */
/*************************************************/
VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteBuffers(1, &mIndexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

/*************************************************/
/*�֐��� : SetVertexActive                       */
/*�߂�l : ����                                  */
/*����   : �Ȃ�                                  */
/*����   : ���_�z��̗L����                      */
/*���l   : ����                                  */
/*************************************************/
void VertexArray::SetVertexActive()
{
	glBindVertexArray(mVertexArrayID);
}