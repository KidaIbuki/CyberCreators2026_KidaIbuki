#include "line.h"
#include "manager.h"
CLine::CLine()
{
	m_start = { 0.0f,0.0f,0.0f };
	m_end = { 0.0f,0.0f,0.0f };
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
}

CLine::~CLine()
{
}

HRESULT CLine::Init()
{
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾
	SetType(CObject::TYPE::LINE);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, nullptr);

	SetLine(m_start, m_end, m_col);

	return S_OK;
}

void CLine::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

}

void CLine::Update()
{

}

void CLine::Draw()
{
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

    //���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);

}

void CLine::SetLine(const D3DXVECTOR3& start, const D3DXVECTOR3& end, D3DXCOLOR col)
{
	m_start = start;
	m_end = end;
	m_col = col;

	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = m_start;
	pVtx[1].pos = m_end;

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

CLine* CLine::Create()
{
	CLine* pLine = new CLine();

	pLine->Init();

	return pLine;
}

Line::Line()
{
	m_pLine = nullptr;
}

Line::~Line()
{
}

void Line::InitLine(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXCreateLine(pDevice, &m_pLine);
}

void Line::CleanupLine()
{
	if (m_pLine) 
	{
		m_pLine->Release();
		m_pLine = nullptr;
	}
}

//void Line::DrawBox(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 min, D3DXVECTOR3 max)
//{
//	// �{�b�N�X�̒��_���X�g�i3D��ԁj
//	D3DXVECTOR3 vertices[8] = {
//		{ min.x, min.y, min.z },
//		{ max.x, min.y, min.z },
//		{ max.x, max.y, min.z },
//		{ min.x, max.y, min.z },
//		{ min.x, min.y, max.z },
//		{ max.x, min.y, max.z },
//		{ max.x, max.y, max.z },
//		{ min.x, max.y, max.z },
//	};
//
//	// ���_���Ȃ��C���f�b�N�X
//	int indices[24] = {
//		0, 1, 1, 2, 2, 3, 3, 0, // Front face
//		4, 5, 5, 6, 6, 7, 7, 4, // Back face
//		0, 4, 1, 5, 2, 6, 3, 7  // Connecting edges
//	};
//
//	if (m_pLine) {
//		m_pLine->SetWidth(1.0f); // ���̑�����ݒ�
//		m_pLine->Begin();
//
//		for (int i = 0; i < 24; i += 2) {
//			// 3D���W��2D�ɕϊ�
//			D3DXVECTOR2 line[] = {
//				{ vertices[indices[i]].x, vertices[indices[i]].y },
//				{ vertices[indices[i + 1]].x, vertices[indices[i + 1]].y }
//			};
//
//			// ���C���`��
//			m_pLine->Draw(line, 2, D3DCOLOR_XRGB(255, 0, 0)); // �ԐF
//		}
//
//		m_pLine->End();
//	}
//}
