#include "Effect.h"
#include "sprite.h"
#include "shader.h"

//=========================================================================================================
// �}�N����`
//=========================================================================================================
#define	EFFECT_MAX	(100)							//�G�t�F�N�g�I�u�W�F�N�g

//=========================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================
// ���ӁI�������ŊO������ݒ肳�����́BRelease�s�v�B
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;
static ID3D11ShaderResourceView* g_Texture;
static	EFFECT	g_Effect[EFFECT_MAX];
static	XMFLOAT2 ScrollOffset = XMFLOAT2(POSITION_OFFSET_X, POSITION_OFFSET_Y);



//=========================================================================================================
// ����������
//=========================================================================================================
void Effect_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	g_pDevice = pDevice;
	g_pContext = pContext;

	//�I�u�W�F�N�g�̏�����
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_Effect[i].Enable = false;
	}

	// �e�N�X�`���ǂݍ���
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"Asset\\Texture\\Explosion.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(pDevice, image.GetImages(), 
						image.GetImageCount(), metadata, &g_Texture);
	assert(g_Texture);

}

//=========================================================================================================
// �I������
//=========================================================================================================
void Effect_Finalize()
{
	if (g_Texture != NULL)
	{
		g_Texture->Release();
	}
}

//=========================================================================================================
// �X�V����
//=========================================================================================================
void Effect_Update()
{
	//�A�j���[�V��������
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].Enable == true)
		{
			g_Effect[i].FrameCount++;	//�J�E���^�[�C���N�������g
			if (g_Effect[i].FrameCount > 30)
			{
				g_Effect[i].Enable = false;
			}
		}

	}

}

//=========================================================================================================
// �`�揈��
//=========================================================================================================
void Effect_Draw()
{
	//�e�N�X�`���̃Z�b�g
	g_pContext->PSSetShaderResources(0, 1, &g_Texture);

	// ��ʃT�C�Y�擾
	const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();
	const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();

	// �V�F�[�_�[��`��p�C�v���C���ɐݒ�
	Shader_Begin();

	// ���_�V�F�[�_�[��2D�ϊ��s���ݒ�
	XMMATRIX	Projection = XMMatrixOrthographicOffCenterLH(
		0.0f,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0.0f,
		0.0f,
		1.0f);

	//�I�u�W�F�N�g�̕\��
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].Enable == true)
		{
			int		PatNo = (int)(g_Effect[i].FrameCount / 30.0f * 16.0f);
			XMFLOAT4	col(1.0f, 1.0f, 1.0f, 1.0f);	//���F
			XMFLOAT2	size(BLOCK_WIDTH * 1.6f, BLOCK_HEIGHT * 1.6f);

			//���s�ړ� �\�����W
			XMMATRIX	Translation =
				XMMatrixTranslation(g_Effect[i].Position.x, g_Effect[i].Position.y, 0.0f);
			//��]
			XMMATRIX	Rotation = XMMatrixRotationZ(XMConvertToRadians(0.0f));
			//�g�嗦�i0�͂��߁j
			XMMATRIX	Scaling = XMMatrixScaling(1.0f, 1.0f, 1.0f);
			//���[���h�s��
			XMMATRIX	World = Scaling * Rotation * Translation;
	
			//�X�N���[���p�s��쐬
			//XMMATRIX	mat = XMMatrixIdentity();//�s��̏������i�P�ʍs��j
			XMMATRIX	mat = XMMatrixTranslation(ScrollOffset.x, ScrollOffset.y, 0.0f);
			//���_�ϊ��s��
			mat = World * mat * Projection;

			//�V�F�[�_�[�֍s����Z�b�g
			Shader_SetMatrix(mat);

			SetBlendState(BLENDSTATE_ALFA);
			DrawSprite(size, col, PatNo, 4, 4);

		}

	}




}


//=========================================================================================================
// �G�t�F�N�g�쐬
//=========================================================================================================
void CreateEffect(XMFLOAT2 Position)
{
	//0718��������
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].Enable == false)
		{
			g_Effect[i].Enable = true;
			g_Effect[i].Position = XMFLOAT3(Position.x, Position.y, 0.0f);
			g_Effect[i].FrameCount = 0;

			break;//1�������I��
		}

	}

}

