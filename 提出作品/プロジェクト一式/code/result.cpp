//=================================
// 
// シーンクラス　result.cpp
//outher kida ibuki 
// 
//==================================
#include "result.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
//静的メンバ変数初期化
LPDIRECT3DTEXTURE9 CResult::m_pTextureTemp = {};
LPDIRECT3DTEXTURE9 CResultLose::m_pTextureTemp = {};

//====================================
// コンストラクタ
//====================================
CResult::CResult()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

}
//====================================
// デストラクタ
//====================================
CResult::~CResult()
{
}
//====================================
// 初期設定
//====================================
HRESULT CResult::Init()
{
	CScene::Init();

	CManager* pManager = CManager::GetInstance();

	// サウンドを流す
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_CLEAR);

	//SetTexture("data/TEXTURE/titleTest.png");

	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	return S_OK;
}
//====================================
// 終了処理
//====================================
void CResult::Uninit()
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

	// サウンドを止める
	pManager->GetSound()->StopSound();

}
//====================================
// 更新処理
//====================================
void CResult::Update()
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
		CFade::SetFade(CScene::MODE::MODE_TITLE);
		//pManager->SetMode(CScene::MODE::MODE_TITLE);
	}
}
//====================================
// 描画処理
//====================================
void CResult::Draw()
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
HRESULT CResult::Load()
{
	CManager* pManager = CManager::GetInstance();

	//ポインタがnullなら
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込む
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\resultclear.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//アンロード
//======================================
void CResult::Unload()
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
// コンストラクタ
//====================================
CResultLose::CResultLose()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

}
//====================================
// デストラクタ
//====================================
CResultLose::~CResultLose()
{
}
//====================================
// 初期設定
//====================================
HRESULT CResultLose::Init()
{
	CManager* pManager = CManager::GetInstance();

	CScene::Init();

	// サウンドを流す
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM_LOSE);

	//SetTexture("data/TEXTURE/titleTest.png");

	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	return S_OK;
}
//====================================
// 終了処理
//====================================
void CResultLose::Uninit()
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

	// サウンドを止める
	pManager->GetSound()->StopSound();

}
//====================================
// 更新処理
//====================================
void CResultLose::Update()
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
		CFade::SetFade(CScene::MODE::MODE_GAME);
		//pManager->SetMode(CScene::MODE::MODE_GAME);
	}
}
//====================================
// 描画処理
//====================================
void CResultLose::Draw()
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
HRESULT CResultLose::Load()
{
	CManager* pManager = CManager::GetInstance();

	//ポインタがnullなら
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込む
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\resultlose.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//アンロード
//======================================
void CResultLose::Unload()
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
