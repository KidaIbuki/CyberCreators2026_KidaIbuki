//==============================================
// 
// 3Dのプレイヤー　playerX.h
//outher kida ibuki 
// 
//==============================================
#ifndef _PLAYERX_H_
#define _PLAYERX_H_

#include "pch.h"
#include "main.h"
#include "objectX.h"
#include "object.h"


class CBlockX;//前方宣言

//マクロ定義
#define MAX_KEYSET (20) //キーの最大数
#define MODEL_PARTS (14) //モデルの数
#define MAX_MOTION (7) //モーションの数

class CPlayerX :public CObjectX
{
public:
	enum PLAYERSTATE
	{
		PLAYERSTATE_NONE = 0,
		PLAYERSTATE_DAMAGE,
		PLAYERSTATE_MAX,
	};
	enum JUMPSTATE
	{
		JUMPSTATE_NONE = 0,//地面にいる時
		JUMPSTATE_JUMP,    //空中にいる時
		JUMPSTATE_MAX
	};

	CPlayerX();
	~CPlayerX()override;
	HRESULT Init() override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理

	static CPlayerX* Create(D3DXVECTOR3 pos, int nType);
	void Collision();
	bool CollisionBlock(CBlockX* pBlockX);	// 当たり判定
	D3DXVECTOR3 PlayerMove();		//オブジェクト(仮プレイヤー)の移動処設定

		//**=================c++版マクロ====================**
	static const float HALF2;				//3.14の半分の２等分
	static const float HALF1;				//3.14の半分の３等分
	static const float HALF;				//上の半分
	static const float MOVE_SPEED;			//移動の速度

	int GetLifePlayer() { return m_nLife; }
	void HItPlayer(int nDamage);

private:

	D3DXVECTOR3 m_posOld;						//プレイヤーの前回の位置
	int m_nLife;

	//**=========ジャンプ用===========**
	bool m_bJumpCnt;
	int m_nTime;
	int m_nFrameJumpCnt;
	int m_nFrameJumpCnt1;

	PLAYERSTATE m_state;
	JUMPSTATE m_JumpState;
	int m_nFrameCnt;
	int m_nFrame;
};

#endif
