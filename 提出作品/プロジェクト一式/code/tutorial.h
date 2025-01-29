//=================================
// 
// �`���[�g���A���N���X�@gaem.h
//outher kida ibuki 
// 
//==================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "scene.h"
#include "camera.h"
#include "light.h"

#define NUM_OBJECT_NUM (512)// �z�u���������f���̐�

#define POSITION_NUM_1 (0.0f)  // �`���[�g���A���p�e�N�X�`��1�̕\���ʒu
#define POSITION_NUM_2 (3.0f)  // �`���[�g���A���p�e�N�X�`��1�̕\���ʒu

#define POSITION_NUM_3 (100.0f)  // �`���[�g���A���p�e�N�X�`��2�̕\���ʒu
#define POSITION_NUM_4 (103.0f)  // �`���[�g���A���p�e�N�X�`��2�̕\���ʒu

#define POSITION_NUM_5 (200.0f)  // �`���[�g���A���p�e�N�X�`��3�̕\���ʒu
#define POSITION_NUM_6 (203.0f)  // �`���[�g���A���p�e�N�X�`��3�̕\���ʒu

class CTutorial :public CScene
{
public:
    CTutorial();			//�R���X�g���N�^
    ~CTutorial()override;			//�f�X�g���N�^
    HRESULT Init()override;
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����
    void Draw()override;		//�`�揈��
     //�E�E�E
    static CTutorial* Create();     //����
    void SetModel_File_tutorial();
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];

private:
    int m_nFrame;

    // ���݂̃v���C���[�̈ʒu�Ƀe�N�X�`���𒣂�
    typedef enum
    {
        POSITION_NONE = 0,
        POSITION_1,
        POSITION_2,
        POSITION_3,
        POSITION_MAX
    }POSITION;

    POSITION m_Position;

};

#endif