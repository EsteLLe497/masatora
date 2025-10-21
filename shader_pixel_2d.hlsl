/*==============================================================================

   2D�`��p�s�N�Z���V�F�[�_�[ [shader_pixel_2d.hlsl]
--------------------------------------------------------------------------------
==============================================================================*/

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

struct PS_INPUT
{
    float4 posH : SV_POSITION; //�s�N�Z���̍��W
    float4 color : COLOR0; //�s�N�Z���̐F
    float2 texcoord : TEXCOORD0;
};

float4 main(PS_INPUT ps_in) : SV_TARGET
{
    float4 col;
    col = g_Texture.Sample(g_SamplerState, ps_in.texcoord);
    col *= ps_in.color;
    return col;
}



