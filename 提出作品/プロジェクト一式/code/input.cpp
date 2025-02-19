//＝＝＝＝＝＝＝＝＝＝＝＝＝
//
//入力処理（input.cpp)
//Author ibuki kida
// 
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "input.h"

//静的メンバ初期化
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//==============================
//コンストラクタ
//==============================
CInput::CInput()
{
	 m_pDevice = nullptr;
}
//===============================
//デストラクタ
//===============================
CInput::~CInput()
{

}

//===================================
//初期設定
//===================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{

	if (m_pInput == nullptr)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, nullptr)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}
//=================================
//終了処理(破棄)
//=================================
void CInput::Uninit()
{
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
	//DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}

}
//====================================================================
//キーボードの入力
//====================================================================

//==============================
//コンストラクタ
//==============================
CInputKeyboard::CInputKeyboard()
{

}
//===============================
//デストラクタ
//===============================
CInputKeyboard::~CInputKeyboard()
{

}
//===================================
//初期設定
//===================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの生成
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// 入力デバイス: キーボードの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;


}
//=================================
//終了処理(破棄)
//=================================
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}
//===================================
//更新処理
//===================================
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_KEY]; //キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //キーボードのトリガー情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire(); //キーボードへのアクセス権を獲得
	}

}
//===================================================================================
//コントローラーの処理
//===================================================================================

//==================================
//コンストラクタ
//==================================
CInputJoypad::CInputJoypad()
{
}
//==================================
//デストラクタ
//==================================
CInputJoypad::~CInputJoypad()
{
}
//==================================
//初期設定
//==================================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));

	//メモリのクリア
	memset(&m_JoypadMotor, 0, sizeof(XINPUT_VIBRATION));


	//XInputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}
//==================================
//終了処理
//==================================
void CInputJoypad::Uninit()
{
	//XInputのステートを設定(無効にする)
	XInputEnable(false);

}
//==================================
//更新処理
//==================================
void CInputJoypad::Update()
{
	XINPUT_STATE joykeyState;		//ジョイパッドの入力情報
	//int nCntJoykey;

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{

		//左スティックからの入力を方向ボタンに変換
		joykeyState.Gamepad.wButtons |= GetJoypadStick(m_joyKeyState.Gamepad.sThumbLX, m_joyKeyState.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

		//g_joyKeyStateTrigger[nCntJoykey] = (g_joyKeyState[nCntJoykey] ^ joykeyState[nCntJoykey]) & joykeyState[nCntJoykey];
		m_joyKeyStateTrigger.Gamepad.wButtons = (m_joyKeyState.Gamepad.wButtons ^ joykeyState.Gamepad.wButtons) & joykeyState.Gamepad.wButtons;

		m_joyKeyState = joykeyState;		//ジョイパッドのプレス情報を保存


	}

}
//==================================
//コントローラーの入力情報
//==================================
WORD CInputJoypad::GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	//上に
	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	//下に
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	//左
	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	//右
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}


	return wButtons;
}


//=====================================
//各入力情報取得
//=====================================

//==================================
//キーボードのプレス情報取得
//==================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) != 0;
}
//==================================
//キーボードのトリガー情報を取得
//==================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//==================================
//コントローラーのプレス情報
//==================================
bool CInputJoypad::GetJoypadPress(JOYKEY key)
{
	return (m_joyKeyState.Gamepad.wButtons & (0x01 << key)) != 0;
}
//==================================
//コントローラーのトリガー情報
//==================================
bool CInputJoypad::GetJoypadTrigger(JOYKEY key)
{
	return (m_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) != 0;
}
