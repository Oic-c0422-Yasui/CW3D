//! �R���X�^���g�o�b�t�@
cbuffer cbSceneParam : register(b0)
{
	float4		vecViewPos		: packoffset(c0);
	matrix		mtxView			: packoffset(c1);
	matrix		mtxProj			: packoffset(c5);
};

cbuffer cbMeshParam : register(b1)
{
	float4x3	mtxWorld[128]	: packoffset(c0);
	float4		colRevise		: packoffset(c384);
	float4		CoordsRevise	: packoffset(c385);
};

cbuffer cbMaterialParam : register(b2)
{
	float4		matDiffuse		: packoffset(c0);
	float4		matAmbient		: packoffset(c1);
	float4		matSpeculer		: packoffset(c2);
	float4		matEmissive		: packoffset(c3);
	float		matPower : packoffset(c4);
};

cbuffer cbLightParam : register(b3)
{
	float3		litDirection	: packoffset(c0);
	float4		litDiffuse		: packoffset(c1);
	float4		litAmbient		: packoffset(c2);
	float4		litSpeculer		: packoffset(c3);
};

Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register(s0);

//! ���_����
struct InputVS
{
	float4		pos			: POSITION;
	float3		normal		: NORMAL;
	float3		Tangent		: TANGENT;
	float3		Binormal	: BINORMAL;
	float2		Tex			: TEXCOORD;
	float4		color		: COLOR0;
	float4		weight1		: BLENDWEIGHT0;
	uint4		bindex1		: BLENDINDICES0;
	float4		weight2		: BLENDWEIGHT1;
	uint4		bindex2		: BLENDINDICES1;
	float4		weight3		: BLENDWEIGHT2;
	uint4		bindex3		: BLENDINDICES2;
	float4		weight4		: BLENDWEIGHT3;
	uint4		bindex4		: BLENDINDICES3;
};

struct OutputVS
{
	float4	pos			: SV_POSITION;
	float3	normal		: NORMAL;
	float3	Tangent		: TANGENT;
	float3	Binormal	: BINORMAL;
	float2	Tex			: TEXCOORD0;
};

//�V�K�̃e�N�X�`���I�u�W�F�N�g�̍쐬
Texture2D txNormalTex : register(t1);



//! ���_�V�F�[�_
OutputVS RenderVS( InputVS inVert )
{
	OutputVS	outVert;

	matrix	mtxVP = mul( mtxView, mtxProj );
	float4 Pos = mul( inVert.pos, mtxWorld );
	outVert.pos = mul( Pos , mtxVP );

	outVert.normal = normalize(mul(inVert.normal, (float3x3)mtxWorld));
	outVert.Tangent = normalize(mul(inVert.Tangent, (float3x3)mtxWorld));
	outVert.Binormal = normalize(mul(inVert.Binormal, (float3x3)mtxWorld));

	outVert.Tex = inVert.Tex;
	return outVert;
}

//! �s�N�Z���V�F�[�_
float4 RenderPS( OutputVS inPixel ) : SV_TARGET
{
	//�@�����e�N�X�`������擾����
	//�e�N�X�`���̐F�ł͂O�`�P�Ȃ̂Ł[�P�`�P�͈̔͂ɕύX����
	float3 n = normalize(2.0f * txNormalTex.Sample(samLinear, inPixel.Tex).xyz - 1.0f);
	//�@���e�N�X�`������̌��ʂ����f���̃��[�J����Ԃɕϊ�����
	//�s��ϊ��Ɠ�������
	n = float3(
	dot(float3(inPixel.Tangent.x,inPixel.Binormal.x,inPixel.normal.x),n),
	dot(float3(inPixel.Tangent.y,inPixel.Binormal.y,inPixel.normal.y),n),
	dot(float3(inPixel.Tangent.z,inPixel.Binormal.z,inPixel.normal.z),n)
	);
	//�n�[�t�����o�[�g���C�e�B���O
	float l = dot(n, -litDirection);
	l = l * 0.5f + 0.5f;
	l *= l;
	//���C�e�B���O���ʂ���F���v�Z����
	float3 diff = l * litDiffuse.xyz * matDiffuse.xyz;
	float4 LP = float4(saturate(diff) , matDiffuse.w);
	return LP * txDiffuse.Sample(samLinear, inPixel.Tex);
	
}

//�@���}�b�v���g�p���Ȃ��`��
float4 RenderSimplePS(OutputVS inPixel) : SV_TARGET
{
	//�n�[�t�����o�[�g���C�e�B���O
	float l = dot(inPixel.normal, -litDirection);
	l = l * 0.5f + 0.5f;
	l *= l;
	//���C�e�B���O���ʂ���F���v�Z����
	float3 diff = l * litDiffuse.xyz * matDiffuse.xyz;
	float4 LP = float4(saturate(diff) , matDiffuse.w);
	return LP * txDiffuse.Sample(samLinear, inPixel.Tex);
}

technique11 TShader
{
	pass P0
	{		
		  SetVertexShader( CompileShader( vs_4_0, RenderVS() ) );
		  SetGeometryShader( NULL );
		  SetHullShader( NULL );
		  SetDomainShader( NULL );
		  SetPixelShader(  CompileShader( ps_4_0, RenderPS() ) );
		  SetComputeShader( NULL );
	}
}

technique11 TSimpleShader
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, RenderVS()));
		SetGeometryShader(NULL);
		SetHullShader(NULL);
		SetDomainShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, RenderSimplePS()));
		SetComputeShader(NULL);
	}
}