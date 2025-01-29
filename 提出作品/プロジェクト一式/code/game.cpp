//=================================
// 
// ゲーム処理クラス　game.cpp
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
//======サウンド========
#include "sound.h"

//====================================
// コンストラクタ
//====================================
CGame::CGame()
{
	m_bPause = false;
}
//====================================
// デストラクタ
//====================================
CGame::~CGame()
{
}
//====================================
// 初期設定
//====================================
HRESULT CGame::Init()
{
	CManager* pManager = CManager::GetInstance();

	SetModel_File();
	SetEnemy_File();
	// サウンドを流す
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_GAME001);

	//**==========================3Dオブジェクト===========================**
	//テクスチャのロード
	CField::Load();
	CLife::Load();   // ライフUI
	CExplosion::Load();

	CLife::Create(D3DXVECTOR2(100.0f, 50.0f));

	// 移動、攻撃などのUI
	CUi::Create(D3DXVECTOR2(1100.0f, 650.0f), 0);
	CUi::Create(D3DXVECTOR2(1000.0f, 650.0f), 1);
	CUi::Create(D3DXVECTOR2(1205.0f, 650.0f), 2);
	CUi::Create(D3DXVECTOR2(300.0f, 650.0f), 3);
	CUi::Create(D3DXVECTOR2(200.0f, 650.0f), 4);

		//床
	for (int i = 0; i < 7; i++)
	{
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, 114.0f));		//3Dオブジェクトの生成
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, -114.0f));		//3Dオブジェクトの生成
	}


	CMarker* pMarker = CMarker::Create(D3DXVECTOR3(-100.0f, 25.0f, 0.0f), 0);  // スタートマーカー(位置を変えるとプレイヤーの位置も一緒に変わる)
	CMarker::Create(D3DXVECTOR3(1300.0f, 25.0f, 0.0f), 2);  // 次に行くマーカー
	D3DXVECTOR3 markerPos = pMarker->GetPos();  // マーカーの位置を取得

	// スタートマーカーの位置にプレイヤーを配置
	CPlayerX* pPlayerX = CPlayerX::Create(D3DXVECTOR3(markerPos.x, markerPos.y, markerPos.z), 0);
	D3DXVECTOR3 playerPos = pPlayerX->GetPos(); // プレイヤーの位置を取得


	return S_OK;
}
//====================================
// 終了処理
//====================================
void CGame::Uninit()
{

	CManager* pManager = CManager::GetInstance();

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


    //テクスチャのアンロード
	CField::Unload();
	CLife::Unload();   // ライフUI
	CExplosion::Unload();

	// サウンドを止める
	pManager->GetSound()->StopSound();

}
//====================================
// 更新処理
//====================================
void CGame::Update()
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

			pObj->Update();

			pObj = pNext;

		}
	}

}
//====================================
// 描画処理
//====================================
void CGame::Draw()
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
//======================================
// ゲームの生成
//======================================
CGame* CGame::Create()
{
	CGame* pGame = new CGame();
	pGame->Init();
	return pGame;
}

//======================================================================
//２つ目のステージ情報
//======================================================================↓



//====================================
// コンストラクタ
//====================================
CGameSecond::CGameSecond()
{
	m_bPause2 = false;
}
//====================================
// デストラクタ
//====================================
CGameSecond::~CGameSecond()
{
}
//====================================
// 初期設定
//====================================
HRESULT CGameSecond::Init()
{

	CManager* pManager = CManager::GetInstance();

	SetModel_File2();
	SetEnemy_File2();
	// サウンドを流す
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_GAME002);

	//**==========================3Dオブジェクト===========================**
	//テクスチャのロード
	CField::Load();
	CLife::Load();   // ライフUI
	CExplosion::Load();

	CLife::Create(D3DXVECTOR2(100.0f, 50.0f));
	// 移動、攻撃などのUI
	CUi::Create(D3DXVECTOR2(1100.0f, 650.0f), 0);
	CUi::Create(D3DXVECTOR2(1000.0f, 650.0f), 1);
	CUi::Create(D3DXVECTOR2(1205.0f, 650.0f), 2);
	CUi::Create(D3DXVECTOR2(300.0f, 650.0f), 3);
	CUi::Create(D3DXVECTOR2(200.0f, 650.0f), 4);

	//床
	for (int i = 0; i < 7; i++)
	{
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, 114.0f));		//3Dオブジェクトの生成
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, -114.0f));		//3Dオブジェクトの生成
	}

	CMarker* pMarker = CMarker::Create(D3DXVECTOR3(-100.0f, 25.0f, 0.0f), 0);  // スタートマーカー(位置を変えるとプレイヤーの位置も一緒に変わる)
	CMarker::Create(D3DXVECTOR3(1300.0f, 25.0f, 0.0f), 3);  // ゴールマーカー
	D3DXVECTOR3 markerPos = pMarker->GetPos();  // マーカーの位置を取得

	// スタートマーカーの位置にプレイヤーを配置
	CPlayerX::Create(D3DXVECTOR3(markerPos.x, markerPos.y, markerPos.z), 0);


	return S_OK;
}
//====================================
// 終了処理
//====================================
void CGameSecond::Uninit()
{
	CManager* pManager = CManager::GetInstance();

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

	//テクスチャのアンロード
	CField::Unload();
	CLife::Unload();   // ライフUI
	CExplosion::Unload();

		// サウンドを止める
	pManager->GetSound()->StopSound();

}
//====================================
// 更新処理
//====================================
void CGameSecond::Update()
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

			pObj->Update();

			pObj = pNext;

		}
	}

}
//====================================
// 描画処理
//====================================
void CGameSecond::Draw()
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
//======================================
// ゲームの生成
//======================================
CGameSecond* CGameSecond::Create()
{
	CGameSecond* pGameSecobd = new CGameSecond();
	pGameSecobd->Init();
	return pGameSecobd;
}



