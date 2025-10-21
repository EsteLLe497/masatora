/*==============================================================================

   2D�`��p���_�V�F�[�_�[ [shader_vertex_2d.hlsl]
--------------------------------------------------------------------------------

==============================================================================*/

// �萔�o�b�t�@
float4x4 mtx;	//C���ꂩ��n���ꂽ�f�[�^�������Ă���

//���͗p���_�\����
struct VS_INPUT
{//              V �R�����I
    float4  posL : POSITION0; //���_���W �I�[�łȂ��[���I
    float4  color : COLOR0;   //���_�J���[�iR,G,B,A�j
    float2 texcoord : TEXCOORD0;
};

//�o�͗p���_�\����
struct VS_OUTPUT
{
    float4  posH : SV_POSITION;     //�ϊ��ϒ��_���W
    float4  color : COLOR0;         //���_�J���[
    float2 texcoord : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT vs_in)
{
    VS_OUTPUT vs_out;   //�o�͗p�\���̕ϐ�
    
    //���_���s��ŕϊ�
    vs_out.posH = mul(vs_in.posL, mtx);
    //���_�J���[�͂��̂܂܏o��
    vs_out.color = vs_in.color;

    vs_out.texcoord = vs_in.texcoord;

    //���ʂ��o�͂���
    return vs_out;
}



////=============================================================================
//// ���_�V�F�[�_
////=============================================================================
//float4 main(in float4 posL : POSITION0 ) : SV_POSITION
//{
//	return mul(posL, mtx);//���_���W��mtx�i�ϊ��s��j
//}
