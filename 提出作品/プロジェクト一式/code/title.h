//=================================
// 
// �^�C�g���N���X�@title.h
//outher kida ibuki 
// 
//==================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "scene.h"
#include <string>

#define NUM_OBJECT_NUM (512)// �z�u���������f���̐�

class CTitle:public CScene
{
public:
    CTitle();			//�R���X�g���N�^
    ~CTitle()override;			//�f�X�g���N�^
    HRESULT Init()override;		//�����ݒ�
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����
    void Draw()override;		//�`�揈��
     //�E�E�E
    static HRESULT Load();							//�e�N�X�`���̃��[�h
    static void Unload();							//�e�N�X�`���̃A�����[�h
    static CTitle* Create();     //����
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];

    void SetModel_File();

private:
    static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//�e�N�X�`���̃e���v���[�g
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
    LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��
};

#endif