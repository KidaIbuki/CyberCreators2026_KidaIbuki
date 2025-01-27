//=================================
// 
// �e�N���X�@bullet.cpp
//outher kida ibuki 
// 
//==================================
#include "manager.h"    // �}�l�[�W���[
#include "bullet.h"   // �e
#include "effect.h"   // �G�t�F�N�g
#include "explosion.h"  // ����

// �ÓI�����o�ϐ���������
LPDIRECT3DTEXTURE9 CBullet::m_pTextureTemp = {};
CTarget* CBullet::m_pTarget = nullptr;

const int CBullet::LIFE = 1500;

//==========================================
// �R���X�g���N�^
//==========================================
CBullet::CBullet()
{
	m_dwLifeTime = timeGetTime();

	m_pos = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_homingStrength = 0.1f;
	m_nHitCnt = 0;
}
//==========================================
// �f�X�g���N�^
//==========================================
CBullet::~CBullet()
{
}
//==========================================
// �����ݒ�
//==========================================
HRESULT CBullet::Init()
{
	CBillboard::Init();

	SetType(CObject::TYPE::BULLET);
	SetBillboard(5.0f, 5.0f, 5.0f);
	SetSize(D3DXVECTOR3(4.0f, 4.0f, 0.0f));
	m_dwLifeTime = timeGetTime() + LIFE;


	return S_OK;

}
//==========================================
// �I������
//==========================================
void CBullet::Uninit()
{
	CBillboard::Uninit();
}
//==========================================
// �X�V����
//==========================================
void CBullet::Update()
{
	if (timeGetTime() >= m_dwLifeTime)
	{
		CBullet::m_bDeath = true;
	}

	CEffect::Create(m_pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 0, 5.0f, 1.0f, 0.0f, 10);



	//CollisionBullet();
	Collision();

	m_pos += m_move;
}
//==========================================
// �`�揈��
//==========================================
void CBullet::Draw()
{
	CBillboard::Draw();

}
//==========================================
// ��������
//==========================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet* pBullet = new CBullet();
	pBullet->Init();
	pBullet->SetBullet(pos, move);
	pBullet->SetPos(pos);

	if (m_pTextureTemp != nullptr)
	{
		pBullet->BindTexture(m_pTextureTemp);
	}

	return pBullet;
}

//=======================================
//���[�h
//=======================================
HRESULT CBullet::Load()
{
	CManager* pManager = CManager::GetInstance();

	//�|�C���^��null�Ȃ�
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\bullet000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//�A�����[�h
//======================================
void CBullet::Unload()
{
	//�e�N�X�`�����g�p���Ă�����j��
	if (m_pTextureTemp != nullptr)
	{
		//null�ɂ���
		m_pTextureTemp = nullptr;
	}
}
//======================================
// �e�̐ݒ�
//======================================
void CBullet::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}

