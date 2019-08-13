#ifndef _UVECTOR4_H_
#define _UVECTOR4_H_

using namespace std;
namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			struct FVector2;
			struct FVector3;
			struct FVector4;

			struct UVector4
			{
				operator FVector2();
				operator FVector3();
				operator FVector4();
				operator float*();

				void operator=(const FVector4& _val);

				float x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 };
			};
		}
	}
}
typedef ParadigmEngine::Core::Math::UVector4 UVector4;

#endif