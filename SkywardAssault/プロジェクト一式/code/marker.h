//==============================================
// 
// スタート、ゴールマーカー　marker.h
//outher kida ibuki 
// 
//==============================================
#ifndef _MARKER_H_
#define _MARKER_H_

#include "pch.h"   // プリコンパイル済みヘッダー
#include "main.h"  // メイン
#include "objectX.h"  // オブジェクトX
#include "playerM.h"   // プレイヤー

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
private:
	int m_nType;
	bool m_bTouch;
	bool m_bTouchNext1;
	bool m_bTouchNext2;
	bool m_bTouchNext3;
	bool m_bTouchNext4;
	bool m_bTouchNext5;
	bool m_bTouchNext6;

};

#endif
