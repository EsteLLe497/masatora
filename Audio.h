#pragma once

#include <xaudio2.h>

//=========================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================
void InitAudio();		//�T�E���h�̏�����
void UninitAudio();		//�T�E���h�̏I��
int LoadAudio(const char* FileName);		//�T�E���h�f�[�^�ǂݍ���
void UnloadAudio(int Index);				//�T�E���h�f�[�^����i��~�j
void PlayAudio(int Index, bool Loop = false);//�T�E���h�f�[�^�Đ�

/*
//�ȉ��̊֐��̓v���O�����̍ŏ��ƍŌ��1�񂸂Ăяo����OK
void InitAudio();		//�T�E���h�̏�����
void UninitAudio();		//�T�E���h�̏I��


//�ȉ��̓V�[�����Ƃ̏���

//�O���[�o���ϐ�
static int g_BgmID = NULL;//���[�h����f�[�^�̐������ϐ����K�v

//��������
g_BgmID = LoadAudio("asset\\Audio\\title.wav");	//�T�E���h�f�[�^�ǂݍ���
PlayAudio(g_BgmID, true);	//�T�E���h�f�[�^�Đ�(���[�v����)

//�I����
UnloadAudio(g_BgmID);		//�T�E���h�f�[�^����i��~�j


*/




