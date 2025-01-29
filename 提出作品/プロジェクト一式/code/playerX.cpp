//==============================================
// 
// 3Dのプレイヤー　playerX.h
//outher kida ibuki 
// 
//==============================================
#include "playerX.h"
#include "marker.h"
#include "manager.h"
#include "blockX.h"
#include "life.h"
#include "attack.h"
#include "obb.h"
#include "tutorial.h"
#include "ui.h"
//定数(マクロ)の定義
const float CPlayerX::HALF2 = 1.0f;
const float CPlayerX::HALF1 = 2.0f;
//const float CPlayerX::HALF = 2.5f;

const float CPlayerX::MOVE_SPEED = 0.15f;


//====================================
// コンストラクタ
//====================================
CPlayerX::CPlayerX()
{
	m_pos = { 0.0f, 0.0f, 0.0f };		// 位置
	m_rot = { 0.0f, 0.0f, 0.0f };		// 向き
	//m_move = { 0.0f, 0.0f, 0.0f };		//移動量
	m_size = { 0.0f,0.0f,10.0f };

	m_posOld = { 0.0f,0.0f,0.0f };

	m_bJumpCnt = false;
	m_nTime = 0;  //1秒くらいかな

	m_nLife = 100;

	m_nFrameCnt = 1;
	m_nFrameJumpCnt = 40;
	m_nFrameJumpCnt1 = 30;
	m_nFrame = 1;
	m_JumpState = JUMPSTATE_NONE;
}
//====================================
// デストラクタ
//====================================
CPlayerX::~CPlayerX()
{
}
//====================================
// 初期設定
//====================================
HRESULT CPlayerX::Init()
{
	CObjectX::Init();

	SetType(CObject::TYPE::PLAYER_X);

	return S_OK;
}
//====================================
// 終了処理
//====================================
void CPlayerX::Uninit()
{
	CObjectX::Uninit();

}
//====================================
// 更新処理
//====================================
void CPlayerX::Update()
{
	CObjectX::Update();

	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();	//キーボード取得
	CInputJoypad* pJoypad = pManager->GetJoypad();    //コントローラー取得

	m_posOld = m_pos;

	//移動量の更新
	m_move += PlayerMove();

	//posを動かす
	m_pos += m_move;

	//重力
#if 1
	m_move.y -= 0.3f;
	m_pos.y += m_move.y;

	//無限ジャンプ防止済みジャンプ
	if (m_JumpState == JUMPSTATE_NONE)
	{// ステートがノーマル(何もしていない状態)の時
		if (pKeyboard->GetTrigger(DIK_SPACE) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_A))
		{
			m_move.y += 10.0f;//ジャンプ力(※ここでこれ以上にあげるとめっちゃ飛ぶ)

			m_JumpState = JUMPSTATE_JUMP;// ステートをジャンプ状態にする

			// サウンドを流す
			pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_JUMP);

		}
	}
	// ジャンプ状態の時
	else if (m_JumpState == JUMPSTATE_JUMP)
	{
		m_nFrameJumpCnt--;  // カウントフレームを減算する
		if (m_nFrameJumpCnt <= 0) // フレームが0になったら
		{
			m_move.y = 0.0f; // ジャンプ値を0にする
			m_JumpState = JUMPSTATE_NONE; // ステートを元に戻す
			m_nFrameJumpCnt = 40; // フレームをもとに戻す
		}
	}

	//地面より下に行けないようにする
	if (m_pos.y <= 0.0f)
	{
		m_pos.y = 0.0f;
		m_move.y = 0.0f;
	}
	Collision();
	//CollisionPlayer();
