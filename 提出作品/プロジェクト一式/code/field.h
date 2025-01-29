//=================================
// 
//�t�B�[���h�@field.h
//outher kida ibuki 
// 
//==================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "object3D.h"

#define MAX_FIELD (1) //�n�ʂ̍ő吔

//�t�B�[���h�N���X�̒�`
class CField :public CObject3D
{
public:
	CField();					//�R���X�g���N�^
	~CField() override;			//�f�X�g���N�^
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��
	static CField* Create(D3DXVECTOR3 pos);    //��������
	static HRESULT Load();													//�e�N�X�`���̃��[�h
	static void Unload();													//�e�N�X�`���̃A�����[�h

private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//�e�N�X�`���̃e���v���[�g

};

#endif