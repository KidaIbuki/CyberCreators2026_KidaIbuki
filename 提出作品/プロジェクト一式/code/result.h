//=================================
// 
// リザルトクラス　result.h
//outher kida ibuki 
// 
//==================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "scene.h"
#include <string>
class CResult :public CScene
{
public:
    CResult();			//コンストラクタ
    ~CResult()override;			//デストラクタ
    HRESULT Init()override;		//初期設定
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理
    void Draw()override;		//描画処理
     //・・・
    static HRESULT Load();							//テクスチャのロード
    static void Unload();							//テクスチャのアンロード
    static CResult* Create();     //生成

private:
    static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//テクスチャのテンプレート
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
    LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャ
};

class CResultLose :public CResult
{
public:
    CResultLose();			//コンストラクタ
    ~CResultLose()override;			//デストラクタ
    HRESULT Init()override;		//初期設定
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理
    void Draw()override;		//描画処理
     //・・・
    static HRESULT Load();							//テクスチャのロード
    static void Unload();							//テクスチャのアンロード
    static CResultLose* Create();     //生成
private:
    static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//テクスチャのテンプレート
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
    LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャ

};

#endif