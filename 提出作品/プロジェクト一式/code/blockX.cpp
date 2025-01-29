//================================
//
//x�t�@�C���Ńu���b�N(blockX.h)
//outher kida ibuki
//================================
#include "blockX.h"
#include "manager.h"

//======================================
//�R���X�g���N�^
//======================================
CBlockX::CBlockX()
{
}
//======================================
//�f�X�g���N�^
//======================================
CBlockX::~CBlockX()
{
}
//======================================
//�����ݒ�
//======================================
HRESULT CBlockX::Init()
{
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	// ��ނ��u���b�N�ɐݒ�
	SetType(CObject::TYPE::BLOCK);


	return S_OK;
}
//======================================
//�I������
//======================================
void CBlockX::Uninit()
{
		CObjectX::Uninit();
}
//======================================
//�X�V����
//======================================
void CBlockX::Update()
{
}
//======================================
//�`�揈��
//======================================
void CBlockX::Draw()
{
	CObjectX::Draw();

}
//======================================
//�u���b�N�̐���
//======================================
CBlockX* CBlockX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat)
{
	CBlockX* pBlockX = new CBlockX();

	pBlockX->SetPos(pos);
	pBlockX->SetRot(rot);
	pBlockX->m_pMesh = pMesh;
	pBlockX->m_pBuffMat = pBuffMat;
	pBlockX->m_dwNumMat = dwNumMat;

	pBlockX->Init();


	return pBlockX;
}
