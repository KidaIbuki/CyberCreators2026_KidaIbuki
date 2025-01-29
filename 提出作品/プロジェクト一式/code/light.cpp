//=================================
// 
//ライトクラス　　light.cpp
//outher kida ibuki 
// 
//==================================
#include "light.h"
#include "manager.h"

//==============================
//コンストラクタ
//==============================
CLight::CLight()
{
	//ライト情報をクリアする
	ZeroMemory(&m_aLight, sizeof(D3DLIGHT9));

}
//==============================
//デストラクタ
//==============================
CLight::~CLight()
{
}
//==============================
//初期設定
//==============================
HRESULT CLight::Init()
{
#if 1
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pManager->GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;		//設定用方向ベクトル

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトの情報をクリアする

		//ライトの種類を設定
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		m_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		switch (nCntLight)
		{
		case 0:
			vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
			break;
		case 1:
			vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(0.89f, 0.11f, 0.44f);
			break;
		}
		//ライトの方向を設定
		//vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		//vecDir[1] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
		//vecDir[2] = D3DXVECTOR3(0.89f, 0.11f, 0.44f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[nCntLight].Direction = vecDir;



		//ライトの設定する
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		//ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
	return S_OK;

#endif
}
//==============================
//終了処理
//==============================
void CLight::Uninit()
{
}
//==============================
//更新処理
//==============================
void CLight::Update()
{
}
