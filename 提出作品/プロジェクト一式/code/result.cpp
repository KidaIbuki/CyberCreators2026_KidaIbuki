//=================================
// 
// �V�[���N���X�@result.cpp
//outher kida ibuki 
// 
//==================================
#include "result.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
//�ÓI�����o�ϐ�������
LPDIRECT3DTEXTURE9 CResult::m_pTextureTemp = {};
LPDIRECT3DTEXTURE9 CResultLose::m_pTextureTemp = {};

//====================================
// �R���X�g���N�^
//====================================
CResult::CResult()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

}
//====================================
// �f�X�g���N�^
//====================================
CResult::~CResult()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CResult::Init()
{
	CScene::Init();

	CManager* pManager = CManager::GetInstance();

	// �T�E���h�𗬂�
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_CLEAR);

	//SetTexture("data/TEXTURE/titleTest.png");

	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	return S_OK;
}
//====================================
// �I������
//====================================
void CResult::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CScene::Uninit();

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

			pObj->DeathFlag();

			pObj = pNext;

		}
	}

	// �T�E���h���~�߂�
	pManager->GetSound()->StopSound();

}
//====================================
// �X�V����
//====================================
void CResult::Update()
{
	CScene::Update();

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

			pObj->Update();

			pObj = pNext;

		}
	}

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* pKeyboard = pManager->GetKeyboard();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�R���g���[���[�擾


	if (pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_START))
	{
		CFade::SetFade(CScene::MODE::MODE_TITLE);
		//pManager->SetMode(CScene::MODE::MODE_TITLE);
	}
}
//====================================
// �`�揈��
//====================================
void CResult::Draw()
{
	CScene::Draw();

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = pTopObject[nPriority];
		// �ő吔���s���Ȃ̂�while���g�p3
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			pObj->Draw();

			pObj = pNext;

		}
	}

}
#if 1
//=======================================
//���[�h
//=======================================
HRESULT CResult::Load()
{
	CManager* pManager = CManager::GetInstance();

	//�|�C���^��null�Ȃ�
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\resultclear.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//�A�����[�h
//======================================
void CResult::Unload()
{
	//�e�N�X�`�����g�p���Ă�����j��
	if (m_pTextureTemp != nullptr)
	{
		//null�ɂ���
		m_pTextureTemp = nullptr;
	}
}
#endif
//======================================
// �^�C�g���̐���
//======================================
CResult* CResult::Create()
{
	CResult* pResult = new CResult();
	pResult->Init();
	if (m_pTextureTemp != nullptr)
	{
		pResult->BindTexture(m_pTextureTemp);
	}

	return pResult;
}



//====================================
// �R���X�g���N�^
//====================================
CResultLose::CResultLose()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

}
//====================================
// �f�X�g���N�^
//====================================
CResultLose::~CResultLose()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CResultLose::Init()
{
	CManager* pManager = CManager::GetInstance();

	CScene::Init();

	// �T�E���h�𗬂�
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_LOSE);

	//SetTexture("data/TEXTURE/titleTest.png");

	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	return S_OK;
}
//====================================
// �I������
//====================================
void CResultLose::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CScene::Uninit();

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

			pObj->DeathFlag();

			pObj = pNext;

		}
	}

	// �T�E���h���~�߂�
	pManager->GetSound()->StopSound();

}
//====================================
// �X�V����
//====================================
void CResultLose::Update()
{
	CScene::Update();

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

			pObj->Update();

			pObj = pNext;

		}
	}

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* pKeyboard = pManager->GetKeyboard();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�R���g���[���[�擾


	if (pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_START))
	{
		CFade::SetFade(CScene::MODE::MODE_GAME);
		//pManager->SetMode(CScene::MODE::MODE_GAME);
	}
}
//====================================
// �`�揈��
//====================================
void CResultLose::Draw()
{
	CScene::Draw();

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = pTopObject[nPriority];
		// �ő吔���s���Ȃ̂�while���g�p3
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			pObj->Draw();

			pObj = pNext;

		}
	}

}
#if 1
//=======================================
//���[�h
//=======================================
HRESULT CResultLose::Load()
{
	CManager* pManager = CManager::GetInstance();

	//�|�C���^��null�Ȃ�
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\resultlose.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//�A�����[�h
//======================================
void CResultLose::Unload()
{
	//�e�N�X�`�����g�p���Ă�����j��
	if (m_pTextureTemp != nullptr)
	{
		//null�ɂ���
		m_pTextureTemp = nullptr;
	}
}
#endif
//======================================
// �^�C�g���̐���
//======================================
CResultLose* CResultLose::Create()
{
	CResultLose* pResultLose = new CResultLose();
	pResultLose->Init();
	if (m_pTextureTemp != nullptr)
	{
		pResultLose->BindTexture(m_pTextureTemp);
	}

	return pResultLose;
}
