//=================================
// 
// �Q�[�������N���X�@game.cpp
//outher kida ibuki 
// 
//==================================
#include "game.h"
#include "manager.h"
//======3D==============
#include "explosion.h"
#include "field.h"
#include "objectX.h"
#include "blockX.h"
#include "playerX.h"
#include "marker.h"
#include "enemyX.h"
//======UI==============
#include "life.h"
#include "ui.h"
//======�T�E���h========
#include "sound.h"

//====================================
// �R���X�g���N�^
//====================================
CGame::CGame()
{
	m_bPause = false;
}
//====================================
// �f�X�g���N�^
//====================================
CGame::~CGame()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CGame::Init()
{
	CManager* pManager = CManager::GetInstance();

	SetModel_File();
	SetEnemy_File();
	// �T�E���h�𗬂�
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_GAME001);

	//**==========================3D�I�u�W�F�N�g===========================**
	//�e�N�X�`���̃��[�h
	CField::Load();
	CLife::Load();   // ���C�tUI
	CExplosion::Load();

	CLife::Create(D3DXVECTOR2(100.0f, 50.0f));

	// �ړ��A�U���Ȃǂ�UI
	CUi::Create(D3DXVECTOR2(1100.0f, 650.0f), 0);
	CUi::Create(D3DXVECTOR2(1000.0f, 650.0f), 1);
	CUi::Create(D3DXVECTOR2(1205.0f, 650.0f), 2);
	CUi::Create(D3DXVECTOR2(300.0f, 650.0f), 3);
	CUi::Create(D3DXVECTOR2(200.0f, 650.0f), 4);

		//��
	for (int i = 0; i < 7; i++)
	{
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, 114.0f));		//3D�I�u�W�F�N�g�̐���
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, -114.0f));		//3D�I�u�W�F�N�g�̐���
	}


	CMarker* pMarker = CMarker::Create(D3DXVECTOR3(-100.0f, 25.0f, 0.0f), 0);  // �X�^�[�g�}�[�J�[(�ʒu��ς���ƃv���C���[�̈ʒu���ꏏ�ɕς��)
	CMarker::Create(D3DXVECTOR3(1300.0f, 25.0f, 0.0f), 2);  // ���ɍs���}�[�J�[
	D3DXVECTOR3 markerPos = pMarker->GetPos();  // �}�[�J�[�̈ʒu���擾

	// �X�^�[�g�}�[�J�[�̈ʒu�Ƀv���C���[��z�u
	CPlayerX* pPlayerX = CPlayerX::Create(D3DXVECTOR3(markerPos.x, markerPos.y, markerPos.z), 0);
	D3DXVECTOR3 playerPos = pPlayerX->GetPos(); // �v���C���[�̈ʒu���擾


	return S_OK;
}
//====================================
// �I������
//====================================
void CGame::Uninit()
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


    //�e�N�X�`���̃A�����[�h
	CField::Unload();
	CLife::Unload();   // ���C�tUI
	CExplosion::Unload();

	// �T�E���h���~�߂�
	pManager->GetSound()->StopSound();

}
//====================================
// �X�V����
//====================================
void CGame::Update()
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

}
//====================================
// �`�揈��
//====================================
void CGame::Draw()
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
//======================================
// �Q�[���̐���
//======================================
CGame* CGame::Create()
{
	CGame* pGame = new CGame();
	pGame->Init();
	return pGame;
}

//======================================================================
//�Q�ڂ̃X�e�[�W���
//======================================================================��



