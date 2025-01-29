//=================================
// 
//フィールド　field.h
//outher kida ibuki 
// 
//==================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "object3D.h"

#define MAX_FIELD (1) //地面の最大数

//フィールドクラスの定義
class CField :public CObject3D
{
public:
	CField();					//コンストラクタ
	~CField() override;			//デストラクタ
	HRESULT Init() override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理
	static CField* Create(D3DXVECTOR3 pos);    //生成処理
	static HRESULT Load();													//テクスチャのロード
	static void Unload();													//テクスチャのアンロード

private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//テクスチャのテンプレート

};

#endif