//=================================
// 
// 階層構造モデルパーツ　modelparts.h
//outher kida ibuki 
// 
//==================================
#include "modelparts.h"   // モデルパーツ
#include "manager.h"    // マネージャー
#include "pch.h"        // プリコンパイル済みヘッダー

//===========================================================================
// コンストラクタ
//===========================================================================
CModelParts::CModelParts()
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		aModel[nCnt].pMesh = nullptr;
		aModel[nCnt].pBuffMat = nullptr;
		aModel[nCnt].dwNumMat = 0;
		aModel[nCnt].m_nMaxVtx = { 0.0f,0.0f,0.0f };
		aModel[nCnt].m_nMinVtx = { 0.0f,0.0f,0.0f };
	}
	m_size = {0.0f,0.0f,0.0f};
}
//===========================================================================
// デストラクタ
//===========================================================================
CModelParts::~CModelParts()
{
}
//===========================================================================
//モデルの頂点情報を元にサイズの最大値最小値を求める
//===========================================================================
void CModelParts::SizeVtx()
{
	//**========================メッシュの情報を取得================**
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (aModel[nCnt].pMesh != nullptr)
		{
			//頂点数の取得
			aModel[nCnt].m_nNumVtx = aModel[nCnt].pMesh->GetNumVertices();

			//頂点フォーマットのサイズを取得
			aModel[nCnt].m_sizeFVF = D3DXGetFVFVertexSize(aModel[nCnt].pMesh->GetFVF());

			//頂点バッファのロック
			aModel[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&aModel[nCnt].m_bpVtxBuff);

			for (int nCntVtx = 0; nCntVtx < aModel[nCnt].m_nNumVtx; nCntVtx++)
			{
				//頂点座標を代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)aModel[nCnt].m_bpVtxBuff;

				//頂点座標を比較してモデルの最大値、最小値を取得
				//xの最大値
				if (vtx.x > aModel[nCnt].m_nMaxVtx.x)
				{
					aModel[nCnt].m_nMaxVtx.x = vtx.x;
				}
				//xの最小値
				else if (vtx.x < aModel[nCnt].m_nMinVtx.x)
				{
					aModel[nCnt].m_nMinVtx.x = vtx.x;
				}
				//yの最大値
				if (vtx.y > aModel[nCnt].m_nMaxVtx.y)
				{
					aModel[nCnt].m_nMaxVtx.y = vtx.y;
				}
				//yの最小値
				else if (vtx.y < aModel[nCnt].m_nMinVtx.y)
				{
					aModel[nCnt].m_nMinVtx.y = vtx.y;
				}
				//zの最大値
				if (vtx.z > aModel[nCnt].m_nMaxVtx.z)
				{
					aModel[nCnt].m_nMaxVtx.z = vtx.z;
				}
				//zの最小値
				else if (vtx.z < aModel[nCnt].m_nMinVtx.z)
				{
					aModel[nCnt].m_nMinVtx.z = vtx.z;
				}

				//頂点フォーマットのサイズ分ポインタを進める
				aModel[nCnt].m_bpVtxBuff += aModel[nCnt].m_sizeFVF;
			}
			//頂点バッファのアンロック
			aModel[nCnt].pMesh->UnlockVertexBuffer();

			//**=========================================================**
			m_size = aModel[nCnt].m_nMaxVtx - aModel[nCnt].m_nMinVtx;
		}
	}
}

