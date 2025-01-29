//=================================
// 
// �}�l�[�W���@manager.h
//outher kida ibuki 
// 
//==================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "scene.h"
#include "fade.h"
#include "sound.h"

class CManager;

// �}�l�[�W���N���X�̒�`
class CManager
{
private:
	CManager();															//�R���X�g���N�^
public:
	~CManager();														//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);			//�����ݒ�
	void Uninit();														//�I������
	void Update();														//�X�V����
	void Draw();	                                                    //�`�揈��

	//�V���O���g��
	static CManager* GetInstance()
	{
		static CManager instance; // �ÓI�C���X�^���X
		return &instance;
	}
	
	void SetSwitch(bool bSwitch) { m_bSwitch = bSwitch; }
	bool GetSwitch() { return m_bSwitch; }
	CRenderer* GetRenderer();									//�����_���[�̎擾
	CCamera* GetCamera();										//�J�����̎擾
	CLight* GetLight();											//���C�g�̎擾
	CInputKeyboard* GetKeyboard();							    //�L�[�{�[�h���͂̎擾
	CInputJoypad* GetJoypad();							    //�R���g���[���[���͂̎擾
	void SetMode(CScene::MODE mode);							//�V�[���̎擾
	CScene* GetScene();
	CFade* GetFade();											//�t�F�[�h�̎擾
	CSound* GetSound();                                         // �T�E���h�̎擾
private:
	CRenderer* m_pRenderer;				//�����_���[���
	CCamera* m_pCamera;					//�r���[���
	CLight* m_pLight;                   //���C�g���
	CInputKeyboard* m_pKeyboard;		//�L�[�{�[�h���
	CInputJoypad* m_pKeyJoypad;		    //�R���g���[���[���
	CScene* m_pScene;					//�V�[�����
	CFade* m_pFade;						//�t�F�[�h�̏��
	CScene::MODE m_mode;
	CSound* m_pSound;                   // �T�E���h�̏��
	bool m_bSwitch;
};

#endif 
