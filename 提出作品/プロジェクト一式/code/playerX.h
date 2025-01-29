//==============================================
// 
// 3D�̃v���C���[�@playerX.h
//outher kida ibuki 
// 
//==============================================
#ifndef _PLAYERX_H_
#define _PLAYERX_H_

#include "pch.h"
#include "main.h"
#include "objectX.h"
#include "object.h"


class CBlockX;//�O���錾

//�}�N����`
#define MAX_KEYSET (20) //�L�[�̍ő吔
#define MODEL_PARTS (14) //���f���̐�
#define MAX_MOTION (7) //���[�V�����̐�

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
		JUMPSTATE_NONE = 0,//�n�ʂɂ��鎞
		JUMPSTATE_JUMP,    //�󒆂ɂ��鎞
		JUMPSTATE_MAX
	};

	CPlayerX();
	~CPlayerX()override;
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��

	static CPlayerX* Create(D3DXVECTOR3 pos, int nType);
	void Collision();
	bool CollisionBlock(CBlockX* pBlockX);	// �����蔻��
	D3DXVECTOR3 PlayerMove();		//�I�u�W�F�N�g(���v���C���[)�̈ړ����ݒ�

		//**=================c++�Ń}�N��====================**
	static const float HALF2;				//3.14�̔����̂Q����
	static const float HALF1;				//3.14�̔����̂R����
	static const float HALF;				//��̔���
	static const float MOVE_SPEED;			//�ړ��̑��x

	int GetLifePlayer() { return m_nLife; }
	void HItPlayer(int nDamage);

private:

	D3DXVECTOR3 m_posOld;						//�v���C���[�̑O��̈ʒu
	int m_nLife;

	//**=========�W�����v�p===========**
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
