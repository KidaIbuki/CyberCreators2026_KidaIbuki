//=================================
// 
//���C�g�N���X�@�@light.cpp
//outher kida ibuki 
// 
//==================================
#include "light.h"
#include "manager.h"

//==============================
//�R���X�g���N�^
//==============================
CLight::CLight()
{
	//���C�g�����N���A����
	ZeroMemory(&m_aLight, sizeof(D3DLIGHT9));

}
//==============================
//�f�X�g���N�^
//==============================
CLight::~CLight()
{
}
//==============================
//�����ݒ�
//==============================
HRESULT CLight::Init()
{
#if 1
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pManager->GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;		//�ݒ�p�����x�N�g��

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g�̏����N���A����

		//���C�g�̎�ނ�ݒ�
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
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
		//���C�g�̕�����ݒ�
		//vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		//vecDir[1] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
		//vecDir[2] = D3DXVECTOR3(0.89f, 0.11f, 0.44f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[nCntLight].Direction = vecDir;



		//���C�g�̐ݒ肷��
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
	return S_OK;

#endif
}
//==============================
//�I������
//==============================
void CLight::Uninit()
{
}
//==============================
//�X�V����
//==============================
void CLight::Update()
{
}
