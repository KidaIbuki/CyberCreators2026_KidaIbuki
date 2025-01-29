//==============================================
// 
//�I�u�W�F�N�g(x�t�@�C���̓ǂݍ���)�@objectX.h
//outher kida ibuki 
// 
//==============================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "object.h"
#include "pch.h"
#include "main.h"

#define MAX_CHAR (256)
#define NUM_MODEL (5) //���f���̎��

class CCamera;

//�I�u�W�F�N�gX�N���X�̒�`
class CObjectX :public CObject
{
public:
	//**==================��{����====================**
	CObjectX();		//�R���X�g���N�^
	~CObjectX() override;		//�f�X�g���N�^
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��


	//**=================�e�����̏���==================**
	static CObjectX* Create();		//�I�u�W�F�N�g�̐���
	void SetModel(std::string sPath);		//���f���̃Z�b�g
	void SizeVtx();						// �I�u�W�F�N�g�̃T�C�Y�̍ő�ŏ������߂�
	//**===============�e�ݒ�̎擾======================**
	D3DXVECTOR3 GetPos() { return m_pos; }			//�ʒu�̎擾
	D3DXVECTOR3 GetSize() { return m_size; }		//�T�C�Y�̎擾
	D3DXVECTOR3 GetRot() { return m_rot; }

	void SetPos(D3DXVECTOR3 pos);			//�e�I�u�W�F�N�g�̈ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(float fWidth, float fHeight, float fDepth);	//�e�I�u�W�F�N�g�̃T�C�Y�ݒ�

	D3DXMATRIX GetWorldMatrix() { return m_mtxWorld; }  //���[���h�}�g���b�N�X���擾(�K�w�\���ɕK�v)

	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_move;							//�ړ���
	D3DXVECTOR3 m_size;							//�T�C�Y

protected:
	//**==============�`��̏��=================**
	D3DXMATRIX m_mtxWorld;		//���[���h�ϊ��s��
	LPD3DXMESH m_pMesh;			//���b�V���ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;    //�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;           //�}�e���A���̐�

	//���f���t�@�C���̓ǂݍ��ݍ\����
	typedef struct
	{
		int nType;
		char cFile[MAX_CHAR];		//�t�@�C����ǂݍ���
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		int nIndexFile;
		int Parent;			//�p�[�c�̐e�q�֌W
	}MODEL_FILENAME;

	MODEL_FILENAME m_gModelData[NUM_MODEL];

private:
	//**=============���̃I�u�W�F�N�gX�ł����g���Ȃ��֐�===============**


	//**==========�����o�ϐ�================**
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��


	//**===========���f���̃��b�V�����擾=============**
	D3DXVECTOR3 m_vtxMinModel;		//���f���̒��_�̍ŏ��l
	D3DXVECTOR3 m_vtxMaxModel;		//���f���̒��_�̍ő�l
	int m_nNumVtx;					//���_��
	DWORD m_sizeFVF;				//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* m_bpVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_nMaxVtx;					//���f���̍ő�l
	D3DXVECTOR3 m_nMinVtx;					//���f���̍ŏ��l



};
#endif
