//=================================
// 
// タイトルクラス　title.h
//outher kida ibuki 
// 
//==================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "scene.h"
#include <string>

#define NUM_OBJECT_NUM (512)// 配置したいモデルの数

class CTitle:public CScene
{
public:
    CTitle();			//コンストラクタ
    ~CTitle()override;			//デストラクタ
    HRESULT Init()override;		//初期設定
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理
    void Draw()override;		//描画処理
     //・・・
    static HRESULT Load();							//テクスチャのロード
    static void Unload();							//テクスチャのアンロード
    static CTitle* Create();     //生成
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];

    void SetModel_File();

private:
    static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//テクスチャのテンプレート
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
    LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャ
};

#endif