//======================================================================
//3つ目のステージ情報
//======================================================================↓

//====================================
// コンストラクタ
//====================================
CGameThird::CGameThird()
{
	m_bPause3 = false;
}
//====================================
// デストラクタ
//====================================
CGameThird::~CGameThird()
{
}
//====================================
// 初期設定
//====================================
HRESULT CGameThird::Init()
{
	CManager* pManager = CManager::GetInstance();

	SetModel_File3();
	SetEnemy_File3();
	// サウンドを流す
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_GAME003);

	//**==========================3Dオブジェクト===========================**
//テクスチャのロード
	CField::Load();
	CLife::Load();   // ライフUI
	CExplosion::Load();

	CLife::Create(D3DXVECTOR2(100.0f, 50.0f));
	// 移動、攻撃などのUI
	CUi::Create(D3DXVECTOR2(1100.0f, 650.0f), 0);
	CUi::Create(D3DXVECTOR2(1000.0f, 650.0f), 1);
	CUi::Create(D3DXVECTOR2(1205.0f, 650.0f), 2);
	CUi::Create(D3DXVECTOR2(300.0f, 650.0f), 3);
	CUi::Create(D3DXVECTOR2(200.0f, 650.0f), 4);

	//床
	for (int i = 0; i < 7; i++)
	{
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, 114.0f));		//3Dオブジェクトの生成
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, -114.0f));		//3Dオブジェクトの生成
	}


	CMarker* pMarker = CMarker::Create(D3DXVECTOR3(-100.0f, 25.0f, 0.0f), 0);  // スタートマーカー(位置を変えるとプレイヤーの位置も一緒に変わる)
	CMarker::Create(D3DXVECTOR3(1300.0f, 25.0f, 0.0f), 1);  // ゴールマーカー
	D3DXVECTOR3 markerPos = pMarker->GetPos();  // マーカーの位置を取得

	// スタートマーカーの位置にプレイヤーを配置
	CPlayerX::Create(D3DXVECTOR3(markerPos.x, markerPos.y, markerPos.z), 0);

	return S_OK;
}
//====================================
// 終了処理
//====================================
void CGameThird::Uninit()
{
	CManager* pManager = CManager::GetInstance();

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

	//テクスチャのアンロード
	CField::Unload();
	CLife::Unload();   // ライフUI
	CExplosion::Unload();

	// サウンドを止める
	pManager->GetSound()->StopSound();

}
//====================================
// 更新処理
//====================================
void CGameThird::Update()
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

			pObj->Update();

			pObj = pNext;

		}
	}

}
//====================================
// 描画処理
//====================================
void CGameThird::Draw()
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
//====================================
// 生成処理
//====================================
CGameThird* CGameThird::Create()
{
	CGameThird* pGameThird = new CGameThird();
	pGameThird->Init();
	return pGameThird;
}
//===========================================
//モデルファイルの読み込み(ステージ1)
//===========================================
void CGame::SetModel_File()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//モデルのパスの長さ
	int nSaveModel = 0;
	int nCntModel = 0;  // 読み込んだモデルファイルのカウント※ MEMO 変数を1つで完結させない！

	//ファイルを開く
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