//=======================================
//�����蔻��(OBB)
//=======================================
#if 0
bool CBullet::CollisionBullet()
{
	CManager* pManager = CManager::GetInstance();

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = pTopObject[nPriority];
		// �ő吔���s���Ȃ̂�while���g�p
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();
			if (type == CObject::TYPE::ENEMY_X)
			{
				CEnemyX* pEnemy = (CEnemyX*)pObj; //�_�E���L���X�g
				D3DXVECTOR3 lengthOBB = pEnemy->m_pos - this->m_pos;  // �����̃x�N�g�������߂�

				D3DXVECTOR3 AxisBulletX, AxisBulletY;   // �e��x,y�����x�N�g��
				D3DXVECTOR3 AxisNBulletX, AxisNBulletY;   // �e��x,y�����@���x�N�g��
				AxisBulletX.x = m_size.x * cosf(m_rot.z);
				AxisBulletX.y = m_size.x * sinf(m_rot.z);
				AxisBulletX.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletX, &AxisBulletX);   // �@���x�N�g���𐳋K��

				AxisBulletY.x = m_size.y * sinf(m_rot.z);
				AxisBulletY.y = m_size.y * cosf(m_rot.z);
				AxisBulletY.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletY, &AxisBulletY);   // �@���x�N�g���𐳋K��

				D3DXVECTOR3 AxisEnemyX, AxisEnemyY;   // �G��x,y�����x�N�g��
				D3DXVECTOR3 AxisNEnemyX, AxisNEnemyY;   // �G��x,y�����@���x�N�g��
				AxisEnemyX.x = pEnemy->m_size.x * cosf(pEnemy->m_rot.z);
				AxisEnemyX.y = pEnemy->m_size.x * sinf(pEnemy->m_rot.z);
				AxisEnemyX.z = 0.0f;
				D3DXVec3Normalize(&AxisNEnemyX, &AxisEnemyX);   // �@���x�N�g���𐳋K��

				AxisEnemyY.x = pEnemy->m_size.y * sinf(pEnemy->m_rot.z);
				AxisEnemyY.y = pEnemy->m_size.y * cosf(pEnemy->m_rot.z);
				AxisEnemyY.z = 0.0f;
				D3DXVec3Normalize(&AxisNEnemyY, &AxisEnemyY);  // �@���x�N�g���𐳋K��

				float rBullet, rEnemy, fLength;  // �v�Z�p�ϐ�

				// ������ : AxisPlayerX
				rBullet = D3DXVec3Length(&AxisBulletX);   // �������̒���
				rEnemy = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyY)); // �G���̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletX)); // ���ɑ΂��Ă̒���
				if (fLength > rBullet + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisPlayerY
				rBullet = D3DXVec3Length(&AxisBulletY);   // �������̒���
				rEnemy = fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyY)); // �G���̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletY)); // ���ɑ΂��Ă̒���
				if (fLength > rBullet + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisBlockX
				rBullet = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyX)); // �G���̒���
				rEnemy = D3DXVec3Length(&AxisEnemyX);   // �������̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyX)); // ���ɑ΂��Ă̒���
				if (fLength > rBullet + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisBlockY
				rBullet = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyY)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyY)); // �G���̒���
				rEnemy = D3DXVec3Length(&AxisEnemyY);   // �������̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyY)); // ���ɑ΂��Ă̒���
				if (fLength > rBullet + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}

				if (fabs(lengthOBB.z) < fabs(m_size.z - pEnemy->m_size.z))   // ��̒������������傫��������
				{
					pEnemy->m_bDeath = true;
					CExplosion::Create(pEnemy->m_pos, D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));
					CBullet::DeathFlag();
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);

					return true;  // �Փ˂���
				}
			}
			if (type == CObject::TYPE::ENEMY_BOSS)
			{
				CEnemyBoss* pEnemy = (CEnemyBoss*)pObj; //�_�E���L���X�g
				D3DXVECTOR3 lengthOBB = pEnemy->m_pos - this->m_pos;  // �����̃x�N�g�������߂�

				D3DXVECTOR3 AxisBulletX, AxisBulletY;   // �e��x,y�����x�N�g��
				D3DXVECTOR3 AxisNBulletX, AxisNBulletY;   // �e��x,y�����@���x�N�g��
				AxisBulletX.x = m_size.x * cosf(m_rot.z);
				AxisBulletX.y = m_size.x * sinf(m_rot.z);
				AxisBulletX.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletX, &AxisBulletX);   // �@���x�N�g���𐳋K��

				AxisBulletY.x = m_size.y * sinf(m_rot.z);
				AxisBulletY.y = m_size.y * cosf(m_rot.z);
				AxisBulletY.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletY, &AxisBulletY);   // �@���x�N�g���𐳋K��

				D3DXVECTOR3 AxisEnemyX, AxisEnemyY;   // �G��x,y�����x�N�g��
				D3DXVECTOR3 AxisNEnemyX, AxisNEnemyY;   // �G��x,y�����@���x�N�g��
				AxisEnemyX.x = pEnemy->m_size.x * cosf(pEnemy->m_rot.z);
				AxisEnemyX.y = pEnemy->m_size.x * sinf(pEnemy->m_rot.z);
				AxisEnemyX.z = 0.0f;
				D3DXVec3Normalize(&AxisNEnemyX, &AxisEnemyX);   // �@���x�N�g���𐳋K��

				AxisEnemyY.x = pEnemy->m_size.y * sinf(pEnemy->m_rot.z);
				AxisEnemyY.y = pEnemy->m_size.y * cosf(pEnemy->m_rot.z);
				AxisEnemyY.z = 0.0f;
				D3DXVec3Normalize(&AxisNEnemyY, &AxisEnemyY);  // �@���x�N�g���𐳋K��

				float rBullet, rEnemy, fLength;  // �v�Z�p�ϐ�

				// ������ : AxisPlayerX
				rBullet = D3DXVec3Length(&AxisBulletX);   // �������̒���
				rEnemy = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyY)); // �G���̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletX)); // ���ɑ΂��Ă̒���
				if (fLength > rBullet + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisPlayerY
				rBullet = D3DXVec3Length(&AxisBulletY);   // �������̒���
				rEnemy = fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyY)); // �G���̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletY)); // ���ɑ΂��Ă̒���
				if (fLength > rBullet + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisBlockX
				rBullet = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyX)); // �G���̒���
				rEnemy = D3DXVec3Length(&AxisEnemyX);   // �������̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyX)); // ���ɑ΂��Ă̒���
				if (fLength > rBullet + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisBlockY
				rBullet = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyY)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyY)); // �G���̒���
				rEnemy = D3DXVec3Length(&AxisEnemyY);   // �������̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyY)); // ���ɑ΂��Ă̒���
				if (fLength > rBullet + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}

				if (fabs(lengthOBB.z) < fabs(m_size.z - pEnemy->m_size.z + 150.0f))  // ��̒������������傫��������
				{
					pEnemy->DamageEnemy(10);
					CBullet::DeathFlag();
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);

					return true;  // �Փ˂���
				}
			}

			pObj = pNext;
		}
	}
	return false;
}
#endif
void CBullet::Collision()
{
	CManager* pManager = CManager::GetInstance();

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
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z - 50.0f);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // �e�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					pEnemy->m_bDeath = true;
					CExplosion::Create(pEnemy->m_pos, D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));
					CBullet::DeathFlag();
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);
				}
				else
				{// �������ĂȂ��Ƃ�
				}

			}
			if (type == CObject::TYPE::ENEMY_BOSS)
			{
				CEnemyBoss* pEnemy = (CEnemyBoss*)pObj; //�_�E���L���X�g
				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z + 150.0f), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // �e�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					pEnemy->DamageEnemy(10);
					CBullet::DeathFlag();
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);
				}
				else
				{// �������ĂȂ��Ƃ�
				}

			}
			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}


}

