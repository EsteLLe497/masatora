#include "sprite.h"

//=========================================================================================================
// �O���[�o���錾
//=========================================================================================================
static constexpr int NUM_VERTEX = 6; // �g�p�ł���ő咸�_��
static ID3D11Buffer* g_pVertexBuffer = nullptr; // ���_�o�b�t�@
// ���ӁI�������ŊO������ݒ肳�����́BRelease�s�v�B
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;


//=========================================================================================================
// ����������
//=========================================================================================================
void		InitializeSprite()
{
	g_pDevice = Direct3D_GetDevice();

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * NUM_VERTEX;//<<<<<<<�i�[����ő咸�_��
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	g_pDevice->CreateBuffer(&bd, NULL, &g_pVertexBuffer);
}

//=========================================================================================================
// �I������
//=========================================================================================================
void		FinalizeSprite()
{
	g_pVertexBuffer->Release();	//���_�o�b�t�@�̉��
}


//=========================================================================================================
// �`�揈��
//=========================================================================================================
void		DrawSprite(XMFLOAT2 pos, XMFLOAT2 size, XMFLOAT4 col)
{

	g_pDevice = Direct3D_GetDevice();
	g_pContext = Direct3D_GetDeviceContext();

	// ���_�o�b�t�@�����b�N����
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾
	Vertex* v = (Vertex*)msr.pData;

	// �w��̈ʒu�Ɏw��̃T�C�Y�A�F�̎l�p�`��`�悷�� /////////�e�N�X�`���ǉ�
	v[0].position = { pos.x - (size.x / 2), pos.y - (size.y / 2), 0.0f };
	v[0].color = col;
	v[0].texCoord = { 0.0f, 0.0f };

	v[1].position = { pos.x + (size.x / 2), pos.y - (size.y / 2), 0.0f };
	v[1].color = col;
	v[1].texCoord = { 1.0f, 0.0f };

	v[2].position = { pos.x - (size.x / 2), pos.y + (size.y / 2), 0.0f };
	v[2].color = col;
	v[2].texCoord = { 0.0f, 1.0f };

	v[3].position = { pos.x + (size.x / 2), pos.y + (size.y / 2), 0.0f };
	v[3].color = col;
	v[3].texCoord = { 1.0f, 1.0f };


	// ���_�o�b�t�@�̃��b�N������
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�
	UINT stride = sizeof(Vertex);//���_�P������̃T�C�Y���w��
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�@�|���S���̕`�惋�[���I�Ȃ���
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`�施�ߔ��s
	g_pContext->Draw(4, 0);//�\���Ɏg�p���钸�_�����w��

}

//=========================================================================================================
// �`�揈��(�e�N�X�`��)
//=========================================================================================================
void	DrawSpriteEx(XMFLOAT2 pos, XMFLOAT2 size, XMFLOAT4 col, int bno, int wc, int hc)
{

	g_pDevice = Direct3D_GetDevice();
	g_pContext = Direct3D_GetDeviceContext();

	// ���_�o�b�t�@�����b�N����
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾
	Vertex* v = (Vertex*)msr.pData;

	//�u���b�N�̏c���T�C�Y���v�Z
	float w = 1.0f / wc;
	float h = 1.0f / hc;
	//bno�̍���̃e�N�X�`�����W���v�Z
	float x = (bno % wc) * w;
	float y = (bno / wc) * h;

	// �w��̈ʒu�Ɏw��̃T�C�Y�A�F�̎l�p�`��`�悷�� /////////�e�N�X�`���ǉ�
	v[0].position = { pos.x - (size.x / 2), pos.y - (size.y / 2), 0.0f };
	v[0].color = col;
	v[0].texCoord = { x, y };

	v[1].position = { pos.x + (size.x / 2), pos.y - (size.y / 2), 0.0f };
	v[1].color = col;
	v[1].texCoord = { x + w, y };

	v[2].position = { pos.x - (size.x / 2), pos.y + (size.y / 2), 0.0f };
	v[2].color = col;
	v[2].texCoord = { x, y + h };

	v[3].position = { pos.x + (size.x / 2), pos.y + (size.y / 2), 0.0f };
	v[3].color = col;
	v[3].texCoord = { x + w, y + h };


	// ���_�o�b�t�@�̃��b�N������
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�
	UINT stride = sizeof(Vertex);//���_�P������̃T�C�Y���w��
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�@�|���S���̕`�惋�[���I�Ȃ���
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`�施�ߔ��s
	g_pContext->Draw(4, 0);//�\���Ɏg�p���钸�_�����w��


}

