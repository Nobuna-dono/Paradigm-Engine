#ifndef _GGEAR_H_
#define _GGEAR_H_

#include <GameFramework\GameEntity\GEntity.h>

namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear
		{
			template <class MetaType, class = IfDeriveGear<MetaType>>
			class GGear
			{
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________	
					GGear() = default;
					GGear(MetaType* _metaGear);
					GGear(UMetaEntity* _metaEntity);
					~GGear() = default;
				
					typedef MetaType MetaType;
				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//____________________________________	
					/** Returns the entity to witch this gear is attach*/
					inline GEntity GetEntity() const;

					MetaType* GetMetaData() const;
				
				public:
					////////////////////////////////////////////////
					// OPERATORS
					//____________________________________	
					void operator=(MetaType* _metaGear);
					operator MetaType*();
					operator bool();

				public:
					////////////////////////////////////////////////
					// PROPERTY
					//____________________________________			
					CUSTOM_GETTER_PROPERTY(MetaType&, Data, { return *m_MetaGear; });
					CUSTOM_PROPERTY(bool, IsEnabeled, { return m_MetaGear->isEnabeled; }, { m_MetaGear->isEnabeled = _value; });


				protected:
					////////////////////////////////////////////////
					// DATA
					//____________________________________				
					MetaType* m_MetaGear{ nullptr };
			};
		}
	}
}

#define GEAR_CLASS(NAME, METATYPE)			\
		class NAME : public GGear<METATYPE>

#define GEAR_CLASS_CONSTRUCTOR(NAME, METATYPE)	\
		public:					\
			NAME(METATYPE* _metaGear) : GGear(_metaGear) {}\
			NAME(UMetaEntity* _metaEntity) : GGear(_metaEntity) {}

#define DEFAULT_GEAR_CLASS(NAME, METATYPE) \
		GEAR_CLASS(NAME, METATYPE)\
		{ GEAR_CLASS_CONSTRUCTOR(NAME, METATYPE) };

#include "GGear.inl"
#endif // !_GGEAR_H_
