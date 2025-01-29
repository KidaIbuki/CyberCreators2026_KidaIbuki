//=================================
// 
//ライトクラス　　light.h
//outher kida ibuki 
// 
//==================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

#define MAX_LIGHT (3) //ライトの数

//ライトのクラス定義
class CLight
{
public:
	CLight();		    //コンストラクタ
	~CLight();		    //デストラクタ
	HRESULT Init();     //初期設定
	void Uninit();		//終了処理
	void Update();      //更新処理
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];  //ライト構造体

};

#endif