//=================================
// 
// �Q�[�������N���X�@gaem.h
//outher kida ibuki 
// 
//==================================
#ifndef _GAME_H_
#define _GAME_H_
#include "scene.h"
#include "camera.h"
#include "light.h"

#define NUM_OBJECT_NUM (512)// �z�u���������f���̐�
#define NUM_ENEMY (100)  // �z�u�������G�̐�

class CGame :public CScene
{
public:
    CGame();			//�R���X�g���N�^
    ~CGame()override;			//�f�X�g���N�^
    HRESULT Init()override;
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����
    void Draw()override;		//�`�揈��
     //�E�E�E
    static CGame* Create();     //����
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];
    ENEMY_FILENAME g_aEnemyData[NUM_ENEMY];
    // �u���b�N�̊O���t�@�C���o��
    void SetModel_File();
    void SetModel_File2();
    void SetModel_File3();
    // �G�̊O���t�@�C���o��
    void SetEnemy_File();
    void SetEnemy_File2();
    void SetEnemy_File3();

private:
    bool m_bPause;
};
class CGameSecond :public CGame
{
public:
    CGameSecond();
    ~CGameSecond();
    HRESULT Init()override;
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����
    void Draw()override;		//�`�揈��

    static CGameSecond* Create();
private:
    bool m_bPause2;
};

class CGameThird :public CGame
{
public:
    CGameThird();
    ~CGameThird();
    HRESULT Init()override;
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����
    void Draw()override;		//�`�揈��

    static CGameThird* Create();
private:
    bool m_bPause3;
};

#endif