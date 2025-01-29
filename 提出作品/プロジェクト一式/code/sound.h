//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA     �N���X�� : ibuki kida
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
	// �T�E���h�ꗗ
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// �^�C�g��bgm
		SOUND_LABEL_BGM_TUTORIAL,   // �`���[�g���A���pbgm
		SOUND_LABEL_BGM_GAME001,    // �X�e�[�W1 bgm
		SOUND_LABEL_BGM_GAME002,    // �X�e�[�W2 bgm
		SOUND_LABEL_BGM_GAME003,    // �X�e�[�W3 bgm
		SOUND_LABEL_BGM_CLEAR,      // �N���A bgm
		SOUND_LABEL_BGM_LOSE,       // ���� bgm
		SOUND_LABEL_SE_SELECT,      // ��ʑJ�ڗp
		SOUND_LABEL_SE_SELECT1,     // ��ʑJ�ڃQ�[����ʗp
		SOUND_LABEL_SE_ATTACK,      // �v���C���[�̍U����
		SOUND_LABEL_SE_PLAYER_DAMAGE,     // �v���C���[�̃_���[�W��
		SOUND_LABEL_SE_ENEMY_DAMAGE,     // �G�̃_���[�W��
		SOUND_LABEL_SE_JUMP,        // �W�����v��
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
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

};

#endif
