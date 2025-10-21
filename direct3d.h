/*==============================================================================

   Direct3D�̏������֘A [direct3d.cpp]
														 Author : Youhei Sato
														 Date   : 2025/05/12
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef DIRECT3D_H
#define DIRECT3D_H


#include <Windows.h>
#include <d3d11.h>
#include <mmsystem.h>

#include "DirectXTex.h"/////////////0602
#if _DEBUG
 #pragma comment(lib, "DirectXTex_Debug.lib");
#else
 #pragma comment(lib, "DirectXTex_Release.lib");
#endif





// �Z�[�t�����[�X�}�N��
#define SAFE_RELEASE(o) if (o) { (o)->Release(); o = NULL; }


bool Direct3D_Initialize(HWND hWnd); // Direct3D�̏�����
void Direct3D_Finalize(); // Direct3D�̏I������

void Direct3D_Clear(); // �o�b�N�o�b�t�@�̃N���A
void Direct3D_Present(); // �o�b�N�o�b�t�@�̕\��

////////////////////////////////////////////////�ǉ�
ID3D11Device* Direct3D_GetDevice(); // �f�o�C�X�̎擾
ID3D11DeviceContext* Direct3D_GetDeviceContext(); // �f�o�C�X�R���e�L�X�g�̎擾

unsigned int Direct3D_GetBackBufferWidth(); // �o�b�N�o�b�t�@�̕����擾
unsigned int Direct3D_GetBackBufferHeight(); // �o�b�N�o�b�t�@�̍������擾


enum	BLENDSTATE
{
	BLENDSTATE_NONE = 0,	//�u�����h���Ȃ�
	BLENDSTATE_ALFA,		//���ʂ̃��u�����h
	BLENDSTATE_ADD,			//���Z���� 
	BLENDSTATE_SUB,			//���Z����

	BLENDSTATE_MAX
};
void SetBlendState(BLENDSTATE blend);


//�u���b�N�c���z��T�C�Y
#define BLOCK_COLS		(6)	//�u���b�N�X�^�b�N���̐�
#define BLOCK_ROWS		(13)//�u���b�N�X�^�b�N�c�̐�

//�u���b�N�T�C�Y
#define		BLOCK_WIDTH		(50.0f)
#define		BLOCK_HEIGHT	(50.0f)

//�X�N���[���l
#define		POSITION_OFFSET_X	(490.0f)
#define		POSITION_OFFSET_Y	(34.0f)


////////////////////////////////////////////////////


#endif // DIRECT3D_H
