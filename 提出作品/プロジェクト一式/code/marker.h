//==============================================
// 
// �X�^�[�g�A�S�[���}�[�J�[�@marker.h
//outher kida ibuki 
// 
//==============================================
#ifndef _MARKER_H_
#define _MARKER_H_

#include "pch.h"
#include "main.h"
#include "objectX.h"
#include "playerX.h"

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
	int GetType() { return m_nType; }
private:
	int m_nType;

};

#endif
