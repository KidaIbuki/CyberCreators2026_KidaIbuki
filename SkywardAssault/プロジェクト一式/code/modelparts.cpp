//=================================
// 
// �K�w�\�����f���p�[�c�@modelparts.h
//outher kida ibuki 
// 
//==================================
#include "modelparts.h"   // ���f���p�[�c
#include "manager.h"    // �}�l�[�W���[
#include "pch.h"        // �v���R���p�C���ς݃w�b�_�[

//===========================================================================
// �R���X�g���N�^
//===========================================================================
CModelParts::CModelParts()
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		aModel[nCnt].pMesh = nullptr;
		aModel[nCnt].pBuffMat = nullptr;
		aModel[nCnt].dwNumMat = 0;
		aModel[nCnt].m_nMaxVtx = { 0.0f,0.0f,0.0f };
		aModel[nCnt].m_nMinVtx = { 0.0f,0.0f,0.0f };
	}
	m_size = {0.0f,0.0f,0.0f};
}
//===========================================================================
// �f�X�g���N�^
//===========================================================================
CModelParts::~CModelParts()
{
}
//===========================================================================
//���f���̒��_�������ɃT�C�Y�̍ő�l�ŏ��l�����߂�
//===========================================================================
void CModelParts::SizeVtx()
{
	//**========================���b�V���̏����擾================**
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (aModel[nCnt].pMesh != nullptr)
		{
			//���_���̎擾
			aModel[nCnt].m_nNumVtx = aModel[nCnt].pMesh->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			aModel[nCnt].m_sizeFVF = D3DXGetFVFVertexSize(aModel[nCnt].pMesh->GetFVF());

			//���_�o�b�t�@�̃��b�N
			aModel[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&aModel[nCnt].m_bpVtxBuff);

			for (int nCntVtx = 0; nCntVtx < aModel[nCnt].m_nNumVtx; nCntVtx++)
			{
				//���_���W����
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)aModel[nCnt].m_bpVtxBuff;

				//���_���W���r���ă��f���̍ő�l�A�ŏ��l���擾
				//x�̍ő�l
				if (vtx.x > aModel[nCnt].m_nMaxVtx.x)
				{
					aModel[nCnt].m_nMaxVtx.x = vtx.x;
				}
				//x�̍ŏ��l
				else if (vtx.x < aModel[nCnt].m_nMinVtx.x)
				{
					aModel[nCnt].m_nMinVtx.x = vtx.x;
				}
				//y�̍ő�l
				if (vtx.y > aModel[nCnt].m_nMaxVtx.y)
				{
					aModel[nCnt].m_nMaxVtx.y = vtx.y;
				}
				//y�̍ŏ��l
				else if (vtx.y < aModel[nCnt].m_nMinVtx.y)
				{
					aModel[nCnt].m_nMinVtx.y = vtx.y;
				}
				//z�̍ő�l
				if (vtx.z > aModel[nCnt].m_nMaxVtx.z)
				{
					aModel[nCnt].m_nMaxVtx.z = vtx.z;
				}
				//z�̍ŏ��l
				else if (vtx.z < aModel[nCnt].m_nMinVtx.z)
				{
					aModel[nCnt].m_nMinVtx.z = vtx.z;
				}

				//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				aModel[nCnt].m_bpVtxBuff += aModel[nCnt].m_sizeFVF;
			}
			//���_�o�b�t�@�̃A�����b�N
			aModel[nCnt].pMesh->UnlockVertexBuffer();

			//**=========================================================**
			m_size = aModel[nCnt].m_nMaxVtx - aModel[nCnt].m_nMinVtx;
		}
	}
}

