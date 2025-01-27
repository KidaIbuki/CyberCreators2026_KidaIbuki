//=================================
// 
// �K�w�\��player�@playerM.h
//outher kida ibuki 
// 
//==================================
#include "manager.h"     // �}�l�[�W���[
#include "playerM.h"   // �v���C���[
#include "bullet.h"    // �e
#include "target.h"    // ���e�B�N��
#include "blockX.h"    // �u���b�N
#include "marker.h"    // �}�[�J�[
#include "ui.h"        // UI
#include "obb.h"
#include "effect.h"
#include "ray.h"

bool CPlayerM::m_bMove = false;

const float CPlayerM::HALF2 = 0.75f;
const float CPlayerM::HALF1 = 0.5f;
const float CPlayerM::HALF = 0.25f;

const float CPlayerM::MOVE_SPEED = 0.25f;

const int CPlayerM::OVER = 190;   // ���E
const int CPlayerM::OVER_UP = 200;  // ��
const int CPlayerM::OVER_DOWN = 100;  // ��
const int CPlayerM::FRAMECNT = 40;   // �t���[���̃J�E���g(�e�̔��ˊԊu��ς����)

//===============================
// �R���X�g���N�^
//===============================
CPlayerM::CPlayerM()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_rotMove = { 0.0f,0.0f,0.0f };
	m_type = BULLET_NONE;
	m_state = STATE_NONE;
	m_nFrameCnt = FRAMECNT;
}
//===============================
// �f�X�g���N�^
//===============================
CPlayerM::~CPlayerM()
{

}
//===============================
// �����ݒ�
//===============================
HRESULT CPlayerM::Init()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾

	// ���f���p�[�c�̐���
	m_pModel = CModelParts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 0);   // ���f���̍ŏ��̈ʒu�����߂�

	// �e���f���p�[�c�̐ݒ�
	m_pModel->aModel[0].nIdxModelParent = -1;

	SetType(CObject::TYPE::PLAYER_M);

	return S_OK;
}
//===============================
// �I������
//===============================
void CPlayerM::Uninit()
{
}
//===============================
// �X�V����
//===============================
void CPlayerM::Update()
{
	CManager* pManager = CManager::GetInstance();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�R���g���[���[�擾
	CInputMouse* pMouse = pManager->GetMouse();    //�R���g���[���[�擾

	// ���f���ɑ����t����

	if (m_bMove == true)
	{
		// �ړ��ʂ̍X�V
		m_move += PlayerMove();
		// pos�𓮂���
		m_pos += m_move;

		// rot�𓮂���
		m_rot += m_rotMove;

		//���ɓ������B
		m_pos.z += 4.0f;

		CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 10.0f, m_pos.z), D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f), 0, 5.0f, 1.0f, 0.0f, 5);

	}
	//�ړ��ʂ�����
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;

	//��]������
	m_rotMove.x += (0.0f - m_rotMove.x) * 0.1f;
	m_rotMove.z += (0.0f - m_rotMove.z) * 0.1f;
	m_rotMove.y += (0.0f - m_rotMove.y) * 0.1f;
	// ��]�̐���
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z -= D3DX_PI * 2;
	}
	else if (m_rot.z < -D3DX_PI)
	{
		m_rot.z += D3DX_PI * 2;
	}

	bool bSwitch = pManager->GetSwitching();   // �z�[�~���O�ƒʏ�e�̐؂�ւ�

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
			if (type == CObject::TYPE::TARGET)
			{
				CTarget* pTarget = (CTarget*)pObj; //�_�E���L���X�g
				if (pTarget != nullptr)
				{
					D3DXVECTOR3 targetPos = pTarget->GetPos();
					if (m_bMove == true)
					{
						//if (bSwitch == false)
						//{// �Ə��͈̔͊O��������ʏ�e
							if (m_type == BULLET_NONE)
							{

								if (pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_A) || pMouse->GetTrigger(pMouse->MOUSEBUTTON_LEFT))
								{
									// �T�E���h�𗬂�
									pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT);

									D3DXVECTOR3 bulletAngle;

									//======================�x�N�g�����g���ă��e�B�N���ɒe���΂�===============================================
									bulletAngle = D3DXVECTOR3(targetPos.x * 0.5f, targetPos.y * 0.5f, targetPos.z) - D3DXVECTOR3(m_pos.x * 0.5f, m_pos.y * 0.5f, m_pos.z);  // �e�̈ʒu���烌�e�B�N���̃x�N�g�������߂�
									D3DXVec3Normalize(&bulletAngle, &bulletAngle);   // ������1�ɂȂ�

									CBullet::Create(m_pos, bulletAngle * 10.0f);
									// MEMO target��pos������Ă��邩�Abullet��move������������
									// x��y�̒l���{�ɂȂ��Ă�
									m_type = BULLET_SHOT;

								}
							}
							// �A�˖h�~���邽�߂̂��
							else if (m_type == BULLET_SHOT)
							{
								m_nFrameCnt--;
								if (m_nFrameCnt <= 0)
								{
									m_type = BULLET_NONE;
									m_nFrameCnt = FRAMECNT;
								}
							}

						//}

					}
				}
			}
			//if (type == CObject::TYPE::ENEMY_X)
			//{
			//	CEnemyX* pEnemy = (CEnemyX*)pObj; //�_�E���L���X�g

			//	D3DXVECTOR3 enemyPos = pEnemy->GetPos();

			//	if (m_bMove == true)
			//	{
			//		if (bSwitch == true)
			//		{// �Ə��͈͓̔��ɓ�������z�[�~���O

			//			if (m_type == BULLET_NONE)
			//			{

			//				if (pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_A) || pMouse->GetTrigger(pMouse->MOUSEBUTTON_RIGHT))
			//				{
			//					// �T�E���h�𗬂�
			//					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT);

			//					D3DXVECTOR3 HomingAngle, position;
			//					HomingAngle = D3DXVECTOR3(enemyPos.x * 0.5f, enemyPos.y * 0.5f, enemyPos.z) - D3DXVECTOR3(m_pos.x * 0.5f, m_pos.y * 0.5f, m_pos.z);  // �e�̈ʒu���烌�e�B�N���̃x�N�g�������߂�
			//					D3DXVec3Normalize(&HomingAngle, &HomingAngle);    // �x�N�g���𐳋K��
			//					position = enemyPos - m_pos;   // �G�ƃv���C���[�̃x�N�g�������߂�
			//					D3DXVec3Normalize(&position, &position);    // �x�N�g���𐳋K��

			//					// �G�����ɍs������e�͌����Ȃ�
			//					//if (D3DXVec3Length(&position) >= 400)   // �G�����苗������Ă�����ȉ��̏��������Ȃ�(�e���΂��Ȃ�)
			//					//{
			//					//}
			//						CBullet::Create(m_pos, position * 10.0f);


			//					m_type = BULLET_SHOT;



			//				}
			//			}
			//			// �A�˖h�~���邽�߂̂��
			//			else if (m_type == BULLET_SHOT)
			//			{
			//				m_nFrameCnt--;
			//				if (m_nFrameCnt <= 0)
			//				{
			//					m_type = BULLET_NONE;
			//					m_nFrameCnt = FRAMECNT;
			//				}
			//			}

			//		}
			//	}


			//}
			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}


	Collision();  // �v���C���[�֌W�̓����蔻��
	// ========================��ʊO�ɏo�Ȃ��悤�ɂ���=================================
	// ��
	if (m_pos.x < -OVER)
	{
		m_pos.x = -OVER;
	}
	//�E
	if (m_pos.x > OVER)
	{
		m_pos.x = OVER;
	}
	//��
	if (m_pos.y < -OVER_DOWN)
	{
		m_pos.y = -OVER_DOWN;
	}
	// ��
	if (m_pos.y > OVER_UP)
	{
		m_pos.y = OVER_UP;
	}

}
//===================================
// �v���C���[�̈ړ�����
//===================================
D3DXVECTOR3 CPlayerM::PlayerMove()
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();	//�L�[�{�[�h�擾
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�R���g���[���[�擾

	D3DXVECTOR3 move = { 0,0,0 };

	//**========�J�����̏��==========**
	CCamera* pCamera = pManager->GetCamera();  //�J�����̎擾
	D3DXVECTOR3 rot = pCamera->GetRot();	//����

	// �{�X��O�͈͓̔���������
	if (m_pos.z >= 0.0f && m_pos.z <= POSITION1)
	{
		if (pKeyboard->GetPress(DIK_D) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
		{//A�L�[�������ꂽ�ꍇ
			if (pKeyboard->GetPress(DIK_D) && pKeyboard->GetPress(DIK_W) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
			{
				move.x -= sinf(rot.y - D3DX_PI * HALF2) * MOVE_SPEED;
				move.y -= cosf(rot.y - D3DX_PI * HALF2) * MOVE_SPEED;
				//m_rot.y = D3DX_PI * -HALF2 - rot.y;
			}
			else if (pKeyboard->GetPress(DIK_D) && pKeyboard->GetPress(DIK_S) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
			{
				move.x -= sinf(rot.y - D3DX_PI * HALF) * MOVE_SPEED;
				move.y -= cosf(rot.y - D3DX_PI * HALF) * MOVE_SPEED;
			}
			else
			{
				move.x -= sinf(rot.y - D3DX_PI * HALF1) * MOVE_SPEED;
				move.y -= cosf(rot.y - D3DX_PI * HALF1) * MOVE_SPEED;
			}

		}
		else if (pKeyboard->GetPress(DIK_A) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT))
		{//D�L�[�������ꂽ�ꍇ

			if (pKeyboard->GetPress(DIK_A) && pKeyboard->GetPress(DIK_W) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
			{
				move.x -= sinf(rot.y + D3DX_PI * HALF2) * MOVE_SPEED;
				move.y -= cosf(rot.y + D3DX_PI * HALF2) * MOVE_SPEED;

			}
			else if (pKeyboard->GetPress(DIK_A) && pKeyboard->GetPress(DIK_S) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
			{
				move.x -= sinf(rot.y + D3DX_PI * HALF) * MOVE_SPEED;
				move.y -= cosf(rot.y + D3DX_PI * HALF) * MOVE_SPEED;
			}
			else
			{
				move.x -= sinf(rot.y + D3DX_PI * HALF1) * MOVE_SPEED;
				move.y -= cosf(rot.y + D3DX_PI * HALF1) * MOVE_SPEED;
			}
		}
		else if (pKeyboard->GetPress(DIK_W) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
		{//W�L�[�������ꂽ�ꍇ
			{
				move.y += MOVE_SPEED;
			}
		}
		else if (pKeyboard->GetPress(DIK_S) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
		{//S�L�[�������ꂽ�ꍇ
			{
				move.y -= MOVE_SPEED;

			}
		}
		if (pKeyboard->GetPress(DIK_E) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT_SHOULDER))
		{
			//m_rot.z = D3DX_PI * 0.5;
			m_rotMove.z += 0.005f;
		}
		else if (pKeyboard->GetPress(DIK_Q) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT_SHOULDER))
		{
			m_rotMove.z -= 0.005f;
		}
		else
		{
			m_rot.z += (0.0f - m_rot.z) * 0.05f;
		}
	}
	// �{�X��͈͓̔���������
	else if (m_pos.z >= POSITION1)
	{
		if (pKeyboard->GetPress(DIK_W) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
		{//W�L�[�������ꂽ�ꍇ
			move.y += MOVE_SPEED;
		}
		if (pKeyboard->GetPress(DIK_S) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
		{//S�L�[�������ꂽ�ꍇ
			move.y -= MOVE_SPEED;
		}

	}
#ifdef _DEBUG
	if (pKeyboard->GetPress(DIK_U))
	{
		move.z += 0.5;
	}
	if (pKeyboard->GetPress(DIK_J))
	{
		move.z -= 0.5;
	}

#endif

	return move;
}
//==============================================
// �v���C���[��x�������ɖ߂�
//==============================================
void CPlayerM::ResetPlayer()
{
	m_pos.x = 0.0f;
	m_rot.z = 0.0f;
	m_rotMove.z = 0.0f;
}
//===============================================
// �v���C���[�̓����蔻��(�L�����E�{�b�N�X)
//===============================================
#if 0
bool CPlayerM::CollisionPlayer()
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
			if (type == CObject::TYPE::BLOCK)
			{
				CBlockX* pBlock = (CBlockX*)pObj; //�_�E���L���X�g
				D3DXVECTOR3 lengthOBB = pBlock->m_pos - this->m_pos;  // �����̃x�N�g�������߂�

				D3DXVECTOR3 AxisPlayerX, AxisPlayerY;   // �v���C���[��x,y�����x�N�g��
				D3DXVECTOR3 AxisNPlayerX, AxisNPlayerY;   // �v���C���[��x,y�����@���x�N�g��
				AxisPlayerX.x = m_size.x * cosf(m_rot.z);
				AxisPlayerX.y = m_size.x * sinf(m_rot.z);
				AxisPlayerX.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerX, &AxisPlayerX);   // �@���x�N�g���𐳋K��

				AxisPlayerY.x = m_size.y * sinf(m_rot.z);
				AxisPlayerY.y = m_size.y * cosf(m_rot.z);
				AxisPlayerY.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerY, &AxisPlayerY);   // �@���x�N�g���𐳋K��

				D3DXVECTOR3 AxisBlockX, AxisBlockY;   // �u���b�N��x,y�����x�N�g��
				D3DXVECTOR3 AxisNBlockX, AxisNBlockY;   // �u���b�N��x,y�����@���x�N�g��
				AxisBlockX.x = pBlock->m_size.x * cosf(pBlock->m_rot.z);
				AxisBlockX.y = pBlock->m_size.x * sinf(pBlock->m_rot.z);
				AxisBlockX.z = 0.0f;
				D3DXVec3Normalize(&AxisNBlockX, &AxisBlockX);   // �@���x�N�g���𐳋K��

				AxisBlockY.x = pBlock->m_size.y * sinf(pBlock->m_rot.z);
				AxisBlockY.y = pBlock->m_size.y * cosf(pBlock->m_rot.z);
				AxisBlockY.z = 0.0f;
				D3DXVec3Normalize(&AxisNBlockY, &AxisBlockY);  // �@���x�N�g���𐳋K��

				float rPlayer, rBlock, fLength;  // �v�Z�p�ϐ�

				// ������ : AxisPlayerX
				rPlayer = D3DXVec3Length(&AxisPlayerX);   // �������̒���
				rBlock = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBlockX)) + fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBlockY)); // �u���b�N���̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerX)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rBlock)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisPlayerY
				rPlayer = D3DXVec3Length(&AxisPlayerY);   // �������̒���
				rBlock = fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBlockX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBlockY)); // �u���b�N���̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerY)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rBlock)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisBlockX
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBlockX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBlockX)); // �u���b�N���̒���
				rBlock = D3DXVec3Length(&AxisBlockX);   // �������̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBlockX)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rBlock)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisBlockY
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBlockY)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBlockY)); // �u���b�N���̒���
				rBlock = D3DXVec3Length(&AxisBlockY);   // �������̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBlockY)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rBlock)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}

				if (fabs(lengthOBB.z) < fabs(m_size.z - pBlock->m_size.z))   // ��̒������������傫��������
				{
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // ��ʂ̗h��
					CLife::SubLife(10);
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);

					return true;  // �Փ˂���
				}
			}
			if (type == CObject::TYPE::ENEMY_X)
			{
				CEnemyX* pEnemy = (CEnemyX*)pObj; //�_�E���L���X�g
				D3DXVECTOR3 lengthOBB = pEnemy->m_pos - this->m_pos;  // �����̃x�N�g�������߂�

				D3DXVECTOR3 AxisPlayerX, AxisPlayerY;   // �v���C���[��x,y�����x�N�g��
				D3DXVECTOR3 AxisNPlayerX, AxisNPlayerY;   // �v���C���[��x,y�����@���x�N�g��
				AxisPlayerX.x = m_size.x * cosf(m_rot.z);
				AxisPlayerX.y = m_size.x * sinf(m_rot.z);
				AxisPlayerX.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerX, &AxisPlayerX);   // �@���x�N�g���𐳋K��

				AxisPlayerY.x = m_size.y * sinf(m_rot.z);
				AxisPlayerY.y = m_size.y * cosf(m_rot.z);
				AxisPlayerY.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerY, &AxisPlayerY);   // �@���x�N�g���𐳋K��

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

				float rPlayer, rEnemy, fLength;  // �v�Z�p�ϐ�

				// ������ : AxisPlayerX
				rPlayer = D3DXVec3Length(&AxisPlayerX);   // �������̒���
				rEnemy = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisPlayerX, &AxisEnemyY)); // �G���̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerX)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisPlayerY
				rPlayer = D3DXVec3Length(&AxisPlayerY);   // �������̒���
				rEnemy = fabs(D3DXVec3Dot(&AxisPlayerY, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisEnemyY)); // �G���̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerY)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisBlockX
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisEnemyX)); // �G���̒���
				rEnemy = D3DXVec3Length(&AxisEnemyX);   // �������̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyX)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisBlockY
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisEnemyY)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisEnemyY)); // �G���̒���
				rEnemy = D3DXVec3Length(&AxisEnemyY);   // �������̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyY)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rEnemy)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}

				if (fabs(lengthOBB.z) < fabs(m_size.z - pEnemy->m_size.z))   // ��̒������������傫��������
				{
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // ��ʂ̗h��
					CLife::SubLife(10);
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
					return true;  // �Փ˂���
				}
			}
			if (type == CObject::TYPE::ENEMY_BULLET)
			{
				CBulletEnemy* pBullet = (CBulletEnemy*)pObj; //�_�E���L���X�g
				D3DXVECTOR3 lengthOBB = pBullet->m_pos - this->m_pos;  // �����̃x�N�g�������߂�

				D3DXVECTOR3 AxisPlayerX, AxisPlayerY;   // �v���C���[��x,y�����x�N�g��
				D3DXVECTOR3 AxisNPlayerX, AxisNPlayerY;   // �v���C���[��x,y�����@���x�N�g��
				AxisPlayerX.x = m_size.x * cosf(m_rot.z);
				AxisPlayerX.y = m_size.x * sinf(m_rot.z);
				AxisPlayerX.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerX, &AxisPlayerX);   // �@���x�N�g���𐳋K��

				AxisPlayerY.x = m_size.y * sinf(m_rot.z);
				AxisPlayerY.y = m_size.y * cosf(m_rot.z);
				AxisPlayerY.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerY, &AxisPlayerY);   // �@���x�N�g���𐳋K��

				D3DXVECTOR3 AxisBulletX, AxisBulletY;   // �G�̒e��x,y�����x�N�g��
				D3DXVECTOR3 AxisNBulletX, AxisNBulletY;   // �G�̒e��x,y�����@���x�N�g��
				AxisBulletX.x = pBullet->m_size.x * cosf(pBullet->m_rot.z);
				AxisBulletX.y = pBullet->m_size.x * sinf(pBullet->m_rot.z);
				AxisBulletX.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletX, &AxisBulletX);   // �@���x�N�g���𐳋K��

				AxisBulletY.x = pBullet->m_size.y * sinf(pBullet->m_rot.z);
				AxisBulletY.y = pBullet->m_size.y * cosf(pBullet->m_rot.z);
				AxisBulletY.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletY, &AxisBulletY);  // �@���x�N�g���𐳋K��

				float rPlayer, rBullet, fLength;  // �v�Z�p�ϐ�

				// ������ : AxisPlayerX
				rPlayer = D3DXVec3Length(&AxisPlayerX);   // �������̒���
				rBullet = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBulletX)) + fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBulletY)); // �G�̒e���̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerX)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rBullet)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisPlayerY
				rPlayer = D3DXVec3Length(&AxisPlayerY);   // �������̒���
				rBullet = fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBulletX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBulletY)); // �G�̒e���̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerY)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rBullet)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisBlockX
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBulletX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBulletX)); // �G�̒e���̒���
				rBullet = D3DXVec3Length(&AxisBulletX);   // �������̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletX)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rBullet)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}
				// ������ : AxisBlockY
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBulletY)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBulletY)); // �G�̒e���̒���
				rBullet = D3DXVec3Length(&AxisBulletY);   // �������̒���
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletY)); // ���ɑ΂��Ă̒���
				if (fLength > rPlayer + rBullet)   // ��̒�����������菬����������
				{
					pObj = pNext;
					continue; // �Փ˂��Ă��Ȃ�
				}

				if (fabs(lengthOBB.z) < fabs(m_size.z - pBullet->m_size.z))   // ��̒������������傫��������
				{
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // ��ʂ̗h��
					CLife::SubLife(10);
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
					return true;  // �Փ˂���
				}
			}

			pObj = pNext;
		}
	}
	return false;
}
#endif
void CPlayerM::Collision()
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
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // ��ʂ̗h��
					CLife::SubLife(10);
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// �������ĂȂ��Ƃ�
				}

			}
			if (type == CObject::TYPE::BLOCK)
			{
				CBlockX* pBlock = (CBlockX*)pObj; //�_�E���L���X�g
				D3DXVECTOR3 blockPos = pBlock->GetPos();
				D3DXVECTOR3 blockSize = pBlock->GetSize();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(blockPos.x, blockPos.y, blockPos.z), halfWidths1(blockSize.x, blockSize.y, blockSize.z);  // �u���b�N�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // �v���C���[�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // ��ʂ̗h��
					CLife::SubLife(10);
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// �������ĂȂ��Ƃ�
				}

			}
			if (type == CObject::TYPE::ENEMY_BULLET)
			{
				CBulletEnemy* pBullet = (CBulletEnemy*)pObj; //�_�E���L���X�g
				D3DXVECTOR3 BulletPos = pBullet->GetPos();
				D3DXVECTOR3 BulletSize = pBullet->GetSize();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(BulletPos.x, BulletPos.y, BulletPos.z), halfWidths1(BulletSize.x, BulletSize.y, BulletSize.z);  // �G�̒e�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // �v���C���[�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // ��ʂ̗h��
					CLife::SubLife(10);
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// �������ĂȂ��Ƃ�
				}

			}

			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}


}
#if 0
void CPlayerM::LockOnEnemy()
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

				D3DXVECTOR3 m_position;
				bool m_isRockOn = false;
				// �v���C���[�̌����Ă���p�x���v�Z
				float degreep = atan2f(m_pos.x, m_pos.z);
				// �v�Z�ŏo����ԏ������p�x���L��
				float degreemum = D3DX_PI * 2;
				D3DXVECTOR3 pos = m_position - pEnemy->GetPos();
				// �v���C���[�ƓG�̋��������O�������珈�����X�L�b�v
				if (D3DXVec3Length(&pos) >= 500)
				{
					pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
					continue;
				}
				// �v���C���[�ƓG�����ԃx�N�g�����o��
				D3DXVECTOR3 pos2 = pEnemy->GetPos() - m_position;
				// ������0�ɂ���
				pos2.y = 0.0f;
				D3DXVec3Normalize(&pos2, &pos2);
				// �v���C���[�ƓG�����ԃx�N�g���̊p�x���v�Z
				float degree = atan2f(pos2.x, pos2.z);
				// �v���C���[�̐��ʂ̃x�N�g���̊p�x�ƃv���C���[�ƓG�����ԃx�N�g���̊p�x�̍����v�Z
				if (D3DX_PI <= (degreep - degree))
				{
					degree = degreep - degree - D3DX_PI * 2;
				}
				else if (-D3DX_PI >= (degreep - degree))
				{
					degree = degreep - degree + D3DX_PI * 2;
				}
				else
				{
					degree = degreep - degree;
				}
				// ���߂��p�x�Ƀv���C���[�ƓG�̋����ɉ����ĕ␳��������
				degree = degree + degree * (D3DXVec3Length(&pos) / 500) * 0.3f;
				// ���߂��l���r���āA��ԏ������l�����߂�
				if (fabs(degreemum) >= fabs(degree))
				{
					degreemum = degree;
				}
				// ���߂���ԏ������l�����l��菬�����ꍇ�^�[�Q�b�g���I���ɂ���
				if (fabs(degreemum) <= D3DX_PI / 3)
				{
					m_isRockOn = true;
				}
				// �t�Ɉ��l���傫���ꍇ�^�[�Q�b�g���I�t�ɂ���
				else
				{
					m_isRockOn = false;
				}
			}
			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}

}
#endif
//===============================
// �`�揈��
//===============================
void CPlayerM::Draw()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾
	
	D3DXMATRIX mtxRot, mtxTrans;											// �v�Z�p�}�g���b�N�X


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�ϊ��s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���p�[�c�̕`��
	m_pModel->Draw();

}

//===============================
// ����
//===============================
CPlayerM* CPlayerM::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayerM* pPlayer = new CPlayerM();
	pPlayer->Init();
	pPlayer->SetPos(pos);
	pPlayer->SetRot(rot);

	return pPlayer;
}
//===================================
// �ʒu�̐ݒ�
//===================================
void CPlayerM::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//===================================
// �����̐ݒ�
//===================================
void CPlayerM::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
