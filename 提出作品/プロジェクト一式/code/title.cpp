//=================================
// 
// シーンクラス　scene.cpp
//outher kida ibuki 
// 
//==================================
#include "title.h"
#include "manager.h"
#include "fade.h"
#include "field.h"
#include "sound.h"
#include "blockX.h"
//静的メンバ変数初期化
LPDIRECT3DTEXTURE9 CTitle::m_pTextureTemp = {};

//====================================
// コンストラクタ
//====================================
CTitle::CTitle()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

}
//====================================
// デストラクタ
//====================================
CTitle::~CTitle()
{
}
//====================================
// 初期設定
//====================================
HRESULT CTitle::Init()
{
	CScene::Init();
	CManager* pManager = CManager::GetInstance();

	SetModel_File();

	SetSize(620, 200);

	SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	CField::Load();

	//床
	for (int i = 0; i < 7; i++)
	{
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, 114.0f));		//3Dオブジェクトの生成
		CField::Create(D3DXVECTOR3(i * 200.0f, 19.0f, -114.0f));		//3Dオブジェクトの生成
	}
	// サウンドを流す
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);


	return S_OK;
}
//====================================
// 終了処理
//====================================
void CTitle::Uninit()
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

	CField::Unload();

	// サウンドを止める
	pManager->GetSound()->StopSound();
}
//====================================
// 更新処理
//====================================
void CTitle::Update()
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

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* pKeyboard = pManager->GetKeyboard();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //コントローラー取得


	if (pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_START))
	{
		// サウンドを流す
		pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SELECT);
		CFade::SetFade(CScene::MODE::MODE_TUTORIAL);

	}
}
//====================================
// 描画処理
//====================================
void CTitle::Draw()
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
#if 1
//=======================================
//ロード
//=======================================
HRESULT CTitle::Load()
{
	CManager* pManager = CManager::GetInstance();

	//ポインタがnullなら
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込む
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\titleLogo.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//アンロード
//======================================
void CTitle::Unload()
{
	//テクスチャを使用していたら破棄
	if (m_pTextureTemp != nullptr)
	{
		//nullにする
		m_pTextureTemp = nullptr;
	}
}
#endif
//======================================
// タイトルの生成
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
//モデルファイルの読み込み(ステージ1)
//===========================================
void CTitle::SetModel_File()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//モデルのパスの長さ
	int nSaveModel = 0;
	int nCntModel = 0;  // 読み込んだモデルファイルのカウント※ MEMO 変数を1つで完結させない！
	//int nLoadData;

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
