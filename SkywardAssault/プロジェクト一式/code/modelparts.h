//=================================
// 
// �K�w�\�����f���p�[�c�@modelparts.h
//outher kida ibuki 
// 
//==================================
#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_

#include "object.h"    // �I�u�W�F�N�g

#define MAX_PARTS (10)		//���f���p�[�c�̍ő吔(���f����ς��鎞����ɍ��킹���p�[�c���Őݒ�)
class CModelParts
{
public:
	CModelParts();    // �R���X�g���N�^
	~CModelParts();   // �f�X�g���N�^
	HRESULT Init();   // �����ݒ�
	void Uninit();    // �I������
	void Update();    // �X�V����
	void Draw();      // �`�揈��
	static CModelParts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int idx);   // ��������

	void SetPos(D3DXVECTOR3 pos, int idx);   // �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot, int idx);   // �����ݒ�

	typedef struct
	{
		LPD3DXMESH pMesh;           // ���b�V��
		LPD3DXBUFFER pBuffMat;      // �o�b�t�@
		DWORD dwNumMat;             // �}�g���b�N�X
		D3DXMATRIX mtxWorld;		// ���[���h�ϊ��s��
		D3DXVECTOR3 pos;            // �ʒu
		D3DXVECTOR3 rot;            // ����
		int nIdxModelParent;	//�e���f���̃C���f�b�N�X

		//**===========���f���̃��b�V�����擾=============**
		D3DXVECTOR3 m_vtxMinModel;		//���f���̒��_�̍ŏ��l
		D3DXVECTOR3 m_vtxMaxModel;		//���f���̒��_�̍ő�l
		int m_nNumVtx;					//���_��
		DWORD m_sizeFVF;				//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* m_bpVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
		D3DXVECTOR3 m_nMaxVtx;			//���f���̍ő�l
		D3DXVECTOR3 m_nMinVtx;			//���f���̍ŏ��l

		//D3DXMATRIX GetmtxWorld() { return mtxWorld; }

	}ModelParts;

	ModelParts aModel[MAX_PARTS];

	void SizeVtx();						// �I�u�W�F�N�g�̃T�C�Y�̍ő�ŏ������߂�

	D3DXVECTOR3 m_size;			//�T�C�Y

private:
	//���f���̍\����
	D3DXMATRIX GetWorldMatrix() { return m_mtxWorld; }  //���[���h�}�g���b�N�X���擾(�K�w�\���ɕK�v)
	D3DXMATRIX m_mtxWorld;		//���[���h�ϊ��s��(�e)

	//LPD3DXMESH m_pMesh;			    //���b�V���ւ̃|�C���^

};
#endif