//===========================================================================
// 初期設定
//===========================================================================
HRESULT CModelParts::Init()
{
	CManager* pManager = CManager::GetInstance();
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/PLAYER/00_bodyB.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[0].pBuffMat, NULL, &aModel[0].dwNumMat, &aModel[0].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/01_bodyF.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[1].pBuffMat, NULL, &aModel[1].dwNumMat, &aModel[1].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/02_leftWingU1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[2].pBuffMat, NULL, &aModel[2].dwNumMat, &aModel[2].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/03_leftWingU2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[3].pBuffMat, NULL, &aModel[3].dwNumMat, &aModel[3].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/04_leftWingD1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[4].pBuffMat, NULL, &aModel[4].dwNumMat, &aModel[4].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/05_leftWingD2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[5].pBuffMat, NULL, &aModel[5].dwNumMat, &aModel[5].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/06_rightWingD1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[6].pBuffMat, NULL, &aModel[6].dwNumMat, &aModel[6].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/07_rightWingD2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[7].pBuffMat, NULL, &aModel[7].dwNumMat, &aModel[7].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/08_rightWingU1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[8].pBuffMat, NULL, &aModel[8].dwNumMat, &aModel[8].pMesh);
	D3DXLoadMeshFromX("data/MODEL/PLAYER/09_rightWingU2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &aModel[9].pBuffMat, NULL, &aModel[9].dwNumMat, &aModel[9].pMesh);

	SizeVtx();

	// 各パーツに親を設定する
	aModel[0].nIdxModelParent = -1;
	aModel[1].nIdxModelParent = 0;
	aModel[2].nIdxModelParent = 0;
	aModel[3].nIdxModelParent = 2;
	aModel[4].nIdxModelParent = 0;
	aModel[5].nIdxModelParent = 4;
	aModel[6].nIdxModelParent = 0;
	aModel[7].nIdxModelParent = 6;
	aModel[8].nIdxModelParent = 0;
	aModel[9].nIdxModelParent = 8;


	//位置(オフセット)の設定
	aModel[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	aModel[1].pos = D3DXVECTOR3(0.0f, 0.0f, -26.0f);
	aModel[2].pos = D3DXVECTOR3(9.0f, 2.0f, -4.0f);
	aModel[3].pos = D3DXVECTOR3(22.0f, 6.0f, 0.0f);
	aModel[4].pos = D3DXVECTOR3(9.0f, -2.0f, -4.0f);
	aModel[5].pos = D3DXVECTOR3(22.0f, -6.0f, 0.0f);
	aModel[6].pos = D3DXVECTOR3(-9.0f, -2.0f, -4.0f);
	aModel[7].pos = D3DXVECTOR3(-22.0f, -6.0f, 0.0f);
	aModel[8].pos = D3DXVECTOR3(-9.0f, 2.0f, -4.0f);
	aModel[9].pos = D3DXVECTOR3(-22.0f, 6.0f, 0.0f);


	//向き(オフセット)の設定
	aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}
//===========================================================================
// 終了処理
//===========================================================================
void CModelParts::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		// メッシュの破棄
		if (aModel[nCnt].pMesh != nullptr)
		{
			aModel[nCnt].pMesh->Release();
			aModel[nCnt].pMesh = nullptr;
		}
		// マテリアルの破棄
		if (aModel[nCnt].pBuffMat != nullptr)
		{
			aModel[nCnt].pBuffMat->Release();
			aModel[nCnt].pBuffMat = nullptr;
		}
	}

}
//===========================================================================
// 更新処理
//===========================================================================
void CModelParts::Update()
{
}
//===========================================================================
// 描画処理
//===========================================================================
void CModelParts::Draw()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// デバイスを取得
	D3DXMATRIX mtxRot, mtxTrans;											// 計算用マトリックス
	D3DMATERIAL9 matDef;				// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;					// マテリアルデータへのポインタ


	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
	    // ワールドマトリックスの初期化
	    D3DXMatrixIdentity(&aModel[nCnt].mtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, aModel[nCnt].rot.y, aModel[nCnt].rot.x, aModel[nCnt].rot.z);
		D3DXMatrixMultiply(&aModel[nCnt].mtxWorld, &aModel[nCnt].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, aModel[nCnt].pos.x, aModel[nCnt].pos.y, aModel[nCnt].pos.z);
		D3DXMatrixMultiply(&aModel[nCnt].mtxWorld, &aModel[nCnt].mtxWorld, &mtxTrans);

		// 親の行列と掛け合わせる
		D3DXMATRIX mtxParent;
		if (aModel[nCnt].nIdxModelParent != -1)
		{
			// 親のワールド変換行列を取得
			mtxParent = aModel[aModel[nCnt].nIdxModelParent].mtxWorld;
		}
		else
		{
			// 最新のワールド変換行列を取得(=プレイヤーの行列)
			pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
		}
		// パーツのワールド変換行列とmtxParentを掛け合わせる
		D3DXMatrixMultiply(&aModel[nCnt].mtxWorld, &aModel[nCnt].mtxWorld, &mtxParent);


		// ワールド変換行列の設定
		pDevice->SetTransform(D3DTS_WORLD, &aModel[nCnt].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)aModel[nCnt].pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)aModel[nCnt].dwNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			pDevice->SetTexture(0, NULL);

			// モデルの描画
			aModel[nCnt].pMesh->DrawSubset(nCntMat);
		}

		// 保存していたマテリアルに戻す
		pDevice->SetMaterial(&matDef);
	}
}
//===========================================================================
// 生成
//===========================================================================
CModelParts* CModelParts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int idx)
{
	CModelParts* pParts = new CModelParts();
	pParts->SetPos(pos, idx);
	pParts->SetRot(rot, idx);
	pParts->Init();
	return pParts;
}


//===========================================================================
// オフセットの位置の設定
//===========================================================================
void CModelParts::SetPos(D3DXVECTOR3 pos, int idx)
{
	aModel[idx].pos = pos;
}
//===========================================================================
// オフセットの向きの設定
//===========================================================================
void CModelParts::SetRot(D3DXVECTOR3 rot, int idx)
{
	aModel[idx].rot = rot;
}



