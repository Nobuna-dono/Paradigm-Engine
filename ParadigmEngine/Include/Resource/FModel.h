#ifndef _FMODEL_H_
#define _FMODEL_H_

#include <Resource/UModel.h>

namespace ParadigmEngine
{
	namespace Resource
	{	
		/** The @UModel's functionality class. */
		class FModel 
		{
			public:
				////////////////////////////////////////////////
				// FUNCTIONALITY
				//____________________________________	
				/** Create a model from data and add it into the resource management.*/
				static KModel CreateModelFromMemory(TArray<TArray<UVertex>> _vertices, TArray<uint> _triangles);
				/** Create a model from data and add it into the resource management.*/
				static KModel CreateModelFromMemory(TArray<TArray<UVertex>> _vertices, uint _trianglesCount);

				/** Creates or reupload natives buffers.*/
				static void SyncResource(UModel& _model, bool _clearResource = true);
				
				/** Clear arrays (vertices, indices, ...). After synchronize data buffers, you should clean resources cause their data are already store in the buffers. */
				static void CleanResourceData(UModel& _model);
		};
	}
}

typedef ParadigmEngine::Resource::FModel FModel;

#endif 