//! コンスタントバッファ
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
	float		matPower		: packoffset(c4);
};

cbuffer cbLightParam : register(b3)
{
	float3		litDirection	: packoffset(c0);
	float4		litDiffuse		: packoffset(c1);
	float4		litAmbient		: packoffset(c2);
	float4		litSpeculer		: packoffset(c3);
};

Texture2D txDiffuse : register(t0);
Texture2D txNormalTex : register(t1);
SamplerState samLinear : register(s0);

//! 頂点属性
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
	float4		pos			: SV_POSITION;
	float3		normal		: NORMAL;
	float3		Tangent		: TANGENT;
	float3		Binormal	: BINORMAL;
	float2		Tex			: TEXCOORD0;
	float4		color		: COLOR0;
	float3		Eye			: COLOR1;
};




//! 頂点シェーダ
OutputVS RenderVS( InputVS inVert )
{
	OutputVS	outVert;
	int bind1[4] = (int[4])inVert.bindex1;
	int bind2[4] = (int[4])inVert.bindex2;
	int bind3[4] = (int[4])inVert.bindex3;
	int bind4[4] = (int[4])inVert.bindex4;
	float bweight1[4] = (float[4])inVert.weight1;
	float bweight2[4] = (float[4])inVert.weight2;
	float bweight3[4] = (float[4])inVert.weight3;
	float bweight4[4] = (float[4])inVert.weight4;
	float lweight = 0;

	float3 cPos = mul(inVert.pos, mtxWorld[bind1[0]]) * bweight1[0];
	float3 cNormal = mul(inVert.normal, mtxWorld[bind1[0]]) * bweight1[0];
	float3 t = mul(inVert.Tangent, mtxWorld[bind1[0]]) * bweight1[0];
	float3 b = mul(inVert.Binormal, mtxWorld[bind1[0]]) * bweight1[0];
	lweight += bweight1[0];
	if (bweight1[1] > 0)
	{
		cPos += mul(inVert.pos, mtxWorld[bind1[1]]) * bweight1[1];
		cNormal += mul(inVert.normal, mtxWorld[bind1[1]]) * bweight1[1];
		t += mul(inVert.Tangent, mtxWorld[bind1[1]]) * bweight1[1];
		b += mul(inVert.Binormal, mtxWorld[bind1[1]]) * bweight1[1];
		lweight += bweight1[1];

		if (bweight1[2] > 0)
		{
			cPos += mul(inVert.pos, mtxWorld[bind1[2]]) * bweight1[2];
			cNormal += mul(inVert.normal, mtxWorld[bind1[2]]) * bweight1[2];
			t += mul(inVert.Tangent, mtxWorld[bind1[2]]) * bweight1[2];
			b += mul(inVert.Binormal, mtxWorld[bind1[2]]) * bweight1[2];
			lweight += bweight1[2];

			if (bweight1[3] > 0)
			{
				cPos += mul(inVert.pos, mtxWorld[bind1[3]]) * bweight1[3];
				cNormal += mul(inVert.normal, mtxWorld[bind1[3]]) * bweight1[3];
				t += mul(inVert.Tangent, mtxWorld[bind1[3]]) * bweight1[3];
				b += mul(inVert.Binormal, mtxWorld[bind1[3]]) * bweight1[3];
				lweight += bweight1[3];

				if (bweight2[0] > 0 && lweight < 1)
				{
					cPos += mul(inVert.pos, mtxWorld[bind2[0]]) * bweight2[0];
					cNormal += mul(inVert.normal, mtxWorld[bind2[0]]) * bweight2[0];
					t += mul(inVert.Tangent, mtxWorld[bind2[0]]) * bweight2[0];
					b += mul(inVert.Binormal, mtxWorld[bind2[0]]) * bweight2[0];
					lweight += bweight2[0];

					if (bweight2[1] > 0)
					{
						cPos += mul(inVert.pos, mtxWorld[bind2[1]]) * bweight2[1];
						cNormal += mul(inVert.normal, mtxWorld[bind2[1]]) * bweight2[1];
						t += mul(inVert.Tangent, mtxWorld[bind2[1]]) * bweight2[1];
						b += mul(inVert.Binormal, mtxWorld[bind2[1]]) * bweight2[1];
						lweight += bweight2[1];

						if (bweight2[2] > 0)
						{
							cPos += mul(inVert.pos, mtxWorld[bind2[2]]) * bweight2[2];
							cNormal += mul(inVert.normal, mtxWorld[bind2[2]]) * bweight2[2];
							t += mul(inVert.Tangent, mtxWorld[bind2[2]]) * bweight2[2];
							b += mul(inVert.Binormal, mtxWorld[bind2[2]]) * bweight2[2];
							lweight += bweight2[2];

							if (bweight2[3] > 0)
							{
								cPos += mul(inVert.pos, mtxWorld[bind2[3]]) * bweight2[3];
								cNormal += mul(inVert.normal, mtxWorld[bind2[3]]) * bweight2[3];
								t += mul(inVert.Tangent, mtxWorld[bind2[3]]) * bweight2[3];
								b += mul(inVert.Binormal, mtxWorld[bind2[3]]) * bweight2[3];
								lweight += bweight2[3];

								if (bweight3[0] > 0 && lweight < 1)
								{
									cPos += mul(inVert.pos, mtxWorld[bind3[0]]) * bweight3[0];
									cNormal += mul(inVert.normal, mtxWorld[bind3[0]]) * bweight3[0];
									t += mul(inVert.Tangent, mtxWorld[bind3[0]]) * bweight3[0];
									b += mul(inVert.Binormal, mtxWorld[bind3[0]]) * bweight3[0];
									lweight += bweight3[0];

									if (bweight3[1] > 0)
									{
										cPos += mul(inVert.pos, mtxWorld[bind3[1]]) * bweight3[1];
										cNormal += mul(inVert.normal, mtxWorld[bind3[1]]) * bweight3[1];
										t += mul(inVert.Tangent, mtxWorld[bind3[1]]) * bweight3[1];
										b += mul(inVert.Binormal, mtxWorld[bind3[1]]) * bweight3[1];
										lweight += bweight3[1];

										if (bweight3[2] > 0)
										{
											cPos += mul(inVert.pos, mtxWorld[bind3[2]]) * bweight3[2];
											cNormal += mul(inVert.normal, mtxWorld[bind3[2]]) * bweight3[2];
											t += mul(inVert.Tangent, mtxWorld[bind3[2]]) * bweight3[2];
											b += mul(inVert.Binormal, mtxWorld[bind3[2]]) * bweight3[2];
											lweight += bweight3[2];

											if (bweight3[3] > 0)
											{
												cPos += mul(inVert.pos, mtxWorld[bind3[3]]) * bweight3[3];
												cNormal += mul(inVert.normal, mtxWorld[bind3[3]]) * bweight3[3];
												t += mul(inVert.Tangent, mtxWorld[bind3[3]]) * bweight3[3];
												b += mul(inVert.Binormal, mtxWorld[bind3[3]]) * bweight3[3];
												lweight += bweight3[3];

												if (bweight4[0] > 0 && lweight < 1)
												{
													cPos += mul(inVert.pos, mtxWorld[bind4[0]]) * bweight4[0];
													cNormal += mul(inVert.normal, mtxWorld[bind4[0]]) * bweight4[0];
													t += mul(inVert.Tangent, mtxWorld[bind4[0]]) * bweight4[0];
													b += mul(inVert.Binormal, mtxWorld[bind4[0]]) * bweight4[0];
													lweight += bweight4[0];

													if (bweight4[1] > 0)
													{
														cPos += mul(inVert.pos, mtxWorld[bind4[1]]) * bweight4[1];
														cNormal += mul(inVert.normal, mtxWorld[bind4[1]]) * bweight4[1];
														t += mul(inVert.Tangent, mtxWorld[bind4[1]]) * bweight4[1];
														b += mul(inVert.Binormal, mtxWorld[bind4[1]]) * bweight4[1];
														lweight += bweight4[1];

														if (bweight4[2] > 0)
														{
															cPos += mul(inVert.pos, mtxWorld[bind4[2]]) * bweight4[2];
															cNormal += mul(inVert.normal, mtxWorld[bind4[2]]) * bweight4[2];
															t += mul(inVert.Tangent, mtxWorld[bind4[2]]) * bweight4[2];
															b += mul(inVert.Binormal, mtxWorld[bind4[2]]) * bweight4[2];
															lweight += bweight4[2];

															if (bweight4[3] > 0)
															{
																cPos += mul(inVert.pos, mtxWorld[bind4[3]]) * bweight4[3];
																cNormal += mul(inVert.normal, mtxWorld[bind4[3]]) * bweight4[3];
																t += mul(inVert.Tangent, mtxWorld[bind4[3]]) * bweight4[3];
																b += mul(inVert.Binormal, mtxWorld[bind4[3]]) * bweight4[3];
																lweight += bweight4[3];
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	float4 Pos = mul(float4(cPos, 1.0f), mtxView);
	outVert.pos = mul(Pos, mtxProj);
	outVert.normal = normalize(cNormal);

	outVert.Eye = cPos - vecViewPos.xyz;

	outVert.color = inVert.color * colRevise;

	outVert.Tex = inVert.Tex + CoordsRevise.xy;

	outVert.Tangent = normalize(t);
	outVert.Binormal = normalize(b);

	return outVert;
}

//! ピクセルシェーダ
float4 RenderPS( OutputVS inPixel ) : SV_TARGET
{

	//法線をテクスチャから取得する
	//テクスチャの色では０～１なのでー１～１の範囲に変更する
	float3 n = normalize(2.0f * txNormalTex.Sample(samLinear, inPixel.Tex).xyz - 1.0f);
	//法線テクスチャからの結果をモデルのローカル空間に変換する
	//行列変換と同じ原理
	n = float3(
	dot(float3(inPixel.Tangent.x,inPixel.Binormal.x,inPixel.normal.x),n),
	dot(float3(inPixel.Tangent.y,inPixel.Binormal.y,inPixel.normal.y),n),
	dot(float3(inPixel.Tangent.z,inPixel.Binormal.z,inPixel.normal.z),n)
	);
	//ハーフランバートライティング
	float l = dot(n, -litDirection);
	l = l * 0.5f + 0.5f;
	l *= l;
	//ライティング結果から色を計算する
	float3 diff = l * litDiffuse.xyz * matDiffuse.xyz;
	float4 LP = float4(saturate(diff) , matDiffuse.w) * colRevise;
	return LP * txDiffuse.Sample(samLinear, inPixel.Tex);
	
}

//法線マップを使用しない描画
float4 RenderSimplePS(OutputVS inPixel) : SV_TARGET
{
	//ハーフランバートライティング
	float l = dot(inPixel.normal, -litDirection);
	l = l * 0.5f + 0.5f;
	l *= l;
	//ライティング結果から色を計算する
	float3 diff = l * litDiffuse.xyz * matDiffuse.xyz;
	float4 LP = float4(saturate(diff) , matDiffuse.w) * colRevise;
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