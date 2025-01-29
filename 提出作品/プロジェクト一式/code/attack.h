//=================================
// 
// 攻撃処理クラス　attack.h
//outher kida ibuki 
// 
//==================================
#ifndef _ATTACK_H_
#define _ATTACK_H_

#include "objectX.h"
#include "enemyX.h"

class CAttack :public CObjectX
{
public:
	CAttack();							// コンストラクタ
	~CAttack() override;				// デストラクタ
	HRESULT Init() override;			// 初期設定
	void Uninit() override;				// 終了処理
	void Update() override;				// 更新処理
	void Draw() override;				// 描画処理
	static CAttack* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);           // 生成処理
	void Collision();

private:
	int m_nType;
	int m_nFramCnt;
	int m_nFrameCnt3;
	bool m_bTouch;
	int m_nDamage;
};

#endif