//=================================
// 
// 弾クラス　bullet.cpp
//outher kida ibuki 
// 
//==================================
#include "manager.h"    // マネージャー
#include "bullet.h"   // 弾
#include "effect.h"   // エフェクト
#include "explosion.h"  // 爆発

// 静的メンバ変数を初期化
LPDIRECT3DTEXTURE9 CBullet::m_pTextureTemp = {};
CTarget* CBullet::m_pTarget = nullptr;

const int CBullet::LIFE = 1500;

//==========================================
// コンストラクタ
//==========================================
CBullet::CBullet()
{
	m_dwLifeTime = timeGetTime();

	m_pos = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_homingStrength = 0.1f;
	m_nHitCnt = 0;
}
//==========================================
// デストラクタ
//==========================================
CBullet::~CBullet()
{
}
//==========================================
// 初期設定
//==========================================
HRESULT CBullet::Init()
{
	CBillboard::Init();

	SetType(CObject::TYPE::BULLET);
	SetBillboard(5.0f, 5.0f, 5.0f);
	SetSize(D3DXVECTOR3(4.0f, 4.0f, 0.0f));
	m_dwLifeTime = timeGetTime() + LIFE;


	return S_OK;

}
//==========================================
// 終了処理
//==========================================
void CBullet::Uninit()
{
	CBillboard::Uninit();
}
//==========================================
// 更新処理
//==========================================
void CBullet::Update()
{
	if (timeGetTime() >= m_dwLifeTime)
	{
		CBullet::m_bDeath = true;
	}

	CEffect::Create(m_pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 0, 5.0f, 1.0f, 0.0f, 10);



	//CollisionBullet();
	Collision();

	m_pos += m_move;
}
//==========================================
// 描画処理
//==========================================
void CBullet::Draw()
{
	CBillboard::Draw();

}
//==========================================
// 生成処理
//==========================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet* pBullet = new CBullet();
	pBullet->Init();
	pBullet->SetBullet(pos, move);
	pBullet->SetPos(pos);

	if (m_pTextureTemp != nullptr)
	{
		pBullet->BindTexture(m_pTextureTemp);
	}

	return pBullet;
}

//=======================================
//ロード
//=======================================
HRESULT CBullet::Load()
{
	CManager* pManager = CManager::GetInstance();

	//ポインタがnullなら
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込む
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\bullet000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//アンロード
//======================================
void CBullet::Unload()
{
	//テクスチャを使用していたら破棄
	if (m_pTextureTemp != nullptr)
	{
		//nullにする
		m_pTextureTemp = nullptr;
	}
}
//======================================
// 弾の設定
//======================================
void CBullet::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}

