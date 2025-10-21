#include	"fade.h"
#include	"shader.h"

//=========================================================================================================
// �\���̐錾
//=========================================================================================================
FadeObject	g_Fade;		//�t�F�[�h�����\����

//=========================================================================================================
// �O���[�o���錾
//=========================================================================================================
static	ID3D11ShaderResourceView* g_Texture = NULL;	//�e�N�X�`���P����\���I�u�W�F�N�g
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;


//=========================================================================================================
// ����������
//=========================================================================================================
void Fade_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	g_pDevice = pDevice;
	g_pContext = pContext;

	//�e�N�X�`���ǂݍ���
	TexMetadata		metadata;
	ScratchImage	image;
	LoadFromWICFile(L"asset\\texture\\fade.bmp", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(pDevice, image.GetImages(), image.GetImageCount(), metadata, &g_Texture);
	assert(g_Texture);//�ǂݍ��ݎ��s���Ƀ_�C�A���O��\��

	g_Fade.fadecolor.x = 0.0f;
	g_Fade.fadecolor.y = 0.0f;
	g_Fade.fadecolor.z = 0.0f;
	g_Fade.fadecolor.w = 1.0f;
	g_Fade.frame = 60.0f;	//60�t���[���Ńt�F�[�h����
	g_Fade.state = FADE_STATE::FADE_NONE;

}

//=========================================================================================================
// �I������
//=========================================================================================================
void Fade_Finalize()
{
	if (g_Texture != NULL)
	{
		g_Texture->Release();
		g_Texture = NULL;
	}
}

//=========================================================================================================
// �X�V����
//=========================================================================================================
void Fade_Update()
{
}

//=========================================================================================================
// �`�揈��
//=========================================================================================================
void Fade_Draw()
{ 
	//���݂̏�
	switch (g_Fade.state)
	{
		case FADE_STATE::FADE_NONE:
			return;
		case FADE_STATE::FADE_IN:
			if (g_Fade.fadecolor.w < 0.0)
			{//�t�F�[�h�C���I��
				g_Fade.fadecolor.w = 0.0f;
				g_Fade.state = FADE_STATE::FADE_NONE;
			}
			break;
		case FADE_STATE::FADE_OUT:
			if (g_Fade.fadecolor.w > 1.0f)
			{//�t�F�[�h�A�E�g�I��
				g_Fade.fadecolor.w = 1.0;
				//�t�F�[�h�C��������
				SetFade(g_Fade.frame, g_Fade.fadecolor, FADE_STATE::FADE_IN, g_Fade.scene);
				//�V�[���؂�ւ�
				SetScene(g_Fade.scene);
			}
			break;
	}

	//�X�v���C�g�\��

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
	g_pContext->PSSetShaderResources(0, 1, &g_Texture);

	//�X�v���C�g�`��
	SetBlendState(BLENDSTATE_ALFA);//���u�����h
	XMFLOAT2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	XMFLOAT2 size = { SCREEN_WIDTH, SCREEN_HEIGHT };
	DrawSprite(pos, size, g_Fade.fadecolor);

	//�t�F�[�h����
	switch (g_Fade.state)
	{
		case FADE_STATE::FADE_IN:
			g_Fade.fadecolor.w -= (1.0f / g_Fade.frame);//�����ɂ��Ă���
			break;
		case FADE_STATE::FADE_OUT:
			g_Fade.fadecolor.w += (1.0f / g_Fade.frame);//�s�����ɂ��Ă���
			break;
	}


}

//=========================================================================================================
// �t�F�[�h�ݒ�
//=========================================================================================================
void	SetFade(int fadeframe, XMFLOAT4 color, FADE_STATE state, SCENE scene)
{ 
	g_Fade.frame = fadeframe;
	g_Fade.fadecolor = color;
	g_Fade.state = state;
	g_Fade.scene = scene;

	if (g_Fade.state == FADE_IN)
	{
		g_Fade.fadecolor.w = 1.0f;	//�s�����ɂ���
	}
	else
	{
		g_Fade.fadecolor.w = 0.0f;	//�����ɂ���
	}


}

//=========================================================================================================
// �t�F�[�h��Ԏ擾
//=========================================================================================================
FADE_STATE	GetFadeState()
{
	return	g_Fade.state;	//���݂̏��
}


