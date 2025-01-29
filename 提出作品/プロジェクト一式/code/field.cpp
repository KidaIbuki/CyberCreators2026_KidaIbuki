//=================================
// 
//フィールド　field.cpp
//outher kida ibuki 
// 
//==================================
#include "field.h"
#include "manager.h"

// 静的メンバの初期化
LPDIRECT3DTEXTURE9 CField::m_pTextureTemp = {};

//===============================
//コンストラクタ
//===============================
CField::CField()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//===============================
//デストラクタ
//===============================
CField::~CField()
{
}
//===============================
//初期設定
//===============================
HRESULT CField::Init()
{
	CObject3D::Init();
	SetField(100.0f, 100.0f);

	return S_OK;
}
//===============================
//終了処理
//===============================
void CField::Uninit()
{
	CObject3D::Uninit();
}
//===============================
//更新処理
//===============================
void CField::Update()
{
	//CObject3D::Update();
}
//===============================
//描画処理
//===============================
void CField::Draw()
{
	CObject3D::Draw();

}
//===============================
//生成処理
//===============================
CField* CField::Create(D3DXVECTOR3 pos)
{
	CField* pField = new CField;

	pField->Init();
	pField->SetPos(pos);
	if (m_pTextureTemp != nullptr)
	{
		pField->BindTexture(m_pTextureTemp);
	}


	return pField;

}
//=======================================
//ロード
//=======================================
HRESULT CField::Load()
{
	CManager* pManager = CManager::GetInstance();

	//ポインタがnullなら
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込む
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\Grass000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//アンロード
//======================================
void CField::Unload()
{
	//テクスチャを使用していたら破棄
	if (m_pTextureTemp != nullptr)
	{
		//nullにする
		m_pTextureTemp = nullptr;
	}
}

