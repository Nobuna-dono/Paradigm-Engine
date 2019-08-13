////////////////////////////////////////
// Geometry shader HLSL 5
//_______________________________
// * Display normal debug and wireframe.

struct GeometryInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;	
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;	
};

[maxvertexcount(12)]
void GeometryToPixel( triangle GeometryInput input[3], inout LineStream<PixelInput> OutputStream )
{	
    PixelInput v;

	for(uint i = 0; i < 3 ; i++)
	{
		v.position = input[i].position;
		v.normal = float3(1,0.847,0);//input[i].normal;
	
		OutputStream.Append( v );
		
  
		v.position = input[i].position + float4(input[i].normal * 0.05, 0.0);
		v.normal = float3(1,0.847,0);//input[i].normal;
	
		OutputStream.Append( v );

		OutputStream.RestartStrip();
	}

	float4 p0 = input[0].position;
	float4 p1 = input[1].position;
	float4 p2 = input[2].position;

	v.position = p0;
	v.normal = float3(1,1,1);
	OutputStream.Append( v );

	v.position = p1;
	v.normal = float3(1,1,1);
	OutputStream.Append( v );
	OutputStream.RestartStrip();

	v.position = p1;
	v.normal = float3(1,1,1);
	OutputStream.Append( v );

	v.position = p2;
	v.normal = float3(1,1,1);
	OutputStream.Append( v );
	OutputStream.RestartStrip();

	v.position = p2;
	v.normal = float3(1,1,1);
	OutputStream.Append( v );

	v.position = p0;
	v.normal = float3(1,1,1);
	OutputStream.Append( v );  
	OutputStream.RestartStrip();
}



/*[maxvertexcount(6)]
void GeometryToPixel( triangle GeometryInput input[3], inout TriangleStream<PixelInput> OutputStream )
{	
    PixelInput v;

	for(uint i = 0; i < 3 ; i++)
	{

		v.position = input[i].position;
		v.normal = input[i].normal;
		v.uv = input[i].uv;
	
		OutputStream.Append( v );

	}
	OutputStream.RestartStrip();
}*/