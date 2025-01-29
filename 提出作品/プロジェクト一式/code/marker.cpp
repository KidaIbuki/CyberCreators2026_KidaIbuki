//==============================================
// 
// 3Dのプレイヤー　playerX.h
//outher kida ibuki 
// 
//==============================================
#include "marker.h"
#include "playerX.h"
#include "manager.h"
#include "sound.h"
#include "tutorial.h"
//====================================
// コンストラクタ
//====================================
CMarker::CMarker()
{
	m_nType = 0;
}
//====================================
// デストラクタ
//====================================
CMarker::~CMarker()
{
}
//====================================
// 初期設定
//====================================
HRESULT CMarker::Init()
{
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}


	SetType(CObject::TYPE::MARKER);


	return S_OK;
}
//====================================
// 終了処理
//====================================
void CMarker::Uninit()
{
	CObjectX::Uninit();
}
//====================================
// 更新処理
//====================================
void CMarker::Update()
{
}
//====================================
// 描画処理
//====================================
void CMarker::Draw()
{
	CObjectX::Draw();
}
//====================================
// 生成処理
//====================================
CMarker* CMarker::Create(D3DXVECTOR3 pos, int nType)
{
	CMarker* pMarker = new CMarker();
	pMarker->m_nType = nType;
	pMarker->Init();
	pMarker->SetPos(pos);

	if (nType == 0) // プレイヤーのスタート位置
	{// スタートマーカー
		pMarker->SetModel("data/MODEL/StartMarker.x");
	}
	if (nType == 1)  // ステージ3のゴール
	{// ゴールマーカー
		pMarker->SetModel("data/MODEL/GoalMarker.x");
	}
	if (nType == 2)  // ステージ1のゴール
	{
		pMarker->SetModel("data/MODEL/NextMarker01.x");
	}
	if (nType == 3)  // ステージ2のゴール
	{
		pMarker->SetModel("data/MODEL/NextMarker01.x");
	}
	if (nType == 4)  // チュートリアルのゴール
	{
		pMarker->SetModel("data/MODEL/NextMarker01.x");
	}

	return pMarker;
}


