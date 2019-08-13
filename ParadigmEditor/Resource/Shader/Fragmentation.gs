////////////////////////////////////////
// Geometry shader HLSL 5
//_______________________________
// * Shrink triangles sample.

cbuffer FragBuffer
{
	float FragCoef;
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
};


[maxvertexcount(3)]
void GeometryToPixel( triangle GeometryInput input[3], inout TriangleStream<PixelInput> OutputStream )
{	
    PixelInput v;
	
	float4 p0 = input[0].position;
	float4 p1 = input[1].position;
	float4 p2 = input[2].position;
	
	float fragCoef = FragCoef;
	if(fragCoef == 0)
		fragCoef = 0.25;

	for(int i = 0; i < 3; i++)
	{
		float3 face_normal = normalize(cross(p2.xyz - p0.xyz, p1.xyz - p0.xyz));
		float4 newPos = input[i].position + float4(fragCoef * face_normal, 0);
		
		v.normal = input[i].normal;	
		v.position = newPos;
		OutputStream.Append( v );
	}

	OutputStream.RestartStrip();
}