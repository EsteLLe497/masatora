#pragma once

#include <d3d11.h>

//=========================================================================================================
// �\���̐錾
//=========================================================================================================
enum PIECE_STATE
{
	PIECE_STATE_IDLE = 0,	//�������Ȃ�
	PIECE_STATE_MOVE,		//�ړ���
	PIECE_STATE_GROUND_IDLE,	//���n��
	PIECE_STATE_MISS_IDLE,		//�~�X����

};

//�����u���b�N
class PIECE
{
	public:
		XMFLOAT2		Position;	//�\�����W
		int				Type[3];	//�F���
		PIECE_STATE		State;		//���

		int				StateCount;	//�X�e�[�g�؂�ւ��E�F�C�g

};

//=========================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================
void Player_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void Player_Finalize(void);
void Player_Update();
void Player_Draw(void);
void Player_Create();
void Player_Move();	

