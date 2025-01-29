//==============================================
// 
// スタート、ゴールマーカー　marker.h
//outher kida ibuki 
// 
//==============================================
#ifndef _MARKER_H_
#define _MARKER_H_

#include "pch.h"
#include "main.h"
#include "objectX.h"
#include "playerX.h"

class CMarker :public CObjectX
{
public:

	CMarker();
	~CMarker()override;
	HRESULT Init() override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理

	static CMarker* Create(D3DXVECTOR3 pos, int nType);			// type:スタート 0 /ゴール 1
	int GetType() { return m_nType; }
private:
	int m_nType;

};

#endif
