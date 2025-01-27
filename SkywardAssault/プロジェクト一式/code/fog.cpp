//=================================
// 
// フォグクラス　　fog.cpp
//outher kida ibuki 
// 
//==================================
#include "fog.h"
#include "manager.h"

#define NUM (1)   // 0->範囲指定フォグ:  1->密度指定フォグ
//==============================================
// コンストラクタ
//==============================================
CFog::CFog()
{
	m_fFogDensity = 0.0f;
	m_fFogStartPos = 0.0f;
	m_fFogEndPos = 0.0f;
}
//==============================================
// デストラクタ
//==============================================
CFog::~CFog()
{
}
//==============================================
// 初期設定
//==============================================
HRESULT CFog::Init()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// デバイスを取得

#if NUM
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);  // フォグモードの指定(それぞれに合ったモードを指定)
#else
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);  // フォグモードの指定(それぞれに合ったモードを指定)
#endif
	// フォグの有効
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	// フォグカラーの設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//フォグパラメーターを設定

#if NUM  // 0か1でフォグ設定を変えれる(変えたらフォグモードも変える)

	m_fFogDensity = 0.0005f;   // 密度設定

	// D3DFOG_EXP(密度指定の場合)
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));
#else
	// D3DFOG_LINEAR(範囲指定の場合)
	m_fFogStartPos = 100.0f;
	m_fFogEndPos = 1000.0f;

	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&m_fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&m_fFogEndPos));
#endif

	return S_OK;
}
//==============================================
// 終了処理
//==============================================
void CFog::Uninit()
{
}
//==============================================
// 更新処理
//==============================================
void CFog::Update()
{
}
//==============================================
// 描画処理
//==============================================
void CFog::Draw()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// デバイスを取得

		// アルファブレンディング設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// アルファテスト設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// テクスチャアルファ設定
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

}
