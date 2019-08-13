#define WIN32_LEAN_AND_MEAN
//#define TEMPOPENGl


#include <map>
#include <unordered_map>

#include <GameFramework/GameEntity/GEntity.h>
#include <GameFramework/GameGear/Physics/GCollider.h>
#include <GameFramework/GameGear/Physics/GRigidbody.h>
#include <GameFramework/GameGear/Physics/GTransform.h>
#include <GameFramework/GameGear/LowRenderer/GCamera.h>
#include <GameFramework/GameGear/LowRenderer/GMeshShape.h>
#include <GameFramework/GameGear/LowRenderer/GMeshRender.h>
#include <GameFramework/GameGear/LowRenderer/GMaterialViewver.h>

#include <FParadigmEngine.h>
#include <Resource/FResourceSupervisor.h>
#include <Core/Serialization/ParadigmSerialization.h>
#include <Physics/Collider.h>

void DataStructurePerformanceTest();
UKeyRegister ContextChecking();
void GraphicsChecking();
void PhysicsChecking();
void ResourceChecking();
void FactoryChecking();
void ArchiveChecking();
void ArchiveChecking_BETA();
void ArchiveChecking_OMEGA();

#define CHRONOSA(Texte, X) { AUTOCHRONO(Texte); X; }

namespace ParadigmEngine
{
	//FLayerSupervisor UMetaEntity::EntityLayers;
	void NativeSynchronizationChecking();
	void MaterialViewverChecking()
	{
		GEntity entity = GEntity::Instanciate();
		entity.GetMetaEntity()->Tag = RENDER_LAYERS.AddLayer("NativeFactory");
		entity.GetMetaEntity()->GetTransform()->Position = { 0,0,-1 };

		GMaterialViewver matv = entity.AddGear<GMaterialViewver>();
		matv.Data.VertexFilename = "Resource/Shader/Hidden/PlaneFramework.vs";
		matv.Data.VertexEntry = "VertexToGeometry";
		matv.Data.GeometryFilename = "Resource/Shader/Hidden/PlaneFramework.gs";
		matv.Data.GeometryEntry = "GeometryToPixel";
		matv.Data.PixelFilename = "Resource/Shader/Hidden/PlaneFramework.ps";
		matv.Data.PixelEntry = "PixelToFrameBuffer";

		/*matv.Data.VertexFilename = "Resource/Shader/BasicVertex.vs";
		matv.Data.VertexEntry = "VertexToGeometry";
		matv.Data.PixelFilename = "Resource/Shader/BasicPixel.ps";
		matv.Data.PixelEntry = "PixelToFrameBuffer"; */
		// matv.Data.kModel = PARADIGM_RESOURCE->ModelKey("Resource/kModel/Primitive/" + FENUMERATOR(EPrimitiveShape::Sphere)::ToString() + ".fbx");

		GEntity entity2 = GEntity::Instanciate();
		entity2.GetMetaEntity()->GetTransform()->Position = { 1,2,3 };
		entity2.GetMetaEntity()->GetTransform()->Rotation = FQuaternion::FromEulerAngles(45, 0, 0);
		GTransform tr2 = entity2.GetGear<GTransform>();
		GMeshShape meshShape = entity2.AddGear<GMeshShape>();
		GMeshRender meshRender = entity2.AddGear<GMeshRender>();
		GCollider hCollider = entity2.AddGear<GCollider>();
		hCollider.Shape = EColliderShape::CAPSULE;

		entity2.GetMetaEntity()->Tag = RENDER_LAYERS.AddLayer("MaterialViewver");
		meshShape.SetModel("Resource/Mesh/ironman/ironman.fbx");
		meshRender.Data.Materials.Add({ PARADIGM_RESOURCE->Shader("Resource/Shader/Foo.shader") });
		FMaterial& material = meshRender.Data.Materials[0];
		material.SetTexture("Albedo", PARADIGM_RESOURCE->Texture("Resource/Mesh/ironman/ironman.dds"));

		GMeshShape shape = entity.AddGear<GMeshShape>();
		UModel model;
		TArray<TArray<UVertex>> vertices;
		vertices.Add({});
		uint a = 0;
		TArray<uint> triangles;
		for (float i = -5; i < 5; i++)
		{
			for (float j = -5; j < 5; ++j)
			{
				triangles.Add(a);
				a++;
				vertices[0].Add({ {i * 20, 0, j * 20}, {}, {}, {} });
			}
		}
		matv.Data.kModel = FModel::CreateModelFromMemory(vertices, triangles);
		shape.Data.Topology = ENativePrimitiveTopology::EPrimitiveTopology_PointList;
		FModel::SyncResource(PARADIGM_RESOURCE->Model(matv.Data.kModel));
		shape.SetModel(PARADIGM_RESOURCE->Model(matv.Data.kModel));
		shape.SetModel(PARADIGM_RESOURCE->Model(matv.Data.kModel));

		try
		{
			UShader& shader = PARADIGM_RESOURCE->Shader("Resource/Shader/Hidden/PlaneFramework.shader");
			FShader::SetShard(shader, PARADIGM_RESOURCE->ShardShader("Resource/Shader/Hidden/PlaneFramework.vs", "VertexToGeometry"));
			FShader::SetShard(shader, PARADIGM_RESOURCE->ShardShader("Resource/Shader/Hidden/PlaneFramework.gs", "GeometryToPixel"));
			FShader::SetShard(shader, PARADIGM_RESOURCE->ShardShader("Resource/Shader/Hidden/PlaneFramework.ps", "PixelToFrameBuffer"));

			GMeshRender render = entity.AddGear<GMeshRender>();
			render.SetMaterial(shader);
		}
		PARADIGM_CATCH_EXCEPTION

			//PARADIGM_RESOURCE
			UModel myModel;
		matv.Data.MaterialData.TextureValues.Add(std::pair<FString, UTexture>("Albedo", PARADIGM_RESOURCE->Texture("Resource/Mesh/ironman/ironman.dds")));
		/*
		UArchive archive;
		{
			AUTOCHRONO("Archived time : ");
			archive = entity2.GetMetaEntity()->GetArchived();
		}
		size_t hETargetViewport = typeid(ETargetViewport).hash_code();
		size_t hEClearFlag = typeid(EClearFlag).hash_code();

		uint countGear;
		FArchive::Deserialize<uint>(archive, countGear);
		
		TArray<UArchive> GearArchives;

		// GEARS CONSTRUCTION
		for (uint i = 0; i < countGear; ++i)
		{
			GearArchives.Add({});
			archive.LinkArchive(&GearArchives.Back());

			size_t gearId;
			FString gearName;
			FArchive::Deserialize<FString>(archive, gearName);
			FArchive::Deserialize<size_t>(archive, gearId); //Skip #type
			uint countValues;
			FArchive::Deserialize<uint>(archive, countValues);

			// VALUES CONSTRUCTION
			for (uint i = 0; i < countValues; ++i)
			{
				bool bMustBeDearchived;
				size_t typeCode;
				size_t typeField;
				FString valueName;

				////////////////////////////////////////////////////////////
				// NEW !!!
				//___________________________________________
				FArchive::Deserialize<bool>(archive, bMustBeDearchived); // Store this value to know if the value can be set from name!
				
				FArchive::Deserialize<size_t>(archive, typeField); // ONLY FOR ENGINE ARCHIVE else uint field
				FArchive::Deserialize<FString>(archive, valueName);
				FArchive::Deserialize<size_t>(archive, typeCode); // In case of Iarchivable value (none fundamental type)
				

				if (typeCode == typeid(bool).hash_code())
				{
					bool b;
					FArchive::Deserialize(archive, b);
					FPrint::Print("Name : " + valueName + " - Type : Bool - Value : " + FString::ToString(b));
					if(bMustBeDearchived)
						entity2.GetMetaEntity()->SetGearValueFromName(gearId,0, valueName, false);
					//else
						//entity2.GetMetaEntity()->Get
				}
				else if (typeCode == typeid(FString).hash_code())
				{
					FString b;
					FArchive::Deserialize(archive, b);
					FPrint::Print("Name : " + valueName + " - Type : FString - Value : " + b);
				}
				else if (typeCode == typeid(uint).hash_code() || typeCode == typeid(int).hash_code() || typeCode == typeid(float).hash_code())
				{
					uint b;
					FArchive::Deserialize(archive, b);
					FPrint::Print("Name : " + valueName + " - Type : FString - Value : " + FString::ToString(b));
				}
				else if (typeCode == typeid(short).hash_code())
				{
					short b;
					FArchive::Deserialize(archive, b);
					FPrint::Print("Name : " + valueName + " - Type : FString - Value : " + FString::ToString(b));
				}
				else if (typeCode == typeid(UVector3).hash_code())
				{
					UVector3 b;
					FArchive::Deserialize(archive, b);
					FPrint::Print("Name : " + valueName + " - Type : UVector3 - Value : " + FVector3(b));
					if (bMustBeDearchived)
						entity2.GetMetaEntity()->SetGearValueFromName<UVector3>(gearId, 0, valueName, {4,5, 6});
				}
				else if (typeCode == typeid(UQuaternion).hash_code())
				{
					UQuaternion b;
					FArchive::Deserialize(archive, b);
					FPrint::Print("Name : " + valueName + " - Type : UQuaternion - Value : ");// +FQuaternion(b) );
					if (bMustBeDearchived)
						entity2.GetMetaEntity()->SetGearValueFromName<UQuaternion>(gearId, 0, valueName, FQuaternion::FromEulerAngles(45,0,0));
				}
				else if(PARADIGM_ARCHIVE.IsEnum(typeCode))
				{
					uint b;
					auto strs = PARADIGM_ARCHIVE.GetEnumValues(typeCode);
					FArchive::Deserialize<uint>(archive, b);
					FPrint::Print("Name : " + valueName + " - Type : Enum - Value : " + strs[b]);
					if (bMustBeDearchived)
						entity2.GetMetaEntity()->SetGearValueFromName(gearId, 0, valueName, 5);
				}
			

		}
		

		// GEARS DEARCHIVAGE
		GMeshShape meshShape2 = entity2.GetGear<GMeshShape>();
		for (uint i = 0; i < GearArchives.Count(); ++i)
		{
			UArchive& archiveA = GearArchives[i];
			bool result = entity2.GetMetaEntity()->ReplaceValueInGear(archiveA, "Model", FString("Resource/Mesh/Cube.fbx"));
		}*/
	}
}

