#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"

//=========================================================================================================
// �\���̐錾
//=========================================================================================================
class EFFECT
{
	public:
		bool		Enable;
		XMFLOAT3	Position;
		int			FrameCount;	//�A�j���[�V�����J�E���^�[

};

//=========================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================
void Effect_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void Effect_Finalize();
void Effect_Update();
void Effect_Draw();
void CreateEffect(XMFLOAT2 Position);
