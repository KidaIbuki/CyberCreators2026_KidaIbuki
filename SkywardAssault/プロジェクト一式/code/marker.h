//==============================================
// 
// �X�^�[�g�A�S�[���}�[�J�[�@marker.h
//outher kida ibuki 
// 
//==============================================
#ifndef _MARKER_H_
#define _MARKER_H_

#include "pch.h"   // �v���R���p�C���ς݃w�b�_�[
#include "main.h"  // ���C��
#include "objectX.h"  // �I�u�W�F�N�gX
#include "playerM.h"   // �v���C���[

class CMarker :public CObjectX
{
public:
	CMarker();
	~CMarker()override;
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��

	static CMarker* Create(D3DXVECTOR3 pos, int nType);			// type:�X�^�[�g 0 /�S�[�� 1
private:
	int m_nType;
	bool m_bTouch;
	bool m_bTouchNext1;
	bool m_bTouchNext2;
	bool m_bTouchNext3;
	bool m_bTouchNext4;
	bool m_bTouchNext5;
	bool m_bTouchNext6;

};

#endif
