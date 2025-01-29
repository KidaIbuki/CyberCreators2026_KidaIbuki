//=================================
// 
// UI�N���X�@ui.h
//outher kida ibuki 
// 
//==================================

#include "ui.h"
#include "manager.h"

LPDIRECT3DTEXTURE9 CUi::m_pTextureTemp = {};

//==================================
// �R���X�g���N�^
//==================================
CUi::CUi()
{
	m_nType = 0;
	m_nFrame = 10;
}
//==================================
// �f�X�g���N�^
//==================================
CUi::~CUi()
{
}
//==================================
// �����ݒ�
//==================================
HRESULT CUi::Init()
{
	CObject2D::Init();

	if (m_nType == 0)
	{// �E�U��
		SetSize(100.0f, 100.0f);
	}
	else if (m_nType == 1)
	{// ���U��
		SetSize(100.0f, 100.0f);
	}
	else if (m_nType == 2)
	{// �W�����v
		SetSize(140.0f, 140.0f);
	}
	else if (m_nType == 3)
	{// �E�ړ�
		SetSize(120.0f, 120.0f);
	}
	else if (m_nType == 4)
	{// ���ړ�
		SetSize(120.0f, 120.0f);
	}
	else if (m_nType == 5)
	{
		SetSize(420.0f, 240.0f);
	}
	else if (m_nType == 6)
	{
		SetSize(420.0f, 240.0f);
	}
	else if (m_nType == 7)
	{
		SetSize(420.0f, 240.0f);
	}

	return S_OK;
}
//==================================
// �I������
//==================================
void CUi::Uninit()
{
	CObject2D::Uninit();
}
//==================================
// �X�V����
//==================================
void CUi::Update()
{
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* pKeyboard = pManager->GetKeyboard();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�L�[�{�[�h�擾

	CObject2D::Update();

	if (m_nType == 0)
	{
		// �E�U���̎�
		if (pKeyboard->GetPress(DIK_RIGHT) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_B))
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[(�ԐF�ɂ���)
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 200);

			m_pVtxBuff->Unlock();

		}
		else// ������ĂȂ��Ƃ�
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[(�F��t���Ȃ�)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			m_pVtxBuff->Unlock();
		}

	}
	else if (m_nType == 1)
	{
		// ���U���̎�
		if (pKeyboard->GetPress(DIK_LEFT) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_X))
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[(�ԐF�ɂ���)
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 200);

			m_pVtxBuff->Unlock();

		}
		else// ������ĂȂ��Ƃ�
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[(�F��t���Ȃ�)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			m_pVtxBuff->Unlock();
		}

	}
	else if (m_nType == 2)
	{
		// �W�����v�̎�
		if (pKeyboard->GetPress(DIK_SPACE) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_A))
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[(�ԐF�ɂ���)
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 200);

			m_pVtxBuff->Unlock();

		}
		else// ������ĂȂ��Ƃ�
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[(�F��t���Ȃ�)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			m_pVtxBuff->Unlock();
		}

	}
	else if (m_nType == 3)
	{
		// �E�ړ��̎�
		if (pKeyboard->GetPress(DIK_D) == true || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[(�ԐF�ɂ���)
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 200);

			m_pVtxBuff->Unlock();

		}
		else// ������ĂȂ��Ƃ�
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[(�F��t���Ȃ�)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			m_pVtxBuff->Unlock();
		}

	}
	else if (m_nType == 4)
	{
		// ���ړ��̎�
		if (pKeyboard->GetPress(DIK_A) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT))
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[(�ԐF�ɂ���)
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 200);

			m_pVtxBuff->Unlock();

		}
		else// ������ĂȂ��Ƃ�
		{
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[(�F��t���Ȃ�)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			m_pVtxBuff->Unlock();
		}

	}


}
//==================================
// �`�揈��
//==================================
void CUi::Draw()
{
	CObject2D::Draw();
}
//==================================
// ��������
//==================================
CUi* CUi::Create(D3DXVECTOR2 pos, int nType)
{
	CUi* pUi = new CUi();
	pUi->m_nType = nType;
	pUi->Init();
	pUi->SetPos(pos.x, pos.y);
	if (nType == 0)
	{// �E�U��
		pUi->SetTexture("data/TEXTURE/attackright.png");
	}
	else if (nType == 1)
	{// ���U��
		pUi->SetTexture("data/TEXTURE/attackleft.png");
	}
	else if (nType == 2)
	{// �W�����v
		pUi->SetTexture("data/TEXTURE/jumpicon.png");
	}
	else if (nType == 3)
	{//�E�ړ�
		pUi->SetTexture("data/TEXTURE/righticon.png");
	}
	else if (nType == 4)
	{// ���ړ�
		pUi->SetTexture("data/TEXTURE/lefticon.png");
	}
	else if (nType == 5)
	{
		// �ړ��e�N�X�`��(�`���[�g���A���p)
		pUi->SetTexture("data/TEXTURE/tutorial_move.png");
	}
	else if (nType == 6)
	{
		// �W�����v�e�N�X�`��(�`���[�g���A���p)
		pUi->SetTexture("data/TEXTURE/tutorial_jump.png");
	}
	else if (nType == 7)
	{
		// �U���e�N�X�`��(�`���[�g���A���p)
		pUi->SetTexture("data/TEXTURE/tutorial_attack.png");
	}

	return pUi;
}
//=====================================
// �e�N�X�`���̃��[�h
//=====================================
HRESULT CUi::Load()
{
	CManager* pManager = CManager::GetInstance();

	//�|�C���^��null�Ȃ�
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\life001.png",
			&m_pTextureTemp);
	}

	return S_OK;
}
//=====================================
// �e�N�X�`���̃A�����[�h
//=====================================
void CUi::Unload()
{
	//�e�N�X�`�����g�p���Ă�����j��
	if (m_pTextureTemp != nullptr)
	{
		//null�ɂ���
		m_pTextureTemp = nullptr;
	}
}

