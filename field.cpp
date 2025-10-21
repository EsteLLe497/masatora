#include "field.h"
#include "sprite.h"
#include "shader.h"

//=========================================================================================================
// �O���[�o���錾
//=========================================================================================================
static	ID3D11ShaderResourceView* g_Texture = NULL;	//�e�N�X�`���P����\���I�u�W�F�N�g
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;

//=========================================================================================================
// ����������
//=========================================================================================================
void field_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̕ۑ�
	g_pDevice = pDevice;
	g_pContext = pContext;

	//�e�N�X�`���ǂݍ���
	TexMetadata		metadata;
	ScratchImage	image;
	LoadFromWICFile(L"asset\\texture\\Bg.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(pDevice, image.GetImages(), image.GetImageCount(), metadata, &g_Texture);
	assert(g_Texture);//�ǂݍ��ݎ��s���Ƀ_�C�A���O��\��

}

//=========================================================================================================
// �I������
//=========================================================================================================
void field_Finalize(void)
{
	SAFE_RELEASE(g_Texture);

}

//=========================================================================================================
// �X�V����
//=========================================================================================================
void field_Draw(void)
{
//---------------------------------------------------
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
	DrawSpriteScroll(pos, size, col,texcoord);//1���G��\��

//	texcoord.x += -1.0f / (60.0f * 5.0f);

}

