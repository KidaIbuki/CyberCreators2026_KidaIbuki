//=================================
// 
//���C�g�N���X�@�@light.h
//outher kida ibuki 
// 
//==================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

#define MAX_LIGHT (3) //���C�g�̐�

//���C�g�̃N���X��`
class CLight
{
public:
	CLight();		    //�R���X�g���N�^
	~CLight();		    //�f�X�g���N�^
	HRESULT Init();     //�����ݒ�
	void Uninit();		//�I������
	void Update();      //�X�V����
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];  //���C�g�\����

};

#endif