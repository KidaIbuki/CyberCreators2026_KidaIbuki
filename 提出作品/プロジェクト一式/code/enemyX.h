//=================================
// 
// 敵クラス　enemyX.h
//outher kida ibuki 
// 
//==================================
#ifndef _ENEMYX_H_
#define _ENEMYX_H_


#include "pch.h"
#include "objectX.h"
#include "playerX.h"
// 通常の敵クラス
class CEnemyX :public CObjectX
{
public:
	CEnemyX();							// コンストラクタ
	~CEnemyX() override;				// デストラクタ
	HRESULT Init() override;			// 初期設定
	void Uninit() override;				// 終了処理
	void Update() override;				// 更新処理
	void Draw() override;				// 描画処理
	static CEnemyX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat,
		D3DXVECTOR3 movex1, D3DXVECTOR3 movex2, D3DXVECTOR3 movey1, D3DXVECTOR3 movey2, float fSpeed, float fSpeed1, int nLife, int nDamage);

	static CEnemyX* Create2(D3DXVECTOR3 pos);
	int GetLife() { return m_nLife; }  // ライフの取得
	static void HitLife(int nDamage);
	void HitLife2();

private:
	static int m_nLife;    // 敵のライフ
	int m_nAttack;  // 敵の攻撃力

	bool m_bMove;     // 動いているか否かx軸
	bool m_bMove1;     // 動いているか否かy軸
	bool m_bTouch;  // 触れているかどうか

	//移動量などを格納する変数
	float m_fMoveStorage1;
	float m_fMoveStorage2;
	float m_fMoveStorage3;
	float m_fMoveStorage4;

	float m_fSpeedStorage;	
    float m_fSpeedStorage1;

	static int m_nFrameCnt;

	int m_nDamageCnt;

	static bool m_bDeath;   // 死んだかどうか
};
#endif