#ifdef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
int ParadigmMain()
{
#ifndef _PARADIGM_EDITOR
	try
	{
		PARADIGM.Initialize();

		// CreateViewport from handle
		/*{
			PARADIGM_CONTEXT->CreateContext(ETargetViewport::VIEWPORT_0);
			const UContextAttributes& contextDesc = PARADIGM_CONTEXT->GetContextAttributes();
			PARADIGM_GRAPHICS->CreateViewport(ETargetViewport::VIEWPORT_1, false, true);
			//PARADIGM_GRAPHICS->CreateViewport(ETargetViewport::VIEWPORT_0, false, true);
			PARADIGM_INPUT->CreateInputSystem(ETargetViewport::VIEWPORT_1, { EInputDeviceType::InputDeviceType_Mouse | EInputDeviceType::InputDeviceType_Keyboard });
		}*/

		//PARADIGM.Time.SetTimeScale(10.f);
		//ParadigmEngine::MaterialViewverChecking();
		FactoryChecking();
		//ParadigmEngine::NativeSynchronizationChecking();
		//ArchiveChecking();
		//ArchiveChecking_BETA();
		//ArchiveChecking_OMEGA();
		while (!PARADIGM.Frame(true));
		//PARADIGM.Terminate();
		//PhysicsChecking();
		//ContextChecking();
		//GraphicsChecking();
	}
	catch (const ParadigmException& paradigmException)
	{
		FPrint::Print(paradigmException.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
		PARADIGM_PAUSE;
		return EXIT_FAILURE;
	}
	catch (const std::exception& exception)
	{ 
		FPrint::Print(exception.what(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
		PARADIGM_PAUSE;
		return EXIT_FAILURE;
	}
#endif
	return EXIT_SUCCESS;
}



int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, PSTR _pScmdline, int _cmdshow)
{
#ifndef _PARADIGM_EDITOR
	return ParadigmMain();
#endif
}

#elif OPENGL4_5
int main()
{
	try
	{
		DataStructurePerformanceTest();
	}
	catch (const std::exception& exception)
	{
		FPrint::Print(exception.what(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
		throw;
	}
	catch (const ParadigmException& paradigmException)
	{
		FPrint::Print(paradigmException.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
	}
	PARADIGM_PAUSE
}
#endif 


void DataStructurePerformanceTest()
{
	std::string string;
	FString fstring;

	std::vector<FString> vector;
	TArray<FString> tarray;

	TKeyTable<FString> keytable;
	keytable.Add("lol");
	FString b = keytable.Back();
	TStaticKeyTable<FString> statickeytable;

	std::map<int, FString> map;
	std::unordered_map<int, FString> umap;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// INITIALIZE
	//________________________________________________________________________________________________________
	unsigned int fillcount = 0xEFFF;
	//PARADIGM_PAUSE;
	FPrint::Print("Initialization of [" + FString::ToString<uint>(fillcount) + "] elements in: \n");
	CHRONOSA("[std::string] : ", string.reserve(fillcount));
	CHRONOSA("[FString] : ", fstring.Reserve(fillcount));

	CHRONOSA("[std::vector] : ", vector.reserve(fillcount));
	CHRONOSA("[TArray] : ", tarray.Reserve(fillcount));

	CHRONOSA("[TKeyTable] : ", keytable.Reserve(fillcount));
	CHRONOSA("[TStaticKeyTable] : ", statickeytable.Reserve(fillcount));

	FPrint::Print("[std::map] : NULL\n");
	FPrint::Print("[std::unordered_map] : NULL\n");


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FILL
	//________________________________________________________________________________________________________
	//PARADIGM_PAUSE;
	FPrint::Print("\nFill of [" + FString::ToString<uint>(0xFFFF) + "] elements in:\n");
	{
		AUTOCHRONO("[std::string] : ");

		for (uint i = 0; i < fillcount; ++i)
			string += "FILL";
	}
	{
		AUTOCHRONO("[FString] : ");

		for (uint i = 0; i < fillcount; ++i)
			fstring += "FILL";
	}

	{
		AUTOCHRONO("[std::vector] : ");

		for (uint i = 0; i < fillcount; ++i)
			vector.push_back({ "FILL" });
	}
	{
		AUTOCHRONO("[TArray] : ");

		for (uint i = 0; i < fillcount; ++i)
			tarray.Add({ "FILL !!!" });
	}

	{
		AUTOCHRONO("[TKeyTable] : ");

		for (unsigned int i = 0; i < fillcount; ++i)
			keytable.Add({ "FILL !!!" });
	}
	{
		AUTOCHRONO("[TStaticKeyTable] : ");

		for (unsigned int i = 0; i < fillcount; ++i)
			statickeytable.Add({ "FILL" });
	}


	{
		AUTOCHRONO("[std::map] : ");

		for (unsigned int i = 0; i < fillcount; ++i)
			map.emplace(std::pair<int, FString>(i, { "FILL !!!" }));
	}
	{
		AUTOCHRONO("[std::unordered_map] : ");

		for (unsigned int i = 0; i < fillcount; ++i)
			umap.emplace(std::pair<int, FString>(i, { "FILL !!!" }));
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// COPY
	//________________________________________________________________________________________________________
	PARADIGM_PAUSE;
	TStaticKeyTable<FString> TEST;
	TEST.Copy(keytable);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// TEST REMOVE
	//________________________________________________________________________________________________________
	/*PARADIGM_PAUSE
	{
		AUTOCHRONO("[statickeytable] REMOVE 10k element in :")
			for (unsigned int i = 0; i < 10000; ++i)
				statickeytable.Remove(UKeyRegister(i + 500, 1));
	}
	{
		AUTOCHRONO("[KeyTable] REMOVE 10k element in :")
			for (unsigned int i = 0; i < 10000; ++i)
				keytable.Remove(UKeyRegister(i, 1));
	}
	{
		AUTOCHRONO("[TArray] REMOVE 10k element in :")
		tarray.Remove(0, 10000);
	}*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ITERATION
	//________________________________________________________________________________________________________
	//PARADIGM_PAUSE;

	FPrint::Print("\nIteration (and modify value) of [" + FString::ToString<uint>(0xFFFF) + "] elements in:\n");
	{
		AUTOCHRONO("[std::string] : ");
		for (std::string::iterator it = string.begin(); it != string.end(); ++it)
			*it += '0';
	}
	{
		AUTOCHRONO("[FString] : ");
		for (FString::Iterator it = fstring.Begin(); it != fstring.End(); ++it)
			*it += '0';
	}
	{
		AUTOCHRONO("[std::vector] : ");
		for (std::vector<FString>::iterator it = vector.begin(); it != vector.end(); ++it)
			*it += '0';
	}
	{
		AUTOCHRONO("[TArray] : ");
		for (TArray<FString>::Iterator it = tarray.Begin(); it != tarray.End(); ++it)
			*it += '0';
	}
	{
		AUTOCHRONO("[TKeyTable] : ");
		for (TKeyTable<FString>::Iterator it = keytable.Begin(); it != keytable.End(); ++it)
			*it += '0';
	}
	{
		AUTOCHRONO("[TStaticKeyTable] Ref [TKeyTable]: ");
		for (TStaticKeyTable<FString>::Iterator it = TEST.Begin(); it != TEST.End(); ++it)
			*it += '0';

		PARADIGM_PAUSE;
	}
	{
		AUTOCHRONO("[TStaticKeyTable] : ");
		for (TStaticKeyTable<FString>::Iterator it = statickeytable.Begin(); it != statickeytable.End(); ++it)
			*it += '0';

		PARADIGM_PAUSE;
	}
	{
		AUTOCHRONO("[std::map] : ");
		for (std::map<int, FString>::iterator it = map.begin(); it != map.end(); ++it)
			it->second += '0';
	}
	{
		AUTOCHRONO("[std::unordered_map] : ");
		for (std::unordered_map<int, FString>::iterator it = umap.begin(); it != umap.end(); ++it)
			it->second += '0';
	}
	FString a = keytable.Back();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Find or Remove
	//________________________________________________________________________________________________________
	//PARADIGM_PAUSE;

	FPrint::Print("\nFind or Remove:\n");
	int toFind = 4654;
	bool bFind = false;
	{
		vector[toFind] = "Iasd";
		AUTOCHRONO("[std::vector] : ");
		for (std::vector<FString>::iterator it = vector.begin(); it != vector.end(); ++it)
		{
			if (*it == "Iasd")
			{
				bFind = true;
				break;
			}
		}
	}
	std::cout << std::boolalpha << "Found : " << bFind << "\n";
	tarray[toFind] = "Iasd";
	CHRONOSA("[TArray] : ", bFind = tarray.Contains({ "Iasd" }));
	std::cout << std::boolalpha << "Found : " << bFind << "\n";

	CHRONOSA("[TKeyTable] : ", bFind = keytable.Contains(UKeyRegister(toFind, 1)));
	std::cout << std::boolalpha << "Found : " << bFind << "\n";

	CHRONOSA("[TStaticKeyTable] : ", bFind = statickeytable.Contains(UKeyRegister(toFind, 1)));
	std::cout << std::boolalpha << "Found : " << bFind << "\n";


	CHRONOSA("[std::map] : ", bFind = map.find(toFind) != map.end() ? true : false);
	std::cout << std::boolalpha << "Found : " << bFind << "\n";

	CHRONOSA("[std::unordered_map] : ", bFind = umap.find(toFind) != umap.end() ? true : false);
	std::cout << std::boolalpha << "Found : " << bFind << "\n";

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CLEAR
	//________________________________________________________________________________________________________
	PARADIGM_PAUSE;

	FPrint::Print("\nClear :\n");
	CHRONOSA("[std::string] : ", string.clear());
	CHRONOSA("[FString] : ", fstring.Clear());
	CHRONOSA("[std::vector] : ", vector.clear());
	CHRONOSA("[TArray] : ", tarray.Clear());
	CHRONOSA("[TKeyTable] : ", keytable.Clear());
	CHRONOSA("[TStaticKeyTable] : ", statickeytable.Clear());
	CHRONOSA("[std::map] : ", map.clear());
	CHRONOSA("[std::unordered_map] : ", umap.clear());

	PARADIGM_PAUSE;
}

//void GraphicsChecking()
//{
//	FContextInterface context = PARADIGM_NATIVE_CONTEXT("WINDOWSAPI");
//	UContextAttributes contextDesc;
//	CHRONOSA("Context Initialize :", context->Initialize());
//
//	context->GetNativeContextAttributes(contextDesc);
//	UKeyRegister keyContext = context->CreateContext({});
//	const UContextAttributes contextDesc2 = context->GetContextAttributes(keyContext);
//
//	FGraphicsInterface graphics = PARADIGM_NATIVE_GRAPHICS("DIRECT3D11");
//	CHRONOSA("Graphics Initialize :", graphics->Initialize());
//
//	graphics->CreateViewport(contextDesc.Dimension.Width, contextDesc.Dimension.Height, 0.f, 1.f, false, true, contextDesc.Handle);
//
//
//	PARADIGM_PAUSE;
//
//	MSG msg;
//	bool done = false;
//	while (!done)
//	{
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//
//		if (msg.message == WM_QUIT)
//			done = true;
//		else
//		{
//			//CHRONOSA("Begin scene in :", graphics->BeginScene(ParadigmEngine::NativeInterface::Graphics::ETargetViewport::VIEWPORT_0, { 0.1f,0.1f,0.1f,1 }));
//			graphics->BeginScene(ETargetViewport::VIEWPORT_0, { 0.1f,0.1f,0.1f,1 });
//			//DataStructurePerformanceTest();
//			//CHRONOSA("End scene in :", graphics->EndScene(ParadigmEngine::NativeInterface::Graphics::ETargetViewport::VIEWPORT_0));
//			graphics->EndScene(ETargetViewport::VIEWPORT_0);
//		}
//	}
//
//	context->Terminate();
//	graphics->Terminate();
//	delete context;
//	delete graphics;
//}

//UKeyRegister ContextChecking()
//{
//	ParadigmEngine::NativeInterface::Context::IDynamicContextInterface* context = new FWindowsInterface();
//	UContextAttributes contextDesc;
//
//	context->Initialize();
//
//	PARADIGM_PAUSE;
//	contextDesc.Name = PARADIGM_APPLICATION_NAME + " [1]NAT_BORDER";
//	contextDesc.ResolutionMode = ENativeResolutionMode::NAT_BORDER;
//	contextDesc.Resolution = ENativeResolution::NAT_3840x2160;
//	contextDesc.PositionX = 150;
//	contextDesc.PositionY = 500;
//	contextDesc.Dimension = { 800, 800 };
//	context->CreateContext(contextDesc);
//
//	PARADIGM_PAUSE;
//	contextDesc.Name = PARADIGM_APPLICATION_NAME + " [2]NAT_BORDERLESS";
//	contextDesc.ResolutionMode = ENativeResolutionMode::NAT_BORDERLESS;
//	contextDesc.Resolution = ENativeResolution::NAT_3840x2160;
//	contextDesc.PositionX = -1;
//	contextDesc.PositionY = -1;
//	contextDesc.Dimension = { 800, 200 };
//	context->CreateContext(contextDesc);
//
//	PARADIGM_PAUSE;
//	contextDesc.Name = PARADIGM_APPLICATION_NAME + " [3]NAT_FULLSCREEN";
//	contextDesc.ResolutionMode = ENativeResolutionMode::NAT_FULLSCREEN;
//	contextDesc.Resolution = ENativeResolution::NAT_3840x2160;
//	contextDesc.PositionX = 900;
//	contextDesc.PositionY = 550;
//	contextDesc.Dimension = { 5000, 500 };
//	UKeyRegister kregister = context->CreateContext(contextDesc);
//
//	PARADIGM_PAUSE;
//	context->DestroyContext(kregister);
//
//	PARADIGM_PAUSE;
//	context->Terminate();
//
//	return kregister;
//}


void ResourceChecking()
{
	ParadigmEngine::Resource::FResourceSupervisor supervisor;
	supervisor.LoadModel("Resource/Mesh/ironman/ironman.fbx");
	supervisor.LoadModel("Resource/Mesh/Neptune/NeptuneChristmas_ColladaMax.DAE");
	supervisor.LoadModel("Resource/Mesh/Neptune/NeptuneChristmas_ColladaMax.DAE");

	supervisor.LoadShardShader("teasd.vs");
	supervisor.LoadTexture("Resource/Mesh/Neptune/images/base_00.png");

	PARADIGM_PAUSE;

	supervisor.Terminate();
}


//#define IRONMEN

void FactoryChecking()
{
	using namespace ParadigmEngine;
	UShader& shader = PARADIGM_RESOURCE->Shader("Resource/Shader/Foo.shader");
	shader.kShardVertexShader = PARADIGM_RESOURCE->ShardShaderKey("Resource/Shader/BasicVertex.vs", "VertexToPixel");
	//shader.kShardGeometryShader = PARADIGM_RESOURCE->ShardShaderKey("Resource/Shader/Fragmentation.gs", "GeometryToPixel");
	shader.kShardPixelShader = PARADIGM_RESOURCE->ShardShaderKey("Resource/Shader/BasicPixel.ps", "PixelToFrameBuffer");

	////////////////////////////////////////
	// CAMERA
	//_______________________
	GEntity Camera = GEntity::Instanciate();
	Camera.GetMetaEntity()->Name = "Camera";
	GCamera camera = Camera.AddGear<GCamera>();

	/** Physics on camera */
	GCollider colcam = Camera.AddGear<GCollider>();
	colcam.Shape = ParadigmEngine::Physics::Collision::BOX;
	UMetaBoxCollider* collcam = (UMetaBoxCollider*)(colcam.ShapeData);
	collcam->size = FVector3(10.f, 10.f, 10.f);

	GRigidbody rigcam = Camera.AddGear<GRigidbody>();	
	rigcam.Mass = 10000.f;
	rigcam.useGravity = false;
	/** Physics on camera */

	camera.Data.DisplayTarget = ETargetViewport::VIEWPORT_0;
	GTransform cameraTransform = Camera.GetGear<GTransform>();
	cameraTransform.Position = { 0.f, 2.f, -10.5f };
	//cameraTransform.Rotation = FQuaternion::FromAngleAxis(30, FVector3::Up);
	camera.Data.Near = 0.1f;
	UMetaEntity::EntityLayers.AddLayer("NativeFactory");
	camera.Data.CullingMask = UMetaEntity::EntityLayers.GetLayer("NativeFactory");

	if (true)
	{
		UShader& debugNormal = PARADIGM_RESOURCE->Shader("Resource/Shader/Debug.shader");
		debugNormal.kShardVertexShader = PARADIGM_RESOURCE->ShardShaderKey("Resource/Shader/DebugNormals.vs", "VertexToPixel");
		//debugNormal.kShardGeometryShader = PARADIGM_RESOURCE->ShardShaderKey("Resource/Shader/DebugNormals.gs", "GeometryToPixel");
		debugNormal.kShardPixelShader = PARADIGM_RESOURCE->ShardShaderKey("Resource/Shader/DebugNormals.ps", "PixelToFrameBuffer");

		GEntity entity = GEntity::Instanciate();
		entity.GetMetaEntity()->Name = "Ground";
		entity.GetMetaEntity()->Tag = UMetaEntity::EntityLayers.GetLayer("NativeFactory");
		GTransform tr1 = entity.GetGear<GTransform>();
		tr1.Position = { 0, 0,0 };
		tr1.Scale = { 100.f,.5f,100.f };
		GCollider col1 = entity.AddGear<GCollider>();
		col1.Shape = ParadigmEngine::Physics::Collision::BOX;
		GRigidbody rig1 = entity.AddGear<GRigidbody>();
		//	rig1.Mass = 0;
		rig1.useGravity = false;
		rig1.FreezePositionX = true;
		rig1.FreezePositionY = true;
		rig1.FreezePositionZ = true;
		rig1.FreezeRotationX = true;
		rig1.FreezeRotationY = true;
		rig1.FreezeRotationZ = true;
		GMeshRender meshRender1 = entity.AddGear<GMeshRender>();
		GMeshShape meshShape1 = entity.AddGear<GMeshShape>();
		meshShape1.SetModel("Resource/Mesh/Cube.fbx");
		meshRender1.Data.Materials.Add({ PARADIGM_RESOURCE->Shader("Resource/Shader/Debug.shader") });
		FMaterial& material1 = meshRender1.Data.Materials[0];
		material1.SetRenderQueue(1000);
	}

	uint j = 0, a = 0, b = 0, c = 0;
	uint cubesize = 20;
	for (; a < cubesize; ++a)
	{
		b = 0;
		for (; b < cubesize; ++b)
		{
			c = 0;
			for (; c < cubesize; ++c, ++j)
			{
				float xrand = (std::rand() % 50)*0.1f - 2.5f;
				float zrand = (std::rand() % 50)*0.1f - 2.5f;

				//		GEntity entity = GEntity::Instanciate(nullptr, { 0,1,0 }, FQuaternion::FromEulerAngles(0, 0, 60));
				//GEntity entity = GEntity::Instanciate(nullptr, { a *1.001f - cubesize * 0.25f, 1 + c *1.25f,b *1.001f - cubesize * 0.25f }, FQuaternion::FromEulerAngles(0, 0, -30));
					GEntity entity = GEntity::Instanciate(nullptr, { xrand,5.f + j,zrand }, FQuaternion::FromEulerAngles(0, 0, 45));
				entity.GetMetaEntity()->Name = "Cube1";
				GMeshRender meshRender = entity.AddGear<GMeshRender>();
				GMeshShape meshShape = entity.AddGear<GMeshShape>();
				entity.GetMetaEntity()->Tag = UMetaEntity::EntityLayers.GetLayer("NativeFactory");

#ifdef IRONMEN
				meshShape.SetModel("Resource/Mesh/ironman/ironman.fbx");
#else
				meshShape.SetModel("Resource/Mesh/Cube.fbx");
#endif // IRONMEN

				meshRender.Data.Materials.Add({ PARADIGM_RESOURCE->Shader("Resource/Shader/Foo.shader") });
				FMaterial& material = meshRender.Data.Materials[0];
				material.SetTexture("Albedo", PARADIGM_RESOURCE->Texture("Resource/Mesh/ironman/ironman.dds"));
				GRigidbody rig = entity.AddGear<GRigidbody>();

				//			if (j % 2)
				{
					GCollider col = entity.AddGear<GCollider>();
					col.Shape = ParadigmEngine::Physics::Collision::BOX;
					UMetaBoxCollider* coll = (UMetaBoxCollider*)(col.ShapeData);
					coll->size = FVector3{1.f,2.f,1.f};
				}
				//else
				{
					//	GCollider col = entity.AddGear<GCollider>();
					//	col.Shape = ParadigmEngine::Physics::Collision::SPHERE;
				}


				if (false)
				{
					GEntity entity2 = GEntity::Instanciate(&entity, { 2.f,2.f,2.f });
					GTransform tr = entity2.GetGear<GTransform>();
					entity2.GetMetaEntity()->Name = "Cube2";
					GMeshRender meshRender2 = entity2.AddGear<GMeshRender>();
					GMeshShape meshShape2 = entity2.AddGear<GMeshShape>();
					entity2.GetMetaEntity()->Tag = UMetaEntity::EntityLayers.GetLayer("NativeFactory");
#ifdef IRONMEN
					meshShape2.SetModel("Resource/Mesh/ironman/ironman.fbx");
#else
					meshShape2.SetModel("Resource/Mesh/Cube.fbx");
#endif // IRONMEN
					meshRender2.Data.Materials.Add({ PARADIGM_RESOURCE->Shader("Resource/Shader/Foo.shader") });
					FMaterial& material2 = meshRender2.Data.Materials[0];
					material2.SetTexture("Albedo", PARADIGM_RESOURCE->Texture("Resource/Mesh/ironman/ironman.dds"));
					GCollider col2 = entity2.AddGear<GCollider>();
					col2.Shape = ParadigmEngine::Physics::Collision::BOX;
					entity.GetGear<GTransform>().Position = entity.GetGear<GTransform>().Position - FVector3{ 7,0,0 };
					//GRigidbody rig2 = entity2.AddGear<GRigidbody>();
					//--c; ++b;

					GEntity entity3 = GEntity::Instanciate(&entity2, { 5,5,5 });
					entity3.GetMetaEntity()->Name = "Cube3";
					GMeshRender meshRender3 = entity3.AddGear<GMeshRender>();
					GMeshShape meshShape3 = entity3.AddGear<GMeshShape>();
					entity3.GetMetaEntity()->Tag = UMetaEntity::EntityLayers.GetLayer("NativeFactory");
#ifdef IRONMEN
					meshShape3.SetModel("Resource/Mesh/ironman/ironman.fbx");
#else
					meshShape3.SetModel("Resource/Mesh/Cube.fbx");
#endif // IRONMEN
					meshRender3.Data.Materials.Add({ PARADIGM_RESOURCE->Shader("Resource/Shader/Foo.shader") });
					FMaterial& material3 = meshRender3.Data.Materials[0];
					material3.SetTexture("Albedo", PARADIGM_RESOURCE->Texture("Resource/Mesh/ironman/ironman.dds"));
					GCollider col3 = entity3.AddGear<GCollider>();
					col3.Shape = ParadigmEngine::Physics::Collision::BOX;
					GRigidbody rig3 = entity3.AddGear<GRigidbody>();

				}
			}
		}
	}

	//auto entityhandler = PARADIGM.Factory->CreateMetaEntity();
	//ParadigmEngine::EngineFramework::Factory::FMetaEntity::AddGear<ParadigmEngine::Physics::FTransform>(entityhandler.Pointer->GetMetaEntity());
	//ParadigmEngine::EngineFramework::Factory::FMetaEntity::AddGear<ParadigmEngine::Physics::Collision::UMetaBoxCollider>(entityhandler.Pointer->GetMetaEntity());
	//ParadigmEngine::EngineFramework::Factory::FMetaEntity::AddGear<ParadigmEngine::Physics::Force::UMetaRigidbody>(entityhandler.Pointer->GetMetaEntity());
	//ParadigmEngine::Physics::Force::UMetaRigidbody* ptr = entityhandler.Pointer->GetMetaEntity()->GetGear<ParadigmEngine::Physics::Force::UMetaRigidbody>();
	//ptr->m_mass = 10;

	//FVector3 angles(30.f,60.f,90.f);
	//for (uint i = 0; i < 100; ++i) angles = FQuaternion::FromEulerAngles(angles).ToEulerAngles();
	//FPrint::Print(angles);
}



#ifdef TEMPOPENGl
#include "TEMP/TEMPMian.h" 
#endif
using namespace ParadigmEngine::Core::Math;
using namespace ParadigmEngine::Core::Debug;
using namespace ParadigmEngine::Physics;

void doShit(UMetaTransform* _tr)
{
	FVector3 pos = _tr->Position;
	pos *= 1.01f;
	_tr->Position = pos;
	//std::cout << "Shit " << pos << std::endl;
//	for (int i= 0; i < 5000; ++i)
//		pos *= sqrtf(cosf(sqrtf(sqrtf(i))));
}

class Foo
{
public:
	void foo(int _i) { FPrint::Print("num of member fonction is " + std::to_string(_i) + "\n"); };
};

void fifoo(int _i) { FPrint::Print("num is " + std::to_string(_i) + "\n"); };

void PhysicsChecking()
{
	AUTOCHRONO("All finished in : ");

#pragma region UnitTests tests
	/*SUnitTests UT;
	UT.WriteAndCompile(1000u);*/
#pragma endregion

#pragma region Multithread tests
	/*Core::Multiprograming::FThread ServiceThread(3);
	string str = "print this";
	Core::Multiprograming::FThread::UJobInfo* jobinfo;
	{
		int i = 0;
		AUTOCHRONO("All pushed in : ");
		for (; i < 100000; ++i)
			jobinfo = ServiceThread.AddJob(&doShit, &tr);
		//ServiceThread.AddMemberJob(Log::print<std::string>, str, LogLvl::CYAN);
	}
	//jobinfo->Join();
	ServiceThread.FinishJobs();*/
#pragma endregion

#pragma region Multicast tests
	Foo fiou;
	//Foo fio;
	ParadigmEngine::Core::Dispatch::FEvent<int> ev;
	ev.Subscribe(&fifoo);
	ev.Subscribe(&Foo::foo, &fiou);
	//ev.Subscribe(&Foo::foo, &fio);
	ev(10);
	ev.Unsubscribe(&Foo::foo, &fiou);
	ev(5);

	//UMetaTransform tr;
	//FMultiCast mc;
	//mc += new UJob<UMetaTransform&>(&doShit, tr);
	//UDynamicJob* j = new UMemberJob<FTransform, const FQuaternion&>(&UMetaTransform::_SetRotation, tr, FQuaternion::FromEulerAngles(90, 0, 0));
	//mc += j;
	//mc();
	//mc -= j;
	//mc();
#pragma endregion

#pragma region Transform tests
	//FTransform tr;
	//tr.SetPosition(FVector3(10, 20, 30));
	//doShit(&tr);
	std::cout << "UVector is trivialy copyable : " << (std::is_trivially_copyable<UVector3>() ? "true" : "false") << std::endl;
	std::cout << "FQuaternion is trivialy copyable : " << (std::is_trivially_copyable<FQuaternion>() ? "true" : "false") << std::endl;

	//ParadigmEngine::EngineFramework::NativeProcessor::FProcessorSupervisor FPS;
	//FPS.AddProcessor<ParadigmEngine::EngineFramework::Processor::TGearProcessor<UMetaRigidbody>>();
	//FPS.Update();

#ifdef TEMPOPENGl
	TempMain();
#endif
#pragma endregion
}


using namespace ParadigmEngine::Core::Serialization;
//struct SimpleArchivableStruct : public IArchivable
//{
//	float x, y, z;
//	FString str;
//	TArray<char> vectors;
//	unordered_map<int, int> umap;
//	USHORT ushort;
//	SimpleArchivableStruct() = default;
//	SimpleArchivableStruct(SimpleArchivableStruct& _other)
//	{
//		x = _other.x;
//		y = _other.y;
//		z = _other.z;
//		str = _other.str;
//	}
//
//	SimpleArchivableStruct(float _x, float _y, float _z, FString _str, TArray<char> _vectors, unordered_map<int, int> _umap)
//	{
//		x = _x;
//		y = _y;
//		z = _z;
//		str = _str;
//		vectors = _vectors;
//		umap = _umap;
//	}
//
//	void Archive(UArchive& out_archive) override
//	{
//		FArchive::Serialize<float>(out_archive, x);
//		FArchive::Serialize<float>(out_archive, y);
//		FArchive::Serialize<float>(out_archive, z);
//		FArchive::Serialize(out_archive, str);
//		FArchive::Serialize<char>(out_archive, vectors);
//		FArchive::Serialize(out_archive, umap);
//	}
//
//	bool Dearchive(UArchive& _toArchive) override
//	{
//		FArchive::Deserialize<float>(_toArchive, x);
//		FArchive::Deserialize<float>(_toArchive, y);
//		FArchive::Deserialize<float>(_toArchive, z);
//		FArchive::Deserialize(_toArchive, str);
//		FArchive::Deserialize(_toArchive, vectors);
//		
//	}
//};
//struct ComplexArchivableStruct : public SimpleArchivableStruct
//{
//	TArray<SimpleArchivableStruct*> ComplexeArray;
//	ComplexArchivableStruct() = default;
//
//	void Archive(UArchive& out_archive) override
//	{
//		SimpleArchivableStruct::Archive(out_archive);
//		PARADIGM_ARCHIVE::Archive(out_archive, ComplexeArray);
//	}
//
//	bool Dearchive(UArchive& _toArchive) override
//	{
//		SimpleArchivableStruct::Dearchive(_toArchive);
//		PARADIGM_ARCHIVE::Dearchive(_toArchive, ComplexeArray);
//	}
//};
//
//void ArchiveChecking()
//{
//#pragma region Serialization
//	UArchive serial;
//	TArray<char> _vector;
//	unordered_map<int, int> u_map;
//	u_map.emplace(3, 14);
//	u_map.emplace(4, 18);
//	u_map.emplace(5, 22);
//	SimpleArchivableStruct vec{ 0.f,1.f,3.f, "APERTURE SCIENCE", _vector, u_map };
//	vec.Archive(serial);
//
//	serial.Index = 0;
//
//	TArray<char> _grrr;
//	unordered_map<int, int> test;
//	test.emplace(8, 21);
//	test.emplace(9, 25);
//	test.emplace(10, 29);
//	SimpleArchivableStruct wfd{ 4, 2, 5, "Why?", _grrr, test };
//	wfd.Dearchive(serial);
//		cout << "\nwfd.X : " << wfd.x << " wfd.y : " << wfd.y << " wfd.Z : " << wfd.z << " And This is my sentence: " << wfd.str << " is now deserialized" << endl;
//#pragma endregion
//
//	UArchive archive;
//	ComplexArchivableStruct* complexArch1 = nullptr;
//	TArray<ComplexArchivableStruct*> _vec;
//	for (unsigned int i = 0; i < 50; i += 10)
//	{
//		complexArch1 = new ComplexArchivableStruct();
//		complexArch1->str = vec.str;
//		complexArch1->x = vec.x+i;
//		complexArch1->y = vec.y+i;
//		complexArch1->z = vec.z+i;
//		complexArch1->ComplexeArray.Add(new SimpleArchivableStruct(wfd));
//		_vec.Add(complexArch1);
//	}
//
//	TArray<ComplexArchivableStruct*> _v2;
//
//	FArchive::Archive(archive, _vec);
//
//	archive.Index = 0;
//
//	FArchive::Dearchive(archive, _v2);
//
//#pragma region Transfer
//	UArchive alpha;
//	cout << "This is ALPHA data BEFORE: " << alpha.Data << " \n and this is ALPHA index BEFORE: " << alpha.Index << endl;
//	short _ushort = 535;
//	uint _uint = 165535;
//	FArchive::Serialize(alpha, _ushort);
//	FArchive::Serialize(alpha, _uint);
//	alpha.Index = 0;
//	cout << "This is ALPHA data AFTER: " << alpha.Data << " \n and this is ALPHA index AFTER: " << alpha.Index << endl;
//
//	UArchive beta;
//	cout << "This is BETA data BEFORE: " << alpha.Data << " \n and this is BETA index BEFORE: " << alpha.Index << endl;
//	FTransfer::Transfer<short>(alpha, beta);
//	cout << "This is ALPHA data AT THE END: " << alpha.Data << " \n and this is ALPHA index AT THE END: " << alpha.Index << endl;
//	cout << "This is BETA data AFTER: " << alpha.Data << " \n and this is BETA index AFTER: " << alpha.Index << endl;
//#pragma endregion
//}




namespace ParadigmEngine
{
	SERIALIZABLE_STRUCT(UArchiveCheck_Player_BasicMember)
	{
		META_SERIALIZABLE_ATTRIBUTES(UArchiveCheck_Player_BasicMember)

			FString Name;
		uint Strength;
		UVector2 Position;
		TArray<uint> Items;

		void Archive(UArchive& out_archive)  override
		{
			SERIALIZE_MEMBER(out_archive, Name);
			SERIALIZE_MEMBER(out_archive, Strength);
			SERIALIZE_MEMBER(out_archive, Position);
			SERIALIZE_MEMBER(out_archive, Items);
		}

		bool Dearchive(UArchive& out_archive) override
		{
			DESERIALIZE_MEMBER(out_archive, Name);
			DESERIALIZE_MEMBER(out_archive, Strength);
			DESERIALIZE_MEMBER(out_archive, Position);
			DESERIALIZE_MEMBER(out_archive, Items);
			return true;
		}
	};
	SERIALIZABLE_INSTANCE(UArchiveCheck_Player_BasicMember)


		SERIALIZABLE_STRUCT(UArchiveCheck_Player_ArchivableMember)
	{
		META_SERIALIZABLE_ATTRIBUTES(UArchiveCheck_Player_ArchivableMember)

			UArchiveCheck_Player_BasicMember Player;
		TArray<UArchiveCheck_Player_BasicMember> AllPlayers;
		TArray<UArchiveCheck_Player_BasicMember*> AllPlayers2;

		void Archive(UArchive& out_archive)  override
		{
			SERIALIZE_MEMBER(out_archive, Player);
			SERIALIZE_MEMBER(out_archive, AllPlayers);
			SERIALIZE_MEMBER(out_archive, AllPlayers2);
		}

		bool Dearchive(UArchive& out_archive) override
		{
			DESERIALIZE_MEMBER(out_archive, Player);
			DESERIALIZE_MEMBER(out_archive, AllPlayers);
			DESERIALIZE_MEMBER(out_archive, AllPlayers2);
			return true;
		}
	};
	SERIALIZABLE_INSTANCE(UArchiveCheck_Player_ArchivableMember)
}
using namespace ParadigmEngine;

#include <EngineFramework/Factory/FFactorySupervisor.h>

void ArchiveChecking_OMEGA()
{
	UArchive archive;
	GEntity entity = GEntity::Instanciate();
	GCamera cameraGear = entity.AddGear<GCamera>();
	cameraGear.Data.ClearColor = UColor::Aqua;
	cameraGear.Data.FieldOfView = 1;

	SERIALIZE(archive, *cameraGear.GetMetaData());
	
	IArchivable* rebuildCamera = PARADIGM_ARCHIVE.ReplicateFromID(typeid(*cameraGear.GetMetaData()).hash_code());
	archive.ResetIndex();
	
	rebuildCamera->Dearchive(archive);
	UKeyHandler<UMetaEntity> kEntity;
	FMetaEntity::CreateMetaEntity(kEntity);

	FMetaEntity::AddGearFromArchive(kEntity.Pointer, rebuildCamera);
	UMetaCamera* MUSASHI_FOR_WIN = kEntity.Pointer->GetGear<UMetaCamera>();
	size_t hMUSASHI = typeid(*MUSASHI_FOR_WIN).hash_code();	

	//GEntity::Destroy(&entity);
	//FMetaEntity::DestroyGears<UMetaCamera>(kEntity.Pointer);
}

void ArchiveChecking_BETA()
{
	/** SERIALIZABLE */
	UArchive archive;

	ParadigmEngine::UArchiveCheck_Player_BasicMember playerA;
	ParadigmEngine::UArchiveCheck_Player_BasicMember playerB;
	playerA.Name = "RobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobertRobert";
	playerA.Strength = 45;
	playerA.Position = { 27, 3 };
	playerA.Items = { 1, 0 , 84, 12 };

	archive.ResetIndex();
	{
		AUTOCHRONO("Serialize Time 1 : ");
		SERIALIZE(archive, playerA);
	}
	archive.ResetIndex();
	DESERIALIZE(archive, playerB);
	/** Works if playerA == playerB */

	/** ARCHIVABLE */
	archive.Clear();

	ParadigmEngine::UArchiveCheck_Player_ArchivableMember archiPlayerA;
	ParadigmEngine::UArchiveCheck_Player_ArchivableMember archiPlayerB;
	archiPlayerA.Player = playerA;
	for (uint i = 0; i < 5; ++i)
	{
		ParadigmEngine::UArchiveCheck_Player_BasicMember player;
		player.Name = "Persona" + FString::ToString(i);
		player.Strength = 22 * cosf(i);
		player.Position = { 7.f * cosf(i), 3.f * cosf(i) };
		player.Items = { i + 1, i / 5 , i * 3, 12 + i };

		UArchiveCheck_Player_BasicMember* playerPtr = new UArchiveCheck_Player_BasicMember();
		playerPtr->Name = "PersonaPtr" + FString::ToString(i);
		playerPtr->Strength = uint(22 * i);
		playerPtr->Position = { cosf(i), 3.f * cosf(i) };
		playerPtr->Items = { i , i, i };

		archiPlayerA.AllPlayers.Add(player);
		archiPlayerA.AllPlayers2.Add(playerPtr);
	}

	IArchivable* cloneA = PARADIGM_ARCHIVE.ReplicateFromID(typeid(UArchiveCheck_Player_ArchivableMember).hash_code());
	{
		AUTOCHRONO("Serialize Time : ");
		SERIALIZE(archive, archiPlayerA);
	}
	archive.Clear();
	SERIALIZE(archive, archiPlayerA);
	archive.ResetIndex();
	{
		AUTOCHRONO("Deserialize Time : ");
		DESERIALIZE(archive, *cloneA);
	}
	/** Works if archiPlayerA == cloneA */

	archive.ResetIndex();
	{
		AUTOCHRONO("Set Value from name Time : ");
		playerA.Name = "Personna";
		playerA.Position = {3,3};
		archiPlayerA.SetValueFromName("Player", playerA);
	}
}

namespace ParadigmEngine
{
	using namespace Resource;

	void NativeSynchronizationChecking()
	{
		////////////////////////////////////////
		// SHADER
		//_______________________

		UShader& shader = PARADIGM_RESOURCE->Shader("Resource/Shader/Foo.shader");
		shader.kShardVertexShader = PARADIGM_RESOURCE->ShardShaderKey("Resource/Shader/BasicVertex.vs", "VertexToPixel");
		//shader.kShardGeometryShader = PARADIGM_RESOURCE->ShardShaderKey("Resource/Shader/Fragmentation.gs", "GeometryToPixel");
		shader.kShardPixelShader = PARADIGM_RESOURCE->ShardShaderKey("Resource/Shader/BasicPixel.ps", "PixelToFrameBuffer");

		////////////////////////////////////////
		// CAMERA
		//_______________________
		UContextAttributes desc;
		desc.Dimension = { 0,0 };
		desc.Resolution = ENativeResolution::NAT_640x480;
		desc.PositionX = 0;
		desc.PositionY = 0;
		PARADIGM_GRAPHICS->CreateViewport(ETargetViewport::VIEWPORT_1, desc, false, false);
		PARADIGM_INPUT->CreateInputSystem(ETargetViewport::VIEWPORT_1);

		GEntity Camera = GEntity::Instanciate();
		GCamera camera = Camera.AddGear<GCamera>();
		GTransform cameraTransform = Camera.GetGear<GTransform>();
		cameraTransform.Position = { 0.f, 0.f, -1.5f };
		//cameraTransform.Rotation = FQuaternion::FromAngleAxis(30, FVector3::Up);
		camera.Data.Near = 0.1f;
		camera.Data.DisplayTarget = ETargetViewport::VIEWPORT_1;
		UMetaEntity::EntityLayers.AddLayer("NativeContext");
		camera.Data.CullingMask = UMetaEntity::EntityLayers.GetLayer("NativeContext");

		////////////////////////////////////////
		// ENTITY
		//_______________________
		int flip = 1;
		for (uint i = 0; i < PARADIGM_LIMITATION_MAX_ENTITY - 10; i++)
		{
			GEntity Ironman = GEntity::Instanciate();
			Ironman.GetMetaEntity()->Tag = UMetaEntity::EntityLayers.GetLayer("NativeContext");
			GTransform ironmanTransform = Ironman.GetGear<GTransform>();
			GMeshRender ironmanMeshRender = Ironman.AddGear<GMeshRender>();
			GMeshShape ironmanMeshShape = Ironman.AddGear<GMeshShape>();

			ironmanTransform.Position = { flip*-1.f, flip*-1.f, 0.5f + i };
			ironmanTransform.Rotate(FQuaternion::FromAngleAxis(flip*-30.f, FVector3::Up));
			ironmanMeshShape.SetModel("Resource/Mesh/ironman/ironman.fbx");

			ironmanMeshRender.Data.Materials.Add({ shader });

			////////////////////////////////////////
			// MATERIAL RESOURCES
			//_______________________
			FMaterial& material = ironmanMeshRender.Data.Materials[0];
			material.SetTexture("Albedo", PARADIGM_RESOURCE->Texture("Resource/Mesh/ironman/ironman.dds"));
			flip *= -1;
		}
		flip *= 0;

		/*material.SetMatrix("ProjectionMatrix", camera.ComputeProjection());
		material.SetMatrix("ViewMatrix", camera.ComputeView());
		material.SetMatrix("WorldMatrix", ironmanTransform.Data.ToMatrix());*/

		/*PARADIGM_GRAPHICS->BeginScene(NativeInterface::Graphics::ETargetViewport::VIEWPORT_0, { 0.2f,0.2f,0.2f,1 });
		PARADIGM_GRAPHICS->BindShader(material);
		PARADIGM_GRAPHICS->BindShaderResources(material);
		PARADIGM_GRAPHICS->BindInputAssembly(ironmanMeshShape.Data.kNativeModelBuffer.kElementBuffer, ironmanMeshShape.Data.kNativeModelBuffer.kVerticesBuffer);
		PARADIGM_GRAPHICS->DrawCall(ironmanMeshShape.Data.TriangleCount);*/


		/*	UVector3 MyModelPosition = { 0.f, -1.f, 0.f };
		UMatrix4 worldMatrix = {
		1.f,	0.f,	0.f,	MyModelPosition.x,
		0.f,	1.f,	0.f,	MyModelPosition.y,
		0.f,	0.f,	1.f,	MyModelPosition.z,
		0,	0,	0,	1.f
		};

		PARADIGM_RESOURCE->LoadModel("Resource/Mesh/Neptune/NeptuneChristmas_ColladaMax.DAE");
		UModel model1 = PARADIGM_RESOURCE->kModel("Mesh/Neptune/NeptuneChristmas_ColladaMax_1");
		UModel model2 = PARADIGM_RESOURCE->kModel("Mesh/Neptune/NeptuneChristmas_ColladaMax.DAE");
		UModel model3 = PARADIGM_RESOURCE->kModel("Mesh/Neptune/NeptuneChristmas_ColladaMax_2");

		material.SetTexture("Albedo", PARADIGM_RESOURCE->Texture("Mesh/Neptune/images/hair.png"));
		material.SetMatrix("WorldMatrix", worldMatrix);

		PARADIGM_GRAPHICS->BindShaderResources(shader.kNativeShaderResources);
		PARADIGM_GRAPHICS->BindInputAssembly(model1.GetElementBufferHandle(), model1.GetVertexBufferHandle());
		PARADIGM_GRAPHICS->DrawCall(model1.TriangleCount);

		material.SetTexture("Albedo", PARADIGM_RESOURCE->Texture("Mesh/Neptune/images/face_c.png"));

		PARADIGM_GRAPHICS->BindShaderResources(shader.kNativeShaderResources);
		PARADIGM_GRAPHICS->BindInputAssembly(model2.GetElementBufferHandle(), model2.GetVertexBufferHandle());
		PARADIGM_GRAPHICS->DrawCall(model2.TriangleCount);

		material.SetTexture("Albedo", PARADIGM_RESOURCE->Texture("Mesh/Neptune/images/body_c_christmas.png"));

		PARADIGM_GRAPHICS->BindShaderResources(shader.kNativeShaderResources);
		PARADIGM_GRAPHICS->BindInputAssembly(model3.GetElementBufferHandle(), model3.GetVertexBufferHandle());
		PARADIGM_GRAPHICS->DrawCall(model3.TriangleCount);

		PARADIGM_GRAPHICS->EndScene(NativeInterface::Graphics::ETargetViewport::VIEWPORT_0);
		PARADIGM_PAUSE;*/
	}
}