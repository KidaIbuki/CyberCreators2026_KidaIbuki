//================================
//
//x�t�@�C���Ńu���b�N(blockX.h)
//outher kida ibuki
//================================
#ifndef _BLOCKX_H_
#define _BLOCKX_H_

#include "objectX.h"
#include "object.h"

//�u���b�N�̃N���X��`
class CBlockX : public CObjectX
{
public:
	CBlockX();																				//�R���X�g���N�^
	~CBlockX();																		//�f�X�g���N�^
	HRESULT Init();																//�����ݒ�
	void Uninit();																	//�I������
	void Update();																	//�X�V����
	void Draw();																	//�`�揈��
	static CBlockX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat);					//�u���b�N�̐���
protected:

private:
};
#endif
