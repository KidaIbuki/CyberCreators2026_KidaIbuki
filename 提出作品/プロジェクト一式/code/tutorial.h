//=================================
// 
// チュートリアルクラス　gaem.h
//outher kida ibuki 
// 
//==================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "scene.h"
#include "camera.h"
#include "light.h"

#define NUM_OBJECT_NUM (512)// 配置したいモデルの数

#define POSITION_NUM_1 (0.0f)  // チュートリアル用テクスチャ1の表示位置
#define POSITION_NUM_2 (3.0f)  // チュートリアル用テクスチャ1の表示位置

#define POSITION_NUM_3 (100.0f)  // チュートリアル用テクスチャ2の表示位置
#define POSITION_NUM_4 (103.0f)  // チュートリアル用テクスチャ2の表示位置

#define POSITION_NUM_5 (200.0f)  // チュートリアル用テクスチャ3の表示位置
#define POSITION_NUM_6 (203.0f)  // チュートリアル用テクスチャ3の表示位置

class CTutorial :public CScene
{
public:
    CTutorial();			//コンストラクタ
    ~CTutorial()override;			//デストラクタ
    HRESULT Init()override;
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理
    void Draw()override;		//描画処理
     //・・・
    static CTutorial* Create();     //生成
    void SetModel_File_tutorial();
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];

private:
    int m_nFrame;

    // 現在のプレイヤーの位置にテクスチャを張る
    typedef enum
    {
        POSITION_NONE = 0,
        POSITION_1,
        POSITION_2,
        POSITION_3,
        POSITION_MAX
    }POSITION;

    POSITION m_Position;

};

#endif