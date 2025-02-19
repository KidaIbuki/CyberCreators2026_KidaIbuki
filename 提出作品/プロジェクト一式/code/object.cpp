//=================================
// 
// オブジェクトクラス　object.cpp
//outher kida ibuki 
// 
//==================================
#include <cassert>
#include "object.h"
#include "manager.h"
//静的メンバの初期化
CObject* CObject::m_pTop[NUM_MAX_PRIORITY] = {};
CObject* CObject::m_pCur[NUM_MAX_PRIORITY] = {};

//====================================================
// コンストラクタ(自分自身の登録)
//====================================================
CObject::CObject()
{

	m_pNext = nullptr;	// オブジェクトの次のポインタを初期化
	m_pPrev = nullptr;	// オブジェクトの前のポインタを初期化
	m_bDeath = false;	// 死亡フラグを初期化
	m_type = NONE;      // タイプの初期化

	if (m_pCur[3] != nullptr)
	{ // 最後尾が空じゃなかった
		m_pPrev = m_pCur[3];			// 自分自身の1つ前のオブジェクトは現在の最後尾
		m_pPrev->m_pNext = this;	// 自分自身の1つ前のオブジェクトの次のポインタに自分自身を代入
	}

	if (m_pTop[3] == nullptr)
	{ // 先頭が空だった
		m_pTop[3] = this;	// 先頭に自分自身を代入
		m_pCur[3] = this;
	}

	m_pCur[3] = this;	// 最後尾に自分自身を代入

}
CObject::CObject(int nPriority)
{

	m_pNext = nullptr;	// オブジェクトの次のポインタを初期化
	m_pPrev = nullptr;	// オブジェクトの前のポインタを初期化
	m_bDeath = false;	// 死亡フラグを初期化
	m_type = NONE;      // タイプの初期化

	if (m_pCur != nullptr)
	{ // 最後尾が空じゃなかった
		m_pPrev = m_pCur[nPriority];			// 自分自身の1つ前のオブジェクトは現在の最後尾
		m_pPrev->m_pNext = this;	// 自分自身の1つ前のオブジェクトの次のポインタに自分自身を代入
	}

	if (m_pTop == nullptr)
	{ // 先頭が空だった
		m_pTop[nPriority] = this;	// 先頭に自分自身を代入
		m_pCur[nPriority] = this;
	}

	m_pCur[nPriority] = this;	// 最後尾に自分自身を代入

}

//====================================================
// デストラクタ
//====================================================
CObject::~CObject()
{

}

//====================================================
// 初期設定
//====================================================
HRESULT CObject::Init()
{
	return S_OK;
}
//====================================================
// 全オブジェクト解放
//====================================================
void CObject::ReleaseAll()
{
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		CObject* pObj = nullptr;
		pObj = m_pTop[nPriority];   // 先頭取得
		// 最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->m_bDeath = true;
			pObj = pNext;
		}
	}
}

//====================================================
//全オブジェクト更新
//====================================================
void CObject::UpdateAll()
{

	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		CObject* pObj = nullptr;
		pObj = m_pTop[nPriority];   // 先頭取得

		// 最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			pObj->Update();

			pObj = pNext;
		}


	}
}
//====================================================
//全オブジェクト描画
//====================================================
void CObject::DrawAll()
{

	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		CObject* pObj = nullptr;
		pObj = m_pTop[nPriority];   // 先頭取得
		// 最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->Draw();

			pObj = pNext;
		}
	}
}
//====================================================
// 全オブジェクトを破棄
//====================================================
void CObject::DeathAll()
{
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		CObject* pObj = nullptr;
		pObj = m_pTop[nPriority];   // 先頭取得

				// 最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			if (pObj->m_bDeath == true)  // TODO: 今までオブジェクト自身が Relese を呼んでいたところを、"m_bDeath = true" にする
			{
				pObj->Release();
			}
			pObj = pNext;
		}
	}

}
//====================================================
// オブジェクトの取得
//====================================================
CObject* CObject::GetObj(int nPriority)
{
	return m_pTop[nPriority];
}
void CObject::GetObj(CObject* pObject[NUM_MAX_PRIORITY])
{
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		pObject[nPriority] = m_pTop[nPriority];
	}
}
//====================================================
//タイプ設定
//====================================================
void CObject::SetType(TYPE type)
{
	assert(type >= NONE && type < MAX);
	m_type = type;
}

//====================================================
//自分自身の解放(変えなくてOK)
//====================================================
void CObject::Release()
{
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		if (m_pTop[nPriority] == this) // || m_pPrev == nullptr でもできそう
		{ // 自分自身が先頭だった
			m_pTop[nPriority] = m_pNext;	// 自分の次のオブジェクトを先頭にする
		}
		if (m_pCur[nPriority] == this) // || m_pNext == nullptr でもできそう
		{ // 自分自身が最後尾だった
			m_pCur[nPriority] = m_pPrev;	// 自分の前のオブジェクトを先頭にする
		}
	}
	if (m_pPrev != nullptr)
	{
		m_pPrev->m_pNext = m_pNext;   // 消したいオブジェクトが消えたら、消したオブジェクトの前後を繋げる
	}
	if (m_pNext != nullptr)
	{
		m_pNext->m_pPrev = m_pPrev;   // 消したいオブジェクトが消えたら、消したオブジェクトの前後を繋げる
	}
	delete this;
}
//====================================================
// 死亡フラグを立てる
//====================================================
void CObject::DeathFlag()
{
	m_bDeath = true;
}
