Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
}


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos  : POSITION;
    float3 Norm : NORMAL;
    float2 Tex : TEXCOORD1;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : TEXCOORD0;
    float2 Tex : TEXCOORD1;
};



//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul(input.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    output.Norm = mul(float4(input.Norm, 1), World).xyz;
    output.Tex = input.Tex;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
    float3 vLightDir = float3(3.f, 3.f, -3.f);
    float k = 1.f;
    float dotNL = dot(normalize(vLightDir), input.Norm);

    if (dotNL <= 0.1f) {
        k = 0.7f;
    }
    else if (dotNL <= 0.4f && dotNL > 0.1f) {
        k = 0.8f;
    }
    else if (dotNL > 0.4f) {
        k = 1.f;
    }

    return tex.Sample(samLinear, input.Tex) * k;
}
