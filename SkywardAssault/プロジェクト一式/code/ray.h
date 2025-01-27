//=================================
// 
// ���C�@ray.h
//outher kida ibuki 
// 
//==================================
#ifndef _RAY_H_
#define _RAY_H_

#include "pch.h"
class Ray 
{
private:
    D3DXVECTOR3 origin;      // ���C�̎n�_
    D3DXVECTOR3 direction;   // ���C�̕����x�N�g���i���K���ς݁j

public:
    // �R���X�g���N�^
    Ray(const D3DXVECTOR3& start, const D3DXVECTOR3& end);

    // ���C�̎n�_���擾
    const D3DXVECTOR3& GetOrigin() const;

    // ���C�̕����x�N�g�����擾
    const D3DXVECTOR3& GetDirection() const;

    // �C�ӂ�t�l�ł̈ʒu���v�Z (P(t) = origin + t * direction)
    D3DXVECTOR3 GetPoint(float t) const;

    // ���C�Ƌ��̏Փ˔���
    bool IntersectSphere(const D3DXVECTOR3& sphereCenter, float sphereRadius, float& distance) const;

};

#endif