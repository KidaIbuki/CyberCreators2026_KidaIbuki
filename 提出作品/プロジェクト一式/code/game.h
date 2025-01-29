//=================================
// 
// ゲーム処理クラス　gaem.h
//outher kida ibuki 
// 
//==================================
#ifndef _GAME_H_
#define _GAME_H_
#include "scene.h"
#include "camera.h"
#include "light.h"

#define NUM_OBJECT_NUM (512)// 配置したいモデルの数
#define NUM_ENEMY (100)  // 配置したい敵の数

class CGame :public CScene
{
public:
    CGame();			//コンストラクタ
    ~CGame()override;			//デストラクタ
    HRESULT Init()override;
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理
    void Draw()override;		//描画処理
     //・・・
    static CGame* Create();     //生成
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];
    ENEMY_FILENAME g_aEnemyData[NUM_ENEMY];
    // ブロックの外部ファイル出力
    void SetModel_File();
    void SetModel_File2();
    void SetModel_File3();
    // 敵の外部ファイル出力
    void SetEnemy_File();
    void SetEnemy_File2();
    void SetEnemy_File3();

private:
    bool m_bPause;
};
class CGameSecond :public CGame
{
public:
    CGameSecond();
    ~CGameSecond();
    HRESULT Init()override;
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理
    void Draw()override;		//描画処理

    static CGameSecond* Create();
private:
    bool m_bPause2;
};

class CGameThird :public CGame
{
public:
    CGameThird();
    ~CGameThird();
    HRESULT Init()override;
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理
    void Draw()override;		//描画処理

    static CGameThird* Create();
private:
    bool m_bPause3;
};

#endif