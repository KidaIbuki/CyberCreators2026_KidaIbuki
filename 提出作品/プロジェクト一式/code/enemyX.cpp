//=================================
// 
// 敵クラス　enemyX.h
//outher kida ibuki 
// 
//==================================
#include "manager.h"
#include "enemyX.h"
#include "life.h"
#include "explosion.h"
int CEnemyX::m_nLife = 0;
int CEnemyX::m_nFrameCnt = 0;
bool CEnemyX::m_bDeath = {};

//==================================
// コンストラクタ
//==================================
CEnemyX::CEnemyX()
{
	// 敵の基本パラメーター
	m_move = { 0.0f,0.0f,0.0f };
	m_pos = { 0.0f,0.0f,0.0f };
	m_bMove = true;   // 動いているかどうかx軸
	m_bMove1 = true;   // y軸
	m_bTouch = false;
	m_fMoveStorage1 = 0.0f;
	m_fMoveStorage2 = 0.0f;
	m_fMoveStorage3 = 0.0f;
	m_fMoveStorage4 = 0.0f;

	m_fSpeedStorage = 0.0f;
	m_fSpeedStorage1 = 0.0f;
	m_nFrameCnt = 10;
	m_nDamageCnt = 5;
	m_nLife = 50;
	m_bDeath = false;
}
//==================================
// デストラクタ
//==================================
CEnemyX::~CEnemyX()
{
}
//==================================
// 初期設定
//==================================
HRESULT CEnemyX::Init()
{
	CObjectX::Init();

	SetType(CObject::TYPE::ENEMY_X);

	return S_OK;
}
//==================================
// 終了処理
//==================================
void CEnemyX::Uninit()
{
	CObjectX::Uninit();
}
//==================================
// 更新処理
//==================================
void CEnemyX::Update()
{
	// 敵の行動処理
    m_pos += m_move;

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;


	// 指定した座標の間を行き来する処理
	//x軸
	if (m_pos.x > m_fMoveStorage1)//奥
	{
		m_bMove = true;
	}
	else if (m_pos.x < m_fMoveStorage2)//手前
	{
		m_bMove = false;
	}
	if (m_bMove == true)
	{
		m_pos.x -= m_fSpeedStorage;
	}
	else if (m_bMove == false)
	{
		m_pos.x += m_fSpeedStorage;
	}

	//y軸
	if (m_pos.y > m_fMoveStorage3)//奥
	{
		m_bMove1 = true;
	}
	else if (m_pos.y < m_fMoveStorage4)//手前
	{
		m_bMove1 = false;
	}
	if (m_bMove1 == true)
	{
		m_pos.y -= m_fSpeedStorage1;
	}
	else if (m_bMove1 == false)
	{
		m_pos.y += m_fSpeedStorage1;
	}

	//移動量を減衰
	m_move.x += (0.0f - m_move.x) * 0.3f;
	m_move.y += (0.0f - m_move.y) * 0.3f;

	if (m_bDeath == true)
	{
		DeathFlag();
		CExplosion::Create(m_pos, D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));
		m_bDeath = false;
	}

}
//==================================
// 描画処理
//==================================
void CEnemyX::Draw()
{
	CObjectX::Draw();
}
//==================================
// 生成処理
//==================================
CEnemyX* CEnemyX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat,
	D3DXVECTOR3 movex1, D3DXVECTOR3 movex2, D3DXVECTOR3 movey1, D3DXVECTOR3 movey2, float fSpeed, float fSpeed1, int nLife, int nDamage)
{
	CEnemyX* pEnemyX = new CEnemyX();
	pEnemyX->SetPos(pos);
	pEnemyX->SetRot(rot);
	pEnemyX->SizeVtx();
	pEnemyX->m_pMesh = pMesh;
	pEnemyX->m_pBuffMat = pBuffMat;
	pEnemyX->m_dwNumMat = dwNumMat;
	pEnemyX->m_fMoveStorage1 = movex1.x;
	pEnemyX->m_fMoveStorage2 = movex2.x;
	pEnemyX->m_fMoveStorage3 = movey1.y;
	pEnemyX->m_fMoveStorage4 = movey2.y;

	pEnemyX->m_nLife = nLife;
	pEnemyX->m_nAttack = nDamage;
	//y軸も追加するかも...
	pEnemyX->m_fSpeedStorage = fSpeed;
	pEnemyX->m_fSpeedStorage1 = fSpeed1;


	pEnemyX->Init();
	return pEnemyX;
}
CEnemyX* CEnemyX::Create2(D3DXVECTOR3 pos)
{
	CEnemyX* pEnemyX2 = new CEnemyX;
	pEnemyX2->SetPos(pos);
	pEnemyX2->Init();
	pEnemyX2->SetModel("data/MODEL/out.x");


	return pEnemyX2;
}
//======================================
// 敵のライフ減算処理
//======================================
void CEnemyX::HitLife(int nDamage)
{
	CManager* pManager = CManager::GetInstance();

	if (m_nFrameCnt >= 0)  // 0より多かったら
	{
		m_nFrameCnt--;   // カウントダウン
	}
	if (m_nFrameCnt <= 0)
	{ // 座標を増やす
		pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ENEMY_DAMAGE);

		m_nLife -= nDamage;  // ライフを減らす
		m_nFrameCnt = 30;   // フレームを戻す
	}
	if (m_nLife <= 0)
	{// ライフが無くなったら
		m_bDeath = true;
	}

}
//======================================
// 敵のライフ減算処理
//======================================
void CEnemyX::HitLife2()
{
	CManager* pManager = CManager::GetInstance();

	m_nDamageCnt--;

	// サウンドを流す(プレイヤーのダメージ)
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ENEMY_DAMAGE);

	if (m_nDamageCnt <= 0)
	{
		DeathFlag();
	}

}
