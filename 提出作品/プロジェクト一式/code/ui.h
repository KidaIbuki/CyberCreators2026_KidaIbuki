//=================================
// 
// UI�N���X�@ui.h
//outher kida ibuki 
// 
//==================================
#ifndef _UI_H_
#define _UI_H_

#include "pch.h"
#include "object2D.h"


class CUi :public CObject2D
{
public:
	CUi();
	~CUi()override;
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��
	static CUi* Create(D3DXVECTOR2 pos, int nType);
	static HRESULT Load();											//�e�N�X�`���̃��[�h
	static void Unload();											//�e�N�X�`���̃A�����[�h
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//�e�N�X�`���̃e���v���[�g
	static int m_nFrameCnt;
	int m_nType;
	int m_nFrame;
};
#endif