//===========================================================================
// �����ݒ�
//===========================================================================
HRESULT CModelParts::Init()
{
	CManager* pManager = CManager::GetInstance();
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/PLAYER/00_bodyB.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[0].pBuffMat, NULL, &aModel[0].dwNumMat, &aModel[0].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/01_bodyF.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[1].pBuffMat, NULL, &aModel[1].dwNumMat, &aModel[1].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/02_leftWingU1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[2].pBuffMat, NULL, &aModel[2].dwNumMat, &aModel[2].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/03_leftWingU2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[3].pBuffMat, NULL, &aModel[3].dwNumMat, &aModel[3].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/04_leftWingD1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[4].pBuffMat, NULL, &aModel[4].dwNumMat, &aModel[4].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/05_leftWingD2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[5].pBuffMat, NULL, &aModel[5].dwNumMat, &aModel[5].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/06_rightWingD1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[6].pBuffMat, NULL, &aModel[6].dwNumMat, &aModel[6].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/07_rightWingD2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[7].pBuffMat, NULL, &aModel[7].dwNumMat, &aModel[7].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/08_rightWingU1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[8].pBuffMat, NULL, &aModel[8].dwNumMat, &aModel[8].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/09_rightWingU2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[9].pBuffMat, NULL, &aModel[9].dwNumMat, &aModel[9].pMesh);

	SizeVtx();

	// �e�p�[�c�ɐe��ݒ肷��
	aModel[0].nIdxModelParent = -1;
	aModel[1].nIdxModelParent = 0;
	aModel[2].nIdxModelParent = 0;
	aModel[3].nIdxModelParent = 2;
	aModel[4].nIdxModelParent = 0;
	aModel[5].nIdxModelParent = 4;
	aModel[6].nIdxModelParent = 0;
	aModel[7].nIdxModelParent = 6;
	aModel[8].nIdxModelParent = 0;
	aModel[9].nIdxModelParent = 8;


	//�ʒu(�I�t�Z�b�g)�̐ݒ�
	aModel[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	aModel[1].pos = D3DXVECTOR3(0.0f, 0.0f, -26.0f);
	aModel[2].pos = D3DXVECTOR3(9.0f, 2.0f, -4.0f);
	aModel[3].pos = D3DXVECTOR3(22.0f, 6.0f, 0.0f);
	aModel[4].pos = D3DXVECTOR3(9.0f, -2.0f, -4.0f);
	aModel[5].pos = D3DXVECTOR3(22.0f, -6.0f, 0.0f);
	aModel[6].pos = D3DXVECTOR3(-9.0f, -2.0f, -4.0f);
	aModel[7].pos = D3DXVECTOR3(-22.0f, -6.0f, 0.0f);
	aModel[8].pos = D3DXVECTOR3(-9.0f, 2.0f, -4.0f);
	aModel[9].pos = D3DXVECTOR3(-22.0f, 6.0f, 0.0f);


	//����(�I�t�Z�b�g)�̐ݒ�
	aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}
//===========================================================================
// �I������
//===========================================================================
void CModelParts::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		// ���b�V���̔j��
		if (aModel[nCnt].pMesh != nullptr)
		{
			aModel[nCnt].pMesh->Release();
			aModel[nCnt].pMesh = nullptr;
		}
		// �}�e���A���̔j��
		if (aModel[nCnt].pBuffMat != nullptr)
		{
			aModel[nCnt].pBuffMat->Release();
			aModel[nCnt].pBuffMat = nullptr;
		}
	}

}
//===========================================================================
// �X�V����
//===========================================================================
void CModelParts::Update()
{
}
//===========================================================================
// �`�揈��
//===========================================================================
void CModelParts::Draw()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾
	D3DXMATRIX mtxRot, mtxTrans;											// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;					// �}�e���A���f�[�^�ւ̃|�C���^


	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
	    // ���[���h�}�g���b�N�X�̏�����
	    D3DXMatrixIdentity(&aModel[nCnt].mtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, aModel[nCnt].rot.y, aModel[nCnt].rot.x, aModel[nCnt].rot.z);
		D3DXMatrixMultiply(&aModel[nCnt].mtxWorld, &aModel[nCnt].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, aModel[nCnt].pos.x, aModel[nCnt].pos.y, aModel[nCnt].pos.z);
		D3DXMatrixMultiply(&aModel[nCnt].mtxWorld, &aModel[nCnt].mtxWorld, &mtxTrans);

		// �e�̍s��Ɗ|�����킹��
		D3DXMATRIX mtxParent;
		if (aModel[nCnt].nIdxModelParent != -1)
		{
			// �e�̃��[���h�ϊ��s����擾
			mtxParent = aModel[aModel[nCnt].nIdxModelParent].mtxWorld;
		}
		else
		{
			// �ŐV�̃��[���h�ϊ��s����擾(=�v���C���[�̍s��)
			pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
		}
		// �p�[�c�̃��[���h�ϊ��s���mtxParent���|�����킹��
		D3DXMatrixMultiply(&aModel[nCnt].mtxWorld, &aModel[nCnt].mtxWorld, &mtxParent);


		// ���[���h�ϊ��s��̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &aModel[nCnt].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)aModel[nCnt].pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)aModel[nCnt].dwNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			pDevice->SetTexture(0, NULL);

			// ���f���̕`��
			aModel[nCnt].pMesh->DrawSubset(nCntMat);
		}

		// �ۑ����Ă����}�e���A���ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}
//===========================================================================
// ����
//===========================================================================
CModelParts* CModelParts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int idx)
{
	CModelParts* pParts = new CModelParts();
	pParts->SetPos(pos, idx);
	pParts->SetRot(rot, idx);
	pParts->Init();
	return pParts;
}


//===========================================================================
// �I�t�Z�b�g�̈ʒu�̐ݒ�
//===========================================================================
void CModelParts::SetPos(D3DXVECTOR3 pos, int idx)
{
	aModel[idx].pos = pos;
}
//===========================================================================
// �I�t�Z�b�g�̌����̐ݒ�
//===========================================================================
void CModelParts::SetRot(D3DXVECTOR3 rot, int idx)
{
	aModel[idx].rot = rot;
}



