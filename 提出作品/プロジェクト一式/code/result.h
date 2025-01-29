//=================================
// 
// ���U���g�N���X�@result.h
//outher kida ibuki 
// 
//==================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "scene.h"
#include <string>
class CResult :public CScene
{
public:
    CResult();			//�R���X�g���N�^
    ~CResult()override;			//�f�X�g���N�^
    HRESULT Init()override;		//�����ݒ�
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����
    void Draw()override;		//�`�揈��
     //�E�E�E
    static HRESULT Load();							//�e�N�X�`���̃��[�h
    static void Unload();							//�e�N�X�`���̃A�����[�h
    static CResult* Create();     //����

private:
    static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//�e�N�X�`���̃e���v���[�g
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
    LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��
};

class CResultLose :public CResult
{
public:
    CResultLose();			//�R���X�g���N�^
    ~CResultLose()override;			//�f�X�g���N�^
    HRESULT Init()override;		//�����ݒ�
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����
    void Draw()override;		//�`�揈��
     //�E�E�E
    static HRESULT Load();							//�e�N�X�`���̃��[�h
    static void Unload();							//�e�N�X�`���̃A�����[�h
    static CResultLose* Create();     //����
private:
    static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//�e�N�X�`���̃e���v���[�g
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
    LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��

};

#endif