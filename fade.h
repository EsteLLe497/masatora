#pragma once

#include "direct3d.h"
#include "sprite.h"
#include "Manager.h"

//=========================================================================================================
// �\���̒�`
//=========================================================================================================
enum FADE_STATE
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,

};

struct FadeObject
{
	FADE_STATE	state;			//�t�F�[�h�������
	float		count;			//�J�E���^�[
	float		frame;			//�t�F�[�h��������
	XMFLOAT4	fadecolor;		//�t�F�[�h�F
	SCENE		scene;			//���ɐ؂�ւ��V�[��
};

//=========================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================
void Fade_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void Fade_Finalize();
void Fade_Update();
void Fade_Draw();
void	SetFade(int fadeframe, XMFLOAT4 color, FADE_STATE state, SCENE scene);
FADE_STATE	GetFadeState();



