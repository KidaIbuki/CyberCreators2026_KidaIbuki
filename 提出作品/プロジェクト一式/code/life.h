//=================================
// 
// ���C�tUI�N���X�@life.h
//outher kida ibuki 
// 
//==================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "pch.h"
#include "object2D.h"

#define SCREEN_SPACE	(30/2)

class CLife :public CObject2D
{
public:

	CLife();
	~CLife()override;
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��
	static CLife* Create(D3DXVECTOR2 pos);
	static HRESULT Load();											//�e�N�X�`���̃��[�h
	static void Unload();											//�e�N�X�`���̃A�����[�h
	static void HitLife(int nDamage);
private:
	static float m_fTexHeight;
	static float m_fTexWidht;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//�e�N�X�`���̃e���v���[�g
	static int m_nFrame;
	static int m_nLife;

};
#endif