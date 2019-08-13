////////////////////////////////////////
// Vertex shader HLSL 5
//_______________________________


cbuffer MatrixBuffer
{
	matrix WorldMatrix;
	matrix ViewMatrix;
	matrix ProjectionMatrix;
};

struct VertexInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 uv : TEXCOORD0;
};

struct PixelInput
{
    	float4 position : SV_POSITION;
};

PixelInput VertexToPixel(VertexInput input)
{
	PixelInput output;
	output.position = mul(float4(input.position, 1), WorldMatrix);
 	output.position = mul(ViewMatrix, output.position);
    	output.position = mul(ProjectionMatrix, output.position);

	return output;
}