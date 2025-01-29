//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA     クラス化 : ibuki kida
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include "renderer.h"
#include "pch.h"

class CSound
{
public:
	// サウンド一覧
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// タイトルbgm
		SOUND_LABEL_BGM_TUTORIAL,   // チュートリアル用bgm
		SOUND_LABEL_BGM_GAME001,    // ステージ1 bgm
		SOUND_LABEL_BGM_GAME002,    // ステージ2 bgm
		SOUND_LABEL_BGM_GAME003,    // ステージ3 bgm
		SOUND_LABEL_BGM_CLEAR,      // クリア bgm
		SOUND_LABEL_BGM_LOSE,       // 負け bgm
		SOUND_LABEL_SE_SELECT,      // 画面遷移用
		SOUND_LABEL_SE_SELECT1,     // 画面遷移ゲーム画面用
		SOUND_LABEL_SE_ATTACK,      // プレイヤーの攻撃音
		SOUND_LABEL_SE_PLAYER_DAMAGE,     // プレイヤーのダメージ音
		SOUND_LABEL_SE_ENEMY_DAMAGE,     // 敵のダメージ音
		SOUND_LABEL_SE_JUMP,        // ジャンプ音
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

};

#endif
