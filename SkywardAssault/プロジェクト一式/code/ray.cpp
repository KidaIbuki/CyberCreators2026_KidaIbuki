//=================================
// 
// ���C�@ray.cpp
//outher kida ibuki 
// 
//==================================
#include "ray.h"

// �R���X�g���N�^�F2�_�Ԃ̃��C���쐬
Ray::Ray(const D3DXVECTOR3& start, const D3DXVECTOR3& end) {
    origin = start;  // ���C�̎n�_
    direction = end - start;  // �n�_����I�_�ւ̕����x�N�g��
    D3DXVec3Normalize(&direction, &direction);  // �����x�N�g���𐳋K��
}

// ���C�̎n�_���擾
const D3DXVECTOR3& Ray::GetOrigin() const {
    return origin;
}

// ���C�̕����x�N�g�����擾
const D3DXVECTOR3& Ray::GetDirection() const {
    return direction;
}

// �C�ӂ�t�l�ł̈ʒu���v�Z
D3DXVECTOR3 Ray::GetPoint(float t) const {
    return origin + direction * t;
}

// ���C�Ƌ��̏Փ˔���
bool Ray::IntersectSphere(const D3DXVECTOR3& sphereCenter, float sphereRadius, float& distance) const {
    D3DXVECTOR3 m = origin - sphereCenter;  // ���̒��S���烌�C�̎n�_�ւ̃x�N�g��

    float b = D3DXVec3Dot(&m, &direction);  // b = dot(m, direction)
    float c = D3DXVec3Dot(&m, &m) - sphereRadius * sphereRadius;  // c = dot(m, m) - r^2

    // ���ʎ��ib^2 - c�j�����Ȃ�Փ˂Ȃ�
    if (c > 0.0f && b > 0.0f) return false;

    float discriminant = b * b - c;
    if (discriminant < 0.0f) return false;

    // �Փ˓_�܂ł̋������v�Z
    distance = -b - sqrtf(discriminant);
    if (distance < 0.0f) distance = 0.0f;

    return true;
}
