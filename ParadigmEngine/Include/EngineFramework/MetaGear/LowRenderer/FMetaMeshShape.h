#ifndef _FMETAMESHSHAPE_H_ 
#define _FMETAMESHSHAPE_H_ 

#include <EngineFramework/MetaGear/LowRenderer/UMetaMeshShape.h>


namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace MetaGear
		{
			namespace LowRenderer
			{
				class FMetaMeshShape
				{
					public:
						//////////////////////////////////////////////// 
						// CONSTRUCTOR - DESTRUCTOR
						//____________________________________   
						FMetaMeshShape() = delete;

					public:
						//////////////////////////////////////////////// 
						// METHODS 
						//____________________________________   
						/** */
						static void SetModel(UMetaMeshShape& out_meta, const FString& _resourceName);
						/** */
						static void SetModel(UMetaMeshShape& out_meta, KModel _kmodel);
						/** */
						static UModel& GetModel(UMetaMeshShape& out_meta);
				};
			}
		}
	}
}

#endif