//=================================
// 
// UIクラス　ui.h
//outher kida ibuki 
// 
//==================================
#ifndef _UI_H_
#define _UI_H_

#include "pch.h"
#include "object2D.h"


class CUi :public CObject2D
{
public:
	CUi();
	~CUi()override;
	HRESULT Init() override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理
	static CUi* Create(D3DXVECTOR2 pos, int nType);
	static HRESULT Load();											//テクスチャのロード
	static void Unload();											//テクスチャのアンロード
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//テクスチャのテンプレート
	static int m_nFrameCnt;
	int m_nType;
	int m_nFrame;
};
#endif