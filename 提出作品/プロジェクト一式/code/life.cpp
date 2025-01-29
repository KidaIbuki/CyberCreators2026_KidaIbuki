//=================================
// 
// ���C�tUI�N���X�@life.h
//outher kida ibuki 
// 
//==================================
#include "manager.h"
#include "life.h"
#include "pch.h"
#include "sound.h"
LPDIRECT3DTEXTURE9 CLife::m_pTextureTemp = {};
float CLife::m_fTexHeight = 0;
float CLife::m_fTexWidht = 0;
int CLife::m_nFrame = 0;
int CLife::m_nLife = 0;
//==================================
// �R���X�g���N�^
//==================================
CLife::CLife()
{
	m_fTexHeight = 0.2f;   //�c
	m_fTexWidht = 0.0f;    //��
	m_nFrame = 30;
	m_nLife = 50;
}
//==================================
// �f�X�g���N�^
//==================================
CLife::~CLife()
{
}
//==================================
// �����ݒ�
//==================================
HRESULT CLife::Init()
{
	CObject2D::Init();
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice;

	pDevice = pManager->GetRenderer()->GetDevice();

	SetSize(170.0f, 120.0f);


	return S_OK;

}
//==================================
// �I������
//==================================
void CLife::Uninit()
{
	CObject2D::Uninit();
}
//==================================
// �X�V����
//==================================
void CLife::Update()
{
	CObject2D::Update();

	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, m_fTexWidht);
	pVtx[1].tex = D3DXVECTOR2(1.0f, m_fTexWidht);
	pVtx[2].tex = D3DXVECTOR2(0.0f, m_fTexHeight);
	pVtx[3].tex = D3DXVECTOR2(1.0f, m_fTexHeight);
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}
//==================================
// �`�揈��
//==================================
void CLife::Draw()
{
	CObject2D::Draw();
}
//==================================
// ��������
//==================================
CLife* CLife::Create(D3DXVECTOR2 pos)
{
	CLife* pLife = new CLife();
	pLife->Init();
	pLife->SetPos(pos.x, pos.y); //������ƍ�������u
	if (m_pTextureTemp != nullptr)
	{
		pLife->BindTexture(m_pTextureTemp);
	}
	return pLife;
}
//=====================================
//�e�N�X�`���̃��[�h
//=====================================
HRESULT CLife::Load()
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
//�e�N�X�`���̃A�����[�h
//=====================================
void CLife::Unload()
{
	//�e�N�X�`�����g�p���Ă�����j��
	if (m_pTextureTemp != nullptr)
	{
		//null�ɂ���
		m_pTextureTemp = nullptr;
	}
}

//=======================================
// ���C�t�̌��Z����
//=======================================
void CLife::HitLife(int nDamage)
{
	CManager* pManager = CManager::GetInstance();

	// �T�E���h�𗬂�(�v���C���[�̃_���[�W)

	if (m_nFrame >= 0)  // 0��葽��������
	{
		m_nFrame--;   // �J�E���g�_�E��
	}
	if (m_nFrame <= 0)
	{ // ���W�𑝂₷
		pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // ��ʂ̗h��
	    pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_PLAYER_DAMAGE);

		m_fTexHeight += 0.2f;
		m_fTexWidht += 0.2f;
		m_nLife -= nDamage;  // ���C�t�����炷
		m_nFrame = 30;   // �t���[����߂�
	}
	if (m_nLife <= 0)
	{// ���C�t�������Ȃ�����
		CFade::SetFade(CScene::MODE::MODE_RESULT_LOSE);
	}

}
