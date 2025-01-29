//=================================
// 
//�J�����N���X�@camera.cpp
//outher kida ibuki 
// 
//==================================
#include "camera.h"
#include "manager.h"
#include "objectX.h"
#include "playerX.h"
#include "title.h"
//==============================
//�R���X�g���N�^
//==============================
CCamera::CCamera()
{
}
//==============================
//�f�X�g���N�^
//==============================
CCamera::~CCamera()
{
}
//==============================
//�����ݒ�
//==============================
HRESULT CCamera::Init()
{
	//�����o�ϐ�������
	m_posV = { -70.0f, 130.0f, -270.0f };			// ���_
	m_posR = { 0.0f, 40.0f, 60.0f };		        // �����_
	m_vecU = { 0.0f, 1.0f, 0.0f };				// �����
	m_rot = { D3DX_PI * 0.5f, 0.0f, 0.0f };
    m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(100 * 100 + -250 * -250);		//����
	m_fScaleDis = 1.0f;	//�{��

	m_nShakeFrame = 0;
	m_nShakeVolume = 0;
	m_move = { 0.0f,0.0f,0.0f };

	return S_OK;

}
//==============================
//�I������
//==============================
void CCamera::Uninit()
{
}
//==============================
//�X�V����
//==============================
void CCamera::Update()
{
	CManager* pManager = CManager::GetInstance();	//�}�l�[�W���[�̃C���X�^���X���擾
    	
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
			if (type == CObject::TYPE::PLAYER_X)
			{
				CPlayerX* pPlayer = (CPlayerX*)pObj; //�_�E���L���X�g
				if (pPlayer != nullptr)
				{

					D3DXVECTOR3 playerPos = pPlayer->GetPos(); // �v���C���[�̈ʒu���擾

					m_posR = playerPos;  // �����_�̒Ǐ]
					m_posV.y = playerPos.y + 80.0f;  //���_���Œ蒍���_�ɍ��킵�ĒǏ]  +�`�͎x�X�̍���
					//�J�����̎��_�̒Ǐ]
					m_posV.x = sinf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + playerPos.x;
					m_posV.z = cosf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + playerPos.z;
				}
			}
			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}

	CScene* pScene = pManager->GetScene();
	CScene::MODE mode = pScene->GetMode();
	// ���[�h�̎擾
	if (mode == CScene::MODE::MODE_TITLE)
	{// �^�C�g����ʂ�z�������ɃJ�������ړ�������
		m_rot.y += 0.002f;

		//�����_�𒆐S�Ɍ��]
		m_posV.x = sinf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis;
		m_posV.z = cosf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis;

	}

}
//==============================
//�J�����ݒ�
//==============================
void CCamera::SetCamera()
{
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);


	// �v���W�F�N�V�����}�g���b�N�X���쐬(�������e)
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,		//near
		5000.0f);   //far


	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	//D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// �J�����̗h��
	D3DXVECTOR3 adjust = { 0.0f,0.0f,0.0f };
	if (m_nShakeFrame > 0)
	{
		m_nShakeFrame--;
		adjust.x = (float)(rand() % m_nShakeVolume);
		adjust.y = (float)(rand() % m_nShakeVolume);
		//adjust.z = random;
	}
	D3DXVECTOR3 posR, posV;
	posR = m_posR + adjust;  // �����_
	posV = m_posV + adjust;  // ���_
	D3DXMatrixLookAtLH(&m_mtxView, &posV, &posR, &m_vecU);
	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//==============================
//�J�����̃��Z�b�g
//==============================
void CCamera::ResetCamera()
{
	m_posV = { -70.0f, 130.0f, -270.0f };			// ���_
	m_posR = { 0.0f, 40.0f, 60.0f };		        // �����_
	m_vecU = { 0.0f, 1.0f, 0.0f };				// �����
	m_rot = { D3DX_PI * 0.5f, 0.0f, 0.0f };
	m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(100 * 100 + -250 * -250);		//����
	m_fScaleDis = 1.0f;	//�{��

}
//==============================
//�J�����̈ʒu�ݒ�
//==============================
void CCamera::SetPos(D3DXVECTOR3 pos)
{
	m_posR = pos;
}
//==============================
// �J�����̗h��̐ݒ�
//==============================
void CCamera::SetShake(int shakeFrame, float shakeVolume)
{
	m_nShakeFrame = shakeFrame;
	m_nShakeVolume = (int)shakeVolume;
}


