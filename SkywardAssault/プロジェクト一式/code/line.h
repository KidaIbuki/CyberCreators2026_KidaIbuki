//=================================
// 
// ���C�� �N���X�@obb.h
//outher kida ibuki 
// 
//==================================
#ifndef _LINE_H_
#define _LINE_H_
#include "pch.h"
#include "object.h"

class CLine :public CObject
{
public:
	CLine();
	~CLine();
	HRESULT Init();     // �����ݒ�
	void Uninit();		// �I������
	void Update();      // �X�V����
	void Draw();        // �`�揈�� 
	void SetLine(const D3DXVECTOR3& start, const D3DXVECTOR3& end, D3DXCOLOR col);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			//�e�I�u�W�F�N�g�̈ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			//�e�I�u�W�F�N�g�̌����ݒ�

	static CLine* Create();
private:
	D3DXVECTOR3 m_start;
	D3DXVECTOR3 m_end;
	D3DXCOLOR m_col;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	D3DXMATRIX m_mtxWorld;						//���[���h�ϊ��s��
	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_rot;							//����

};
class Line
{
public:
	Line();
	~Line();
	void InitLine(LPDIRECT3DDEVICE9 pDevice);
	void CleanupLine();
	void DrawBox(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 min, D3DXVECTOR3 max);
private:
	ID3DXLine* m_pLine;
};

#endif
