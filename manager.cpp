
#include "direct3d.h"
#include "Manager.h"
#include "keyboard.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "fade.h"


//=========================================================================================================
// �O���[�o���錾
//=========================================================================================================
static	SCENE	g_Scene = SCENE_NONE;	//���݂̃V�[���ԍ�

//=========================================================================================================
// ����������
//=========================================================================================================
void	Manager_Initialize()
{ 
	Fade_Initialize(Direct3D_GetDevice(), Direct3D_GetDeviceContext());

	////�{����title�̏������Ńt�F�[�h�C�����Z�b�g����
	//XMFLOAT4 color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//SetFade(60.0f, color, FADE_STATE::FADE_IN, SCENE_GAME);
	//SetScene(SCENE_GAME);	//�ŏ��ɓ������V�[���ɐ؂�ւ���


	//�{���̌`
	Fade_Initialize(Direct3D_GetDevice(), Direct3D_GetDeviceContext());
	SetScene(SCENE_TITLE);	//�ŏ��ɓ������V�[���ɐ؂�ւ���

}

//=========================================================================================================
// �I������
//=========================================================================================================
void	Manager_Finalize()
{ 
	Fade_Finalize();
	SetScene(SCENE_NONE);
}

//=========================================================================================================
// �X�V����
//=========================================================================================================
void	Manager_Update()
{
	switch (g_Scene)	//���݃V�[���̃A�b�v�f�[�g�֐����Ăяo��
	{
		case SCENE_NONE:
			break;
		case SCENE_TITLE:
			Title_Update();	
			break;
		case SCENE_GAME:
			Game_Update();
			break;
		case SCENE_RESULT:
			Result_Update();
			break;
		default:
			break;
	}

	Fade_Update();

}

//=========================================================================================================
// �`�揈��
//=========================================================================================================
void	Manager_Draw()
{ 
	switch (g_Scene)	//���݃V�[���̕`��֐����Ăяo��
	{
		case SCENE_NONE:
			break;
		case SCENE_TITLE:
			Title_Draw();	
			break;
		case SCENE_GAME:
			Game_Draw();
			break;
		case SCENE_RESULT:
			Result_Draw();
			break;
		default:
			break;
	}

	Fade_Draw();

}

//=========================================================================================================
// �V�[���؂�ւ�
//=========================================================================================================
void	SetScene(SCENE scene) //�V�[����؂�ւ���
{
	//���s���̃V�[�����I��������
	switch (g_Scene)	//���݃V�[���̏I���֐����Ăяo��
	{
		case SCENE_NONE:
			break;
		case SCENE_TITLE:
			Title_Finalize();	
			break;
		case SCENE_GAME:
			Game_Finalize();
			break;
		case SCENE_RESULT:
			Result_Finalize();
			break;
		default:
			break;
	}

	g_Scene = scene;	//�w��̃V�[���֐؂�ւ���

	//���̃V�[��������������
	switch (g_Scene)	//���݃V�[���̏������֐����Ăяo��
	{
		case SCENE_NONE:
			break;
		case SCENE_TITLE:
			Title_Initialize(Direct3D_GetDevice(), Direct3D_GetDeviceContext());
			break;
		case SCENE_GAME:
			Game_Initialize( Direct3D_GetDevice(), Direct3D_GetDeviceContext());
			break;
		case SCENE_RESULT:
			Result_Initialize(Direct3D_GetDevice(), Direct3D_GetDeviceContext());
			break;
		default:
			break;
	}

}
