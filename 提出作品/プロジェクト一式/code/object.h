//=================================
// 
// オブジェクトクラス　object.h
//outher kida ibuki 
// 
//==================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"
#include "pch.h"

#define MAX_OBJ (1024)     // TODO : 配置オブジェクトの数たびに(マーカーやプレイヤー込み)増やす！8/23追記：敵の数も含む!

#define NUM_MAX_PRIORITY (6) // プライオリティの最大数


// TODO: undef して良いマクロか先生とか先輩に確認して！
//#ifdef GetObject
//#undef GetObject
//#endif

//全オブジェクトの基底クラス
class CObject
{
public:
	// オブジェクトの種類
	typedef enum
	{
		NONE = 0,	//無し
		PLAYER,		//プレイヤー
		ENEMY,		//敵
		BLOCK,		//箱
		CAMERA,     //カメラ
		SCENE,      //シーン
		PLAYER_X,   //3Dのプレイヤー
		MARKER,     //スタート＆ゴールマーカー
        ENEMY_X,    // 3Dの敵
		LIFE,       // ライフのUI
		ATTACK,     // 攻撃
		EXPLOSION,  // 爆発
		MAX
	}TYPE;

	CObject();		// コンストラクタ
	CObject(int nPriority);		// コンストラクタ オーバーライド

	virtual ~CObject();		// デストラクタ
	virtual HRESULT Init() = 0;		// 純粋仮想関数の初期設定
	virtual void Uninit() = 0;		// 純粋仮想関数の終了処理
	virtual void Update() = 0;		// 純粋仮想関数の更新処理
	virtual void Draw() = 0;		// 純粋仮想関数の描画処理
	static void ReleaseAll();		// 全オブジェクトの解放
	static void UpdateAll();		// 全オブジェクトの更新
	static void DrawAll();			// 全オブジェクトの描画
	static void DeathAll();         // 全オブジェクト破棄


	static CObject* GetObj(int nPriority);						// オブジェクト取得
	static void GetObj(CObject* pObject[NUM_MAX_PRIORITY]);						// オブジェクト取得

	TYPE GetType() { return m_type; }		// タイプ取得
	CObject* GetNext() { return m_pNext; }  // 次のオブジェクトを取得
	void SetType(TYPE type);				// タイプ設定

	void Release();					// 自分自身の解放
	bool m_bDeath;

	virtual void DeathFlag();
private:
	TYPE m_type;

	//==========リスト構造==============================================

	static CObject* m_pTop[NUM_MAX_PRIORITY];  // 先頭のオブジェクトのポインタ
	static CObject* m_pCur[NUM_MAX_PRIORITY];  // 現在(最後尾)のポインタ

	CObject* m_pPrev;  // 前のオブジェクトのポインタ
	CObject* m_pNext;  // 次のオブジェクトのポインタ

};

#endif
