#ifndef _FLAYER_H_
#define _FLAYER_H_

#include <map>
#include <TArray.h>
//

typedef std::string LayerName;
typedef uint Layer;
typedef uint LayerMask;

namespace ParadigmEngine
{
	namespace Core
	{
		namespace DataStructure
		{
			class FLayerSupervisor
			{
				std::map<LayerName, Layer> m_strMap;
				std::map<Layer, LayerMask> m_binMap;

			public:

				/** Add a layer and return is value. */
				Layer AddLayer(const LayerName& _tag);

				/** Get the layer value from it's name. */
				inline Layer GetLayer(const LayerName& _tag);

				bool GetLayerMaskValue(const LayerName& _tag, const  LayerName& _tag2);

				inline LayerMask GetLayerMask(const LayerName& _tag);

				void SetLayerMaskValue(const LayerName& _tag, const LayerName& _tag2, bool _newValue);

				void SetLayerMask(const LayerName& _tag, TArray<LayerName>& _tags, bool _newValue = true);

			private:
				inline void InternSetTagRelation(const LayerName& _tag, const LayerName& _tag2, bool _newValue);
			};
		}
	}
}
#include "FLayer.inl"

#endif // !_UTAG_H_