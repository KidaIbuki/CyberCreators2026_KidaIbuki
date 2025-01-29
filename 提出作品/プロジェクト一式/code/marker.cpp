//==============================================
// 
// 3D�̃v���C���[�@playerX.h
//outher kida ibuki 
// 
//==============================================
#include "marker.h"
#include "playerX.h"
#include "manager.h"
#include "sound.h"
#include "tutorial.h"
//====================================
// �R���X�g���N�^
//====================================
CMarker::CMarker()
{
	m_nType = 0;
}
//====================================
// �f�X�g���N�^
//====================================
CMarker::~CMarker()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CMarker::Init()
{
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}


	SetType(CObject::TYPE::MARKER);


	return S_OK;
}
//====================================
// �I������
//====================================
void CMarker::Uninit()
{
	CObjectX::Uninit();
}
//====================================
// �X�V����
//====================================
void CMarker::Update()
{
}
//====================================
// �`�揈��
//====================================
void CMarker::Draw()
{
	CObjectX::Draw();
}
//====================================
// ��������
//====================================
CMarker* CMarker::Create(D3DXVECTOR3 pos, int nType)
{
	CMarker* pMarker = new CMarker();
	pMarker->m_nType = nType;
	pMarker->Init();
	pMarker->SetPos(pos);

	if (nType == 0) // �v���C���[�̃X�^�[�g�ʒu
	{// �X�^�[�g�}�[�J�[
		pMarker->SetModel("data/MODEL/StartMarker.x");
	}
	if (nType == 1)  // �X�e�[�W3�̃S�[��
	{// �S�[���}�[�J�[
		pMarker->SetModel("data/MODEL/GoalMarker.x");
	}
	if (nType == 2)  // �X�e�[�W1�̃S�[��
	{
		pMarker->SetModel("data/MODEL/NextMarker01.x");
	}
	if (nType == 3)  // �X�e�[�W2�̃S�[��
	{
		pMarker->SetModel("data/MODEL/NextMarker01.x");
	}
	if (nType == 4)  // �`���[�g���A���̃S�[��
	{
		pMarker->SetModel("data/MODEL/NextMarker01.x");
	}

	return pMarker;
}