//=======================================
//当たり判定(OBB)
//=======================================
#if 0
bool CBullet::CollisionBullet()
{
	CManager* pManager = CManager::GetInstance();

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];
		// 最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();
			if (type == CObject::TYPE::ENEMY_X)
			{
				CEnemyX* pEnemy = (CEnemyX*)pObj; //ダウンキャスト
				D3DXVECTOR3 lengthOBB = pEnemy->m_pos - this->m_pos;  // 距離のベクトルを求める

				D3DXVECTOR3 AxisBulletX, AxisBulletY;   // 弾のx,y方向ベクトル
				D3DXVECTOR3 AxisNBulletX, AxisNBulletY;   // 弾のx,y方向法線ベクトル
				AxisBulletX.x = m_size.x * cosf(m_rot.z);
				AxisBulletX.y = m_size.x * sinf(m_rot.z);
				AxisBulletX.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletX, &AxisBulletX);   // 法線ベクトルを正規化

				AxisBulletY.x = m_size.y * sinf(m_rot.z);
				AxisBulletY.y = m_size.y * cosf(m_rot.z);
				AxisBulletY.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletY, &AxisBulletY);   // 法線ベクトルを正規化

				D3DXVECTOR3 AxisEnemyX, AxisEnemyY;   // 敵のx,y方向ベクトル
				D3DXVECTOR3 AxisNEnemyX, AxisNEnemyY;   // 敵のx,y方向法線ベクトル
				AxisEnemyX.x = pEnemy->m_size.x * cosf(pEnemy->m_rot.z);
				AxisEnemyX.y = pEnemy->m_size.x * sinf(pEnemy->m_rot.z);
				AxisEnemyX.z = 0.0f;
				D3DXVec3Normalize(&AxisNEnemyX, &AxisEnemyX);   // 法線ベクトルを正規化

				AxisEnemyY.x = pEnemy->m_size.y * sinf(pEnemy->m_rot.z);
				AxisEnemyY.y = pEnemy->m_size.y * cosf(pEnemy->m_rot.z);
				AxisEnemyY.z = 0.0f;
				D3DXVec3Normalize(&AxisNEnemyY, &AxisEnemyY);  // 法線ベクトルを正規化

				float rBullet, rEnemy, fLength;  // 計算用変数

				// 分離軸 : AxisPlayerX
				rBullet = D3DXVec3Length(&AxisBulletX);   // 分離軸の長さ
				rEnemy = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyY)); // 敵側の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletX)); // 軸に対しての長さ
				if (fLength > rBullet + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisPlayerY
				rBullet = D3DXVec3Length(&AxisBulletY);   // 分離軸の長さ
				rEnemy = fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyY)); // 敵側の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletY)); // 軸に対しての長さ
				if (fLength > rBullet + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisBlockX
				rBullet = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyX)); // 敵側の長さ
				rEnemy = D3DXVec3Length(&AxisEnemyX);   // 分離軸の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyX)); // 軸に対しての長さ
				if (fLength > rBullet + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisBlockY
				rBullet = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyY)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyY)); // 敵側の長さ
				rEnemy = D3DXVec3Length(&AxisEnemyY);   // 分離軸の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyY)); // 軸に対しての長さ
				if (fLength > rBullet + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}

				if (fabs(lengthOBB.z) < fabs(m_size.z - pEnemy->m_size.z))   // 二つの長さが距離より大きかったら
				{
					pEnemy->m_bDeath = true;
					CExplosion::Create(pEnemy->m_pos, D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));
					CBullet::DeathFlag();
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);

					return true;  // 衝突した
				}
			}
			if (type == CObject::TYPE::ENEMY_BOSS)
			{
				CEnemyBoss* pEnemy = (CEnemyBoss*)pObj; //ダウンキャスト
				D3DXVECTOR3 lengthOBB = pEnemy->m_pos - this->m_pos;  // 距離のベクトルを求める

				D3DXVECTOR3 AxisBulletX, AxisBulletY;   // 弾のx,y方向ベクトル
				D3DXVECTOR3 AxisNBulletX, AxisNBulletY;   // 弾のx,y方向法線ベクトル
				AxisBulletX.x = m_size.x * cosf(m_rot.z);
				AxisBulletX.y = m_size.x * sinf(m_rot.z);
				AxisBulletX.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletX, &AxisBulletX);   // 法線ベクトルを正規化

				AxisBulletY.x = m_size.y * sinf(m_rot.z);
				AxisBulletY.y = m_size.y * cosf(m_rot.z);
				AxisBulletY.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletY, &AxisBulletY);   // 法線ベクトルを正規化

				D3DXVECTOR3 AxisEnemyX, AxisEnemyY;   // 敵のx,y方向ベクトル
				D3DXVECTOR3 AxisNEnemyX, AxisNEnemyY;   // 敵のx,y方向法線ベクトル
				AxisEnemyX.x = pEnemy->m_size.x * cosf(pEnemy->m_rot.z);
				AxisEnemyX.y = pEnemy->m_size.x * sinf(pEnemy->m_rot.z);
				AxisEnemyX.z = 0.0f;
				D3DXVec3Normalize(&AxisNEnemyX, &AxisEnemyX);   // 法線ベクトルを正規化

				AxisEnemyY.x = pEnemy->m_size.y * sinf(pEnemy->m_rot.z);
				AxisEnemyY.y = pEnemy->m_size.y * cosf(pEnemy->m_rot.z);
				AxisEnemyY.z = 0.0f;
				D3DXVec3Normalize(&AxisNEnemyY, &AxisEnemyY);  // 法線ベクトルを正規化

				float rBullet, rEnemy, fLength;  // 計算用変数

				// 分離軸 : AxisPlayerX
				rBullet = D3DXVec3Length(&AxisBulletX);   // 分離軸の長さ
				rEnemy = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyY)); // 敵側の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletX)); // 軸に対しての長さ
				if (fLength > rBullet + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisPlayerY
				rBullet = D3DXVec3Length(&AxisBulletY);   // 分離軸の長さ
				rEnemy = fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyY)); // 敵側の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletY)); // 軸に対しての長さ
				if (fLength > rBullet + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisBlockX
				rBullet = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyX)); // 敵側の長さ
				rEnemy = D3DXVec3Length(&AxisEnemyX);   // 分離軸の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyX)); // 軸に対しての長さ
				if (fLength > rBullet + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisBlockY
				rBullet = fabs(D3DXVec3Dot(&AxisBulletX, &AxisEnemyY)) + fabs(D3DXVec3Dot(&AxisBulletY, &AxisEnemyY)); // 敵側の長さ
				rEnemy = D3DXVec3Length(&AxisEnemyY);   // 分離軸の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyY)); // 軸に対しての長さ
				if (fLength > rBullet + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}

				if (fabs(lengthOBB.z) < fabs(m_size.z - pEnemy->m_size.z + 150.0f))  // 二つの長さが距離より大きかったら
				{
					pEnemy->DamageEnemy(10);
					CBullet::DeathFlag();
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);

					return true;  // 衝突した
				}
			}

			pObj = pNext;
		}
	}
	return false;
}
#endif
void CBullet::Collision()
{
	CManager* pManager = CManager::GetInstance();

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
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z - 50.0f);  // 敵の中心点とサイズ
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // 弾の中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					pEnemy->m_bDeath = true;
					CExplosion::Create(pEnemy->m_pos, D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));
					CBullet::DeathFlag();
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);
				}
				else
				{// 当たってないとき
				}

			}
			if (type == CObject::TYPE::ENEMY_BOSS)
			{
				CEnemyBoss* pEnemy = (CEnemyBoss*)pObj; //ダウンキャスト
				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z + 150.0f), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // 敵の中心点とサイズ
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // 弾の中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					pEnemy->DamageEnemy(10);
					CBullet::DeathFlag();
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);
				}
				else
				{// 当たってないとき
				}

			}
			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}


}

