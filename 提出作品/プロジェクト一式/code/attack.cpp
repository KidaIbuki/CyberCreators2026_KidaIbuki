//=================================
// 
// 攻撃処理クラス　attack.h
//outher kida ibuki 
// 
//==================================
#include "attack.h"
#include "manager.h"
#include "playerX.h"
#include "obb.h"

//==================================
// コンストラクタ
//==================================
CAttack::CAttack()
{
	m_bTouch = false;
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_nDamage = 0;
	m_nFramCnt = 20;
	m_nFrameCnt3 = 30;
}

//==================================
// デストラクタ
//==================================
CAttack::~CAttack()
{
}

//==================================
// 初期設定
//==================================
HRESULT CAttack::Init()
{
	CObjectX::Init();
	SetType(CObject::TYPE::ATTACK);

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CAttack::Uninit()
{
	CObjectX::Uninit();
}

//==================================
// 更新処理
//==================================
void CAttack::Update()
{
	// 攻撃した後に、攻撃オブジェクトを消す
	m_nFramCnt--;
	if (m_nFramCnt <= 0)
	{
		Collision();
		DeathFlag();
		m_nFramCnt = 20;
	}

}

//==================================
// 描画処理
//==================================
void CAttack::Draw()
{
	CObjectX::Draw();
}

//==================================
// 生成処理
//==================================
CAttack* CAttack::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	CAttack* pAttack = new CAttack();
	pAttack->Init();
	pAttack->SetPos(pos);
	pAttack->SetRot(rot);

	if (nType == 0)
	{
		pAttack->SetModel("data/MODEL/ATTACK/attack_obj.x");
		pAttack->m_bTouch = true;
	}
	return pAttack;
}
//==================================
// 攻撃が敵に当たる処理
//==================================

void CAttack::Collision()
{

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];

		//種類の取得
		while (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();
			CObject* pNext = pObj->GetNext(); // 次のポインタを取得
			if (type == CObject::TYPE::ENEMY_X)
			{
				CEnemyX* pEnemy = (CEnemyX*)pObj; //ダウンキャスト
				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // 敵の中心点とサイズ
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // 攻撃の中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					pEnemy->HitLife2();
				}
				else
				{// 当たってないとき
				}

			}

			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}


}






