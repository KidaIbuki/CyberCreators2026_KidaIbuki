//=================================
// 
//カメラクラス　camera.h
//outher kida ibuki 
// 
//==================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"
#include "objectX.h"

//前方宣言
class CObjectX;

//カメラクラスの定義
class CCamera
{
public:
	CCamera();					//コンストラクタ
	~CCamera();					//デストラクタ
	HRESULT Init();				//初期設定
	void Uninit();				//終了処理
	void Update();				//更新処理
	void SetCamera();			//カメラ設定

	void ResetCamera();
	D3DXVECTOR3 GetRot() { return m_rot; }			//向きを取得
	D3DXVECTOR3 GetPosR() { return m_posR; }		//注視点の取得
	D3DXVECTOR3 GetPosV() { return m_posV; }		//注視点の取得

	void SetPos(D3DXVECTOR3 pos);
	void SetShake(int shakeFrame, float shakeVolume);
private:
	D3DXVECTOR3 m_posV;			//視点
	D3DXVECTOR3 m_posR;         //注視点
	D3DXVECTOR3 m_vecU;			//上方向
	D3DXVECTOR3 m_rot;			//向き
	D3DXMATRIX m_mtxProjection;	//プロジェクション行列
	D3DXMATRIX m_mtxView;		//ビュー行列
	float m_fScaleDis;
	float m_fDistance;		//距離
	D3DXVECTOR3 m_move;
	int m_nShakeFrame;
	int m_nShakeVolume;
};

#endif
