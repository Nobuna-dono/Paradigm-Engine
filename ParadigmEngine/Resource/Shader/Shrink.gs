////////////////////////////////////////
// Geometry shader HLSL 5
//_______________________________
// * Shrink triangles sample.

cbuffer ShrinkBuffer
{
	float ShrinkCoef;
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

/*
[maxvertexcount(3)]
void GeometryToPixel( triangle GeometryInput input[3], inout TriangleStream<PixelInput> OutputStream )
{	
    PixelInput v;
	
	float4 p0 = input[0].position;
	float4 p1 = input[1].position;
	float4 p2 = input[2].position;
	
	float4 center = (p0 + p1 + p2) / 3;
	float shrink = 1;

	v.normal = input[0].normal;	
	v.position = center + shrink * (p0 - center);
	v.uv = input[0].uv;
	OutputStream.Append( v );

	v.normal = input[1].normal;
	v.position = center + shrink * (p1 - center);
	v.uv = input[1].uv;
	OutputStream.Append( v );

	v.normal = input[2].normal;
	v.position = center + shrink * (p2 - center);
	v.uv = input[2].uv;
	OutputStream.Append( v );

	OutputStream.RestartStrip();
}
*/

[maxvertexcount(6)]
void GeometryToPixel( triangle GeometryInput input[3], inout TriangleStream<PixelInput> OutputStream )
{	
    PixelInput v;
		
	float4 p0 = normalize(input[0].position);
	float4 p1 = normalize(input[1].position);
	float4 p2 = normalize(input[2].position);
	float4 p3 = normalize(p1+p2);
	
	float2 uv0 = input[0].uv;
	float2 uv1 = input[1].uv;
	float2 uv2 = input[2].uv;
	float2 uv3 = normalize(uv1+uv2);

	float4 center = (p0 + p1 + p2) / 3;
	float shrink = 1;
	float fragCoef = 0.01;
	
	float3 face_normal = normalize(cross(p1.xyz - p0.xyz, p3.xyz - p0.xyz));
	float4 newPos; 

	float3 normal = normalize(cross(p3.xyz - p0.xyz, p1.xyz - p0.xyz));	
	p0 = p0 + float4(fragCoef * face_normal, 0);
	v.position = center + shrink * (p0 - center);
	v.normal = normal;
	v.uv = uv0;
	OutputStream.Append( v );
	p1 = p1 + float4(fragCoef * face_normal, 0);
	v.position = center + shrink * (p1 - center);
	v.normal = normal;
	v.uv = uv1;
	OutputStream.Append( v );
	p3 = p3 + float4(fragCoef * face_normal, 0);
	v.position = center + shrink * (p3 - center);;
	v.normal = normal;
	v.uv = uv3;
	OutputStream.Append( v );
	OutputStream.RestartStrip();
	
	face_normal = normalize(cross(p3.xyz - p0.xyz, p2.xyz - p0.xyz));
	normal = normalize(cross(p2.xyz - p0.xyz, p3.xyz - p0.xyz));	
	p0 = p0 + float4(fragCoef * face_normal, 0);
	v.position = center + shrink * (p0 - center);;
	v.normal = normal;
	v.uv = uv0;
	OutputStream.Append( v );
	p3 = p3 + float4(fragCoef * face_normal, 0);
	v.position = center + shrink * (p3 - center);;
	v.normal = normal;
	v.uv = uv3;
	OutputStream.Append( v );
	p2 = p2 + float4(fragCoef * face_normal, 0);
	v.position = center + shrink * (p2 - center);;
	v.normal = normal;
	v.uv = uv2;
	OutputStream.Append( v );

	OutputStream.RestartStrip();
}