//==========================================
// コンストラクタ
//==========================================
CBulletEnemy::CBulletEnemy()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
}
//==========================================
// デストラクタ
//==========================================
CBulletEnemy::~CBulletEnemy()
{
}
//==========================================
// 初期設定
//==========================================
HRESULT CBulletEnemy::Init()
{
	CBillboard::Init();

	SetType(CObject::TYPE::ENEMY_BULLET);
	SetBillboard(5.0f, 5.0f, 5.0f);
	SetSize(D3DXVECTOR3(10.0f, 10.0f, 10.0f));

	m_dwLifeTime = timeGetTime() + LIFE;


	return S_OK;

}
//==========================================
// 終了処理
//==========================================
void CBulletEnemy::Uninit()
{
	CBillboard::Uninit();
}
//==========================================
// 更新処理
//==========================================
void CBulletEnemy::Update()
{

	if (timeGetTime() >= m_dwLifeTime)
	{
		CBullet::m_bDeath = true;
	}

	CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0, 5.0f, 1.0f, 0.0f, 10);

	m_pos += m_move;
}
//==========================================
// 描画処理
//==========================================
void CBulletEnemy::Draw()
{
	CBillboard::Draw();

}
//==========================================
// 生成処理
//==========================================
CBulletEnemy* CBulletEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBulletEnemy* pBullet = new CBulletEnemy();
	pBullet->Init();
	pBullet->SetBullet(pos, move);
	pBullet->SetPos(pos);

	if (m_pTextureTemp != nullptr)
	{
		pBullet->BindTexture(m_pTextureTemp);
	}

	return pBullet;
}
//=======================================
//ロード
//=======================================
HRESULT CBulletEnemy::Load()
{
	CManager* pManager = CManager::GetInstance();

	//ポインタがnullなら
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込む
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\bullet000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//アンロード
//======================================
void CBulletEnemy::Unload()
{
	//テクスチャを使用していたら破棄
	if (m_pTextureTemp != nullptr)
	{
		//nullにする
		m_pTextureTemp = nullptr;
	}
}
//======================================
// 弾の設定
//======================================
void CBulletEnemy::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}

