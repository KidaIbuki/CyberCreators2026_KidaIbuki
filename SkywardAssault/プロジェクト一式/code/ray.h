//=================================
// 
// レイ　ray.h
//outher kida ibuki 
// 
//==================================
#ifndef _RAY_H_
#define _RAY_H_

#include "pch.h"
class Ray 
{
private:
    D3DXVECTOR3 origin;      // レイの始点
    D3DXVECTOR3 direction;   // レイの方向ベクトル（正規化済み）

public:
    // コンストラクタ
    Ray(const D3DXVECTOR3& start, const D3DXVECTOR3& end);

    // レイの始点を取得
    const D3DXVECTOR3& GetOrigin() const;

    // レイの方向ベクトルを取得
    const D3DXVECTOR3& GetDirection() const;

    // 任意のt値での位置を計算 (P(t) = origin + t * direction)
    D3DXVECTOR3 GetPoint(float t) const;

    // レイと球の衝突判定
    bool IntersectSphere(const D3DXVECTOR3& sphereCenter, float sphereRadius, float& distance) const;

};

#endif