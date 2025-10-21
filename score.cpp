#include	"shader.h"
#include	"sprite.h"
#include	"score.h"

//=========================================================================================================
// �}�N����`
//=========================================================================================================
#define		SCORE_MAX	(5)		//�\������

//=========================================================================================================
// �O���[�o���錾
//=========================================================================================================
// ���ӁI�������ŊO������ݒ肳�����́BRelease�s�v�B
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;
static ID3D11ShaderResourceView* g_Texture = NULL;
static	float	Score;			//�X�R�A�l
static	float	ScoreBuffer;	//�X�R�A�l�o�b�t�@

//=========================================================================================================
// ����������
//=========================================================================================================
void Score_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{ 
	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̕ۑ�
	g_pDevice = pDevice;
	g_pContext = pContext;

	//
	Score = 0.0f;
	ScoreBuffer = 0.0f;

	//
	//�e�N�X�`���摜�ǂݍ���
	TexMetadata		metadata;
	ScratchImage	image;
	LoadFromWICFile(L"asset\\texture\\number000.png", 
		WIC_FLAGS_NONE, &metadata, image);//�e�N�X�`���͕ύX��
	CreateShaderResourceView(pDevice, image.GetImages(),
		image.GetImageCount(), metadata, &g_Texture);
	assert(g_Texture);//�ǂݍ��ݎ��s���Ƀ_�C�A���O��\��

}

//=========================================================================================================
// �I������
//=========================================================================================================
void Score_Finalize(void)
{ 
	if (g_Texture != NULL)
	{
		g_Texture->Release();//�e�N�X�`�������
		g_Texture = NULL;
	}

}

//=========================================================================================================
// �X�V����
//=========================================================================================================
void Score_Update()
{ 
	if (ScoreBuffer > 0.0f)//�o�b�t�@�ɃX�R�A�����܂��Ă���
	{
		Score += 0.5f;			//�o�b�t�@�̒��g��Score�֏�������
		ScoreBuffer -= 0.5f;	//�ڂ��Ă���
	}
	else
	{
		ScoreBuffer = 0.0f;
	}

}
//=========================================================================================================
// �`�揈��
//=========================================================================================================
void Score_Draw(void)
{ 
	//������
	int		PatNo[5] = { 0,0,0,0,0 };//�����������ʂ��i�[

	int		temp = (int)Score;
	PatNo[0] = temp / 10000;			//�P���̈�
	PatNo[1] = (temp % 10000) / 1000;	//��̈�
	PatNo[2] = (temp % 1000) / 100;		//�S�̈�
	PatNo[3] = (temp % 100) / 10;		//�\�̈�
	PatNo[4] = (temp % 10);				//�P�̈�

	XMFLOAT3	position = XMFLOAT3(100.0f, 100.0f, 0.0f);
	XMFLOAT2	size = XMFLOAT2(50.0f, 80.0f);
	XMFLOAT4	color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̃Z�b�g
	g_pContext->PSSetShaderResources(0, 1, &g_Texture);

	//��ʃT�C�Y�擾
	const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();
	const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();

	//�V�F�[�_�[�̃Z�b�g
	Shader_Begin();

	//�V�F�[�_�[�ɂQD�`��̐ݒ������
	XMMATRIX	Projection = XMMatrixOrthographicOffCenterLH(
		0.0f,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0.0f,
		0.0f,
		1.0f
	);

	//�X�R�A�\���i�T�����j
	for (int i = 0; i < SCORE_MAX; i++)
	{

		//���s�ړ� �\�����W
		XMMATRIX	Translation =
			XMMatrixTranslation(position.x, position.y, 0.0f);
		//��]
		XMMATRIX	Rotation = XMMatrixRotationZ(XMConvertToRadians(0.0f));
		//�g�嗦�i0�͂��߁j
		XMMATRIX	Scaling = XMMatrixScaling(1.0f, 1.0f, 1.0f);
		//���[���h�s��
		XMMATRIX	World = Scaling * Rotation * Translation;
		//�X�N���[���p�s��쐬
		XMMATRIX	mat = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

		mat = World * mat * Projection;

		//�V�F�[�_�[�֍s����Z�b�g
		Shader_SetMatrix(mat);

		//�u�����h����
		SetBlendState(BLENDSTATE_ALFA);

		//�X�v���C�g�`��
		DrawSprite(size, color, PatNo[i], 10, 1);

		position.x += size.x;//�\�����W���P�������炷

	}

}
//=========================================================================================================
// �X�R�A���Z����
//=========================================================================================================
void	AddScore(int sc)	//�X�R�A�ɉ��Z����
{ 
	ScoreBuffer += sc;
}

//=========================================================================================================
// �X�R�A�l�擾
//=========================================================================================================
float	GetScore()			//�X�R�A�l�擾
{ 
	return Score;
}

