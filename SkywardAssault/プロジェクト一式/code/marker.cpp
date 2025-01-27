//==============================================
// 
// 3Dのプレイヤー　playerX.h
//outher kida ibuki 
// 
//==============================================
#include "marker.h"   // マーカー
#include "manager.h"    // マネージャー
#include "sound.h"      // サウンド
//====================================
// コンストラクタ
//====================================
CMarker::CMarker()
{
	m_bTouch = false;
	m_bTouchNext1 = false;
	m_bTouchNext2 = false;
	m_bTouchNext3 = false;
	m_bTouchNext4 = false;
	m_bTouchNext5 = false;
	m_bTouchNext6 = false;
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
	CMarker* pMarker = new CMarker;
	pMarker->Init();
	pMarker->SetPos(pos);


	if (nType == 0)
	{// ゴールマーカー
		pMarker->SetModel("data/MODEL/GoalPoint.x");
		pMarker->m_bTouch = true;
	}

	return pMarker;
}

