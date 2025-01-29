//=================================
// 
// �I�u�W�F�N�g�N���X�@object.h
//outher kida ibuki 
// 
//==================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"
#include "pch.h"

#define MAX_OBJ (1024)     // TODO : �z�u�I�u�W�F�N�g�̐����т�(�}�[�J�[��v���C���[����)���₷�I8/23�ǋL�F�G�̐����܂�!

#define NUM_MAX_PRIORITY (6) // �v���C�I���e�B�̍ő吔


// TODO: undef ���ėǂ��}�N�����搶�Ƃ���y�Ɋm�F���āI
//#ifdef GetObject
//#undef GetObject
//#endif

//�S�I�u�W�F�N�g�̊��N���X
class CObject
{
public:
	// �I�u�W�F�N�g�̎��
	typedef enum
	{
		NONE = 0,	//����
		PLAYER,		//�v���C���[
		ENEMY,		//�G
		BLOCK,		//��
		CAMERA,     //�J����
		SCENE,      //�V�[��
		PLAYER_X,   //3D�̃v���C���[
		MARKER,     //�X�^�[�g���S�[���}�[�J�[
        ENEMY_X,    // 3D�̓G
		LIFE,       // ���C�t��UI
		ATTACK,     // �U��
		EXPLOSION,  // ����
		MAX
	}TYPE;

	CObject();		// �R���X�g���N�^
	CObject(int nPriority);		// �R���X�g���N�^ �I�[�o�[���C�h

	virtual ~CObject();		// �f�X�g���N�^
	virtual HRESULT Init() = 0;		// �������z�֐��̏����ݒ�
	virtual void Uninit() = 0;		// �������z�֐��̏I������
	virtual void Update() = 0;		// �������z�֐��̍X�V����
	virtual void Draw() = 0;		// �������z�֐��̕`�揈��
	static void ReleaseAll();		// �S�I�u�W�F�N�g�̉��
	static void UpdateAll();		// �S�I�u�W�F�N�g�̍X�V
	static void DrawAll();			// �S�I�u�W�F�N�g�̕`��
	static void DeathAll();         // �S�I�u�W�F�N�g�j��


	static CObject* GetObj(int nPriority);						// �I�u�W�F�N�g�擾
	static void GetObj(CObject* pObject[NUM_MAX_PRIORITY]);						// �I�u�W�F�N�g�擾

	TYPE GetType() { return m_type; }		// �^�C�v�擾
	CObject* GetNext() { return m_pNext; }  // ���̃I�u�W�F�N�g���擾
	void SetType(TYPE type);				// �^�C�v�ݒ�

	void Release();					// �������g�̉��
	bool m_bDeath;

	virtual void DeathFlag();
private:
	TYPE m_type;

	//==========���X�g�\��==============================================

	static CObject* m_pTop[NUM_MAX_PRIORITY];  // �擪�̃I�u�W�F�N�g�̃|�C���^
	static CObject* m_pCur[NUM_MAX_PRIORITY];  // ����(�Ō��)�̃|�C���^

	CObject* m_pPrev;  // �O�̃I�u�W�F�N�g�̃|�C���^
	CObject* m_pNext;  // ���̃I�u�W�F�N�g�̃|�C���^

};

#endif
