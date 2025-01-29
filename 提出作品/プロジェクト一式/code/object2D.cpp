//=================================
// 
// オブジェクト2Dクラス　object2D.cpp
//outher kida ibuki 
// 
//==================================
#include "object2D.h"
#include "manager.h"
#include "pch.h"
//==============================
//コンストラクタ
//==============================
CObject2D::CObject2D()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_nDivide = 1;
	m_nTime = 0;
	m_nextTime = timeGetTime();
	m_nAnimIdx = 0;
	m_bReverse = false;
	m_pos = D3DXVECTOR2(0.0f, 0.0f);
	m_size = D3DXVECTOR2(10.0f, 10.0f);
	m_fAngle = 0.0f;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;

	Init();
}

//==============================
//デストラクタ
//==============================
CObject2D::~CObject2D()
{

}
//==============================
//初期設定(頂点バッファ生成)
//==============================
HRESULT CObject2D::Init()
{
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice;

	pDevice = pManager->GetRenderer()->GetDevice();

	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, NULL, &m_pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================
//終了処理(頂点バッファ破棄)
//==============================
void CObject2D::Uninit()
{
	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

}

//==============================
//更新処理(頂点座標の更新)
//==============================
void CObject2D::Update()
{
	//UpdateAnim();
	UpdateVertex();
}
//==============================
//描画処理(ポリゴンの生成)
//==============================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager* pManager = CManager::GetInstance();

	pDevice = pManager->GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//Zの比較方法を変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Zバッファに書き込まない(奥に表示するか、手前に表示するか)
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);


	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=========================================
// [CObject2D] 座標の設定
//=========================================
void CObject2D::SetPos(float x, float y)
{
	m_pos = D3DXVECTOR2(x, y);
}

void CObject2D::SetPos3(D3DXVECTOR3 pos)
{
	m_pos3 = pos;
}

//=========================================
//アニメーション設定
//=========================================
void CObject2D::SetAnim(int nDivide, int nTime)
{
	if (nDivide > 0)
	{
		m_nDivide = nDivide;
		m_nTime = nTime;
		m_nextTime = timeGetTime() + m_nTime;
	}
}

//================================================
//アニメーションの更新
//================================================
void CObject2D::UpdateAnim()
{
	VERTEX_2D* pVtx; //頂点情報へのポインタ
	float fDivideSize = 1.0f / (float)m_nDivide;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	if (!m_bReverse)
	{
		pVtx[0].tex = D3DXVECTOR2(fDivideSize * m_nAnimIdx, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fDivideSize * (m_nAnimIdx + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fDivideSize * m_nAnimIdx, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fDivideSize * (m_nAnimIdx + 1), 1.0f);
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2(fDivideSize * (m_nAnimIdx + 1), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fDivideSize * m_nAnimIdx, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fDivideSize * (m_nAnimIdx + 1), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fDivideSize * m_nAnimIdx, 1.0f);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// アニメーションを進める
	if (timeGetTime() >= m_nextTime)
	{
		// 次のアニメーションに移る
		m_nAnimIdx++;

		// 次の時間を設定する
		m_nextTime = timeGetTime() + m_nTime;

		if (m_nAnimIdx >= m_nDivide)
		{ // アニメーションが最大数に達したとき
			m_nAnimIdx = 0;
		}
	}
}
//=============================
//テクスチャの設定
//=============================
void CObject2D::SetTexture(std::string sPath)		//引数に読み込みたいテクスチャのパスを書く
{
	CManager* pManager = CManager::GetInstance();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	// テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, sPath.c_str(), &m_pTexture);
}
//============================
//サイズ設定
//============================
void CObject2D::SetSize(float fWidth, float fHeight)
{
	m_size = D3DXVECTOR2(fWidth, fHeight);
}
//===========================
//高さと幅の設定
//==========================
void CObject2D::SetHeight(float fHeight)
{
	m_fHeight = fHeight;
}
void CObject2D::SetWidth(float fWedth)
{
	m_fWidth = fWedth;
}
//============================
//向き設定
//============================
void CObject2D::SetAngle(float fAngle)
{
	m_fAngle = fAngle;
}
//==============================
//テクスチャの設定2
//==============================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}
//==============================
//位置の更新
//=============================
void CObject2D::UpdateVertex()
{
	VERTEX_2D* pVtx; //頂点情報へのポインタ

	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);

	D3DXVECTOR3 sizePos[4] =
	{
		{-m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f},
		{m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f},
		{-m_size.x * 0.5f, m_size.y * 0.5f, 0.0f},
		{m_size.x * 0.5f, m_size.y * 0.5f, 0.0f}
	};
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// サイズと回転
	D3DXVec3TransformCoord(&pVtx[0].pos, &sizePos[0], &mtx);
	D3DXVec3TransformCoord(&pVtx[1].pos, &sizePos[1], &mtx);
	D3DXVec3TransformCoord(&pVtx[2].pos, &sizePos[2], &mtx);
	D3DXVec3TransformCoord(&pVtx[3].pos, &sizePos[3], &mtx);

	// 位置
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].pos.x += m_pos.x;
		pVtx[nCnt].pos.y += m_pos.y;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();


}
//==============================
//Object2Dの生成
//==============================
//CObject2D* CObject2D::Create()
//{
//	CObject2D* pObject2D = new CObject2D;
//	pObject2D->Init();
//	return pObject2D;
//}

LPDIRECT3DVERTEXBUFFER9 CObject2D::GetBuff(void)
{
	return m_pVtxBuff;
}