//====================================
// �R���X�g���N�^
//====================================
CGameSecond::CGameSecond()
{
	m_bPause2 = false;
}
//====================================
// �f�X�g���N�^
//====================================
CGameSecond::~CGameSecond()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CGameSecond::Init()
{

	CManager* pManager = CManager::GetInstance();

	SetModel_File2();
	SetEnemy_File2();
	// �T�E���h�𗬂�
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_GAME002);

	//**==========================3D�I�u�W�F�N�g===========================**
	//�e�N�X�`���̃��[�h
	CField::Load();
	CLife::Load();   // ���C�tUI
	CExplosion::Load();

	CLife::Create(D3DXVECTOR2(100.0f, 50.0f));
	// �ړ��A�U���Ȃǂ�UI
	CUi::Create(D3DXVECTOR2(1100.0f, 650.0f), 0);
	CUi::Create(D3DXVECTOR2(1000.0f, 650.0f), 1);
	CUi::Create(D3DXVECTOR2(1205.0f, 650.0f), 2);
	CUi::Create(D3DXVECTOR2(300.0f, 650.0f), 3);
	CUi::Create(D3DXVECTOR2(200.0f, 650.0f), 4);

	//��
	for (int i = 0; i < 7; i++)
	{
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, 114.0f));		//3D�I�u�W�F�N�g�̐���
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, -114.0f));		//3D�I�u�W�F�N�g�̐���
	}

	CMarker* pMarker = CMarker::Create(D3DXVECTOR3(-100.0f, 25.0f, 0.0f), 0);  // �X�^�[�g�}�[�J�[(�ʒu��ς���ƃv���C���[�̈ʒu���ꏏ�ɕς��)
	CMarker::Create(D3DXVECTOR3(1300.0f, 25.0f, 0.0f), 3);  // �S�[���}�[�J�[
	D3DXVECTOR3 markerPos = pMarker->GetPos();  // �}�[�J�[�̈ʒu���擾

	// �X�^�[�g�}�[�J�[�̈ʒu�Ƀv���C���[��z�u
	CPlayerX::Create(D3DXVECTOR3(markerPos.x, markerPos.y, markerPos.z), 0);


	return S_OK;
}
//====================================
// �I������
//====================================
void CGameSecond::Uninit()
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

	//�e�N�X�`���̃A�����[�h
	CField::Unload();
	CLife::Unload();   // ���C�tUI
	CExplosion::Unload();

		// �T�E���h���~�߂�
	pManager->GetSound()->StopSound();

}
//====================================
// �X�V����
//====================================
void CGameSecond::Update()
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

}
//====================================
// �`�揈��
//====================================
void CGameSecond::Draw()
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
//======================================
// �Q�[���̐���
//======================================
CGameSecond* CGameSecond::Create()
{
	CGameSecond* pGameSecobd = new CGameSecond();
	pGameSecobd->Init();
	return pGameSecobd;
}



//======================================================================
//3�ڂ̃X�e�[�W���
//======================================================================��

//====================================
// �R���X�g���N�^
//====================================
CGameThird::CGameThird()
{
	m_bPause3 = false;
}
//====================================
// �f�X�g���N�^
//====================================
CGameThird::~CGameThird()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CGameThird::Init()
{
	CManager* pManager = CManager::GetInstance();

	SetModel_File3();
	SetEnemy_File3();
	// �T�E���h�𗬂�
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_GAME003);

	//**==========================3D�I�u�W�F�N�g===========================**
//�e�N�X�`���̃��[�h
	CField::Load();
	CLife::Load();   // ���C�tUI
	CExplosion::Load();

	CLife::Create(D3DXVECTOR2(100.0f, 50.0f));
	// �ړ��A�U���Ȃǂ�UI
	CUi::Create(D3DXVECTOR2(1100.0f, 650.0f), 0);
	CUi::Create(D3DXVECTOR2(1000.0f, 650.0f), 1);
	CUi::Create(D3DXVECTOR2(1205.0f, 650.0f), 2);
	CUi::Create(D3DXVECTOR2(300.0f, 650.0f), 3);
	CUi::Create(D3DXVECTOR2(200.0f, 650.0f), 4);

	//��
	for (int i = 0; i < 7; i++)
	{
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, 114.0f));		//3D�I�u�W�F�N�g�̐���
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, -114.0f));		//3D�I�u�W�F�N�g�̐���
	}


	CMarker* pMarker = CMarker::Create(D3DXVECTOR3(-100.0f, 25.0f, 0.0f), 0);  // �X�^�[�g�}�[�J�[(�ʒu��ς���ƃv���C���[�̈ʒu���ꏏ�ɕς��)
	CMarker::Create(D3DXVECTOR3(1300.0f, 25.0f, 0.0f), 1);  // �S�[���}�[�J�[
	D3DXVECTOR3 markerPos = pMarker->GetPos();  // �}�[�J�[�̈ʒu���擾

	// �X�^�[�g�}�[�J�[�̈ʒu�Ƀv���C���[��z�u
	CPlayerX::Create(D3DXVECTOR3(markerPos.x, markerPos.y, markerPos.z), 0);

	return S_OK;
}
//====================================
// �I������
//====================================
void CGameThird::Uninit()
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

	//�e�N�X�`���̃A�����[�h
	CField::Unload();
	CLife::Unload();   // ���C�tUI
	CExplosion::Unload();

	// �T�E���h���~�߂�
	pManager->GetSound()->StopSound();

}
//====================================
// �X�V����
//====================================
void CGameThird::Update()
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

}
//====================================
// �`�揈��
//====================================
void CGameThird::Draw()
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
//====================================
// ��������
//====================================
CGameThird* CGameThird::Create()
{
	CGameThird* pGameThird = new CGameThird();
	pGameThird->Init();
	return pGameThird;
}
//===========================================
//���f���t�@�C���̓ǂݍ���(�X�e�[�W1)
//===========================================
void CGame::SetModel_File()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//���f���̃p�X�̒���
	int nSaveModel = 0;
	int nCntModel = 0;  // �ǂݍ��񂾃��f���t�@�C���̃J�E���g�� MEMO �ϐ���1�Ŋ��������Ȃ��I

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

