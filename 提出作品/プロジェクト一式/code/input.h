//��������������������������
//
//���͏����iinput.h)
//Author ibuki kida
// 
//��������������������������
#ifndef _INPUT_H_	//���̃}�N����`������ĂȂ�������
#define _INPUT_H_	//��d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "pch.h"
#include "dinput.h"						//���͏����ɕK�v

#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")		//�W���C�p�b�h�����ɕK�v

#define MAX_KEY (256)


//���͊��N���X(DirectInput�̊Ǘ�)
class CInput
{
public:
	CInput();		//�R���X�g���N�^
	virtual ~CInput();		//�f�X�g���N�^
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;	//�������z�֐��̍X�V����

protected:
	//�S���͏����ŋ��L
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//�L�[�{�[�h����(�h���N���X)
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();		//�R���X�g���N�^
	~CInputKeyboard() override;		//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;
	bool GetPress(int nKey);		//�v���X��Ԏ擾
	bool GetTrigger(int nKey);		//�g���K�[��Ԏ擾

private:
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];
};
//�p�b�h����(�h���N���X)��
class CInputJoypad :public CInput
{
public:
	//�L�[�̎��
	typedef enum
	{
		JOYKEY_UP = 0,			//�\���L�[(��)
		JOYKEY_DOWN,			//�\���L�[(��)
		JOYKEY_LEFT,			//�\���L�[(��)					���̏��Ԃ���Ȃ��ƃL�[���킩��Ȃ��Ȃ�I
		JOYKEY_RIGHT,			//�\���L�[(�E)
		JOYKEY_START,			//START�{�^��
		JOYKEY_BACK,			//BACK�{�^��
		JOYKEY_LEFT_THUMB,		//���X�e�B�b�N��������
		JOYKEY_RIGHT_THUMB,		//�E�X�e�B�b�N��������
		JOYKEY_LEFT_SHOULDER,	//LB�{�^��
		JOYKEY_RIGHT_SHOULDER,	//RB�{�^��
		JOYKEY_UNCOMN1,			//��L�[
		JOYKEY_UNCOMN2,
		JOYKEY_A,				//A�{�^��
		JOYKEY_B,				//B�{�^��
		JOYKEY_X,				//X�{�^��
		JOYKEY_Y,				//Y�{�^��
		JOYKEY_MAX
	}JOYKEY;

	CInputJoypad();		//�R���X�g���N�^
	~CInputJoypad() override;		//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;
	bool GetJoypadPress(JOYKEY key);
	bool GetJoypadTrigger(JOYKEY key);
	WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

private:
	XINPUT_STATE m_joyKeyState;		//�W���C�p�b�h�̃v���X���
	XINPUT_STATE m_joyKeyStateTrigger;		//�g���K�[���
	XINPUT_VIBRATION m_JoypadMotor;				//�R���g���[���̃��[�^�[���			
};


#endif
