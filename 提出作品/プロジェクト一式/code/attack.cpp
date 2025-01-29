//=================================
// 
// �U�������N���X�@attack.h
//outher kida ibuki 
// 
//==================================
#include "attack.h"
#include "manager.h"
#include "playerX.h"
#include "obb.h"

//==================================
// �R���X�g���N�^
//==================================
CAttack::CAttack()
{
	m_bTouch = false;
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_nDamage = 0;
	m_nFramCnt = 20;
	m_nFrameCnt3 = 30;
}

//==================================
// �f�X�g���N�^
//==================================
CAttack::~CAttack()
{
}

//==================================
// �����ݒ�
//==================================
HRESULT CAttack::Init()
{
	CObjectX::Init();
	SetType(CObject::TYPE::ATTACK);

	return S_OK;
}

//==================================
// �I������
//==================================
void CAttack::Uninit()
{
	CObjectX::Uninit();
}

//==================================
// �X�V����
//==================================
void CAttack::Update()
{
	// �U��������ɁA�U���I�u�W�F�N�g������
	m_nFramCnt--;
	if (m_nFramCnt <= 0)
	{
		Collision();
		DeathFlag();
		m_nFramCnt = 20;
	}

}

//==================================
// �`�揈��
//==================================
void CAttack::Draw()
{
	CObjectX::Draw();
}

//==================================
// ��������
//==================================
CAttack* CAttack::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	CAttack* pAttack = new CAttack();
	pAttack->Init();
	pAttack->SetPos(pos);
	pAttack->SetRot(rot);

	if (nType == 0)
	{
		pAttack->SetModel("data/MODEL/ATTACK/attack_obj.x");
		pAttack->m_bTouch = true;
	}
	return pAttack;
}
//==================================
// �U�����G�ɓ����鏈��
//==================================

void CAttack::Collision()
{

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = pTopObject[nPriority];

		//��ނ̎擾
		while (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();
			CObject* pNext = pObj->GetNext(); // ���̃|�C���^���擾
			if (type == CObject::TYPE::ENEMY_X)
			{
				CEnemyX* pEnemy = (CEnemyX*)pObj; //�_�E���L���X�g
				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // �U���̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					pEnemy->HitLife2();
				}
				else
				{// �������ĂȂ��Ƃ�
				}

			}

			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}


}






