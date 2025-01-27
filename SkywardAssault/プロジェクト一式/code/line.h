//=================================
// 
// ライン クラス　obb.h
//outher kida ibuki 
// 
//==================================
#ifndef _LINE_H_
#define _LINE_H_
#include "pch.h"
#include "object.h"

class CLine :public CObject
{
public:
	CLine();
	~CLine();
	HRESULT Init();     // 初期設定
	void Uninit();		// 終了処理
	void Update();      // 更新処理
	void Draw();        // 描画処理 
	void SetLine(const D3DXVECTOR3& start, const D3DXVECTOR3& end, D3DXCOLOR col);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			//各オブジェクトの位置設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			//各オブジェクトの向き設定

	static CLine* Create();
private:
	D3DXVECTOR3 m_start;
	D3DXVECTOR3 m_end;
	D3DXCOLOR m_col;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	D3DXMATRIX m_mtxWorld;						//ワールド変換行列
	D3DXVECTOR3 m_pos;							//位置
	D3DXVECTOR3 m_rot;							//向き

};
class Line
{
public:
	Line();
	~Line();
	void InitLine(LPDIRECT3DDEVICE9 pDevice);
	void CleanupLine();
	void DrawBox(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 min, D3DXVECTOR3 max);
private:
	ID3DXLine* m_pLine;
};

#endif
