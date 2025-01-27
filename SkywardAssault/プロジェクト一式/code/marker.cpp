//==============================================
// 
// 3D�̃v���C���[�@playerX.h
//outher kida ibuki 
// 
//==============================================
#include "marker.h"   // �}�[�J�[
#include "manager.h"    // �}�l�[�W���[
#include "sound.h"      // �T�E���h
//====================================
// �R���X�g���N�^
//====================================
CMarker::CMarker()
{
	m_bTouch = false;
	m_bTouchNext1 = false;
	m_bTouchNext2 = false;
	m_bTouchNext3 = false;
	m_bTouchNext4 = false;
	m_bTouchNext5 = false;
	m_bTouchNext6 = false;
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
	CMarker* pMarker = new CMarker;
	pMarker->Init();
	pMarker->SetPos(pos);


	if (nType == 0)
	{// �S�[���}�[�J�[
		pMarker->SetModel("data/MODEL/GoalPoint.x");
		pMarker->m_bTouch = true;
	}

	return pMarker;
}

