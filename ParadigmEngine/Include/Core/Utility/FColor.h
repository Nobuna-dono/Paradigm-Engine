#ifndef _FCOLOR_H_
#define _FCOLOR_H_

#include <Core/Math/UVector4.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Utility
		{
			struct UColor
			{
				UColor(float _r = 0, float _g = 0, float _b = 0, float _a = 0);

				float r, g, b, a;
				
				static const UColor Black;
				static const UColor Navy;
				static const UColor Blue;
				static const UColor Green;
				static const UColor Teal;
				static const UColor Lime;
				static const UColor Aqua;
				static const UColor Maroon;
				static const UColor Purple;
				static const UColor Olive;
				static const UColor Gray;
				static const UColor Silver;
				static const UColor Red;
				static const UColor Magenta;
				static const UColor Yellow;
				static const UColor White;

				static const UColor ParadigmGold;
				static const UColor ParadigmDarkGray;

			};

			class FColor
			{
				public:
					FColor() = delete;


				public:
					static UColor Lerp(UColor _a, UColor _b, float _time)
					{return{};}
					static UColor LerpUnclamped(UColor _a, UColor _b, float _time)
					{return{}; }

					/*static UColor operator +(UColor _a, UColor _b);
					static UColor operator -(UColor _a, UColor _b);
					static UColor operator *(float _b, UColor _a);
					static UColor operator *(UColor _a, float _b);
					static UColor operator *(UColor _a, UColor _b);
					static UColor operator /(UColor _a, float _b);
					static bool operator ==(UColor _lhs, UColor _rhs);
					static bool operator !=(UColor _lhs, UColor _rhs);

					static operator UColor(UVector4 v);
					static operator UVector4(UColor c);*/
			};
		}
	}
}

typedef ParadigmEngine::Core::Utility::UColor UColor;

#endif