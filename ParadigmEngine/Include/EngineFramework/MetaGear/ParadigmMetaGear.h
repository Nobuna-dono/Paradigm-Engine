#ifndef _PARADIGMMETAGEAR_H_
#define _PARADIGMMETAGEAR_H_

#include <EngineFramework/Factory/FFactorySupervisor.h>
#include <Serialization/ParadigmSerialization.h>
#include <EngineFramework/MetaGear/UMetaGear.h>

#define METAGEAR_CLASS(ClassName)\
	class ClassName : public UMetaGear

/** Generate the default constructor, the replication method and meta data for metaGear's reflection. */
#define METAGEAR_ATTRIBUTES(ClassName)\
					public:\
						ClassName()\
						{\
							FParadigmEngine::FParadigmEngine::GetInstance().Archive.AddGearReplica(this, #ClassName);\
							FParadigmEngine::GetInstance().Factory->AddMetaGearReflector<ClassName>(new UJob<>(std::bind(&ClassName::CompleteGearReflection, this)));\
						}\
						void CompleteGearReflection()\
						{ FParadigmEngine::GetInstance().Factory->ReflectGearsOfType<ClassName>(); }\
						ClassName* Replicate() const override\
						{ return new ClassName(static_cast<const ClassName &>(*this)); }\
					

#endif