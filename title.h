#pragma once

#include "direct3d.h"

//=========================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================
void Title_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void Title_Finalize();
void Title_Update();
void Title_Draw();

