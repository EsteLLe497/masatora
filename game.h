#pragma once

#include "direct3d.h"

//=========================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================
void Game_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void Game_Finalize();
void Game_Update();
void Game_Draw();



