//==============================================
// 
//オブジェクト(xファイルの読み込み)　objectX.h
//outher kida ibuki 
// 
//==============================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "object.h"
#include "pch.h"
#include "main.h"

#define MAX_CHAR (256)
#define NUM_MODEL (5) //モデルの種類

class CCamera;

//オブジェクトXクラスの定義
class CObjectX :public CObject
{
public:
	//**==================基本処理====================**
	CObjectX();		//コンストラクタ
	~CObjectX() override;		//デストラクタ
	HRESULT Init() override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理


	//**=================各生成の処理==================**
	static CObjectX* Create();		//オブジェクトの生成
	void SetModel(std::string sPath);		//モデルのセット
	void SizeVtx();						// オブジェクトのサイズの最大最小を求める
	//**===============各設定の取得======================**
	D3DXVECTOR3 GetPos() { return m_pos; }			//位置の取得
	D3DXVECTOR3 GetSize() { return m_size; }		//サイズの取得
	D3DXVECTOR3 GetRot() { return m_rot; }

	void SetPos(D3DXVECTOR3 pos);			//各オブジェクトの位置設定
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(float fWidth, float fHeight, float fDepth);	//各オブジェクトのサイズ設定

	D3DXMATRIX GetWorldMatrix() { return m_mtxWorld; }  //ワールドマトリックスを取得(階層構造に必要)

	D3DXVECTOR3 m_pos;							//位置
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_move;							//移動量
	D3DXVECTOR3 m_size;							//サイズ

protected:
	//**==============描画の情報=================**
	D3DXMATRIX m_mtxWorld;		//ワールド変換行列
	LPD3DXMESH m_pMesh;			//メッシュへのポインタ
	LPD3DXBUFFER m_pBuffMat;    //マテリアルへのポインタ
	DWORD m_dwNumMat;           //マテリアルの数

	//モデルファイルの読み込み構造体
	typedef struct
	{
		int nType;
		char cFile[MAX_CHAR];		//ファイルを読み込む
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		int nIndexFile;
		int Parent;			//パーツの親子関係
	}MODEL_FILENAME;

	MODEL_FILENAME m_gModelData[NUM_MODEL];

private:
	//**=============このオブジェクトXでしか使えない関数===============**


	//**==========メンバ変数================**
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャ


	//**===========モデルのメッシュ情報取得=============**
	D3DXVECTOR3 m_vtxMinModel;		//モデルの頂点の最小値
	D3DXVECTOR3 m_vtxMaxModel;		//モデルの頂点の最大値
	int m_nNumVtx;					//頂点数
	DWORD m_sizeFVF;				//頂点フォーマットのサイズ
	BYTE* m_bpVtxBuff;				//頂点バッファへのポインタ
	D3DXVECTOR3 m_nMaxVtx;					//モデルの最大値
	D3DXVECTOR3 m_nMinVtx;					//モデルの最小値



};
#endif
