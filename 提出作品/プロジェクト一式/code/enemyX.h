//=================================
// 
// �G�N���X�@enemyX.h
//outher kida ibuki 
// 
//==================================
#ifndef _ENEMYX_H_
#define _ENEMYX_H_


#include "pch.h"
#include "objectX.h"
#include "playerX.h"
// �ʏ�̓G�N���X
class CEnemyX :public CObjectX
{
public:
	CEnemyX();							// �R���X�g���N�^
	~CEnemyX() override;				// �f�X�g���N�^
	HRESULT Init() override;			// �����ݒ�
	void Uninit() override;				// �I������
	void Update() override;				// �X�V����
	void Draw() override;				// �`�揈��
	static CEnemyX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat,
		D3DXVECTOR3 movex1, D3DXVECTOR3 movex2, D3DXVECTOR3 movey1, D3DXVECTOR3 movey2, float fSpeed, float fSpeed1, int nLife, int nDamage);

	static CEnemyX* Create2(D3DXVECTOR3 pos);
	int GetLife() { return m_nLife; }  // ���C�t�̎擾
	static void HitLife(int nDamage);
	void HitLife2();

private:
	static int m_nLife;    // �G�̃��C�t
	int m_nAttack;  // �G�̍U����

	bool m_bMove;     // �����Ă��邩�ۂ�x��
	bool m_bMove1;     // �����Ă��邩�ۂ�y��
	bool m_bTouch;  // �G��Ă��邩�ǂ���

	//�ړ��ʂȂǂ��i�[����ϐ�
	float m_fMoveStorage1;
	float m_fMoveStorage2;
	float m_fMoveStorage3;
	float m_fMoveStorage4;

	float m_fSpeedStorage;	
    float m_fSpeedStorage1;

	static int m_nFrameCnt;

	int m_nDamageCnt;

	static bool m_bDeath;   // ���񂾂��ǂ���
};
#endif