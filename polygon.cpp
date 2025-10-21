/*==============================================================================

   �|���S���`�� [polygon.cpp]
--------------------------------------------------------------------------------

==============================================================================*/
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "shader.h"
#include "debug_ostream.h"
#include "sprite.h"//�X�v���C�g�@�\��ǉ�

#include	"keyboard.h"//<<<<<<<<<<<<<<<<<<<�ǉ�


static	ID3D11ShaderResourceView* g_Texture = NULL;	//�e�N�X�`���P����\���I�u�W�F�N�g

// ���ӁI�������ŊO������ݒ肳�����́BRelease�s�v�B
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;


void Polygon_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̃`�F�b�N
	if (!pDevice || !pContext) {
		hal::dout << "Polygon_Initialize() : �^����ꂽ�f�o�C�X���R���e�L�X�g���s���ł�" << std::endl;
		return;
	}

	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̕ۑ�
	g_pDevice = pDevice;
	g_pContext = pContext;

	//�e�N�X�`���摜�ǂݍ���
	TexMetadata		metadata;
	ScratchImage	image;
//	LoadFromWICFile(L"asset\\texture\\shadow.png", WIC_FLAGS_NONE, &metadata, image);
	LoadFromWICFile(L"asset\\texture\\runningman003.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(pDevice, image.GetImages(), image.GetImageCount(), metadata, &g_Texture);
	assert(g_Texture);//�ǂݍ��ݎ��s���Ƀ_�C�A���O��\��

}

void Polygon_Finalize(void)
{
	g_Texture->Release();

}
void Polygon_Draw(void)
{
	// ��ʃT�C�Y�擾
	const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();
	const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();


	XMFLOAT4 col = { 1.0f, 1.0f, 1.0f, 1.0f };	//�X�v���C�g�̐F
	XMFLOAT2 size = { 200, 300 };


	static XMFLOAT2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT - 150 };
	if (Keyboard_IsKeyDown(KK_W))//W�L�[
	{
		//�L�[�������ꂽ�ꍇ
		pos.y += -2.0f;
	}
	//�g���K�[�L�[�̏ꍇ
	if (Keyboard_IsKeyDown(KK_S))//S���L�[
	{
		//�L�[�������ꂽ�ꍇ
		pos.y += 2.0f;
	}
	if (Keyboard_IsKeyDown(KK_A))//A�L�[
	{
		//�L�[�������ꂽ�ꍇ
		pos.x += -2.0f;
	}
	//�g���K�[�L�[�̏ꍇ
	if (Keyboard_IsKeyDown(KK_D))//D���L�[
	{
		//�L�[�������ꂽ�ꍇ
		pos.x += 2.0f;
	}

	//�X�v���C�g��]�p(�x)
	static float deg = 0.0f;
	//�L�[�{�[�h�̓��̓`�F�b�N
	if (Keyboard_IsKeyDown(KK_LEFT))//�����L�[
	{
		//�L�[�������ꂽ�ꍇ
		deg += 2.0f;
	}
	//�g���K�[�L�[�̏ꍇ
	if (Keyboard_IsKeyDown(KK_RIGHT))//�E���L�[
	{
		//�L�[�������ꂽ�ꍇ
		deg += -2.0f;
	}
	//�X�P�[�����O
	static	float	scl = 1.0f;
	if (Keyboard_IsKeyDown(KK_UP))//����L�[
	{
		//�L�[�������ꂽ�ꍇ
		scl += 0.1f;
		if (scl > 5.0f) scl = 5.0f;
	}
	//�g���K�[�L�[�̏ꍇ
	if (Keyboard_IsKeyDown(KK_DOWN))//�����L�[
	{
		//�L�[�������ꂽ�ꍇ
		scl += -0.1f;
		if (scl < 1.0f) scl = 1.0f;
	}




	// �V�F�[�_�[��`��p�C�v���C���ɐݒ�
	Shader_Begin();


	// ���_�V�F�[�_�[�ɕϊ��s���ݒ�

	XMMATRIX	Projection = XMMatrixOrthographicOffCenterLH(
								0.0f,
								SCREEN_WIDTH,
								SCREEN_HEIGHT,
								0.0f,
								0.0f,
								1.0f);

	XMMATRIX	Translation  = XMMatrixTranslation(pos.x,pos.y, 0.0f);
	XMMATRIX	Rotation = XMMatrixRotationZ(XMConvertToRadians(deg));
	XMMATRIX	Scaling = XMMatrixScaling(scl, scl, scl);
	XMMATRIX	World = Scaling * Rotation * Translation;

	XMMATRIX	mat = XMMatrixIdentity();
	mat = mat * World * Projection;

	Shader_SetMatrix(mat);

	SetBlendState(BLENDSTATE_ALFA);//�u�����h����

	//�X�v���C�g�`��e�X�g
	g_pContext->PSSetShaderResources(0, 1, &g_Texture);//g_Texture���g���悤�ɐݒ肷��



	static float bno = 0;	//�u���b�N�̔ԍ�
	DrawSprite(size, col, (int)bno, 5, 2);

	bno += 10.0f/60.0f;	//�K���ɐ����𑝂₷
	if (bno >= 10.0f)
	{
		bno = 0.0f;
	}

}
