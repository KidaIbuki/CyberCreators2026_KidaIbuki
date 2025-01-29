//=================================
// 
// �`���[�g���A���N���X�@gaem.h
//outher kida ibuki 
// 
//==================================
#include "manager.h"
#include "tutorial.h"

#include "field.h"
#include "objectX.h"
#include "blockX.h"
#include "playerX.h"
#include "marker.h"
#include "attack.h"
#include "sound.h"
#include "ui.h"

//==========================================
// �R���X�g���N�^
//==========================================
CTutorial::CTutorial()
{
	m_nFrame = 1;
}
//==========================================
// �f�X�g���N�^
//==========================================
CTutorial::~CTutorial()
{
}
//==========================================
// �����ݒ�
//==========================================
HRESULT CTutorial::Init()
{
	CManager* pManager = CManager::GetInstance();

	// �T�E���h�𗬂�
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_TUTORIAL);

	//�e�N�X�`���̃��[�h
	CField::Load();

	SetModel_File_tutorial();

	// �ړ��A�U���Ȃǂ�UI
	CUi::Create(D3DXVECTOR2(1100.0f, 650.0f), 0);
	CUi::Create(D3DXVECTOR2(1000.0f, 650.0f), 1);
	CUi::Create(D3DXVECTOR2(1205.0f, 650.0f), 2);
	CUi::Create(D3DXVECTOR2(300.0f, 650.0f), 3);
	CUi::Create(D3DXVECTOR2(200.0f, 650.0f), 4);


	//��
	for (int i = 0; i < 3; i++)
	{
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, 114.0f));		//3D�I�u�W�F�N�g�̐���
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, -114.0f));		//3D�I�u�W�F�N�g�̐���
	}

	CMarker* pMarker = CMarker::Create(D3DXVECTOR3(-100.0f, 25.0f, 0.0f), 0);  // �X�^�[�g�}�[�J�[(�ʒu��ς���ƃv���C���[�̈ʒu���ꏏ�ɕς��)
	CMarker::Create(D3DXVECTOR3(500.0f, 25.0f, 0.0f), 4);  // ���ɍs���}�[�J�[
	D3DXVECTOR3 markerPos = pMarker->GetPos();  // �}�[�J�[�̈ʒu���擾


	// �X�^�[�g�}�[�J�[�̈ʒu�Ƀv���C���[��z�u
	CPlayerX* pPlayerX = CPlayerX::Create(D3DXVECTOR3(markerPos.x, markerPos.y, markerPos.z), 0);
	D3DXVECTOR3 playerPos = pPlayerX->GetPos(); // �v���C���[�̈ʒu���擾

	return S_OK;
}
//==========================================
// �I������
//==========================================
void CTutorial::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	//�e�N�X�`���̃A�����[�h
	CField::Unload();

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
//==========================================
// �X�V����
//==========================================
void CTutorial::Update()
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
			CObject::TYPE type = pObj->GetType();

			pObj->Update();

			if (type == CObject::TYPE::PLAYER_X)
			{
				CPlayerX* pPlayer = (CPlayerX*)pObj; //�_�E���L���X�g
				if (pPlayer != nullptr)
				{

					D3DXVECTOR3 playerPos = pPlayer->GetPos();

					// �e�ʒu�Ƀ`���[�g���A���p�̃e�N�X�`���𒣂�
					if (playerPos.x >= POSITION_NUM_1 && playerPos.x <= POSITION_NUM_2)
					{
						m_Position = POSITION_1;
						m_nFrame = 1;   // �t���[���ɑ��
					}
					else if (playerPos.x >= POSITION_NUM_3 && playerPos.x <= POSITION_NUM_4)
					{
						m_Position = POSITION_2;
						m_nFrame = 1;   // �t���[���ɑ��
					}
					else if (playerPos.x >= POSITION_NUM_5 && playerPos.x <= POSITION_NUM_6)
					{
						m_Position = POSITION_3;
						m_nFrame = 1;   // �t���[���ɑ��
					}
					else
					{
						m_Position = POSITION_NONE;
					}

				}

			}
			pObj = pNext;
		}
	}

	// �e�N�X�`����\��
	switch (m_Position)
	{
	case POSITION_1:
		m_nFrame--;
		if (m_nFrame <= 0)
		{
			CUi::Create(D3DXVECTOR2(640.0f, 120.0f), 5);
		}
		break;
	case POSITION_2:
		m_nFrame--;
		if (m_nFrame <= 0)
		{
			CUi::Create(D3DXVECTOR2(640.0f, 120.0f), 6);
		}
		break;
	case POSITION_3:
		m_nFrame--;
		if (m_nFrame <= 0)
		{
			CUi::Create(D3DXVECTOR2(640.0f, 120.0f), 7);
		}
		break;
	}

}
//==========================================
// �`�揈��
//==========================================
void CTutorial::Draw()
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
//==========================================
// ��������
//==========================================
CTutorial* CTutorial::Create()
{
	CTutorial* pTutorial = new CTutorial();
	pTutorial->Init();
	return pTutorial;
}

//========================================================================================================
//���f���t�@�C���̓ǂݍ���(�`���[�g���A���p)
//===========================================
void CTutorial::SetModel_File_tutorial()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//���f���̃p�X�̒���
	int nSaveModel = 0;
	int nCntModel = 0;  // �ǂݍ��񂾃��f���t�@�C���̃J�E���g�� MEMO �ϐ���1�Ŋ��������Ȃ��I
	//int nLoadData;

	//�t�@�C�����J��
	FILE* pFile = fopen("data\\TXT\\SetModel_File_tutorial.txt", "r");

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
