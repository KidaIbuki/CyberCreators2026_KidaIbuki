//=================================
// 
// チュートリアルクラス　gaem.h
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
// コンストラクタ
//==========================================
CTutorial::CTutorial()
{
	m_nFrame = 1;
}
//==========================================
// デストラクタ
//==========================================
CTutorial::~CTutorial()
{
}
//==========================================
// 初期設定
//==========================================
HRESULT CTutorial::Init()
{
	CManager* pManager = CManager::GetInstance();

	// サウンドを流す
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_TUTORIAL);

	//テクスチャのロード
	CField::Load();

	SetModel_File_tutorial();

	// 移動、攻撃などのUI
	CUi::Create(D3DXVECTOR2(1100.0f, 650.0f), 0);
	CUi::Create(D3DXVECTOR2(1000.0f, 650.0f), 1);
	CUi::Create(D3DXVECTOR2(1205.0f, 650.0f), 2);
	CUi::Create(D3DXVECTOR2(300.0f, 650.0f), 3);
	CUi::Create(D3DXVECTOR2(200.0f, 650.0f), 4);


	//床
	for (int i = 0; i < 3; i++)
	{
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, 114.0f));		//3Dオブジェクトの生成
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, -114.0f));		//3Dオブジェクトの生成
	}

	CMarker* pMarker = CMarker::Create(D3DXVECTOR3(-100.0f, 25.0f, 0.0f), 0);  // スタートマーカー(位置を変えるとプレイヤーの位置も一緒に変わる)
	CMarker::Create(D3DXVECTOR3(500.0f, 25.0f, 0.0f), 4);  // 次に行くマーカー
	D3DXVECTOR3 markerPos = pMarker->GetPos();  // マーカーの位置を取得


	// スタートマーカーの位置にプレイヤーを配置
	CPlayerX* pPlayerX = CPlayerX::Create(D3DXVECTOR3(markerPos.x, markerPos.y, markerPos.z), 0);
	D3DXVECTOR3 playerPos = pPlayerX->GetPos(); // プレイヤーの位置を取得

	return S_OK;
}
//==========================================
// 終了処理
//==========================================
void CTutorial::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	//テクスチャのアンロード
	CField::Unload();

	CScene::Uninit();

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];
		// 最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			pObj->DeathFlag();

			pObj = pNext;

		}
	}
	// サウンドを止める
	pManager->GetSound()->StopSound();

}
//==========================================
// 更新処理
//==========================================
void CTutorial::Update()
{
	CScene::Update();

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];
		// 最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();
			CObject::TYPE type = pObj->GetType();

			pObj->Update();

			if (type == CObject::TYPE::PLAYER_X)
			{
				CPlayerX* pPlayer = (CPlayerX*)pObj; //ダウンキャスト
				if (pPlayer != nullptr)
				{

					D3DXVECTOR3 playerPos = pPlayer->GetPos();

					// 各位置にチュートリアル用のテクスチャを張る
					if (playerPos.x >= POSITION_NUM_1 && playerPos.x <= POSITION_NUM_2)
					{
						m_Position = POSITION_1;
						m_nFrame = 1;   // フレームに代入
					}
					else if (playerPos.x >= POSITION_NUM_3 && playerPos.x <= POSITION_NUM_4)
					{
						m_Position = POSITION_2;
						m_nFrame = 1;   // フレームに代入
					}
					else if (playerPos.x >= POSITION_NUM_5 && playerPos.x <= POSITION_NUM_6)
					{
						m_Position = POSITION_3;
						m_nFrame = 1;   // フレームに代入
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

	// テクスチャを貼る
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
// 描画処理
//==========================================
void CTutorial::Draw()
{
	CScene::Draw();

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];
		// 最大数が不明なのでwhileを使用3
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			pObj->Draw();

			pObj = pNext;

		}
	}

}
//==========================================
// 生成処理
//==========================================
CTutorial* CTutorial::Create()
{
	CTutorial* pTutorial = new CTutorial();
	pTutorial->Init();
	return pTutorial;
}

//========================================================================================================
//モデルファイルの読み込み(チュートリアル用)
//===========================================
void CTutorial::SetModel_File_tutorial()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//モデルのパスの長さ
	int nSaveModel = 0;
	int nCntModel = 0;  // 読み込んだモデルファイルのカウント※ MEMO 変数を1つで完結させない！
	//int nLoadData;

	//ファイルを開く
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
			continue;		//繰り返す。連続で読み込みたいので
		}
		if (!strcmp(cFileModel, "NUM_MODEL"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//モデルの名前を検索する
		if (!strcmp(cFileModel, "MODEL_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &m_gModelData[nCntModel].cFile[0]);
			m_gModelData[nCntModel].nType = nCntModel;  // typeに現在のカウントにする(これにより上から0，1，2...と設定できる)
			nCntModel++;
		}


		//モデル設定
		if (!strcmp(cFileModel, "MODELSET"))
		{
			// TODO: 初期値
			int nType = 0;
			D3DXVECTOR3 pos, rot;

			while (1)
			{
				fscanf(pFile, "%s", cFileModel);

				if (!strcmp(cFileModel, "END_MODELSET"))
				{
					CManager* pManager = CManager::GetInstance();
					// デバイスの取得
					LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
					// 一時変数(外部ファイルで読み取った情報を格納)
					LPD3DXMESH pMesh = nullptr;			//メッシュへのポインタ
					LPD3DXBUFFER pBuffMat = nullptr;    //マテリアルへのポインタ
					DWORD dwNumMat = 0;           //マテリアルの数

					for (int nCntE = 0; nCntE < nSaveModel; nCntE++)
					{
						if (nType == m_gModelData[nCntE].nType)
						{
							//ファイルを設定したモデル分読み込む
							D3DXLoadMeshFromX(&m_gModelData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

						}
					}
					// Create関数に格納した情報を引数で渡す
					CBlockX::Create(pos, rot, pMesh, pBuffMat, dwNumMat)->SizeVtx();

					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "POS"))
				{// オブジェクトの位置を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &pos.x);
					fscanf(pFile, "%f", &pos.y);
					fscanf(pFile, "%f", &pos.z);

				}
				else if (!strcmp(cFileModel, "ROT"))
				{// オブジェクトの向きを指定
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
