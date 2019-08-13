#include <GameFramework/GameGear/LowRenderer/GMeshRender.h>

namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear
		{
			namespace LowRenderer
			{
				void GMeshRender::SetMaterial(const FMaterial& _mat, uint _index)
				{
					if (Data.Materials.Count() >= _index)
					{
						uint sizeEmpty = (_index + 1) - Data.Materials.Count();
						Data.Materials.Reserve(_index);
						for (uint i = 0; i < sizeEmpty; ++i)
							Data.Materials.Add({});
					}
					
					Data.Materials[_index] = _mat;
				}

				FMaterial& GMeshRender::GetMaterial(uint _index)
				{		
					if (Data.Materials.Count() < _index)
						THROW_PARADIGM_EXCEPTION("This GMeshRender don't have this number["+FString::ToString(_index)+"] of materials(Current number of materials["+ FString::ToString(Data.Materials.Count())+"]).");
					
					return Data.Materials[_index];
				}

			}
		}
	}
}