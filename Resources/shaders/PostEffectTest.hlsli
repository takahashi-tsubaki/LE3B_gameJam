
cbuffer cbuff0 : register(b0)
{

};

//���_�V�F�[�_�[�̏o�͍\����
//(���_�V�F�[�_����s�N�Z���V�F�[�_�ւ̂����Ɏg�p����)
struct VSOutput
{
	//�V�X�e���p���_���W
	float4 svpos : SV_POSITION;
	//uv�l
	float2 uv : TEXCOORD;
};