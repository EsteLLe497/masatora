#pragma once

#include <d3d11.h>
#include "direct3d.h"
#include <DirectXMath.h>
using namespace DirectX;

//=========================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================
void Score_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void Score_Finalize(void);
void Score_Update();
void Score_Draw(void);
void	AddScore(int sc);	
float GetScore();



