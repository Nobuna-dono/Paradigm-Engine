namespace ParadigmEngine
{
	namespace Core
	{
		namespace Serialization
		{
			template<typename T>
			static bool FTransfer::Transfer(UArchive& out_archiSrc, UArchive& out_archiDest)
			{
				size_t size = sizeof(T);

				for (size_t i = 0; i < size; ++i)
					out_archiDest.Data.PushBack(out_archiSrc.Data[out_archiSrc.Index + i]);
				return true;
			}
		}
	}
}