//========================================================================================================
//モデルファイルの読み込み(ステージ2)
//===========================================
void CGame::SetModel_File2()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//モデルのパスの長さ
	int nSaveModel = 0;
	int nCntModel = 0;  // 読み込んだモデルファイルのカウント※ MEMO 変数を1つで完結させない！
	//int nLoadData;

	//ファイルを開く
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
//========================================================================================================
//モデルファイルの読み込み(ステージ3)
//===========================================
void CGame::SetModel_File3()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//モデルのパスの長さ
	int nSaveModel = 0;
	int nCntModel = 0;  // 読み込んだモデルファイルのカウント※ MEMO 変数を1つで完結させない！
	//int nLoadData;

	//ファイルを開く
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
//===========================================
//敵のモデルファイルの読み込み(ステージ1用)
//===========================================
void CGame::SetEnemy_File()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//モデルのパスの長さ
	int nSaveModel = 0;
	int nCntModel = 0;  // 読み込んだモデルファイルのカウント※ MEMO 変数を1つで完結させない！
	//int nLoadData;

	//ファイルを開く
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
			continue;		//繰り返す。連続で読み込みたいので
		}
		if (!strcmp(cFileModel, "NUM_ENEMY"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//モデルの名前を検索する
		if (!strcmp(cFileModel, "ENEMY_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &g_aEnemyData[nCntModel].cFile[0]);
			g_aEnemyData[nCntModel].nType = nCntModel;  // typeに現在のカウントにする(これにより上から0，1，2...と設定できる)
			nCntModel++;
		}


		//モデル設定
		if (!strcmp(cFileModel, "ENEMY_MODELSET"))
		{
			// TODO: 初期値
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
					// デバイスの取得
					LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
					// 一時変数(外部ファイルで読み取った情報を格納)
					LPD3DXMESH pMesh = nullptr;			//メッシュへのポインタ
					LPD3DXBUFFER pBuffMat = nullptr;    //マテリアルへのポインタ
					DWORD dwNumMat = 0;           //マテリアルの数

					for (int nCntE = 0; nCntE < nSaveModel; nCntE++)
					{
						if (nType == g_aEnemyData[nCntE].nType)
						{
							//ファイルを設定したモデル分読み込む
							D3DXLoadMeshFromX(&g_aEnemyData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

						}
					}
					// Create関数に格納した情報を引数で渡す
					CEnemyX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1, nLife, nDamage);

					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "LIFE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nLife);
				}
				else if (!strcmp(cFileModel, "DAMAGE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nDamage);
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
				else if (!strcmp(cFileModel, "MOVEBACK"))
				{// 敵がどこまで移動するか(奥)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move1.x);
					fscanf(pFile, "%f", &move1.y);
					fscanf(pFile, "%f", &move1.z);

				}
				else if (!strcmp(cFileModel, "MOVEFLONT"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move2.x);
					fscanf(pFile, "%f", &move2.y);
					fscanf(pFile, "%f", &move2.z);

				}
				else if (!strcmp(cFileModel, "MOVEUP"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey1.x);
					fscanf(pFile, "%f", &movey1.y);
					fscanf(pFile, "%f", &movey1.z);

				}
				else if (!strcmp(cFileModel, "MOVEDOWN"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey2.x);
					fscanf(pFile, "%f", &movey2.y);
					fscanf(pFile, "%f", &movey2.z);

				}

				else if (!strcmp(cFileModel, "SPEED_X"))
				{// どのくらいの速度で移動するかを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed);

				}
				else if (!strcmp(cFileModel, "SPEED_Y"))
				{// どのくらいの速度で移動するかを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed1);

				}

			}
			nCnt++;
		}
	}

}
//===========================================
//敵のモデルファイルの読み込み(ステージ2用)
//===========================================
void CGame::SetEnemy_File2()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//モデルのパスの長さ
	int nSaveModel = 0;
	int nCntModel = 0;  // 読み込んだモデルファイルのカウント※ MEMO 変数を1つで完結させない！
	//int nLoadData;

	//ファイルを開く
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
			continue;		//繰り返す。連続で読み込みたいので
		}
		if (!strcmp(cFileModel, "NUM_ENEMY"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//モデルの名前を検索する
		if (!strcmp(cFileModel, "ENEMY_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &g_aEnemyData[nCntModel].cFile[0]);
			g_aEnemyData[nCntModel].nType = nCntModel;  // typeに現在のカウントにする(これにより上から0，1，2...と設定できる)
			nCntModel++;
		}


		//モデル設定
		if (!strcmp(cFileModel, "ENEMY_MODELSET"))
		{
			// TODO: 初期値
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
					// デバイスの取得
					LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
					// 一時変数(外部ファイルで読み取った情報を格納)
					LPD3DXMESH pMesh = nullptr;			//メッシュへのポインタ
					LPD3DXBUFFER pBuffMat = nullptr;    //マテリアルへのポインタ
					DWORD dwNumMat = 0;           //マテリアルの数

					for (int nCntE = 0; nCntE < nSaveModel; nCntE++)
					{
						if (nType == g_aEnemyData[nCntE].nType)
						{
							//ファイルを設定したモデル分読み込む
							D3DXLoadMeshFromX(&g_aEnemyData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

						}
					}
					// Create関数に格納した情報を引数で渡す
					CEnemyX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1, nLife, nDamage);

					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "LIFE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nLife);
				}
				else if (!strcmp(cFileModel, "DAMAGE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nDamage);
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
				else if (!strcmp(cFileModel, "MOVEBACK"))
				{// 敵がどこまで移動するか(奥)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move1.x);
					fscanf(pFile, "%f", &move1.y);
					fscanf(pFile, "%f", &move1.z);

				}
				else if (!strcmp(cFileModel, "MOVEFLONT"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move2.x);
					fscanf(pFile, "%f", &move2.y);
					fscanf(pFile, "%f", &move2.z);

				}
				else if (!strcmp(cFileModel, "MOVEUP"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey1.x);
					fscanf(pFile, "%f", &movey1.y);
					fscanf(pFile, "%f", &movey1.z);

				}
				else if (!strcmp(cFileModel, "MOVEDOWN"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey2.x);
					fscanf(pFile, "%f", &movey2.y);
					fscanf(pFile, "%f", &movey2.z);

				}

				else if (!strcmp(cFileModel, "SPEED_X"))
				{// どのくらいの速度で移動するかを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed);

				}
				else if (!strcmp(cFileModel, "SPEED_Y"))
				{// どのくらいの速度で移動するかを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed1);

				}

			}
			nCnt++;
		}
	}

}
//===========================================
//敵のモデルファイルの読み込み(ステージ3用)
//===========================================
void CGame::SetEnemy_File3()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//モデルのパスの長さ
	int nSaveModel = 0;
	int nCntModel = 0;  // 読み込んだモデルファイルのカウント※ MEMO 変数を1つで完結させない！
	//int nLoadData;

	//ファイルを開く
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
			continue;		//繰り返す。連続で読み込みたいので
		}
		if (!strcmp(cFileModel, "NUM_ENEMY"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//モデルの名前を検索する
		if (!strcmp(cFileModel, "ENEMY_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &g_aEnemyData[nCntModel].cFile[0]);
			g_aEnemyData[nCntModel].nType = nCntModel;  // typeに現在のカウントにする(これにより上から0，1，2...と設定できる)
			nCntModel++;
		}


		//モデル設定
		if (!strcmp(cFileModel, "ENEMY_MODELSET"))
		{
			// TODO: 初期値
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
					// デバイスの取得
					LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
					// 一時変数(外部ファイルで読み取った情報を格納)
					LPD3DXMESH pMesh = nullptr;			//メッシュへのポインタ
					LPD3DXBUFFER pBuffMat = nullptr;    //マテリアルへのポインタ
					DWORD dwNumMat = 0;           //マテリアルの数

					for (int nCntE = 0; nCntE < nSaveModel; nCntE++)
					{
						if (nType == g_aEnemyData[nCntE].nType)
						{
							//ファイルを設定したモデル分読み込む
							D3DXLoadMeshFromX(&g_aEnemyData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

						}
					}
					// Create関数に格納した情報を引数で渡す
					CEnemyX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1, nLife, nDamage);

					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "LIFE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nLife);
				}
				else if (!strcmp(cFileModel, "DAMAGE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nDamage);
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
				else if (!strcmp(cFileModel, "MOVEBACK"))
				{// 敵がどこまで移動するか(奥)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move1.x);
					fscanf(pFile, "%f", &move1.y);
					fscanf(pFile, "%f", &move1.z);

				}
				else if (!strcmp(cFileModel, "MOVEFLONT"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move2.x);
					fscanf(pFile, "%f", &move2.y);
					fscanf(pFile, "%f", &move2.z);

				}
				else if (!strcmp(cFileModel, "MOVEUP"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey1.x);
					fscanf(pFile, "%f", &movey1.y);
					fscanf(pFile, "%f", &movey1.z);

				}
				else if (!strcmp(cFileModel, "MOVEDOWN"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey2.x);
					fscanf(pFile, "%f", &movey2.y);
					fscanf(pFile, "%f", &movey2.z);

				}

				else if (!strcmp(cFileModel, "SPEED_X"))
				{// どのくらいの速度で移動するかを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed);

				}
				else if (!strcmp(cFileModel, "SPEED_Y"))
				{// どのくらいの速度で移動するかを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed1);

				}

			}
			nCnt++;
		}
	}

}
