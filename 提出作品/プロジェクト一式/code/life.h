//=================================
// 
// ライフUIクラス　life.h
//outher kida ibuki 
// 
//==================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "pch.h"
#include "object2D.h"

#define SCREEN_SPACE	(30/2)

class CLife :public CObject2D
{
public:

	CLife();
	~CLife()override;
	HRESULT Init() override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理
	static CLife* Create(D3DXVECTOR2 pos);
	static HRESULT Load();											//テクスチャのロード
	static void Unload();											//テクスチャのアンロード
	static void HitLife(int nDamage);
private:
	static float m_fTexHeight;
	static float m_fTexWidht;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//テクスチャのテンプレート
	static int m_nFrame;
	static int m_nLife;

};
#endif