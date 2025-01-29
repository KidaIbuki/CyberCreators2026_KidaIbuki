//==============================================
// 
// 3D�̃v���C���[�@playerX.h
//outher kida ibuki 
// 
//==============================================
#include "playerX.h"
#include "marker.h"
#include "manager.h"
#include "blockX.h"
#include "life.h"
#include "attack.h"
#include "obb.h"
#include "tutorial.h"
#include "ui.h"
//�萔(�}�N��)�̒�`
const float CPlayerX::HALF2 = 1.0f;
const float CPlayerX::HALF1 = 2.0f;
//const float CPlayerX::HALF = 2.5f;

const float CPlayerX::MOVE_SPEED = 0.15f;


//====================================
// �R���X�g���N�^
//====================================
CPlayerX::CPlayerX()
{
	m_pos = { 0.0f, 0.0f, 0.0f };		// �ʒu
	m_rot = { 0.0f, 0.0f, 0.0f };		// ����
	//m_move = { 0.0f, 0.0f, 0.0f };		//�ړ���
	m_size = { 0.0f,0.0f,10.0f };

	m_posOld = { 0.0f,0.0f,0.0f };

	m_bJumpCnt = false;
	m_nTime = 0;  //1�b���炢����

	m_nLife = 100;

	m_nFrameCnt = 1;
	m_nFrameJumpCnt = 40;
	m_nFrameJumpCnt1 = 30;
	m_nFrame = 1;
	m_JumpState = JUMPSTATE_NONE;
}
//====================================
// �f�X�g���N�^
//====================================
CPlayerX::~CPlayerX()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CPlayerX::Init()
{
	CObjectX::Init();

	SetType(CObject::TYPE::PLAYER_X);

	return S_OK;
}
//====================================
// �I������
//====================================
void CPlayerX::Uninit()
{
	CObjectX::Uninit();

}
//====================================
// �X�V����
//====================================
void CPlayerX::Update()
{
	CObjectX::Update();

	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();	//�L�[�{�[�h�擾
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�R���g���[���[�擾

	m_posOld = m_pos;

	//�ړ��ʂ̍X�V
	m_move += PlayerMove();

	//pos�𓮂���
	m_pos += m_move;

	//�d��
#if 1
	m_move.y -= 0.3f;
	m_pos.y += m_move.y;

	//�����W�����v�h�~�ς݃W�����v
	if (m_JumpState == JUMPSTATE_NONE)
	{// �X�e�[�g���m�[�}��(�������Ă��Ȃ����)�̎�
		if (pKeyboard->GetTrigger(DIK_SPACE) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_A))
		{
			m_move.y += 10.0f;//�W�����v��(�������ł���ȏ�ɂ�����Ƃ߂�������)

			m_JumpState = JUMPSTATE_JUMP;// �X�e�[�g���W�����v��Ԃɂ���

			// �T�E���h�𗬂�
			pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_JUMP);

		}
	}
	// �W�����v��Ԃ̎�
	else if (m_JumpState == JUMPSTATE_JUMP)
	{
		m_nFrameJumpCnt--;  // �J�E���g�t���[�������Z����
		if (m_nFrameJumpCnt <= 0) // �t���[����0�ɂȂ�����
		{
			m_move.y = 0.0f; // �W�����v�l��0�ɂ���
			m_JumpState = JUMPSTATE_NONE; // �X�e�[�g�����ɖ߂�
			m_nFrameJumpCnt = 40; // �t���[�������Ƃɖ߂�
		}
	}

	//�n�ʂ�艺�ɍs���Ȃ��悤�ɂ���
	if (m_pos.y <= 0.0f)
	{
		m_pos.y = 0.0f;
		m_move.y = 0.0f;
	}
	Collision();
	//CollisionPlayer();
#endif
	//�ړ��ʂ�����
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;

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
			if (type == CObject::TYPE::BLOCK)
			{
				CBlockX* pBlockX = (CBlockX*)pObj; //�_�E���L���X�g
				if (pBlockX != nullptr)
				{
					//�����蔻��
					if (CollisionBlock(pBlockX))
					{ //�ڐG���Ă���Ƃ�

						return;
					}
				}

			}
			if (type == CObject::TYPE::PLAYER_X)
			{
				CPlayerX* pPlayer = (CPlayerX*)pObj; //�_�E���L���X�g
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 playerPos = pPlayer->GetPos(); // �v���C���[�̈ʒu���擾
					D3DXVECTOR3 playerRot = pPlayer->GetRot();
					if (pKeyboard->GetTrigger(DIK_RIGHT) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_B))
					{
						// �T�E���h�𗬂�
						pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

						CAttack::Create(D3DXVECTOR3(playerPos.x + 40.0f, playerPos.y + 10.0f, playerPos.z), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f), 0);

					}
					if (pKeyboard->GetTrigger(DIK_LEFT) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_X))
					{
						// �T�E���h�𗬂�
						pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

						CAttack::Create(D3DXVECTOR3(playerPos.x - 40.0f, playerPos.y + 10.0f, playerPos.z), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * -0.5f), 0);

					}
					

				}

			}
			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}

}
//==================================================
//�ړ��ݒ�
//==================================================
D3DXVECTOR3 CPlayerX::PlayerMove()
{
	CManager* pManager = CManager::GetInstance();  //�}�l�[�W���[�̃C���X�^���X�擾

	CInputKeyboard* pKeyboard = pManager->GetKeyboard();    //�L�[�{�[�h�擾
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�L�[�{�[�h�擾

	D3DXVECTOR3 move = { 0,0,0 };
	//**========�J�����̏��==========**
	CCamera* pCamera = pManager->GetCamera();  //�J�����̎擾
	D3DXVECTOR3 rot = pCamera->GetRot();	//����

	if (pKeyboard->GetPress(DIK_A) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT))
	{//A�L�[�������ꂽ�ꍇ
		move.x -= MOVE_SPEED;
		m_rot.y = -(D3DX_PI * -HALF2 - rot.y);

		//�����ɉ����ꂽ�Ƃ�
		if (pKeyboard->GetPress(DIK_A) == true && pKeyboard->GetPress(DIK_D) == true || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
		{//D�L�[�������ꂽ�ꍇ

			move.x = 0.0f;
		}
	}
	if (pKeyboard->GetPress(DIK_D) == true || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
	{//D�L�[�������ꂽ�ꍇ

		move.x += MOVE_SPEED;
		m_rot.y = -(D3DX_PI * HALF1 - rot.y);

		//�����ɉ����ꂽ�Ƃ�
		if (pKeyboard->GetPress(DIK_A) == true && pKeyboard->GetPress(DIK_D) == true || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
		{//D�L�[�������ꂽ�ꍇ

			move.x = 0.0f;
		}
	}


	return move;

}
//====================================
// �v���C���[�̃_���[�W����
//====================================
void CPlayerX::HItPlayer(int nDamage)
{
	if (m_state == PLAYERSTATE_NONE)
	{
		m_nLife -= nDamage;
		if (m_nLife <= 0)
		{
			DeathFlag();
		}
		m_nFrameCnt--;
		m_state = PLAYERSTATE_DAMAGE;
		if (m_state == PLAYERSTATE_DAMAGE)
		{
			if (m_nFrameCnt <= 0)
			{
				m_state = PLAYERSTATE_NONE;
				m_nFrameCnt = 1;
			}
		}

	}
}

//====================================
// �`�揈��
//====================================
void CPlayerX::Draw()
{
	CObjectX::Draw();
}
//====================================
// ��������
//====================================
CPlayerX* CPlayerX::Create(D3DXVECTOR3 pos, int nType)
{
	CPlayerX* pPlayerX = new CPlayerX();
	pPlayerX->Init();
	pPlayerX->SetPos(pos);
	if (nType == 0)
	{
		pPlayerX->SetModel("data/MODEL/player002.x");
	}
	return pPlayerX;
}

//=======================================
//�u���b�N�ƃv���C���[�̓����蔻��
//=======================================
bool CPlayerX::CollisionBlock(CBlockX* pBlockX)
{

	D3DXVECTOR3 blockSize = pBlockX->GetSize();		// �u���b�N(�I�u�W�F�N�g��)�T�C�Y�擾
	D3DXVECTOR3 blockPos = pBlockX->GetPos();		// �u���b�N(�I�u�W�F�N�g��)�ʒu�擾

	D3DXVECTOR3 playerSize = this->GetSize();		// �v���C���[�̃T�C�Y���擾
	D3DXVECTOR3 playerPos = this->GetPos();         // �v���C���[�̈ʒu�擾


//**===================x��z��y�̓����蔻��==========================**

// �c���͈͓̔��ɓ����Ă��邩
	if ((playerPos.x + playerSize.x * 0.5f >= blockPos.x - blockSize.x * 0.5f) &&		//�u���b�N�ɂ߂荞��
		(playerPos.x - playerSize.x * 0.5f <= blockPos.x + blockSize.x * 0.5f) &&
		(playerPos.z + playerSize.z * 0.5f >= blockPos.z - blockSize.z * 0.5f) &&
		(playerPos.z - playerSize.z * 0.5f <= blockPos.z + blockSize.z * 0.5f) &&
		(playerPos.y + playerSize.y * 0.5f >= blockPos.y - blockSize.y * 0.5f) &&
		(playerPos.y - playerSize.y * 0.5f <= blockPos.y + blockSize.y * 0.5f))
	{
		// �����������Ă���Ƃ�(�����ゾ��)
		if ((playerPos.y >= blockPos.y - blockSize.y * 0.5f) &&
			(playerPos.y <= blockPos.y + blockSize.y * 0.5f))
		{   // �c�͈͓̔���������

				//**===============z���̔���=====================**

				//������̂߂荞��
			if (m_posOld.z >= blockPos.z + blockSize.z * 0.5f + playerSize.z * 0.5f &&
				playerPos.z <= blockPos.z + blockSize.z * 0.5f + playerSize.z * 0.5f)
			{//
				playerPos.z = blockPos.z + blockSize.z * 0.5f + playerSize.z * 0.5f; // �����Ԃ�
				m_pos = playerPos;
			}
			//��O����̂߂荞��
			else if (m_posOld.z <= blockPos.z - blockSize.z * 0.5f - playerSize.z * 0.5f &&
				playerPos.z >= blockPos.z - blockSize.z * 0.5f - playerSize.z * 0.5f)
			{//
				playerPos.z = blockPos.z - blockSize.z * 0.5f - playerSize.z * 0.5f; // �����Ԃ�
				m_pos = playerPos;
			}
			//**===============x���̔���=====================**

			//������̂߂荞��
			if (m_posOld.x >= blockPos.x + blockSize.x * 0.5f + playerSize.x * 0.5f &&
				playerPos.x <= blockPos.x + blockSize.x * 0.5f + playerSize.x * 0.5f)
			{//
				playerPos.x = blockPos.x + blockSize.x * 0.5f + playerSize.x * 0.5f; // �����Ԃ�
				m_pos = playerPos;
			}
			//�E����̂߂荞��
			else if (m_posOld.x <= blockPos.x - blockSize.x * 0.5f - playerSize.x * 0.5f &&
				playerPos.x >= blockPos.x - blockSize.x * 0.5f - playerSize.x * 0.5f)
			{//
				playerPos.x = blockPos.x - blockSize.x * 0.5f - playerSize.x * 0.5f; // �����Ԃ�
				m_pos = playerPos;
			}
		}
		//**===============y���̔���=====================**
		//�ォ��̂߂荞��
		if (m_posOld.y >= blockPos.y + blockSize.y * 0.5f + playerSize.y * 0.5f &&
			playerPos.y <= blockPos.y + blockSize.y * 0.5f + playerSize.y * 0.5f)
		{//
			playerPos.y = blockPos.y + blockSize.y * 0.5f + playerSize.y * 0.5f; // �����Ԃ�
			m_pos = playerPos;
		}
		//������̂߂荞��
		else if (m_posOld.y <= blockPos.y - blockSize.y * 0.5f - playerSize.y * 0.5f &&
			playerPos.y >= blockPos.y - blockSize.y * 0.5f - playerSize.y * 0.5f)
		{//
			playerPos.y = blockPos.y - blockSize.y * 0.5f - playerSize.y * 0.5f; // �����Ԃ�
			m_pos = playerPos;
		}

	}
	
	return false;
}


void CPlayerX::Collision()
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
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // �v���C���[�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					//CDamage::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z));
					CLife::HitLife(10);
				}
				else
				{// �������ĂȂ��Ƃ�
				}

			}
			if (type == CObject::TYPE::MARKER)
			{

				CMarker* pMarker = (CMarker*)pObj; //�_�E���L���X�g
				int nType = 0;
				nType = pMarker->GetType();
				D3DXVECTOR3 markerPos = pMarker->GetPos();
				D3DXVECTOR3 markerSize = pMarker->GetSize();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(markerPos.x, markerPos.y, markerPos.z), halfWidths1(markerSize.x, markerSize.y, markerSize.z);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // �v���C���[�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					switch (nType)
					{
					case 1:
						CFade::SetFade(CScene::MODE::MODE_RESULT);
						break;
					case 2:
						CFade::SetFade(CScene::MODE::MODE_GAME_SECOND);
						break;
					case 3:
						CFade::SetFade(CScene::MODE::MODE_GAME_THIRD);
						break;
					case 4:
						CFade::SetFade(CScene::MODE::MODE_GAME);
						break;
					}
				}
				else
				{// �������ĂȂ��Ƃ�
				}

			}

			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}


}



