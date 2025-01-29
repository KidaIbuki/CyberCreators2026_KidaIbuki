//=================================
// 
//�t�B�[���h�@field.cpp
//outher kida ibuki 
// 
//==================================
#include "field.h"
#include "manager.h"

// �ÓI�����o�̏�����
LPDIRECT3DTEXTURE9 CField::m_pTextureTemp = {};

//===============================
//�R���X�g���N�^
//===============================
CField::CField()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//===============================
//�f�X�g���N�^
//===============================
CField::~CField()
{
}
//===============================
//�����ݒ�
//===============================
HRESULT CField::Init()
{
	CObject3D::Init();
	SetField(100.0f, 100.0f);

	return S_OK;
}
//===============================
//�I������
//===============================
void CField::Uninit()
{
	CObject3D::Uninit();
}
//===============================
//�X�V����
//===============================
void CField::Update()
{
	//CObject3D::Update();
}
//===============================
//�`�揈��
//===============================
void CField::Draw()
{
	CObject3D::Draw();

}
//===============================
//��������
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
//���[�h
//=======================================
HRESULT CField::Load()
{
	CManager* pManager = CManager::GetInstance();

	//�|�C���^��null�Ȃ�
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\Grass000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//�A�����[�h
//======================================
void CField::Unload()
{
	//�e�N�X�`�����g�p���Ă�����j��
	if (m_pTextureTemp != nullptr)
	{
		//null�ɂ���
		m_pTextureTemp = nullptr;
	}
}

