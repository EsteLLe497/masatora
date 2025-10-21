#pragma once

#include <d3d11.h>
#include "direct3d.h"
#include <DirectXMath.h>
using namespace DirectX;

//=========================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================
void	DrawSprite(XMFLOAT2 pos, XMFLOAT2 size, XMFLOAT4 col);
void	DrawSpriteEx(XMFLOAT2 pos, XMFLOAT2 size, XMFLOAT4 col, int bno, int wc, int hc);
void	InitializeSprite();	
void	FinalizeSprite();
void	DrawSpriteScroll(XMFLOAT2 pos, XMFLOAT2 size, XMFLOAT4 col,XMFLOAT2 texcoord);
void	DrawSpriteExRotation(XMFLOAT2 pos, XMFLOAT2 size, XMFLOAT4 col, int bno, int wc, int hc, float radian);
void	DrawSprite(XMFLOAT2 size, XMFLOAT4 col, int bno, int wc, int hc);

//=========================================================================================================
// �\���̒�`
//=========================================================================================================
struct Vertex
{
	XMFLOAT3 position; // ���_���W  //XMFLOAT3�֕ύX
	XMFLOAT4 color;		//���_�J���[�iR,G,B,A�j
	XMFLOAT2 texCoord;	//�e�N�X�`�����W
};
