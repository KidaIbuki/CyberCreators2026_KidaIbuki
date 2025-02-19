//=================================
// 
//レンダラークラス(DirectX描画)renderer.cpp
//outher kida ibuki 
// 
//==================================
#include "renderer.h"
#include "object2D.h"
#include "manager.h"
#include "sound.h"
//LPDIRECT3DDEVICE9 m_pD3DDevice = nullptr;

bool g_isSwitch = false;

//==========================
//コンストラクタ
//==========================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
}

//===========================
//デストラクタ
//===========================
CRenderer::~CRenderer()
{

}

//============================
//初期化設定
//============================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{

	D3DDISPLAYMODE d3ddm;		//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ

	//DirectXオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードの取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//ゲーム画面のサイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//ゲーム画面のサイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;		//バックバッファの形式
	d3dpp.BackBufferCount = 1;				//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE;//デブスバッファとステンシルバッファを生成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//デブスバッファとして16bitを使用
	d3dpp.Windowed = bWindow;				//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//インターバル

	//DIrectXデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//DIrectXデバイスの生成（描画処理はハードウェア頂点処理はCPUで行う）
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//DIrectXデバイスの生成（描画処理と頂点処理をCPUで行う）
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////サンプラーステートの設定
	//m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	//m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	////テクスチャステージステートの設定
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//pManager->SceneInit();


	return S_OK;

}
//============================
//終了処理
//============================
void CRenderer::Uninit()
{

	//DirectXデバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}
	//DirectXオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
	//pManager->SceneUninit();

}
//============================
//更新処理
//============================
void CRenderer::Update()
{
	CObject::DeathAll();
	CManager* pManager = CManager::GetInstance();  //マネージャーのインスタンス取得
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();    //キーボード取得

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_F10))g_isSwitch = !g_isSwitch;
#endif
}
//============================
//描画処理
//============================
void CRenderer::Draw()
{
	//画面クリア（バックバッファ＆Zバッファのクリア）
	m_pD3DDevice->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_RGBA(0, 200, 200, 0), 1.0f, 0);  //色変えれる


	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		CManager* pManager = CManager::GetInstance();
		

		LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// デバイスを取得
		//ワイヤーフレーム
		g_isSwitch ? pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME) :
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);


		//カメラの設定
		pManager->GetCamera()->SetCamera();

		pManager->GetInstance()->GetScene()->Draw();

		//各種オブジェクトの描画処理
		//CObject::DrawAll();

		//pManager->SceneDraw();
		//描画終了
		m_pD3DDevice->EndScene();

	}
	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}
//===========================
//デバイスの取得
//===========================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;

}
