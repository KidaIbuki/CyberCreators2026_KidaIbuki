//=================================
// 
//プリコンパイル済みヘッダー　pch.h
//outher kida ibuki 
// 
//==================================
#pragma once	// 二重インクルード防止

//=====================================================
// インクルードファイル
//=====================================================
#include <cassert>		//assert使うため
#include <windows.h>	// Windowsアプリケーション用
#include <d3dx9.h>		// DirectX9用


#define DIRECTINPUT_VERSION	(0x0800)	// DirectInputのバージョン
#include <dinput.h>					    // DirectInput用
#include <xinput.h>					    // ジョイパッド処理に必要
#include <xaudio2.h>				    // サウンド処理に必要
#include <string>						//strを使うため(textureなどのファイルパスを書くため)
#include <mmsystem.h>
#include "time.h"                       // 乱数に必要
#include <cmath>                        // sqrt sin cos
#include <algorithm>                    // max,minを使用するのに必要
#include <cmath>                        // std::time
#include <cstdlib>                      // std::rand std::srand
#include <vector>

//=====================================================
// ライブラリのリンク
//=====================================================
#pragma	comment(lib,"d3d9.lib")		// 描画処理に必要
#pragma	comment(lib,"d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma	comment(lib,"dxguid.lib")	// DirectXコンポーネント(部品)使用に必要
#pragma	comment(lib,"dinput8.lib")	// 入力処理に必要
#pragma comment(lib,"xinput.lib")	// ジョイパッド処理に必要
#pragma comment(lib, "winmm.lib")	// システム時刻取得に必要

//=====================================================
// マクロ定義
//=====================================================

// 頂点フォーマット
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)			//2Dのやつ
#define FVF_VERTEX_3D   (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//3D用のやつ

// ウィンドウサイズ
#define SCREEN_WIDTH	(1280)	    //ウインドウの幅
#define SCREEN_HEIGHT	(720)		//ウインドウの高さ


//モデルファイルの読み込み構造体
typedef struct
{
	int nType;
	char cFile[256];		//ファイルを読み込む
	//D3DXVECTOR3 pos;
	//D3DXVECTOR3 rot;
}MODEL_FILENAME;

// 敵のやつ
typedef struct
{
	int nType;
	char cFile[256];		//ファイルを読み込む
	//D3DXVECTOR3 pos;
	//D3DXVECTOR3 rot;
}ENEMY_FILENAME;