//=========================================================================================================
// �`�揈���i�X�N���[���t���j
//=========================================================================================================
void	DrawSpriteScroll(XMFLOAT2 pos, XMFLOAT2 size, XMFLOAT4 col,
	XMFLOAT2 texcoord)
{

	g_pDevice = Direct3D_GetDevice();
	g_pContext = Direct3D_GetDeviceContext();

	// ���_�o�b�t�@�����b�N����
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾
	Vertex* v = (Vertex*)msr.pData;

	// �w��̈ʒu�Ɏw��̃T�C�Y�A�F�̎l�p�`��`�悷�� /////////�e�N�X�`���ǉ�
	v[0].position = { pos.x - (size.x / 2), pos.y - (size.y / 2), 0.0f };
	v[0].color = col;
	v[0].texCoord = { texcoord.x, texcoord.y };

	v[1].position = { pos.x + (size.x / 2), pos.y - (size.y / 2), 0.0f };
	v[1].color = col;
	v[1].texCoord = { 1.0f + texcoord.x, texcoord.y };

	v[2].position = { pos.x - (size.x / 2), pos.y + (size.y / 2), 0.0f };
	v[2].color = col;
	v[2].texCoord = { texcoord.x, 1.0f + texcoord.y };

	v[3].position = { pos.x + (size.x / 2), pos.y + (size.y / 2), 0.0f };
	v[3].color = col;
	v[3].texCoord = { 1.0f + texcoord.x, 1.0f + texcoord.y };


	// ���_�o�b�t�@�̃��b�N������
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�
	UINT stride = sizeof(Vertex);//���_�P������̃T�C�Y���w��
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�@�|���S���̕`�惋�[���I�Ȃ���
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`�施�ߔ��s
	g_pContext->Draw(4, 0);//�\���Ɏg�p���钸�_�����w��}
}

//=========================================================================================================
// �`�揈���i�e�N�X�`���{��]�j
//=========================================================================================================
void	DrawSpriteExRotation(XMFLOAT2 pos, XMFLOAT2 size, XMFLOAT4 col, int bno, int wc, int hc, float radian)
{

	g_pDevice = Direct3D_GetDevice();
	g_pContext = Direct3D_GetDeviceContext();

	// ���_�o�b�t�@�����b�N����
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾
	Vertex* v = (Vertex*)msr.pData;

	//�u���b�N�̏c���T�C�Y���v�Z
	float w = 1.0f / wc;
	float h = 1.0f / hc;
	//bno�̍���̃e�N�X�`�����W���v�Z
	float x = (bno % wc) * w;
	float y = (bno / wc) * h;

	// �w��̈ʒu�Ɏw��̃T�C�Y�A�F�̎l�p�`��`�悷�� /////////�e�N�X�`���ǉ�
	v[0].position = { -(size.x / 2), -(size.y / 2), 0.0f };
	v[0].color = col;
	v[0].texCoord = { x, y };

	v[1].position = { (size.x / 2), -(size.y / 2), 0.0f };
	v[1].color = col;
	v[1].texCoord = { x + w, y };

	v[2].position = { -(size.x / 2), (size.y / 2), 0.0f };
	v[2].color = col;
	v[2].texCoord = { x, y + h };

	v[3].position = { (size.x / 2), (size.y / 2), 0.0f };
	v[3].color = col;
	v[3].texCoord = { x + w, y + h };

	//��]����
	float co = cosf(radian);
	float si = sinf(radian);
	for (int i = 0; i < 4; i++)
	{
		float x = v[i].position.x;
		float y = v[i].position.y;
		v[i].position.x = (x * co - y * si) + pos.x;//��]�����Ă���\���ʒu�܂ŕ��s�ړ�
		v[i].position.y = (x * si + y * co) + pos.y;//
	}


	// ���_�o�b�t�@�̃��b�N������
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�
	UINT stride = sizeof(Vertex);//���_�P������̃T�C�Y���w��
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�@�|���S���̕`�惋�[���I�Ȃ���
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`�施�ߔ��s
	g_pContext->Draw(4, 0);//�\���Ɏg�p���钸�_�����w��


}



//=========================================================================================================
// �`�揈���i�A�j���[�V�����j
//=========================================================================================================
void	DrawSprite(XMFLOAT2 size, XMFLOAT4 col, int bno, int wc, int hc)
{

	g_pDevice = Direct3D_GetDevice();
	g_pContext = Direct3D_GetDeviceContext();

	// ���_�o�b�t�@�����b�N����
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾
	Vertex* v = (Vertex*)msr.pData;

	//�u���b�N�̏c���T�C�Y���v�Z
	float w = 1.0f / wc;
	float h = 1.0f / hc;
	//bno�̍���̃e�N�X�`�����W���v�Z
	float x = (bno % wc) * w;
	float y = (bno / wc) * h;

	// �w��̈ʒu�Ɏw��̃T�C�Y�A�F�̎l�p�`��`�悷�� /////////�e�N�X�`���ǉ�
	v[0].position = { -(size.x / 2), -(size.y / 2), 0.0f };
	v[0].color = col;
	v[0].texCoord = { x, y };

	v[1].position = { (size.x / 2), -(size.y / 2), 0.0f };
	v[1].color = col;
	v[1].texCoord = { x + w, y };

	v[2].position = { -(size.x / 2), (size.y / 2), 0.0f };
	v[2].color = col;
	v[2].texCoord = { x, y + h };

	v[3].position = { (size.x / 2), (size.y / 2), 0.0f };
	v[3].color = col;
	v[3].texCoord = { x + w, y + h };


	// ���_�o�b�t�@�̃��b�N������
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�
	UINT stride = sizeof(Vertex);//���_�P������̃T�C�Y���w��
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�@�|���S���̕`�惋�[���I�Ȃ���
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`�施�ߔ��s
	g_pContext->Draw(4, 0);//�\���Ɏg�p���钸�_�����w��


}