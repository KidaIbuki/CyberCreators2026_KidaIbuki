//=================================
// 
//カメラクラス　camera.cpp
//outher kida ibuki 
// 
//==================================
#include "camera.h"
#include "manager.h"
#include "objectX.h"
#include "playerX.h"
#include "title.h"
//==============================
//コンストラクタ
//==============================
CCamera::CCamera()
{
}
//==============================
//デストラクタ
//==============================
CCamera::~CCamera()
{
}
//==============================
//初期設定
//==============================
HRESULT CCamera::Init()
{
	//メンバ変数初期化
	m_posV = { -70.0f, 130.0f, -270.0f };			// 視点
	m_posR = { 0.0f, 40.0f, 60.0f };		        // 注視点
	m_vecU = { 0.0f, 1.0f, 0.0f };				// 上方向
	m_rot = { D3DX_PI * 0.5f, 0.0f, 0.0f };
    m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(100 * 100 + -250 * -250);		//距離
	m_fScaleDis = 1.0f;	//倍率

	m_nShakeFrame = 0;
	m_nShakeVolume = 0;
	m_move = { 0.0f,0.0f,0.0f };

	return S_OK;

}
//==============================
//終了処理
//==============================
void CCamera::Uninit()
{
}
//==============================
//更新処理
//==============================
void CCamera::Update()
{
	CManager* pManager = CManager::GetInstance();	//マネージャーのインスタンスを取得
    	
	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];

		//種類の取得
		while (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();
			CObject* pNext = pObj->GetNext(); // 次のポインタを取得
			if (type == CObject::TYPE::PLAYER_X)
			{
				CPlayerX* pPlayer = (CPlayerX*)pObj; //ダウンキャスト
				if (pPlayer != nullptr)
				{

					D3DXVECTOR3 playerPos = pPlayer->GetPos(); // プレイヤーの位置を取得

					m_posR = playerPos;  // 注視点の追従
					m_posV.y = playerPos.y + 80.0f;  //視点を固定注視点に合わして追従  +～は支店の高さ
					//カメラの視点の追従
					m_posV.x = sinf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + playerPos.x;
					m_posV.z = cosf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + playerPos.z;
				}
			}
			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}

	CScene* pScene = pManager->GetScene();
	CScene::MODE mode = pScene->GetMode();
	// モードの取得
	if (mode == CScene::MODE::MODE_TITLE)
	{// タイトル画面でz軸方向にカメラを移動させる
		m_rot.y += 0.002f;

		//注視点を中心に公転
		m_posV.x = sinf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis;
		m_posV.z = cosf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis;

	}

}
//==============================
//カメラ設定
//==============================
void CCamera::SetCamera()
{
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// デバイスを取得

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);


	// プロジェクションマトリックスを作成(透視投影)
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,		//near
		5000.0f);   //far


	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスの作成
	//D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// カメラの揺れ
	D3DXVECTOR3 adjust = { 0.0f,0.0f,0.0f };
	if (m_nShakeFrame > 0)
	{
		m_nShakeFrame--;
		adjust.x = (float)(rand() % m_nShakeVolume);
		adjust.y = (float)(rand() % m_nShakeVolume);
		//adjust.z = random;
	}
	D3DXVECTOR3 posR, posV;
	posR = m_posR + adjust;  // 注視点
	posV = m_posV + adjust;  // 視点
	D3DXMatrixLookAtLH(&m_mtxView, &posV, &posR, &m_vecU);
	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//==============================
//カメラのリセット
//==============================
void CCamera::ResetCamera()
{
	m_posV = { -70.0f, 130.0f, -270.0f };			// 視点
	m_posR = { 0.0f, 40.0f, 60.0f };		        // 注視点
	m_vecU = { 0.0f, 1.0f, 0.0f };				// 上方向
	m_rot = { D3DX_PI * 0.5f, 0.0f, 0.0f };
	m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(100 * 100 + -250 * -250);		//距離
	m_fScaleDis = 1.0f;	//倍率

}
//==============================
//カメラの位置設定
//==============================
void CCamera::SetPos(D3DXVECTOR3 pos)
{
	m_posR = pos;
}
//==============================
// カメラの揺れの設定
//==============================
void CCamera::SetShake(int shakeFrame, float shakeVolume)
{
	m_nShakeFrame = shakeFrame;
	m_nShakeVolume = (int)shakeVolume;
}


