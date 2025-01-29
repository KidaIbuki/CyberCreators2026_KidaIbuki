//=================================
// 
//レンダラークラス(DirectX描画)renderer.h
//outher kida ibuki 
// 
//==================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include<windows.h>
#include "d3dx9.h"		//描画処理に必要

//レンダラークラスの定義
class CRenderer
{
public:
	CRenderer();		//コンストラクタ
	~CRenderer();		//デストラクタ
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	LPDIRECT3DDEVICE9 GetDevice();	//3Dデバイスの取得
private:
	LPDIRECT3D9 m_pD3D;		//Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;		//Direct3Dデバイス
};

#endif