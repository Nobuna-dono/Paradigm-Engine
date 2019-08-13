////////////////////////////////////////
// Geometry shader HLSL 5
//_______________________________
// * Display normal debug and wireframe.

struct GeometryInput
{
    float4 position : SV_POSITION;
};

struct PixelInput
{
    float4 position : SV_POSITION;
};

[maxvertexcount(12)]
void GeometryToPixel( triangle GeometryInput input[3], inout LineStream<PixelInput> OutputStream )
{	
    PixelInput v;
	
	
	
	float4 p0 = input[0].position;
	float4 p1 = input[1].position;
	float4 p2 = input[2].position;

	v.position = input[0].position;
	OutputStream.Append( v );
	v.position = input[0].position;
	OutputStream.Append( v );
	v.position = p1;
	OutputStream.Append( v );
	OutputStream.RestartStrip();

	v.position = p1;
	OutputStream.Append( v );
	v.position = p1;
	OutputStream.Append( v );
	v.position = p2;
	OutputStream.Append( v );
	OutputStream.RestartStrip();

	v.position = p2;
	OutputStream.Append( v );
	v.position = p2;
	OutputStream.Append( v );
	v.position = p0;
	OutputStream.Append( v );  
	OutputStream.RestartStrip();
}