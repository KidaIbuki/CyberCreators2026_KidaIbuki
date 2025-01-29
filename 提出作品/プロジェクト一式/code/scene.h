//=================================
// 
// �V�[���N���X�@scene.h
//outher kida ibuki 
// 
//==================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "pch.h"
#include "object.h"

class CScene
{
public:
	//��ʂ̎��
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_GAME_SECOND, //�Q��
		MODE_GAME_THIRD,  //�R��
		MODE_RESULT,
		MODE_RESULT_LOSE,
		MODE_MAX,
	}MODE;

	CScene();			//�R���X�g���N�^
	virtual ~CScene();			//�f�X�g���N�^
	virtual HRESULT Init();		//�����ݒ�
	virtual void Uninit();      //�I������
	virtual void Update();      //�X�V����
	virtual void Draw();		//�`�揈��
	void SetTexture(std::string sPath);  // �e�N�X�`���̐ݒ�
	void UpdateVertex();
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

	static CScene* Create(MODE mode);   //����
	void SetSize(float fWidth, float fHeight);//�e�e�N�X�`���̃T�C�Y�ݒ�
	void SetPos(float x, float y);			//�e�e�N�X�`���̈ʒu�ݒ�
	MODE GetMode() { return m_Mode; }
	int m_nTimerCnt;
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��
private:
	MODE m_Mode;
	D3DXVECTOR2 m_size;
	D3DXVECTOR2 m_pos;							//�ʒu
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//�e�N�X�`���̃e���v���[�g
};

#endif