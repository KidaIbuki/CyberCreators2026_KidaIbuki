//=================================
// 
// �G�N���X�@enemyX.h
//outher kida ibuki 
// 
//==================================
#include "manager.h"
#include "enemyX.h"
#include "life.h"
#include "explosion.h"
int CEnemyX::m_nLife = 0;
int CEnemyX::m_nFrameCnt = 0;
bool CEnemyX::m_bDeath = {};

//==================================
// �R���X�g���N�^
//==================================
CEnemyX::CEnemyX()
{
	// �G�̊�{�p�����[�^�[
	m_move = { 0.0f,0.0f,0.0f };
	m_pos = { 0.0f,0.0f,0.0f };
	m_bMove = true;   // �����Ă��邩�ǂ���x��
	m_bMove1 = true;   // y��
	m_bTouch = false;
	m_fMoveStorage1 = 0.0f;
	m_fMoveStorage2 = 0.0f;
	m_fMoveStorage3 = 0.0f;
	m_fMoveStorage4 = 0.0f;

	m_fSpeedStorage = 0.0f;
	m_fSpeedStorage1 = 0.0f;
	m_nFrameCnt = 10;
	m_nDamageCnt = 5;
	m_nLife = 50;
	m_bDeath = false;
}
//==================================
// �f�X�g���N�^
//==================================
CEnemyX::~CEnemyX()
{
}
//==================================
// �����ݒ�
//==================================
HRESULT CEnemyX::Init()
{
	CObjectX::Init();

	SetType(CObject::TYPE::ENEMY_X);

	return S_OK;
}
//==================================
// �I������
//==================================
void CEnemyX::Uninit()
{
	CObjectX::Uninit();
}
//==================================
// �X�V����
//==================================
void CEnemyX::Update()
{
	// �G�̍s������
    m_pos += m_move;

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;


	// �w�肵�����W�̊Ԃ��s�������鏈��
	//x��
	if (m_pos.x > m_fMoveStorage1)//��
	{
		m_bMove = true;
	}
	else if (m_pos.x < m_fMoveStorage2)//��O
	{
		m_bMove = false;
	}
	if (m_bMove == true)
	{
		m_pos.x -= m_fSpeedStorage;
	}
	else if (m_bMove == false)
	{
		m_pos.x += m_fSpeedStorage;
	}

	//y��
	if (m_pos.y > m_fMoveStorage3)//��
	{
		m_bMove1 = true;
	}
	else if (m_pos.y < m_fMoveStorage4)//��O
	{
		m_bMove1 = false;
	}
	if (m_bMove1 == true)
	{
		m_pos.y -= m_fSpeedStorage1;
	}
	else if (m_bMove1 == false)
	{
		m_pos.y += m_fSpeedStorage1;
	}

	//�ړ��ʂ�����
	m_move.x += (0.0f - m_move.x) * 0.3f;
	m_move.y += (0.0f - m_move.y) * 0.3f;

	if (m_bDeath == true)
	{
		DeathFlag();
		CExplosion::Create(m_pos, D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));
		m_bDeath = false;
	}

}
//==================================
// �`�揈��
//==================================
void CEnemyX::Draw()
{
	CObjectX::Draw();
}
//==================================
// ��������
//==================================
CEnemyX* CEnemyX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat,
	D3DXVECTOR3 movex1, D3DXVECTOR3 movex2, D3DXVECTOR3 movey1, D3DXVECTOR3 movey2, float fSpeed, float fSpeed1, int nLife, int nDamage)
{
	CEnemyX* pEnemyX = new CEnemyX();
	pEnemyX->SetPos(pos);
	pEnemyX->SetRot(rot);
	pEnemyX->SizeVtx();
	pEnemyX->m_pMesh = pMesh;
	pEnemyX->m_pBuffMat = pBuffMat;
	pEnemyX->m_dwNumMat = dwNumMat;
	pEnemyX->m_fMoveStorage1 = movex1.x;
	pEnemyX->m_fMoveStorage2 = movex2.x;
	pEnemyX->m_fMoveStorage3 = movey1.y;
	pEnemyX->m_fMoveStorage4 = movey2.y;

	pEnemyX->m_nLife = nLife;
	pEnemyX->m_nAttack = nDamage;
	//y�����ǉ����邩��...
	pEnemyX->m_fSpeedStorage = fSpeed;
	pEnemyX->m_fSpeedStorage1 = fSpeed1;


	pEnemyX->Init();
	return pEnemyX;
}
CEnemyX* CEnemyX::Create2(D3DXVECTOR3 pos)
{
	CEnemyX* pEnemyX2 = new CEnemyX;
	pEnemyX2->SetPos(pos);
	pEnemyX2->Init();
	pEnemyX2->SetModel("data/MODEL/out.x");


	return pEnemyX2;
}
//======================================
// �G�̃��C�t���Z����
//======================================
void CEnemyX::HitLife(int nDamage)
{
	CManager* pManager = CManager::GetInstance();

	if (m_nFrameCnt >= 0)  // 0��葽��������
	{
		m_nFrameCnt--;   // �J�E���g�_�E��
	}
	if (m_nFrameCnt <= 0)
	{ // ���W�𑝂₷
		pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ENEMY_DAMAGE);

		m_nLife -= nDamage;  // ���C�t�����炷
		m_nFrameCnt = 30;   // �t���[����߂�
	}
	if (m_nLife <= 0)
	{// ���C�t�������Ȃ�����
		m_bDeath = true;
	}

}
//======================================
// �G�̃��C�t���Z����
//======================================
void CEnemyX::HitLife2()
{
	CManager* pManager = CManager::GetInstance();

	m_nDamageCnt--;

	// �T�E���h�𗬂�(�v���C���[�̃_���[�W)
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ENEMY_DAMAGE);

	if (m_nDamageCnt <= 0)
	{
		DeathFlag();
	}

}
