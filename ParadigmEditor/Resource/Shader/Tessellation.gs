////////////////////////////////////////
// Geometry shader HLSL 5
//_______________________________
// * Shrink triangles sample.

cbuffer TesselationBuffer
{
	float TesselationCoef;
	float3 padding;
};

struct GeometryInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;	
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};


[maxvertexcount(6)]
void GeometryToPixel( triangle GeometryInput input[3], inout TriangleStream<PixelInput> OutputStream )
{	
    PixelInput v;
	
	float4 p0 = normalize(input[0].position);
	float4 p1 = normalize(input[1].position);
	float4 p2 = normalize(input[2].position);
	float4 p3 = normalize(p1+p2);
	
	float2 uv0 = normalize(input[0].uv);
	float2 uv1 = normalize(input[1].uv);
	float2 uv2 = normalize(input[2].uv);
	float2 uv3 = normalize(uv1+uv2);

	float3 normal = normalize(cross(p3.xyz - p0.xyz, p1.xyz - p0.xyz));	
	v.position = p0;
	v.normal = normal;
	v.uv = uv0;
	OutputStream.Append( v );
	v.position = p1;
	v.normal = normal;
	v.uv = uv1;
	OutputStream.Append( v );
	v.position = p3;
	v.normal = normal;
	v.uv = uv2;
	OutputStream.Append( v );
	OutputStream.RestartStrip();

	normal = normalize(cross(p2.xyz - p0.xyz, p3.xyz - p0.xyz));	
	v.position = p0;
	v.normal = normal;
	v.uv = uv0;
	OutputStream.Append( v );
	v.position = p3;
	v.normal = normal;
	v.uv = uv3;
	OutputStream.Append( v );
	v.position = p2;
	v.normal = normal;
	v.uv = uv2;
	OutputStream.Append( v );

	OutputStream.RestartStrip();
}