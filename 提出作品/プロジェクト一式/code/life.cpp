//=================================
// 
// ライフUIクラス　life.h
//outher kida ibuki 
// 
//==================================
#include "manager.h"
#include "life.h"
#include "pch.h"
#include "sound.h"
LPDIRECT3DTEXTURE9 CLife::m_pTextureTemp = {};
float CLife::m_fTexHeight = 0;
float CLife::m_fTexWidht = 0;
int CLife::m_nFrame = 0;
int CLife::m_nLife = 0;
//==================================
// コンストラクタ
//==================================
CLife::CLife()
{
	m_fTexHeight = 0.2f;   //縦
	m_fTexWidht = 0.0f;    //横
	m_nFrame = 30;
	m_nLife = 50;
}
//==================================
// デストラクタ
//==================================
CLife::~CLife()
{
}
//==================================
// 初期設定
//==================================
HRESULT CLife::Init()
{
	CObject2D::Init();
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice;

	pDevice = pManager->GetRenderer()->GetDevice();

	SetSize(170.0f, 120.0f);


	return S_OK;

}
//==================================
// 終了処理
//==================================
void CLife::Uninit()
{
	CObject2D::Uninit();
}
//==================================
// 更新処理
//==================================
void CLife::Update()
{
	CObject2D::Update();

	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, m_fTexWidht);
	pVtx[1].tex = D3DXVECTOR2(1.0f, m_fTexWidht);
	pVtx[2].tex = D3DXVECTOR2(0.0f, m_fTexHeight);
	pVtx[3].tex = D3DXVECTOR2(1.0f, m_fTexHeight);
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}
//==================================
// 描画処理
//==================================
void CLife::Draw()
{
	CObject2D::Draw();
}
//==================================
// 生成処理
//==================================
CLife* CLife::Create(D3DXVECTOR2 pos)
{
	CLife* pLife = new CLife();
	pLife->Init();
	pLife->SetPos(pos.x, pos.y); //ちょっと作り方が違u
	if (m_pTextureTemp != nullptr)
	{
		pLife->BindTexture(m_pTextureTemp);
	}
	return pLife;
}
//=====================================
//テクスチャのロード
//=====================================
HRESULT CLife::Load()
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
//テクスチャのアンロード
//=====================================
void CLife::Unload()
{
	//テクスチャを使用していたら破棄
	if (m_pTextureTemp != nullptr)
	{
		//nullにする
		m_pTextureTemp = nullptr;
	}
}

//=======================================
// ライフの減算処理
//=======================================
void CLife::HitLife(int nDamage)
{
	CManager* pManager = CManager::GetInstance();

	// サウンドを流す(プレイヤーのダメージ)

	if (m_nFrame >= 0)  // 0より多かったら
	{
		m_nFrame--;   // カウントダウン
	}
	if (m_nFrame <= 0)
	{ // 座標を増やす
		pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // 画面の揺れ
	    pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_PLAYER_DAMAGE);

		m_fTexHeight += 0.2f;
		m_fTexWidht += 0.2f;
		m_nLife -= nDamage;  // ライフを減らす
		m_nFrame = 30;   // フレームを戻す
	}
	if (m_nLife <= 0)
	{// ライフが無くなったら
		CFade::SetFade(CScene::MODE::MODE_RESULT_LOSE);
	}

}
