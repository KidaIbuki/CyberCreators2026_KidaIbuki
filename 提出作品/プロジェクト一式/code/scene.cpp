//=================================
// 
// �V�[���N���X�@scene.cpp
//outher kida ibuki 
// 
//==================================
#include "scene.h"
#include "manager.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "object.h"

//�ÓI�����o�ϐ�������
LPDIRECT3DTEXTURE9 CScene::m_pTextureTemp = {};

//====================================
// �R���X�g���N�^
//====================================
CScene::CScene()
{
	m_Mode = MODE_TITLE;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_size = { 0.0f,0.0f };
	m_pos = { 0.0f,0.0f };

	Init();
}
//====================================
// �f�X�g���N�^
//====================================
CScene::~CScene()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CScene::Init()
{
	
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	CTitle::Load();
	CResult::Load();
	CResultLose::Load();

	return S_OK;
}
//====================================
// �I������
//====================================
void CScene::Uninit()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	CTitle::Unload();
	CResult::Unload();
	CResultLose::Unload();
}
//====================================
// �X�V����
//====================================
void CScene::Update()
{
	UpdateVertex();

}
//====================================
// �`�揈��
//====================================
void CScene::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager* pManager = CManager::GetInstance();

	pDevice = pManager->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//Z�̔�r���@��ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Z�o�b�t�@�ɏ������܂Ȃ�(���ɕ\�����邩�A��O�ɕ\�����邩)
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);


	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//====================================
// �V�[���̐���
//====================================
CScene* CScene::Create(MODE mode)
{
		//case MODE_TITLE:CTitle::Create(); break;

	CScene* pScene = nullptr;
	switch (mode)
	{
	case MODE_TITLE:
		pScene = CTitle::Create();
		break;
	case MODE_TUTORIAL:
		CManager::GetInstance()->GetCamera()->ResetCamera();   //�^�C�g���ŉ�]�������ʒu�Ȃǂ����Z�b�g(���ƂɈʒu��)����
		pScene = CTutorial::Create();
		break;
		//�X�e�[�W1
	case MODE_GAME:
		CManager::GetInstance()->GetCamera()->ResetCamera();   //�^�C�g���ŉ�]�������ʒu�Ȃǂ����Z�b�g(���ƂɈʒu��)����
		pScene = CGame::Create();
		break;
		//�X�e�[�W2
	case MODE_GAME_SECOND:
		CManager::GetInstance()->GetCamera()->ResetCamera();   //��]�������ʒu�Ȃǂ����Z�b�g(���ƂɈʒu��)����
		pScene = CGameSecond::Create();
		break;
	case MODE_GAME_THIRD:
		CManager::GetInstance()->GetCamera()->ResetCamera();   //��]�������ʒu�Ȃǂ����Z�b�g(���ƂɈʒu��)����
		pScene = CGameThird::Create();
		break;
	case MODE_RESULT:
		pScene = CResult::Create();
		break;
	case MODE_RESULT_LOSE:
		pScene = CResultLose::Create();
		break;
	}
	pScene->m_Mode = mode;

	return pScene;
}
#if 1
//=============================
//�e�N�X�`���̐ݒ�
//=============================
void CScene::SetTexture(std::string sPath)		//�����ɓǂݍ��݂����e�N�X�`���̃p�X������
{
	CManager* pManager = CManager::GetInstance();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, sPath.c_str(), &m_pTexture);
}
//==============================
//�e�N�X�`���̐ݒ�2
//==============================
void CScene::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}
#endif
//=========================================
// ���W�̐ݒ�
//=========================================
void CScene::SetPos(float x, float y)
{
	m_pos = D3DXVECTOR2(x, y);
}
//============================
//�T�C�Y�ݒ�
//============================
void CScene::SetSize(float fWidth, float fHeight)
{
	m_size = D3DXVECTOR2(fWidth, fHeight);
}
#if 1
//==============================
//�ʒu�̍X�V
//=============================
void CScene::UpdateVertex()
{
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);

	D3DXVECTOR3 sizePos[4] =
	{
		{-m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f},
		{m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f},
		{-m_size.x * 0.5f, m_size.y * 0.5f, 0.0f},
		{m_size.x * 0.5f, m_size.y * 0.5f, 0.0f}
	};
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �T�C�Y�Ɖ�]
	D3DXVec3TransformCoord(&pVtx[0].pos, &sizePos[0], &mtx);
	D3DXVec3TransformCoord(&pVtx[1].pos, &sizePos[1], &mtx);
	D3DXVec3TransformCoord(&pVtx[2].pos, &sizePos[2], &mtx);
	D3DXVec3TransformCoord(&pVtx[3].pos, &sizePos[3], &mtx);

	// �ʒu
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].pos.x += m_pos.x;
		pVtx[nCnt].pos.y += m_pos.y;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();


}
#endif
