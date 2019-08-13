#include <FParadigmEngine.h>
#include <EngineFramework/Factory/FFactorySupervisor.h>
#include <NativeInterface/Graphics/FGraphicsInterface.h>
#include <NativeInterface/Context/FContextInterface.h>
#include <Resource/FResourceSupervisor.h>

namespace ParadigmEngine
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PIPELINE 
	//____________________________________________________________________________________________________________
	FParadigmEngine* FParadigmEngine::m_Instance;

	FParadigmEngine::FParadigmEngine()
	{
		FString ContextConfig{ "WINDOWS" };
		FString GraphicsConfig{ "DIRECT3D11" };
		FString MeshLoaderConfig{ "ASSIMP" };
		FString InputLoaderConfig{ "DIRECTINPUT" };
		FString TextureLoaderConfig{ "DIRECTX" };
		FString PhysicsLoaderConfig{ "BULLET" };

		Context = PARADIGM_NATIVE_CONTEXT(ContextConfig);
		Graphics = PARADIGM_NATIVE_GRAPHICS(GraphicsConfig);
		Input = PARADIGM_NATIVE_INPUT(InputLoaderConfig);
		Physics = PARADIGM_NATIVE_PHYSICS(PhysicsLoaderConfig);

		Resource = new Resource::FResourceSupervisor();
		Factory = new EngineFramework::Factory::FFactorySupervisor();
		Processor = new EngineFramework::NativeProcessor::FProcessorSupervisor();		
	}

	FParadigmEngine::~FParadigmEngine()
	{
		Processor->Terminate();
		delete Processor;
		Processor = nullptr;

		Context->Terminate();
		delete Context;
		Context = nullptr;

		Graphics->Terminate();
		delete Graphics;
		Graphics = nullptr;

		Resource->Terminate();
		delete Resource;
		Resource = nullptr;

		Factory->Terminate();
		delete Factory;
		Factory = nullptr;
	}

	void FParadigmEngine::Initialize()
	{
		Context->Initialize();
		Graphics->Initialize();
		Input->Initialize();
		Factory->Initialize();
		Processor->Initialize();
		Resource->Initialize();

#ifndef _PARADIGM_EDITOR
		UContextAttributes contextDesc;
		contextDesc.Dimension = {1280, 720};
		contextDesc.Resolution = ENativeResolution::NAT_1920x1080;
		contextDesc.bForeground = false;
		Graphics->CreateViewport(ETargetViewport::VIEWPORT_0, contextDesc, false, true);
		Input->CreateInputSystem(ETargetViewport::VIEWPORT_0, { EInputDeviceType::InputDeviceType_Mouse | EInputDeviceType::InputDeviceType_Keyboard });
#endif
	}

		// Parsing of native.config
		
		// struct UNativeConfig
		/*FString ContextConfig{"WINDOWS"};
		FString GraphicsConfig{"DIRECT3D11"};
		FString MeshLoaderConfig{"ASSIMP"};
		FString InputLoaderConfig{"DIRECTINPUT"};
		FString TextureLoaderConfig{"DIRECTX"};
		FString PhysicsLoaderConfig{ "BULLET" };*/

		// Initialize interfaces
		//Context = PARADIGM_NATIVE_CONTEXT(ContextConfig);
		//Context->Initialize();		

		/*UContextAttributes contextDesc;
		contextDesc.Dimension = {1280, 720};
		contextDesc.Resolution = ENativeResolution::NAT_1920x1080;
		contextDesc.bForeground = false;*/
		
		//Graphics = PARADIGM_NATIVE_GRAPHICS(GraphicsConfig);
		//Graphics->Initialize();

		//Input = PARADIGM_NATIVE_INPUT(InputLoaderConfig);
		//Input->Initialize();

		//Graphics->CreateViewport(ETargetViewport::VIEWPORT_0, contextDesc, false, true);
		

		//Physics = PARADIGM_NATIVE_PHYSICS(PhysicsLoaderConfig);
		//Resource.Initialize();		
/*
		Factory = new EngineFramework::Factory::FFactorySupervisor();
		Processor = new EngineFramework::NativeProcessor::FProcessorSupervisor();
		Resource.Initialize();
		Factory->Initialize();
		Processor->Initialize();*/
	

	void FParadigmEngine::Run()
	{
		bool block = false;
		bool blockR = false;
		while (!Frame())
		{
			// Test resize
			/*if (!block && PARADIGM_INPUT->IsKeyDown(EKeyCode::Left))
			{
				PARADIGM_GRAPHICS->ResizeViewport(ETargetViewport::VIEWPORT_0, 500, 600);
				block = true;
			}
			else
				block = false;

			if (!blockR && PARADIGM_INPUT->IsKeyDown(EKeyCode::Right))
			{
				PARADIGM_GRAPHICS->ResizeViewport(ETargetViewport::VIEWPORT_0, 1280, 720);
				blockR = true;
			}
			else
				blockR = false;*/
		}
	}

	////////////////////////////////////////////////
	// FUNCTIONALITY
	//____________________________________
	FString FParadigmEngine::ApplicationDirectory() const
	{
		char pathC[200];
		GetCurrentDirectory(200, pathC);
		return { pathC };		
	}

	bool FParadigmEngine::Frame(bool _bOnGame)
	{
		bool bDone = false;
		Time.Update();

		Input->Update(Context->GetCurrentFocusOn());
#ifndef _PARADIGM_EDITOR
		if (Input->IsEscapePressed())
			bDone = true;
		if (!Context->Update())
			bDone = true;
		else
#endif
		{
			if (_bOnGame)
			{
				Processor->Update();

				if (Time.FixedTimeExeeded())
				{
					Processor->PrePhysics();
					Physics.Step();
					Processor->PostPhysics();
				}
			}
						
			if (Time.FixedTimeExeeded())
				Processor->FixedUpdate();
			Processor->LateUpdate();
			Processor->Draw();
			
			if (_bOnGame)
				Processor->PostDraw();
		}

		return bDone;
	}	
}