//==========================================
// �R���X�g���N�^
//==========================================
CBulletEnemy::CBulletEnemy()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
}
//==========================================
// �f�X�g���N�^
//==========================================
CBulletEnemy::~CBulletEnemy()
{
}
//==========================================
// �����ݒ�
//==========================================
HRESULT CBulletEnemy::Init()
{
	CBillboard::Init();

	SetType(CObject::TYPE::ENEMY_BULLET);
	SetBillboard(5.0f, 5.0f, 5.0f);
	SetSize(D3DXVECTOR3(10.0f, 10.0f, 10.0f));

	m_dwLifeTime = timeGetTime() + LIFE;


	return S_OK;

}
//==========================================
// �I������
//==========================================
void CBulletEnemy::Uninit()
{
	CBillboard::Uninit();
}
//==========================================
// �X�V����
//==========================================
void CBulletEnemy::Update()
{

	if (timeGetTime() >= m_dwLifeTime)
	{
		CBullet::m_bDeath = true;
	}

	CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0, 5.0f, 1.0f, 0.0f, 10);

	m_pos += m_move;
}
//==========================================
// �`�揈��
//==========================================
void CBulletEnemy::Draw()
{
	CBillboard::Draw();

}
//==========================================
// ��������
//==========================================
CBulletEnemy* CBulletEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBulletEnemy* pBullet = new CBulletEnemy();
	pBullet->Init();
	pBullet->SetBullet(pos, move);
	pBullet->SetPos(pos);

	if (m_pTextureTemp != nullptr)
	{
		pBullet->BindTexture(m_pTextureTemp);
	}

	return pBullet;
}
//=======================================
//���[�h
//=======================================
HRESULT CBulletEnemy::Load()
{
	CManager* pManager = CManager::GetInstance();

	//�|�C���^��null�Ȃ�
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\bullet000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//�A�����[�h
//======================================
void CBulletEnemy::Unload()
{
	//�e�N�X�`�����g�p���Ă�����j��
	if (m_pTextureTemp != nullptr)
	{
		//null�ɂ���
		m_pTextureTemp = nullptr;
	}
}
//======================================
// �e�̐ݒ�
//======================================
void CBulletEnemy::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}

