//=================================
// 
//�����_���[�N���X(DirectX�`��)renderer.cpp
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
//�R���X�g���N�^
//==========================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
}

//===========================
//�f�X�g���N�^
//===========================
CRenderer::~CRenderer()
{

}

//============================
//�������ݒ�
//============================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{

	D3DDISPLAYMODE d3ddm;		//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;//�v���[���e�[�V�����p�����[�^

	//DirectX�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h�̎擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//�Q�[����ʂ̃T�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//�Q�[����ʂ̃T�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;		//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;				//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;//�f�u�X�o�b�t�@�ƃX�e���V���o�b�t�@�𐶐�
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�f�u�X�o�b�t�@�Ƃ���16bit���g�p
	d3dpp.Windowed = bWindow;				//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//�C���^�[�o��

	//DIrectX�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//DIrectX�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A���_������CPU�ōs���j
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//DIrectX�f�o�C�X�̐����i�`�揈���ƒ��_������CPU�ōs���j
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

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////�T���v���[�X�e�[�g�̐ݒ�
	//m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	//m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	////�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//pManager->SceneInit();


	return S_OK;

}
//============================
//�I������
//============================
void CRenderer::Uninit()
{

	//DirectX�f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}
	//DirectX�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
	//pManager->SceneUninit();

}
//============================
//�X�V����
//============================
void CRenderer::Update()
{
	CObject::DeathAll();
	CManager* pManager = CManager::GetInstance();  //�}�l�[�W���[�̃C���X�^���X�擾
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();    //�L�[�{�[�h�擾

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_F10))g_isSwitch = !g_isSwitch;
#endif
}
//============================
//�`�揈��
//============================
void CRenderer::Draw()
{
	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A�j
	m_pD3DDevice->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_RGBA(0, 200, 200, 0), 1.0f, 0);  //�F�ς����


	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
		CManager* pManager = CManager::GetInstance();
		

		LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾
		//���C���[�t���[��
		g_isSwitch ? pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME) :
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);


		//�J�����̐ݒ�
		pManager->GetCamera()->SetCamera();

		pManager->GetInstance()->GetScene()->Draw();

		//�e��I�u�W�F�N�g�̕`�揈��
		//CObject::DrawAll();

		//pManager->SceneDraw();
		//�`��I��
		m_pD3DDevice->EndScene();

	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}
//===========================
//�f�o�C�X�̎擾
//===========================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;

}
