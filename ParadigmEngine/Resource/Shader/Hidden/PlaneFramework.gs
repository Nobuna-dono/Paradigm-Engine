////////////////////////////////////////
// Geometry shader HLSL 5
//_______________________________
// * Display normal debug and wireframe.

cbuffer MatrixBuffer
{
	matrix WorldMatrix;
	matrix ViewMatrix;
	matrix ProjectionMatrix;
	float4 CameraPosition;
}; 

struct GeometryInput
{
    float4 position : SV_POSITION;
};

struct PixelInput
{
    float4 position : SV_POSITION;
};

[maxvertexcount(80)]
void GeometryToPixel( point GeometryInput input[1], inout LineStream<PixelInput> OutputStream )
{		
    PixelInput v;
		
	float grillSize = (1 + (trunc((CameraPosition.y/ 10)) * 10));
	
	float lineSize  = grillSize * 10;
	float cameraPosX;
	float cameraPosZ;
	if(grillSize > 10)
	{
		grillSize -= 1;
		cameraPosX = (trunc(CameraPosition.x / 10) * 10 * (trunc((CameraPosition.y/ 10))));	
		cameraPosZ = (trunc(CameraPosition.z / 10) * 10 * (trunc((CameraPosition.y/ 10))));
	}
	else
	{
		cameraPosX = trunc(CameraPosition.x);
		cameraPosZ = trunc(CameraPosition.z); 
	}
	
	float4 positionCam = float4(input[0].position.x *grillSize, 0, input[0].position.z *grillSize, 1) + float4( cameraPosX , 0 , cameraPosZ ,0);
	
	float4 position;
	for(int i = -10; i < 10; i++)
	{
		position = positionCam + float4(lineSize, 0, grillSize*i, 0);		
		v.position = mul(position, WorldMatrix);
		v.position = mul(ViewMatrix, v.position);
		v.position = mul(ProjectionMatrix, v.position);
		OutputStream.Append( v );

		position = positionCam + float4(-lineSize, 0, grillSize*i , 0); 
		v.position = mul(position, WorldMatrix);
		v.position = mul(ViewMatrix, v.position);
		v.position = mul(ProjectionMatrix, v.position);
		OutputStream.Append( v );		
		OutputStream.RestartStrip();	
	}	

	for(int i = -10; i < 10; i++)
	{
		position = positionCam + float4(grillSize *i , 0, lineSize, 0);		
		v.position = mul(position, WorldMatrix);
		v.position = mul(ViewMatrix, v.position);
		v.position = mul(ProjectionMatrix, v.position);
		OutputStream.Append( v );

		position = positionCam + float4(grillSize * i , 0, -lineSize, 0); 
		v.position = mul(position, WorldMatrix);
		v.position = mul(ViewMatrix, v.position);
		v.position = mul(ProjectionMatrix, v.position);
		OutputStream.Append( v );		
		OutputStream.RestartStrip();	
	}		
}