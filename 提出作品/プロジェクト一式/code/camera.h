//=================================
// 
//�J�����N���X�@camera.h
//outher kida ibuki 
// 
//==================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"
#include "objectX.h"

//�O���錾
class CObjectX;

//�J�����N���X�̒�`
class CCamera
{
public:
	CCamera();					//�R���X�g���N�^
	~CCamera();					//�f�X�g���N�^
	HRESULT Init();				//�����ݒ�
	void Uninit();				//�I������
	void Update();				//�X�V����
	void SetCamera();			//�J�����ݒ�

	void ResetCamera();
	D3DXVECTOR3 GetRot() { return m_rot; }			//�������擾
	D3DXVECTOR3 GetPosR() { return m_posR; }		//�����_�̎擾
	D3DXVECTOR3 GetPosV() { return m_posV; }		//�����_�̎擾

	void SetPos(D3DXVECTOR3 pos);
	void SetShake(int shakeFrame, float shakeVolume);
private:
	D3DXVECTOR3 m_posV;			//���_
	D3DXVECTOR3 m_posR;         //�����_
	D3DXVECTOR3 m_vecU;			//�����
	D3DXVECTOR3 m_rot;			//����
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����s��
	D3DXMATRIX m_mtxView;		//�r���[�s��
	float m_fScaleDis;
	float m_fDistance;		//����
	D3DXVECTOR3 m_move;
	int m_nShakeFrame;
	int m_nShakeVolume;
};

#endif
