////////////////////////////////////////
// Vertex shader HLSL 5
//_______________________________
// * Basic vertex shader.

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
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;	
};

PixelInput VertexToPixel(VertexInput input)
{
    PixelInput output;    
	
	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(float4(input.position, 1), WorldMatrix);
    output.position = mul(ViewMatrix, output.position);
    output.position = mul(ProjectionMatrix, output.position);
    
	// Store the input color for the pixel shader to use.
    output.normal = input.normal;
    
    return output;
}

struct GeometryInput
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;	
};

GeometryInput VertexToGeometry(VertexInput input)
{
    GeometryInput output;    
	
	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(float4(input.position, 1), WorldMatrix);
    output.position = mul(ViewMatrix, output.position);
    output.position = mul(ProjectionMatrix, output.position);

    output.normal = input.normal; 

	return output;
}