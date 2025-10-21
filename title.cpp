#include	"Manager.h"
#include	"sprite.h"
#include	"keyboard.h"
#include	"Title.h"
#include "fade.h"
#include "shader.h"
#include "mouse.h"

//=========================================================================================================
// �\���̐錾
//=========================================================================================================
static Mouse_State ms{};

//=========================================================================================================
// �O���[�o���錾
//=========================================================================================================
static	ID3D11ShaderResourceView* g_Texture = NULL;	//�e�N�X�`���P����\���I�u�W�F�N�g
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;

//=========================================================================================================
// ����������
//=========================================================================================================
void Title_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	g_pDevice = pDevice;
	g_pContext = pContext;

	//�e�N�X�`���ǂݍ��݂Ȃ�
	TexMetadata		metadata;
	ScratchImage	image;
	LoadFromWICFile(L"asset\\texture\\Title.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(pDevice, image.GetImages(), image.GetImageCount(), metadata, &g_Texture);
	assert(g_Texture);//�ǂݍ��ݎ��s���Ƀ_�C�A���O��\��

	//�t�F�[�h�C���̃Z�b�g
	XMFLOAT4	color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	SetFade(60.0f, color, FADE_IN, SCENE_GAME);

}

//=========================================================================================================
// �I������
//=========================================================================================================
void Title_Finalize()
{
	//�e�N�X�`���̉���Ȃ�
	SAFE_RELEASE(g_Texture);


}

//=========================================================================================================
// �X�V����
//=========================================================================================================
void Title_Update()
{ 
	Mouse_GetState(&ms);
	//�L�[���̓`�F�b�N
	//�X�^�[�g�{�^���������ꂽ��V�[����؂�ւ�
	//�t�F�[�h�������̓L�[���󂯕t���Ȃ�
	if (Keyboard_IsKeyDownTrigger(KK_ENTER) && (GetFadeState() == FADE_NONE))
	{
		//�t�F�[�h�A�E�g�����ăV�[����؂�ւ���
		XMFLOAT4	color(0.0f, 0.0f, 0.0f, 1.0f);
		SetFade(40.0f, color, FADE_OUT, SCENE_GAME);
	}

	if (ms.leftButton)
	{
		//�t�F�[�h�A�E�g�����ăV�[����؂�ւ���
		XMFLOAT4	color(0.0f, 0.0f, 0.0f, 1.0f);
		SetFade(40.0f, color, FADE_OUT, SCENE_GAME);
	}
}

//=========================================================================================================
// �`�揈��
//=========================================================================================================
void Title_Draw()
{
	// �V�F�[�_�[��`��p�C�v���C���ɐݒ�
	Shader_Begin();

	// ��ʃT�C�Y�擾
	const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();
	const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();

	// ���_�V�F�[�_�[�ɕϊ��s���ݒ�
	Shader_SetMatrix(XMMatrixOrthographicOffCenterLH(
		0.0f,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0.0f,
		0.0f,
		1.0f));
	//---------------------------------------------------


		//�e�N�X�`�����Z�b�g
	g_pContext->PSSetShaderResources(0, 1, &g_Texture);//g_Texture���g���悤�ɐݒ肷��

	static XMFLOAT2 texcoord = { 0.0f, 0.0f };

	//�X�v���C�g�`��
	SetBlendState(BLENDSTATE_NONE);//�u�����h����
	XMFLOAT4 col = { 1.0f, 1.0f, 1.0f, 1.0f };	//�X�v���C�g�̐F
	XMFLOAT2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	XMFLOAT2 size = { SCREEN_WIDTH, SCREEN_HEIGHT };
	DrawSprite(pos, size, col);//1���G��\��

}


