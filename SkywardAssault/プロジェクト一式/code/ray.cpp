//=================================
// 
// レイ　ray.cpp
//outher kida ibuki 
// 
//==================================
#include "ray.h"

// コンストラクタ：2点間のレイを作成
Ray::Ray(const D3DXVECTOR3& start, const D3DXVECTOR3& end) {
    origin = start;  // レイの始点
    direction = end - start;  // 始点から終点への方向ベクトル
    D3DXVec3Normalize(&direction, &direction);  // 方向ベクトルを正規化
}

// レイの始点を取得
const D3DXVECTOR3& Ray::GetOrigin() const {
    return origin;
}

// レイの方向ベクトルを取得
const D3DXVECTOR3& Ray::GetDirection() const {
    return direction;
}

// 任意のt値での位置を計算
D3DXVECTOR3 Ray::GetPoint(float t) const {
    return origin + direction * t;
}

// レイと球の衝突判定
bool Ray::IntersectSphere(const D3DXVECTOR3& sphereCenter, float sphereRadius, float& distance) const {
    D3DXVECTOR3 m = origin - sphereCenter;  // 球の中心からレイの始点へのベクトル

    float b = D3DXVec3Dot(&m, &direction);  // b = dot(m, direction)
    float c = D3DXVec3Dot(&m, &m) - sphereRadius * sphereRadius;  // c = dot(m, m) - r^2

    // 判別式（b^2 - c）が負なら衝突なし
    if (c > 0.0f && b > 0.0f) return false;

    float discriminant = b * b - c;
    if (discriminant < 0.0f) return false;

    // 衝突点までの距離を計算
    distance = -b - sqrtf(discriminant);
    if (distance < 0.0f) distance = 0.0f;

    return true;
}
