//================================
//
//xファイルでブロック(blockX.h)
//outher kida ibuki
//================================
#ifndef _BLOCKX_H_
#define _BLOCKX_H_

#include "objectX.h"
#include "object.h"

//ブロックのクラス定義
class CBlockX : public CObjectX
{
public:
	CBlockX();																				//コンストラクタ
	~CBlockX();																		//デストラクタ
	HRESULT Init();																//初期設定
	void Uninit();																	//終了処理
	void Update();																	//更新処理
	void Draw();																	//描画処理
	static CBlockX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat);					//ブロックの生成
protected:

private:
};
#endif