//========================================================================================================
//���f���t�@�C���̓ǂݍ���(�X�e�[�W2)
//===========================================
void CGame::SetModel_File2()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//���f���̃p�X�̒���
	int nSaveModel = 0;
	int nCntModel = 0;  // �ǂݍ��񂾃��f���t�@�C���̃J�E���g�� MEMO �ϐ���1�Ŋ��������Ȃ��I
	//int nLoadData;

	//�t�@�C�����J��
	FILE* pFile = fopen("data\\TXT\\SetModel_File2.txt", "r");

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
//========================================================================================================
//���f���t�@�C���̓ǂݍ���(�X�e�[�W3)
//===========================================
void CGame::SetModel_File3()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//���f���̃p�X�̒���
	int nSaveModel = 0;
	int nCntModel = 0;  // �ǂݍ��񂾃��f���t�@�C���̃J�E���g�� MEMO �ϐ���1�Ŋ��������Ȃ��I
	//int nLoadData;

	//�t�@�C�����J��
	FILE* pFile = fopen("data\\TXT\\SetModel_File3.txt", "r");

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
//===========================================
//�G�̃��f���t�@�C���̓ǂݍ���(�X�e�[�W1�p)
//===========================================
void CGame::SetEnemy_File()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//���f���̃p�X�̒���
	int nSaveModel = 0;
	int nCntModel = 0;  // �ǂݍ��񂾃��f���t�@�C���̃J�E���g�� MEMO �ϐ���1�Ŋ��������Ȃ��I
	//int nLoadData;

	//�t�@�C�����J��
	FILE* pFile = fopen("data\\TXT\\SetEnemy_File.txt", "r");

	if (pFile == NULL)
	{
		return;
	}

	while (1)
	{
		fscanf(pFile, "%s", cFileModel);

		if (!strcmp(cFileModel, "END_MODEL_ENEMYSET"))
		{
			fclose(pFile);
			break;
		}
		if (cFileModel[0] == '#')
		{
			continue;		//�J��Ԃ��B�A���œǂݍ��݂����̂�
		}
		if (!strcmp(cFileModel, "NUM_ENEMY"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//���f���̖��O����������
		if (!strcmp(cFileModel, "ENEMY_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &g_aEnemyData[nCntModel].cFile[0]);
			g_aEnemyData[nCntModel].nType = nCntModel;  // type�Ɍ��݂̃J�E���g�ɂ���(����ɂ��ォ��0�C1�C2...�Ɛݒ�ł���)
			nCntModel++;
		}


		//���f���ݒ�
		if (!strcmp(cFileModel, "ENEMY_MODELSET"))
		{
			// TODO: �����l
			int nType = 0;
			int nLife = 0;
			int	nDamage = 0;
			D3DXVECTOR3 pos, rot, move1, move2, movey1, movey2;
			float fSpeed = 0.0f;
			float fSpeed1 = 0.0f;

			while (1)
			{
				fscanf(pFile, "%s", cFileModel);

				if (!strcmp(cFileModel, "END_ENEMYSET"))
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
						if (nType == g_aEnemyData[nCntE].nType)
						{
							//�t�@�C����ݒ肵�����f�����ǂݍ���
							D3DXLoadMeshFromX(&g_aEnemyData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

						}
					}
					// Create�֐��Ɋi�[�������������œn��
					CEnemyX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1, nLife, nDamage);

					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "LIFE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nLife);
				}
				else if (!strcmp(cFileModel, "DAMAGE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nDamage);
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
				else if (!strcmp(cFileModel, "MOVEBACK"))
				{// �G���ǂ��܂ňړ����邩(��)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move1.x);
					fscanf(pFile, "%f", &move1.y);
					fscanf(pFile, "%f", &move1.z);

				}
				else if (!strcmp(cFileModel, "MOVEFLONT"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move2.x);
					fscanf(pFile, "%f", &move2.y);
					fscanf(pFile, "%f", &move2.z);

				}
				else if (!strcmp(cFileModel, "MOVEUP"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey1.x);
					fscanf(pFile, "%f", &movey1.y);
					fscanf(pFile, "%f", &movey1.z);

				}
				else if (!strcmp(cFileModel, "MOVEDOWN"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey2.x);
					fscanf(pFile, "%f", &movey2.y);
					fscanf(pFile, "%f", &movey2.z);

				}

				else if (!strcmp(cFileModel, "SPEED_X"))
				{// �ǂ̂��炢�̑��x�ňړ����邩���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed);

				}
				else if (!strcmp(cFileModel, "SPEED_Y"))
				{// �ǂ̂��炢�̑��x�ňړ����邩���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed1);

				}

			}
			nCnt++;
		}
	}

}
//===========================================
//�G�̃��f���t�@�C���̓ǂݍ���(�X�e�[�W2�p)
//===========================================
void CGame::SetEnemy_File2()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//���f���̃p�X�̒���
	int nSaveModel = 0;
	int nCntModel = 0;  // �ǂݍ��񂾃��f���t�@�C���̃J�E���g�� MEMO �ϐ���1�Ŋ��������Ȃ��I
	//int nLoadData;

	//�t�@�C�����J��
	FILE* pFile = fopen("data\\TXT\\SetEnemy_File2.txt", "r");

	if (pFile == NULL)
	{
		return;
	}

	while (1)
	{
		fscanf(pFile, "%s", cFileModel);

		if (!strcmp(cFileModel, "END_MODEL_ENEMYSET"))
		{
			fclose(pFile);
			break;
		}
		if (cFileModel[0] == '#')
		{
			continue;		//�J��Ԃ��B�A���œǂݍ��݂����̂�
		}
		if (!strcmp(cFileModel, "NUM_ENEMY"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//���f���̖��O����������
		if (!strcmp(cFileModel, "ENEMY_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &g_aEnemyData[nCntModel].cFile[0]);
			g_aEnemyData[nCntModel].nType = nCntModel;  // type�Ɍ��݂̃J�E���g�ɂ���(����ɂ��ォ��0�C1�C2...�Ɛݒ�ł���)
			nCntModel++;
		}


		//���f���ݒ�
		if (!strcmp(cFileModel, "ENEMY_MODELSET"))
		{
			// TODO: �����l
			int nType = 0;;
			int nLife = 0;
			int	nDamage = 0;
			D3DXVECTOR3 pos, rot, move1, move2, movey1, movey2;
			float fSpeed = 0.0f;
			float fSpeed1 = 0.0f;

			while (1)
			{
				fscanf(pFile, "%s", cFileModel);

				if (!strcmp(cFileModel, "END_ENEMYSET"))
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
						if (nType == g_aEnemyData[nCntE].nType)
						{
							//�t�@�C����ݒ肵�����f�����ǂݍ���
							D3DXLoadMeshFromX(&g_aEnemyData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

						}
					}
					// Create�֐��Ɋi�[�������������œn��
					CEnemyX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1, nLife, nDamage);

					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "LIFE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nLife);
				}
				else if (!strcmp(cFileModel, "DAMAGE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nDamage);
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
				else if (!strcmp(cFileModel, "MOVEBACK"))
				{// �G���ǂ��܂ňړ����邩(��)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move1.x);
					fscanf(pFile, "%f", &move1.y);
					fscanf(pFile, "%f", &move1.z);

				}
				else if (!strcmp(cFileModel, "MOVEFLONT"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move2.x);
					fscanf(pFile, "%f", &move2.y);
					fscanf(pFile, "%f", &move2.z);

				}
				else if (!strcmp(cFileModel, "MOVEUP"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey1.x);
					fscanf(pFile, "%f", &movey1.y);
					fscanf(pFile, "%f", &movey1.z);

				}
				else if (!strcmp(cFileModel, "MOVEDOWN"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey2.x);
					fscanf(pFile, "%f", &movey2.y);
					fscanf(pFile, "%f", &movey2.z);

				}

				else if (!strcmp(cFileModel, "SPEED_X"))
				{// �ǂ̂��炢�̑��x�ňړ����邩���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed);

				}
				else if (!strcmp(cFileModel, "SPEED_Y"))
				{// �ǂ̂��炢�̑��x�ňړ����邩���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed1);

				}

			}
			nCnt++;
		}
	}

}
//===========================================
//�G�̃��f���t�@�C���̓ǂݍ���(�X�e�[�W3�p)
//===========================================
void CGame::SetEnemy_File3()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//���f���̃p�X�̒���
	int nSaveModel = 0;
	int nCntModel = 0;  // �ǂݍ��񂾃��f���t�@�C���̃J�E���g�� MEMO �ϐ���1�Ŋ��������Ȃ��I
	//int nLoadData;

	//�t�@�C�����J��
	FILE* pFile = fopen("data\\TXT\\SetEnemy_File3.txt", "r");

	if (pFile == NULL)
	{
		return;
	}

	while (1)
	{
		fscanf(pFile, "%s", cFileModel);

		if (!strcmp(cFileModel, "END_MODEL_ENEMYSET"))
		{
			fclose(pFile);
			break;
		}
		if (cFileModel[0] == '#')
		{
			continue;		//�J��Ԃ��B�A���œǂݍ��݂����̂�
		}
		if (!strcmp(cFileModel, "NUM_ENEMY"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//���f���̖��O����������
		if (!strcmp(cFileModel, "ENEMY_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &g_aEnemyData[nCntModel].cFile[0]);
			g_aEnemyData[nCntModel].nType = nCntModel;  // type�Ɍ��݂̃J�E���g�ɂ���(����ɂ��ォ��0�C1�C2...�Ɛݒ�ł���)
			nCntModel++;
		}


		//���f���ݒ�
		if (!strcmp(cFileModel, "ENEMY_MODELSET"))
		{
			// TODO: �����l
			int nType = 0;
			int nLife = 0;
			int	nDamage = 0;
			D3DXVECTOR3 pos, rot, move1, move2, movey1, movey2;
			float fSpeed = 0.0f;
			float fSpeed1 = 0.0f;

			while (1)
			{
				fscanf(pFile, "%s", cFileModel);

				if (!strcmp(cFileModel, "END_ENEMYSET"))
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
						if (nType == g_aEnemyData[nCntE].nType)
						{
							//�t�@�C����ݒ肵�����f�����ǂݍ���
							D3DXLoadMeshFromX(&g_aEnemyData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

						}
					}
					// Create�֐��Ɋi�[�������������œn��
					CEnemyX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1, nLife, nDamage);

					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "LIFE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nLife);
				}
				else if (!strcmp(cFileModel, "DAMAGE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nDamage);
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
				else if (!strcmp(cFileModel, "MOVEBACK"))
				{// �G���ǂ��܂ňړ����邩(��)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move1.x);
					fscanf(pFile, "%f", &move1.y);
					fscanf(pFile, "%f", &move1.z);

				}
				else if (!strcmp(cFileModel, "MOVEFLONT"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move2.x);
					fscanf(pFile, "%f", &move2.y);
					fscanf(pFile, "%f", &move2.z);

				}
				else if (!strcmp(cFileModel, "MOVEUP"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey1.x);
					fscanf(pFile, "%f", &movey1.y);
					fscanf(pFile, "%f", &movey1.z);

				}
				else if (!strcmp(cFileModel, "MOVEDOWN"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey2.x);
					fscanf(pFile, "%f", &movey2.y);
					fscanf(pFile, "%f", &movey2.z);

				}

				else if (!strcmp(cFileModel, "SPEED_X"))
				{// �ǂ̂��炢�̑��x�ňړ����邩���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed);

				}
				else if (!strcmp(cFileModel, "SPEED_Y"))
				{// �ǂ̂��炢�̑��x�ňړ����邩���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed1);

				}

			}
			nCnt++;
		}
	}

}
