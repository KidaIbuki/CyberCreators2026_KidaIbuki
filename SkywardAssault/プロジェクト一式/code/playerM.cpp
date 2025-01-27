//=================================
// 
// 階層構造player　playerM.h
//outher kida ibuki 
// 
//==================================
#include "manager.h"     // マネージャー
#include "playerM.h"   // プレイヤー
#include "bullet.h"    // 弾
#include "target.h"    // レティクル
#include "blockX.h"    // ブロック
#include "marker.h"    // マーカー
#include "ui.h"        // UI
#include "obb.h"
#include "effect.h"
#include "ray.h"

bool CPlayerM::m_bMove = false;

const float CPlayerM::HALF2 = 0.75f;
const float CPlayerM::HALF1 = 0.5f;
const float CPlayerM::HALF = 0.25f;

const float CPlayerM::MOVE_SPEED = 0.25f;

const int CPlayerM::OVER = 190;   // 左右
const int CPlayerM::OVER_UP = 200;  // 上
const int CPlayerM::OVER_DOWN = 100;  // 下
const int CPlayerM::FRAMECNT = 40;   // フレームのカウント(弾の発射間隔を変えれる)

//===============================
// コンストラクタ
//===============================
CPlayerM::CPlayerM()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_rotMove = { 0.0f,0.0f,0.0f };
	m_type = BULLET_NONE;
	m_state = STATE_NONE;
	m_nFrameCnt = FRAMECNT;
}
//===============================
// デストラクタ
//===============================
CPlayerM::~CPlayerM()
{

}
//===============================
// 初期設定
//===============================
HRESULT CPlayerM::Init()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// デバイスを取得

	// モデルパーツの生成
	m_pModel = CModelParts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 0);   // モデルの最初の位置を決める

	// 親モデルパーツの設定
	m_pModel->aModel[0].nIdxModelParent = -1;

	SetType(CObject::TYPE::PLAYER_M);

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CPlayerM::Uninit()
{
}
//===============================
// 更新処理
//===============================
void CPlayerM::Update()
{
	CManager* pManager = CManager::GetInstance();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //コントローラー取得
	CInputMouse* pMouse = pManager->GetMouse();    //コントローラー取得

	// モデルに操作を付ける

	if (m_bMove == true)
	{
		// 移動量の更新
		m_move += PlayerMove();
		// posを動かす
		m_pos += m_move;

		// rotを動かす
		m_rot += m_rotMove;

		//奥に動かす。
		m_pos.z += 4.0f;

		CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 10.0f, m_pos.z), D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f), 0, 5.0f, 1.0f, 0.0f, 5);

	}
	//移動量を減衰
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;

	//回転を減衰
	m_rotMove.x += (0.0f - m_rotMove.x) * 0.1f;
	m_rotMove.z += (0.0f - m_rotMove.z) * 0.1f;
	m_rotMove.y += (0.0f - m_rotMove.y) * 0.1f;
	// 回転の制限
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z -= D3DX_PI * 2;
	}
	else if (m_rot.z < -D3DX_PI)
	{
		m_rot.z += D3DX_PI * 2;
	}

	bool bSwitch = pManager->GetSwitching();   // ホーミングと通常弾の切り替え

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
			if (type == CObject::TYPE::TARGET)
			{
				CTarget* pTarget = (CTarget*)pObj; //ダウンキャスト
				if (pTarget != nullptr)
				{
					D3DXVECTOR3 targetPos = pTarget->GetPos();
					if (m_bMove == true)
					{
						//if (bSwitch == false)
						//{// 照準の範囲外だったら通常弾
							if (m_type == BULLET_NONE)
							{

								if (pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_A) || pMouse->GetTrigger(pMouse->MOUSEBUTTON_LEFT))
								{
									// サウンドを流す
									pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT);

									D3DXVECTOR3 bulletAngle;

									//======================ベクトルを使ってレティクルに弾を飛ばす===============================================
									bulletAngle = D3DXVECTOR3(targetPos.x * 0.5f, targetPos.y * 0.5f, targetPos.z) - D3DXVECTOR3(m_pos.x * 0.5f, m_pos.y * 0.5f, m_pos.z);  // 弾の位置からレティクルのベクトルを求める
									D3DXVec3Normalize(&bulletAngle, &bulletAngle);   // 長さが1になる

									CBullet::Create(m_pos, bulletAngle * 10.0f);
									// MEMO targetのposがずれているか、bulletのmoveがおかしいか
									// xとyの値が倍になってる
									m_type = BULLET_SHOT;

								}
							}
							// 連射防止するためのやつ
							else if (m_type == BULLET_SHOT)
							{
								m_nFrameCnt--;
								if (m_nFrameCnt <= 0)
								{
									m_type = BULLET_NONE;
									m_nFrameCnt = FRAMECNT;
								}
							}

						//}

					}
				}
			}
			//if (type == CObject::TYPE::ENEMY_X)
			//{
			//	CEnemyX* pEnemy = (CEnemyX*)pObj; //ダウンキャスト

			//	D3DXVECTOR3 enemyPos = pEnemy->GetPos();

			//	if (m_bMove == true)
			//	{
			//		if (bSwitch == true)
			//		{// 照準の範囲内に入ったらホーミング

			//			if (m_type == BULLET_NONE)
			//			{

			//				if (pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_A) || pMouse->GetTrigger(pMouse->MOUSEBUTTON_RIGHT))
			//				{
			//					// サウンドを流す
			//					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT);

			//					D3DXVECTOR3 HomingAngle, position;
			//					HomingAngle = D3DXVECTOR3(enemyPos.x * 0.5f, enemyPos.y * 0.5f, enemyPos.z) - D3DXVECTOR3(m_pos.x * 0.5f, m_pos.y * 0.5f, m_pos.z);  // 弾の位置からレティクルのベクトルを求める
			//					D3DXVec3Normalize(&HomingAngle, &HomingAngle);    // ベクトルを正規化
			//					position = enemyPos - m_pos;   // 敵とプレイヤーのベクトルを求める
			//					D3DXVec3Normalize(&position, &position);    // ベクトルを正規化

			//					// 敵より後ろに行ったら弾は撃たない
			//					//if (D3DXVec3Length(&position) >= 400)   // 敵から一定距離離れていたら以下の処理をしない(弾を飛ばさない)
			//					//{
			//					//}
			//						CBullet::Create(m_pos, position * 10.0f);


			//					m_type = BULLET_SHOT;



			//				}
			//			}
			//			// 連射防止するためのやつ
			//			else if (m_type == BULLET_SHOT)
			//			{
			//				m_nFrameCnt--;
			//				if (m_nFrameCnt <= 0)
			//				{
			//					m_type = BULLET_NONE;
			//					m_nFrameCnt = FRAMECNT;
			//				}
			//			}

			//		}
			//	}


			//}
			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}


	Collision();  // プレイヤー関係の当たり判定
	// ========================画面外に出ないようにする=================================
	// 左
	if (m_pos.x < -OVER)
	{
		m_pos.x = -OVER;
	}
	//右
	if (m_pos.x > OVER)
	{
		m_pos.x = OVER;
	}
	//下
	if (m_pos.y < -OVER_DOWN)
	{
		m_pos.y = -OVER_DOWN;
	}
	// 上
	if (m_pos.y > OVER_UP)
	{
		m_pos.y = OVER_UP;
	}

}
//===================================
// プレイヤーの移動処理
//===================================
D3DXVECTOR3 CPlayerM::PlayerMove()
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();	//キーボード取得
	CInputJoypad* pJoypad = pManager->GetJoypad();    //コントローラー取得

	D3DXVECTOR3 move = { 0,0,0 };

	//**========カメラの情報==========**
	CCamera* pCamera = pManager->GetCamera();  //カメラの取得
	D3DXVECTOR3 rot = pCamera->GetRot();	//向き

	// ボス戦前の範囲内だったら
	if (m_pos.z >= 0.0f && m_pos.z <= POSITION1)
	{
		if (pKeyboard->GetPress(DIK_D) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
		{//Aキーが押された場合
			if (pKeyboard->GetPress(DIK_D) && pKeyboard->GetPress(DIK_W) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
			{
				move.x -= sinf(rot.y - D3DX_PI * HALF2) * MOVE_SPEED;
				move.y -= cosf(rot.y - D3DX_PI * HALF2) * MOVE_SPEED;
				//m_rot.y = D3DX_PI * -HALF2 - rot.y;
			}
			else if (pKeyboard->GetPress(DIK_D) && pKeyboard->GetPress(DIK_S) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
			{
				move.x -= sinf(rot.y - D3DX_PI * HALF) * MOVE_SPEED;
				move.y -= cosf(rot.y - D3DX_PI * HALF) * MOVE_SPEED;
			}
			else
			{
				move.x -= sinf(rot.y - D3DX_PI * HALF1) * MOVE_SPEED;
				move.y -= cosf(rot.y - D3DX_PI * HALF1) * MOVE_SPEED;
			}

		}
		else if (pKeyboard->GetPress(DIK_A) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT))
		{//Dキーが押された場合

			if (pKeyboard->GetPress(DIK_A) && pKeyboard->GetPress(DIK_W) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
			{
				move.x -= sinf(rot.y + D3DX_PI * HALF2) * MOVE_SPEED;
				move.y -= cosf(rot.y + D3DX_PI * HALF2) * MOVE_SPEED;

			}
			else if (pKeyboard->GetPress(DIK_A) && pKeyboard->GetPress(DIK_S) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
			{
				move.x -= sinf(rot.y + D3DX_PI * HALF) * MOVE_SPEED;
				move.y -= cosf(rot.y + D3DX_PI * HALF) * MOVE_SPEED;
			}
			else
			{
				move.x -= sinf(rot.y + D3DX_PI * HALF1) * MOVE_SPEED;
				move.y -= cosf(rot.y + D3DX_PI * HALF1) * MOVE_SPEED;
			}
		}
		else if (pKeyboard->GetPress(DIK_W) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
		{//Wキーが押された場合
			{
				move.y += MOVE_SPEED;
			}
		}
		else if (pKeyboard->GetPress(DIK_S) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
		{//Sキーが押された場合
			{
				move.y -= MOVE_SPEED;

			}
		}
		if (pKeyboard->GetPress(DIK_E) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT_SHOULDER))
		{
			//m_rot.z = D3DX_PI * 0.5;
			m_rotMove.z += 0.005f;
		}
		else if (pKeyboard->GetPress(DIK_Q) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT_SHOULDER))
		{
			m_rotMove.z -= 0.005f;
		}
		else
		{
			m_rot.z += (0.0f - m_rot.z) * 0.05f;
		}
	}
	// ボス戦の範囲内だったら
	else if (m_pos.z >= POSITION1)
	{
		if (pKeyboard->GetPress(DIK_W) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
		{//Wキーが押された場合
			move.y += MOVE_SPEED;
		}
		if (pKeyboard->GetPress(DIK_S) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
		{//Sキーが押された場合
			move.y -= MOVE_SPEED;
		}

	}
#ifdef _DEBUG
	if (pKeyboard->GetPress(DIK_U))
	{
		move.z += 0.5;
	}
	if (pKeyboard->GetPress(DIK_J))
	{
		move.z -= 0.5;
	}

#endif

	return move;
}
//==============================================
// プレイヤーのx軸を元に戻す
//==============================================
void CPlayerM::ResetPlayer()
{
	m_pos.x = 0.0f;
	m_rot.z = 0.0f;
	m_rotMove.z = 0.0f;
}
//===============================================
// プレイヤーの当たり判定(有向境界ボックス)
//===============================================
#if 0
bool CPlayerM::CollisionPlayer()
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
			if (type == CObject::TYPE::BLOCK)
			{
				CBlockX* pBlock = (CBlockX*)pObj; //ダウンキャスト
				D3DXVECTOR3 lengthOBB = pBlock->m_pos - this->m_pos;  // 距離のベクトルを求める

				D3DXVECTOR3 AxisPlayerX, AxisPlayerY;   // プレイヤーのx,y方向ベクトル
				D3DXVECTOR3 AxisNPlayerX, AxisNPlayerY;   // プレイヤーのx,y方向法線ベクトル
				AxisPlayerX.x = m_size.x * cosf(m_rot.z);
				AxisPlayerX.y = m_size.x * sinf(m_rot.z);
				AxisPlayerX.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerX, &AxisPlayerX);   // 法線ベクトルを正規化

				AxisPlayerY.x = m_size.y * sinf(m_rot.z);
				AxisPlayerY.y = m_size.y * cosf(m_rot.z);
				AxisPlayerY.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerY, &AxisPlayerY);   // 法線ベクトルを正規化

				D3DXVECTOR3 AxisBlockX, AxisBlockY;   // ブロックのx,y方向ベクトル
				D3DXVECTOR3 AxisNBlockX, AxisNBlockY;   // ブロックのx,y方向法線ベクトル
				AxisBlockX.x = pBlock->m_size.x * cosf(pBlock->m_rot.z);
				AxisBlockX.y = pBlock->m_size.x * sinf(pBlock->m_rot.z);
				AxisBlockX.z = 0.0f;
				D3DXVec3Normalize(&AxisNBlockX, &AxisBlockX);   // 法線ベクトルを正規化

				AxisBlockY.x = pBlock->m_size.y * sinf(pBlock->m_rot.z);
				AxisBlockY.y = pBlock->m_size.y * cosf(pBlock->m_rot.z);
				AxisBlockY.z = 0.0f;
				D3DXVec3Normalize(&AxisNBlockY, &AxisBlockY);  // 法線ベクトルを正規化

				float rPlayer, rBlock, fLength;  // 計算用変数

				// 分離軸 : AxisPlayerX
				rPlayer = D3DXVec3Length(&AxisPlayerX);   // 分離軸の長さ
				rBlock = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBlockX)) + fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBlockY)); // ブロック側の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerX)); // 軸に対しての長さ
				if (fLength > rPlayer + rBlock)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisPlayerY
				rPlayer = D3DXVec3Length(&AxisPlayerY);   // 分離軸の長さ
				rBlock = fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBlockX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBlockY)); // ブロック側の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerY)); // 軸に対しての長さ
				if (fLength > rPlayer + rBlock)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisBlockX
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBlockX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBlockX)); // ブロック側の長さ
				rBlock = D3DXVec3Length(&AxisBlockX);   // 分離軸の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBlockX)); // 軸に対しての長さ
				if (fLength > rPlayer + rBlock)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisBlockY
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBlockY)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBlockY)); // ブロック側の長さ
				rBlock = D3DXVec3Length(&AxisBlockY);   // 分離軸の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBlockY)); // 軸に対しての長さ
				if (fLength > rPlayer + rBlock)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}

				if (fabs(lengthOBB.z) < fabs(m_size.z - pBlock->m_size.z))   // 二つの長さが距離より大きかったら
				{
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // 画面の揺れ
					CLife::SubLife(10);
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);

					return true;  // 衝突した
				}
			}
			if (type == CObject::TYPE::ENEMY_X)
			{
				CEnemyX* pEnemy = (CEnemyX*)pObj; //ダウンキャスト
				D3DXVECTOR3 lengthOBB = pEnemy->m_pos - this->m_pos;  // 距離のベクトルを求める

				D3DXVECTOR3 AxisPlayerX, AxisPlayerY;   // プレイヤーのx,y方向ベクトル
				D3DXVECTOR3 AxisNPlayerX, AxisNPlayerY;   // プレイヤーのx,y方向法線ベクトル
				AxisPlayerX.x = m_size.x * cosf(m_rot.z);
				AxisPlayerX.y = m_size.x * sinf(m_rot.z);
				AxisPlayerX.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerX, &AxisPlayerX);   // 法線ベクトルを正規化

				AxisPlayerY.x = m_size.y * sinf(m_rot.z);
				AxisPlayerY.y = m_size.y * cosf(m_rot.z);
				AxisPlayerY.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerY, &AxisPlayerY);   // 法線ベクトルを正規化

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

				float rPlayer, rEnemy, fLength;  // 計算用変数

				// 分離軸 : AxisPlayerX
				rPlayer = D3DXVec3Length(&AxisPlayerX);   // 分離軸の長さ
				rEnemy = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisPlayerX, &AxisEnemyY)); // 敵側の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerX)); // 軸に対しての長さ
				if (fLength > rPlayer + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisPlayerY
				rPlayer = D3DXVec3Length(&AxisPlayerY);   // 分離軸の長さ
				rEnemy = fabs(D3DXVec3Dot(&AxisPlayerY, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisEnemyY)); // 敵側の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerY)); // 軸に対しての長さ
				if (fLength > rPlayer + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisBlockX
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisEnemyX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisEnemyX)); // 敵側の長さ
				rEnemy = D3DXVec3Length(&AxisEnemyX);   // 分離軸の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyX)); // 軸に対しての長さ
				if (fLength > rPlayer + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisBlockY
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisEnemyY)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisEnemyY)); // 敵側の長さ
				rEnemy = D3DXVec3Length(&AxisEnemyY);   // 分離軸の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNEnemyY)); // 軸に対しての長さ
				if (fLength > rPlayer + rEnemy)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}

				if (fabs(lengthOBB.z) < fabs(m_size.z - pEnemy->m_size.z))   // 二つの長さが距離より大きかったら
				{
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // 画面の揺れ
					CLife::SubLife(10);
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
					return true;  // 衝突した
				}
			}
			if (type == CObject::TYPE::ENEMY_BULLET)
			{
				CBulletEnemy* pBullet = (CBulletEnemy*)pObj; //ダウンキャスト
				D3DXVECTOR3 lengthOBB = pBullet->m_pos - this->m_pos;  // 距離のベクトルを求める

				D3DXVECTOR3 AxisPlayerX, AxisPlayerY;   // プレイヤーのx,y方向ベクトル
				D3DXVECTOR3 AxisNPlayerX, AxisNPlayerY;   // プレイヤーのx,y方向法線ベクトル
				AxisPlayerX.x = m_size.x * cosf(m_rot.z);
				AxisPlayerX.y = m_size.x * sinf(m_rot.z);
				AxisPlayerX.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerX, &AxisPlayerX);   // 法線ベクトルを正規化

				AxisPlayerY.x = m_size.y * sinf(m_rot.z);
				AxisPlayerY.y = m_size.y * cosf(m_rot.z);
				AxisPlayerY.z = 0.0f;
				D3DXVec3Normalize(&AxisNPlayerY, &AxisPlayerY);   // 法線ベクトルを正規化

				D3DXVECTOR3 AxisBulletX, AxisBulletY;   // 敵の弾のx,y方向ベクトル
				D3DXVECTOR3 AxisNBulletX, AxisNBulletY;   // 敵の弾のx,y方向法線ベクトル
				AxisBulletX.x = pBullet->m_size.x * cosf(pBullet->m_rot.z);
				AxisBulletX.y = pBullet->m_size.x * sinf(pBullet->m_rot.z);
				AxisBulletX.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletX, &AxisBulletX);   // 法線ベクトルを正規化

				AxisBulletY.x = pBullet->m_size.y * sinf(pBullet->m_rot.z);
				AxisBulletY.y = pBullet->m_size.y * cosf(pBullet->m_rot.z);
				AxisBulletY.z = 0.0f;
				D3DXVec3Normalize(&AxisNBulletY, &AxisBulletY);  // 法線ベクトルを正規化

				float rPlayer, rBullet, fLength;  // 計算用変数

				// 分離軸 : AxisPlayerX
				rPlayer = D3DXVec3Length(&AxisPlayerX);   // 分離軸の長さ
				rBullet = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBulletX)) + fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBulletY)); // 敵の弾側の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerX)); // 軸に対しての長さ
				if (fLength > rPlayer + rBullet)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisPlayerY
				rPlayer = D3DXVec3Length(&AxisPlayerY);   // 分離軸の長さ
				rBullet = fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBulletX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBulletY)); // 敵の弾側の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNPlayerY)); // 軸に対しての長さ
				if (fLength > rPlayer + rBullet)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisBlockX
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBulletX)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBulletX)); // 敵の弾側の長さ
				rBullet = D3DXVec3Length(&AxisBulletX);   // 分離軸の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletX)); // 軸に対しての長さ
				if (fLength > rPlayer + rBullet)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}
				// 分離軸 : AxisBlockY
				rPlayer = fabs(D3DXVec3Dot(&AxisPlayerX, &AxisBulletY)) + fabs(D3DXVec3Dot(&AxisPlayerY, &AxisBulletY)); // 敵の弾側の長さ
				rBullet = D3DXVec3Length(&AxisBulletY);   // 分離軸の長さ
				fLength = fabs(D3DXVec3Dot(&lengthOBB, &AxisNBulletY)); // 軸に対しての長さ
				if (fLength > rPlayer + rBullet)   // 二つの長さが距離より小さかったら
				{
					pObj = pNext;
					continue; // 衝突していない
				}

				if (fabs(lengthOBB.z) < fabs(m_size.z - pBullet->m_size.z))   // 二つの長さが距離より大きかったら
				{
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // 画面の揺れ
					CLife::SubLife(10);
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
					return true;  // 衝突した
				}
			}

			pObj = pNext;
		}
	}
	return false;
}
#endif
void CPlayerM::Collision()
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
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // 敵の中心点とサイズ
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // 画面の揺れ
					CLife::SubLife(10);
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// 当たってないとき
				}

			}
			if (type == CObject::TYPE::BLOCK)
			{
				CBlockX* pBlock = (CBlockX*)pObj; //ダウンキャスト
				D3DXVECTOR3 blockPos = pBlock->GetPos();
				D3DXVECTOR3 blockSize = pBlock->GetSize();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(blockPos.x, blockPos.y, blockPos.z), halfWidths1(blockSize.x, blockSize.y, blockSize.z);  // ブロックの中心点とサイズ
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // 画面の揺れ
					CLife::SubLife(10);
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// 当たってないとき
				}

			}
			if (type == CObject::TYPE::ENEMY_BULLET)
			{
				CBulletEnemy* pBullet = (CBulletEnemy*)pObj; //ダウンキャスト
				D3DXVECTOR3 BulletPos = pBullet->GetPos();
				D3DXVECTOR3 BulletSize = pBullet->GetSize();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(BulletPos.x, BulletPos.y, BulletPos.z), halfWidths1(BulletSize.x, BulletSize.y, BulletSize.z);  // 敵の弾の中心点とサイズ
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					pManager->GetInstance()->GetCamera()->SetShake(30, 10);   // 画面の揺れ
					CLife::SubLife(10);
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// 当たってないとき
				}

			}

			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}


}
#if 0
void CPlayerM::LockOnEnemy()
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

				D3DXVECTOR3 m_position;
				bool m_isRockOn = false;
				// プレイヤーの向いている角度を計算
				float degreep = atan2f(m_pos.x, m_pos.z);
				// 計算で出た一番小さい角度を記憶
				float degreemum = D3DX_PI * 2;
				D3DXVECTOR3 pos = m_position - pEnemy->GetPos();
				// プレイヤーと敵の距離が一定外だったら処理をスキップ
				if (D3DXVec3Length(&pos) >= 500)
				{
					pObj = pNext; // オブジェクトのポインタを次に進める
					continue;
				}
				// プレイヤーと敵を結ぶベクトルを出す
				D3DXVECTOR3 pos2 = pEnemy->GetPos() - m_position;
				// 高さを0にする
				pos2.y = 0.0f;
				D3DXVec3Normalize(&pos2, &pos2);
				// プレイヤーと敵を結ぶベクトルの角度を計算
				float degree = atan2f(pos2.x, pos2.z);
				// プレイヤーの正面のベクトルの角度とプレイヤーと敵を結ぶベクトルの角度の差を計算
				if (D3DX_PI <= (degreep - degree))
				{
					degree = degreep - degree - D3DX_PI * 2;
				}
				else if (-D3DX_PI >= (degreep - degree))
				{
					degree = degreep - degree + D3DX_PI * 2;
				}
				else
				{
					degree = degreep - degree;
				}
				// 求めた角度にプレイヤーと敵の距離に応じて補正をかける
				degree = degree + degree * (D3DXVec3Length(&pos) / 500) * 0.3f;
				// 求めた値を比較して、一番小さい値を決める
				if (fabs(degreemum) >= fabs(degree))
				{
					degreemum = degree;
				}
				// 求めた一番小さい値が一定値より小さい場合ターゲットをオンにする
				if (fabs(degreemum) <= D3DX_PI / 3)
				{
					m_isRockOn = true;
				}
				// 逆に一定値より大きい場合ターゲットをオフにする
				else
				{
					m_isRockOn = false;
				}
			}
			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}

}
#endif
//===============================
// 描画処理
//===============================
void CPlayerM::Draw()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// デバイスを取得
	
	D3DXMATRIX mtxRot, mtxTrans;											// 計算用マトリックス


	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールド変換行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデルパーツの描画
	m_pModel->Draw();

}

//===============================
// 生成
//===============================
CPlayerM* CPlayerM::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayerM* pPlayer = new CPlayerM();
	pPlayer->Init();
	pPlayer->SetPos(pos);
	pPlayer->SetRot(rot);

	return pPlayer;
}
//===================================
// 位置の設定
//===================================
void CPlayerM::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//===================================
// 向きの設定
//===================================
void CPlayerM::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
