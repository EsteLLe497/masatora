#include	"Manager.h"
#include	"sprite.h"
#include	"Game.h"
#include	"keyboard.h"
#include	"player.h"
#include	"field.h"
#include	"Effect.h"
#include	"score.h"
#include	"Audio.h"
#include "mouse.h"

//=========================================================================================================
// �O���[�o���錾
//=========================================================================================================
static	int		g_BgmID = NULL;	//�T�E���h�Ǘ�ID

//=========================================================================================================
// ����������
//=========================================================================================================
void Game_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{

	Player_Initialize(pDevice, pContext); // �|���S���̏�����
	field_Initialize(pDevice, pContext); // �t�B�[���h�̏�����
	Effect_Initialize(pDevice, pContext);//�G�t�F�N�g������
	Score_Initialize(pDevice, pContext);//�X�R�A������

	g_BgmID = LoadAudio("asset\\Audio\\bgm.wav");	//�T�E���h���[�h
	PlayAudio(g_BgmID, true);	//�Đ��J�n�i���[�v����j
	//PlayAudio(g_BgmID);			//�Đ��J�n�i���[�v�Ȃ��j
	//PlayAudio(g_BgmID, false);	//�Đ��J�n�i���[�v�Ȃ��j

}

//=========================================================================================================
// �I������
//=========================================================================================================
void Game_Finalize()
{
	Player_Finalize();	// �|���S���̏I������
	field_Finalize();	// �t�B�[���h�̏I������
	Effect_Finalize();
	Score_Finalize();

	UnloadAudio(g_BgmID);//�T�E���h�̉��
}

//=========================================================================================================
// �X�V����
//=========================================================================================================
void Game_Update()
{
	Player_Update();
	Effect_Update();
	Score_Update();

}

//=========================================================================================================
// �`�揈��
//=========================================================================================================
void Game_Draw()
{ 
	field_Draw();
	Player_Draw();
	Effect_Draw();
	Score_Draw();

}

