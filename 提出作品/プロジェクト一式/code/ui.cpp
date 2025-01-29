//=================================
// 
// UIクラス　ui.h
//outher kida ibuki 
// 
//==================================

#include "ui.h"
#include "manager.h"

LPDIRECT3DTEXTURE9 CUi::m_pTextureTemp = {};

//==================================
// コンストラクタ
//==================================
CUi::CUi()
{
	m_nType = 0;
	m_nFrame = 10;
}
//==================================
// デストラクタ
//==================================
CUi::~CUi()
{
}
//==================================
// 初期設定
//==================================
HRESULT CUi::Init()
{
	CObject2D::Init();

	if (m_nType == 0)
	{// 右攻撃
		SetSize(100.0f, 100.0f);
	}
	else if (m_nType == 1)
	{// 左攻撃
		SetSize(100.0f, 100.0f);
	}
	else if (m_nType == 2)
	{// ジャンプ
		SetSize(140.0f, 140.0f);
	}
	else if (m_nType == 3)
	{// 右移動
		SetSize(120.0f, 120.0f);
	}
	else if (m_nType == 4)
	{// 左移動
		SetSize(120.0f, 120.0f);
	}
	else if (m_nType == 5)
	{
		SetSize(420.0f, 240.0f);
	}
	else if (m_nType == 6)
	{
		SetSize(420.0f, 240.0f);
	}
	else if (m_nType == 7)
	{
		SetSize(420.0f, 240.0f);
	}

	return S_OK;
}
//==================================
// 終了処理
//==================================
void CUi::Uninit()
{
	CObject2D::Uninit();
}
//==================================
// 更新処理
//==================================
void CUi::Update()
{
	VERTEX_2D* pVtx; //頂点情報へのポインタ

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* pKeyboard = pManager->GetKeyboard();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //キーボード取得

	CObject2D::Update();

	if (m_nType == 0)
	{
		// 右攻撃の時
		if (pKeyboard->GetPress(DIK_RIGHT) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_B))
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラー(赤色にする)
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 200);

			m_pVtxBuff->Unlock();

		}
		else// 押されてないとき
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラー(色を付けない)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			m_pVtxBuff->Unlock();
		}

	}
	else if (m_nType == 1)
	{
		// 左攻撃の時
		if (pKeyboard->GetPress(DIK_LEFT) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_X))
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラー(赤色にする)
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 200);

			m_pVtxBuff->Unlock();

		}
		else// 押されてないとき
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラー(色を付けない)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			m_pVtxBuff->Unlock();
		}

	}
	else if (m_nType == 2)
	{
		// ジャンプの時
		if (pKeyboard->GetPress(DIK_SPACE) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_A))
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラー(赤色にする)
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 200);

			m_pVtxBuff->Unlock();

		}
		else// 押されてないとき
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラー(色を付けない)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			m_pVtxBuff->Unlock();
		}

	}
	else if (m_nType == 3)
	{
		// 右移動の時
		if (pKeyboard->GetPress(DIK_D) == true || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラー(赤色にする)
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 200);

			m_pVtxBuff->Unlock();

		}
		else// 押されてないとき
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラー(色を付けない)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			m_pVtxBuff->Unlock();
		}

	}
	else if (m_nType == 4)
	{
		// 左移動の時
		if (pKeyboard->GetPress(DIK_A) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT))
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラー(赤色にする)
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 200);

			m_pVtxBuff->Unlock();

		}
		else// 押されてないとき
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラー(色を付けない)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			m_pVtxBuff->Unlock();
		}

	}


}
//==================================
// 描画処理
//==================================
void CUi::Draw()
{
	CObject2D::Draw();
}
//==================================
// 生成処理
//==================================
CUi* CUi::Create(D3DXVECTOR2 pos, int nType)
{
	CUi* pUi = new CUi();
	pUi->m_nType = nType;
	pUi->Init();
	pUi->SetPos(pos.x, pos.y);
	if (nType == 0)
	{// 右攻撃
		pUi->SetTexture("data/TEXTURE/attackright.png");
	}
	else if (nType == 1)
	{// 左攻撃
		pUi->SetTexture("data/TEXTURE/attackleft.png");
	}
	else if (nType == 2)
	{// ジャンプ
		pUi->SetTexture("data/TEXTURE/jumpicon.png");
	}
	else if (nType == 3)
	{//右移動
		pUi->SetTexture("data/TEXTURE/righticon.png");
	}
	else if (nType == 4)
	{// 左移動
		pUi->SetTexture("data/TEXTURE/lefticon.png");
	}
	else if (nType == 5)
	{
		// 移動テクスチャ(チュートリアル用)
		pUi->SetTexture("data/TEXTURE/tutorial_move.png");
	}
	else if (nType == 6)
	{
		// ジャンプテクスチャ(チュートリアル用)
		pUi->SetTexture("data/TEXTURE/tutorial_jump.png");
	}
	else if (nType == 7)
	{
		// 攻撃テクスチャ(チュートリアル用)
		pUi->SetTexture("data/TEXTURE/tutorial_attack.png");
	}

	return pUi;
}
//=====================================
// テクスチャのロード
//=====================================
HRESULT CUi::Load()
{
	CManager* pManager = CManager::GetInstance();

	//ポインタがnullなら
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込む
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\life001.png",
			&m_pTextureTemp);
	}

	return S_OK;
}
//=====================================
// テクスチャのアンロード
//=====================================
void CUi::Unload()
{
	//テクスチャを使用していたら破棄
	if (m_pTextureTemp != nullptr)
	{
		//nullにする
		m_pTextureTemp = nullptr;
	}
}

