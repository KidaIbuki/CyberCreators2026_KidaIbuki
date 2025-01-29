//================================
//
//xファイルでブロック(blockX.h)
//outher kida ibuki
//================================
#include "blockX.h"
#include "manager.h"

//======================================
//コンストラクタ
//======================================
CBlockX::CBlockX()
{
}
//======================================
//デストラクタ
//======================================
CBlockX::~CBlockX()
{
}
//======================================
//初期設定
//======================================
HRESULT CBlockX::Init()
{
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	// 種類をブロックに設定
	SetType(CObject::TYPE::BLOCK);


	return S_OK;
}
//======================================
//終了処理
//======================================
void CBlockX::Uninit()
{
		CObjectX::Uninit();
}
//======================================
//更新処理
//======================================
void CBlockX::Update()
{
}
//======================================
//描画処理
//======================================
void CBlockX::Draw()
{
	CObjectX::Draw();

}
//======================================
//ブロックの生成
//======================================
CBlockX* CBlockX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat)
{
	CBlockX* pBlockX = new CBlockX();

	pBlockX->SetPos(pos);
	pBlockX->SetRot(rot);
	pBlockX->m_pMesh = pMesh;
	pBlockX->m_pBuffMat = pBuffMat;
	pBlockX->m_dwNumMat = dwNumMat;

	pBlockX->Init();


	return pBlockX;
}
