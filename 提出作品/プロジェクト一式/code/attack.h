//=================================
// 
// �U�������N���X�@attack.h
//outher kida ibuki 
// 
//==================================
#ifndef _ATTACK_H_
#define _ATTACK_H_

#include "objectX.h"
#include "enemyX.h"

class CAttack :public CObjectX
{
public:
	CAttack();							// �R���X�g���N�^
	~CAttack() override;				// �f�X�g���N�^
	HRESULT Init() override;			// �����ݒ�
	void Uninit() override;				// �I������
	void Update() override;				// �X�V����
	void Draw() override;				// �`�揈��
	static CAttack* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);           // ��������
	void Collision();

private:
	int m_nType;
	int m_nFramCnt;
	int m_nFrameCnt3;
	bool m_bTouch;
	int m_nDamage;
};

#endif