#endif
	//移動量を減衰
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;

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
			if (type == CObject::TYPE::BLOCK)
			{
				CBlockX* pBlockX = (CBlockX*)pObj; //ダウンキャスト
				if (pBlockX != nullptr)
				{
					//当たり判定
					if (CollisionBlock(pBlockX))
					{ //接触しているとき

						return;
					}
				}

			}
			if (type == CObject::TYPE::PLAYER_X)
			{
				CPlayerX* pPlayer = (CPlayerX*)pObj; //ダウンキャスト
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 playerPos = pPlayer->GetPos(); // プレイヤーの位置を取得
					D3DXVECTOR3 playerRot = pPlayer->GetRot();
					if (pKeyboard->GetTrigger(DIK_RIGHT) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_B))
					{
						// サウンドを流す
						pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

						CAttack::Create(D3DXVECTOR3(playerPos.x + 40.0f, playerPos.y + 10.0f, playerPos.z), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f), 0);

					}
					if (pKeyboard->GetTrigger(DIK_LEFT) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_X))
					{
						// サウンドを流す
						pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

						CAttack::Create(D3DXVECTOR3(playerPos.x - 40.0f, playerPos.y + 10.0f, playerPos.z), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * -0.5f), 0);

					}
					

				}

			}
			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}

}
//==================================================
//移動設定
//==================================================
D3DXVECTOR3 CPlayerX::PlayerMove()
{
	CManager* pManager = CManager::GetInstance();  //マネージャーのインスタンス取得

	CInputKeyboard* pKeyboard = pManager->GetKeyboard();    //キーボード取得
	CInputJoypad* pJoypad = pManager->GetJoypad();    //キーボード取得

	D3DXVECTOR3 move = { 0,0,0 };
	//**========カメラの情報==========**
	CCamera* pCamera = pManager->GetCamera();  //カメラの取得
	D3DXVECTOR3 rot = pCamera->GetRot();	//向き

	if (pKeyboard->GetPress(DIK_A) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT))
	{//Aキーが押された場合
		move.x -= MOVE_SPEED;
		m_rot.y = -(D3DX_PI * -HALF2 - rot.y);

		//同時に押されたとき
		if (pKeyboard->GetPress(DIK_A) == true && pKeyboard->GetPress(DIK_D) == true || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
		{//Dキーが押された場合

			move.x = 0.0f;
		}
	}
	if (pKeyboard->GetPress(DIK_D) == true || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
	{//Dキーが押された場合

		move.x += MOVE_SPEED;
		m_rot.y = -(D3DX_PI * HALF1 - rot.y);

		//同時に押されたとき
		if (pKeyboard->GetPress(DIK_A) == true && pKeyboard->GetPress(DIK_D) == true || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
		{//Dキーが押された場合

			move.x = 0.0f;
		}
	}


	return move;

}
//====================================
// プレイヤーのダメージ処理
//====================================
void CPlayerX::HItPlayer(int nDamage)
{
	if (m_state == PLAYERSTATE_NONE)
	{
		m_nLife -= nDamage;
		if (m_nLife <= 0)
		{
			DeathFlag();
		}
		m_nFrameCnt--;
		m_state = PLAYERSTATE_DAMAGE;
		if (m_state == PLAYERSTATE_DAMAGE)
		{
			if (m_nFrameCnt <= 0)
			{
				m_state = PLAYERSTATE_NONE;
				m_nFrameCnt = 1;
			}
		}

	}
}

//====================================
// 描画処理
//====================================
void CPlayerX::Draw()
{
	CObjectX::Draw();
}
//====================================
// 生成処理
//====================================
CPlayerX* CPlayerX::Create(D3DXVECTOR3 pos, int nType)
{
	CPlayerX* pPlayerX = new CPlayerX();
	pPlayerX->Init();
	pPlayerX->SetPos(pos);
	if (nType == 0)
	{
		pPlayerX->SetModel("data/MODEL/player002.x");
	}
	return pPlayerX;
}

//=======================================
//ブロックとプレイヤーの当たり判定
//=======================================
bool CPlayerX::CollisionBlock(CBlockX* pBlockX)
{

	D3DXVECTOR3 blockSize = pBlockX->GetSize();		// ブロック(オブジェクトの)サイズ取得
	D3DXVECTOR3 blockPos = pBlockX->GetPos();		// ブロック(オブジェクトの)位置取得

	D3DXVECTOR3 playerSize = this->GetSize();		// プレイヤーのサイズを取得
	D3DXVECTOR3 playerPos = this->GetPos();         // プレイヤーの位置取得


//**===================xとzとyの当たり判定==========================**

// 縦横の範囲内に入っているか
	if ((playerPos.x + playerSize.x * 0.5f >= blockPos.x - blockSize.x * 0.5f) &&		//ブロックにめり込んだ
		(playerPos.x - playerSize.x * 0.5f <= blockPos.x + blockSize.x * 0.5f) &&
		(playerPos.z + playerSize.z * 0.5f >= blockPos.z - blockSize.z * 0.5f) &&
		(playerPos.z - playerSize.z * 0.5f <= blockPos.z + blockSize.z * 0.5f) &&
		(playerPos.y + playerSize.y * 0.5f >= blockPos.y - blockSize.y * 0.5f) &&
		(playerPos.y - playerSize.y * 0.5f <= blockPos.y + blockSize.y * 0.5f))
	{
		// 高さが合っているとき(多分上だけ)
		if ((playerPos.y >= blockPos.y - blockSize.y * 0.5f) &&
			(playerPos.y <= blockPos.y + blockSize.y * 0.5f))
		{   // 縦の範囲内だったら

				//**===============z軸の判定=====================**

				//奥からのめり込み
			if (m_posOld.z >= blockPos.z + blockSize.z * 0.5f + playerSize.z * 0.5f &&
				playerPos.z <= blockPos.z + blockSize.z * 0.5f + playerSize.z * 0.5f)
			{//
				playerPos.z = blockPos.z + blockSize.z * 0.5f + playerSize.z * 0.5f; // 押し返す
				m_pos = playerPos;
			}
			//手前からのめり込み
			else if (m_posOld.z <= blockPos.z - blockSize.z * 0.5f - playerSize.z * 0.5f &&
				playerPos.z >= blockPos.z - blockSize.z * 0.5f - playerSize.z * 0.5f)
			{//
				playerPos.z = blockPos.z - blockSize.z * 0.5f - playerSize.z * 0.5f; // 押し返す
				m_pos = playerPos;
			}
			//**===============x軸の判定=====================**

			//左からのめり込み
			if (m_posOld.x >= blockPos.x + blockSize.x * 0.5f + playerSize.x * 0.5f &&
				playerPos.x <= blockPos.x + blockSize.x * 0.5f + playerSize.x * 0.5f)
			{//
				playerPos.x = blockPos.x + blockSize.x * 0.5f + playerSize.x * 0.5f; // 押し返す
				m_pos = playerPos;
			}
			//右からのめり込み
			else if (m_posOld.x <= blockPos.x - blockSize.x * 0.5f - playerSize.x * 0.5f &&
				playerPos.x >= blockPos.x - blockSize.x * 0.5f - playerSize.x * 0.5f)
			{//
				playerPos.x = blockPos.x - blockSize.x * 0.5f - playerSize.x * 0.5f; // 押し返す
				m_pos = playerPos;
			}
		}
		//**===============y軸の判定=====================**
		//上からのめり込み
		if (m_posOld.y >= blockPos.y + blockSize.y * 0.5f + playerSize.y * 0.5f &&
			playerPos.y <= blockPos.y + blockSize.y * 0.5f + playerSize.y * 0.5f)
		{//
			playerPos.y = blockPos.y + blockSize.y * 0.5f + playerSize.y * 0.5f; // 押し返す
			m_pos = playerPos;
		}
		//下からのめり込み
		else if (m_posOld.y <= blockPos.y - blockSize.y * 0.5f - playerSize.y * 0.5f &&
			playerPos.y >= blockPos.y - blockSize.y * 0.5f - playerSize.y * 0.5f)
		{//
			playerPos.y = blockPos.y - blockSize.y * 0.5f - playerSize.y * 0.5f; // 押し返す
			m_pos = playerPos;
		}

	}
	
	return false;
}


void CPlayerX::Collision()
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
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					//CDamage::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z));
					CLife::HitLife(10);
				}
				else
				{// 当たってないとき
				}

			}
			if (type == CObject::TYPE::MARKER)
			{

				CMarker* pMarker = (CMarker*)pObj; //ダウンキャスト
				int nType = 0;
				nType = pMarker->GetType();
				D3DXVECTOR3 markerPos = pMarker->GetPos();
				D3DXVECTOR3 markerSize = pMarker->GetSize();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(markerPos.x, markerPos.y, markerPos.z), halfWidths1(markerSize.x, markerSize.y, markerSize.z);  // 敵の中心点とサイズ
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					switch (nType)
					{
					case 1:
						CFade::SetFade(CScene::MODE::MODE_RESULT);
						break;
					case 2:
						CFade::SetFade(CScene::MODE::MODE_GAME_SECOND);
						break;
					case 3:
						CFade::SetFade(CScene::MODE::MODE_GAME_THIRD);
						break;
					case 4:
						CFade::SetFade(CScene::MODE::MODE_GAME);
						break;
					}
				}
				else
				{// 当たってないとき
				}

			}

			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}


}



