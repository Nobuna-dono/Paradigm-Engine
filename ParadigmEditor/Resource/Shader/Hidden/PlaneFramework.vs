////////////////////////////////////////
// Geometry shader HLSL 5
//_______________________________
// * Plane framework.

/*cbuffer MatrixBuffer
{
	matrix WorldMatrix;
	matrix ViewMatrix;
	matrix ProjectionMatrix;
};*/

struct VertexInput
{
    float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
    float2 uv : TEXCOORD0;
};

struct GeometryInput
{
    float4 position : SV_POSITION;
};

GeometryInput VertexToGeometry(VertexInput input)
{
	GeometryInput output;	
	output.position = float4(input.position, 1);
	return output;
}