//=================================
// 
// 階層構造モデルパーツ　modelparts.h
//outher kida ibuki 
// 
//==================================
#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_

#include "object.h"    // オブジェクト

#define MAX_PARTS (10)		//モデルパーツの最大数(モデルを変える時それに合わせたパーツ数で設定)
class CModelParts
{
public:
	CModelParts();    // コンストラクタ
	~CModelParts();   // デストラクタ
	HRESULT Init();   // 初期設定
	void Uninit();    // 終了処理
	void Update();    // 更新処理
	void Draw();      // 描画処理
	static CModelParts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int idx);   // 生成処理

	void SetPos(D3DXVECTOR3 pos, int idx);   // 位置設定
	void SetRot(D3DXVECTOR3 rot, int idx);   // 向き設定

	typedef struct
	{
		LPD3DXMESH pMesh;           // メッシュ
		LPD3DXBUFFER pBuffMat;      // バッファ
		DWORD dwNumMat;             // マトリックス
		D3DXMATRIX mtxWorld;		// ワールド変換行列
		D3DXVECTOR3 pos;            // 位置
		D3DXVECTOR3 rot;            // 向き
		int nIdxModelParent;	//親モデルのインデックス

		//**===========モデルのメッシュ情報取得=============**
		D3DXVECTOR3 m_vtxMinModel;		//モデルの頂点の最小値
		D3DXVECTOR3 m_vtxMaxModel;		//モデルの頂点の最大値
		int m_nNumVtx;					//頂点数
		DWORD m_sizeFVF;				//頂点フォーマットのサイズ
		BYTE* m_bpVtxBuff;				//頂点バッファへのポインタ
		D3DXVECTOR3 m_nMaxVtx;			//モデルの最大値
		D3DXVECTOR3 m_nMinVtx;			//モデルの最小値

		//D3DXMATRIX GetmtxWorld() { return mtxWorld; }

	}ModelParts;

	ModelParts aModel[MAX_PARTS];

	void SizeVtx();						// オブジェクトのサイズの最大最小を求める

	D3DXVECTOR3 m_size;			//サイズ

private:
	//モデルの構造体
	D3DXMATRIX GetWorldMatrix() { return m_mtxWorld; }  //ワールドマトリックスを取得(階層構造に必要)
	D3DXMATRIX m_mtxWorld;		//ワールド変換行列(親)

	//LPD3DXMESH m_pMesh;			    //メッシュへのポインタ

};
#endif