//＝＝＝＝＝＝＝＝＝＝＝＝＝
//
//入力処理（input.h)
//Author ibuki kida
// 
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _INPUT_H_	//このマクロ定義がされてなかったら
#define _INPUT_H_	//二重インクルード防止のマクロ定義

#include "main.h"
#include "pch.h"
#include "dinput.h"						//入力処理に必要

#pragma comment(lib,"dinput8.lib")		//入力処理に必要
#pragma comment(lib,"xinput.lib")		//ジョイパッド処理に必要

#define MAX_KEY (256)


//入力基底クラス(DirectInputの管理)
class CInput
{
public:
	CInput();		//コンストラクタ
	virtual ~CInput();		//デストラクタ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;	//純粋仮想関数の更新処理

protected:
	//全入力処理で共有
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//キーボード入力(派生クラス)
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();		//コンストラクタ
	~CInputKeyboard() override;		//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;
	bool GetPress(int nKey);		//プレス状態取得
	bool GetTrigger(int nKey);		//トリガー状態取得

private:
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];
};
//パッド入力(派生クラス)↓
class CInputJoypad :public CInput
{
public:
	//キーの種類
	typedef enum
	{
		JOYKEY_UP = 0,			//十字キー(上)
		JOYKEY_DOWN,			//十字キー(下)
		JOYKEY_LEFT,			//十字キー(左)					この順番じゃないとキーがわからなくなる！
		JOYKEY_RIGHT,			//十字キー(右)
		JOYKEY_START,			//STARTボタン
		JOYKEY_BACK,			//BACKボタン
		JOYKEY_LEFT_THUMB,		//左スティック押し込み
		JOYKEY_RIGHT_THUMB,		//右スティック押し込み
		JOYKEY_LEFT_SHOULDER,	//LBボタン
		JOYKEY_RIGHT_SHOULDER,	//RBボタン
		JOYKEY_UNCOMN1,			//謎キー
		JOYKEY_UNCOMN2,
		JOYKEY_A,				//Aボタン
		JOYKEY_B,				//Bボタン
		JOYKEY_X,				//Xボタン
		JOYKEY_Y,				//Yボタン
		JOYKEY_MAX
	}JOYKEY;

	CInputJoypad();		//コンストラクタ
	~CInputJoypad() override;		//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;
	bool GetJoypadPress(JOYKEY key);
	bool GetJoypadTrigger(JOYKEY key);
	WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

private:
	XINPUT_STATE m_joyKeyState;		//ジョイパッドのプレス情報
	XINPUT_STATE m_joyKeyStateTrigger;		//トリガー情報
	XINPUT_VIBRATION m_JoypadMotor;				//コントローラのモーター情報			
};


#endif
