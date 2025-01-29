//=================================
// 
// マネージャ　manager.h
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

// マネージャクラスの定義
class CManager
{
private:
	CManager();															//コンストラクタ
public:
	~CManager();														//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);			//初期設定
	void Uninit();														//終了処理
	void Update();														//更新処理
	void Draw();	                                                    //描画処理

	//シングルトン
	static CManager* GetInstance()
	{
		static CManager instance; // 静的インスタンス
		return &instance;
	}
	
	void SetSwitch(bool bSwitch) { m_bSwitch = bSwitch; }
	bool GetSwitch() { return m_bSwitch; }
	CRenderer* GetRenderer();									//レンダラーの取得
	CCamera* GetCamera();										//カメラの取得
	CLight* GetLight();											//ライトの取得
	CInputKeyboard* GetKeyboard();							    //キーボード入力の取得
	CInputJoypad* GetJoypad();							    //コントローラー入力の取得
	void SetMode(CScene::MODE mode);							//シーンの取得
	CScene* GetScene();
	CFade* GetFade();											//フェードの取得
	CSound* GetSound();                                         // サウンドの取得
private:
	CRenderer* m_pRenderer;				//レンダラー情報
	CCamera* m_pCamera;					//ビュー情報
	CLight* m_pLight;                   //ライト情報
	CInputKeyboard* m_pKeyboard;		//キーボード情報
	CInputJoypad* m_pKeyJoypad;		    //コントローラー情報
	CScene* m_pScene;					//シーン情報
	CFade* m_pFade;						//フェードの情報
	CScene::MODE m_mode;
	CSound* m_pSound;                   // サウンドの情報
	bool m_bSwitch;
};

#endif 
