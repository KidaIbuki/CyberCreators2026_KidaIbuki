//=================================
// 
// �V�[���N���X�@scene.cpp
//outher kida ibuki 
// 
//==================================
#include "title.h"
#include "manager.h"
#include "fade.h"
#include "field.h"
#include "sound.h"
#include "blockX.h"
//�ÓI�����o�ϐ�������
LPDIRECT3DTEXTURE9 CTitle::m_pTextureTemp = {};

//====================================
// �R���X�g���N�^
//====================================
CTitle::CTitle()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

}
//====================================
// �f�X�g���N�^
//====================================
CTitle::~CTitle()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CTitle::Init()
{
	CScene::Init();
	CManager* pManager = CManager::GetInstance();

	SetModel_File();

	SetSize(620, 200);

	SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	CField::Load();

	//��
	for (int i = 0; i < 7; i++)
	{
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, 114.0f));		//3D�I�u�W�F�N�g�̐���
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, -114.0f));		//3D�I�u�W�F�N�g�̐���
	}
	// �T�E���h�𗬂�
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);


	return S_OK;
}
//====================================
// �I������
//====================================
void CTitle::Uninit()
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

	CField::Unload();

	// �T�E���h���~�߂�
	pManager->GetSound()->StopSound();
}
//====================================
// �X�V����
//====================================
void CTitle::Update()
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
		// �T�E���h�𗬂�
		pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SELECT);
		CFade::SetFade(CScene::MODE::MODE_TUTORIAL);

	}
}
//====================================
// �`�揈��
//====================================
void CTitle::Draw()
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
HRESULT CTitle::Load()
{
	CManager* pManager = CManager::GetInstance();

	//�|�C���^��null�Ȃ�
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\titleLogo.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//�A�����[�h
//======================================
void CTitle::Unload()
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
CTitle* CTitle::Create()
{
	CTitle* pTitle = new CTitle();
	pTitle->Init();
	if (m_pTextureTemp != nullptr)
	{
		pTitle->BindTexture(m_pTextureTemp);
	}

	return pTitle;
}
//===========================================
//���f���t�@�C���̓ǂݍ���(�X�e�[�W1)
//===========================================
void CTitle::SetModel_File()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//���f���̃p�X�̒���
	int nSaveModel = 0;
	int nCntModel = 0;  // �ǂݍ��񂾃��f���t�@�C���̃J�E���g�� MEMO �ϐ���1�Ŋ��������Ȃ��I
	//int nLoadData;

	//�t�@�C�����J��
	FILE* pFile = fopen("data\\TXT\\SetModel_File.txt", "r");

	if (pFile == NULL)
	{
		return;
	}

	while (1)
	{
		fscanf(pFile, "%s", cFileModel);

		if (!strcmp(cFileModel, "END_OBJECTSET"))
		{
			fclose(pFile);
			break;
		}
		if (cFileModel[0] == '#')
		{
			continue;		//�J��Ԃ��B�A���œǂݍ��݂����̂�
		}
		if (!strcmp(cFileModel, "NUM_MODEL"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//���f���̖��O����������
		if (!strcmp(cFileModel, "MODEL_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &m_gModelData[nCntModel].cFile[0]);
			m_gModelData[nCntModel].nType = nCntModel;  // type�Ɍ��݂̃J�E���g�ɂ���(����ɂ��ォ��0�C1�C2...�Ɛݒ�ł���)
			nCntModel++;
		}


		//���f���ݒ�
		if (!strcmp(cFileModel, "MODELSET"))
		{
			// TODO: �����l
			int nType = 0;
			D3DXVECTOR3 pos, rot;

			while (1)
			{
				fscanf(pFile, "%s", cFileModel);

				if (!strcmp(cFileModel, "END_MODELSET"))
				{
					CManager* pManager = CManager::GetInstance();
					// �f�o�C�X�̎擾
					LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
					// �ꎞ�ϐ�(�O���t�@�C���œǂݎ���������i�[)
					LPD3DXMESH pMesh = nullptr;			//���b�V���ւ̃|�C���^
					LPD3DXBUFFER pBuffMat = nullptr;    //�}�e���A���ւ̃|�C���^
					DWORD dwNumMat = 0;           //�}�e���A���̐�

					for (int nCntE = 0; nCntE < nSaveModel; nCntE++)
					{
						if (nType == m_gModelData[nCntE].nType)
						{
							//�t�@�C����ݒ肵�����f�����ǂݍ���
							D3DXLoadMeshFromX(&m_gModelData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

						}
					}
					// Create�֐��Ɋi�[�������������œn��
					CBlockX::Create(pos, rot, pMesh, pBuffMat, dwNumMat)->SizeVtx();

					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "POS"))
				{// �I�u�W�F�N�g�̈ʒu���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &pos.x);
					fscanf(pFile, "%f", &pos.y);
					fscanf(pFile, "%f", &pos.z);

				}
				else if (!strcmp(cFileModel, "ROT"))
				{// �I�u�W�F�N�g�̌������w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &rot.x);
					fscanf(pFile, "%f", &rot.y);
					fscanf(pFile, "%f", &rot.z);

				}
			}
			nCnt++;
		}
	}
}
