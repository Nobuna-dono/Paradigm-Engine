#ifndef _FTRANSFER_H_
#define _FTRANSFER_H_

#include <Core/Serialization/FArchive.h>

const size_t _bool_hash_code = typeid(bool).hash_code();
const size_t _int_hash_code = typeid(int).hash_code();
const size_t _uint_hash_code = typeid(uint).hash_code();
const size_t _float_hash_code = typeid(float).hash_code();
const size_t _char_hash_code = typeid(char).hash_code();
const size_t _uchar_hash_code = typeid(unsigned char).hash_code();
const size_t _short_hash_code = typeid(short).hash_code();
const size_t _ushort_hash_code = typeid(unsigned short).hash_code();
const size_t _double_hash_code = typeid(double).hash_code();
const size_t _long_hash_code = typeid(long).hash_code();
const size_t _ulong_hash_code = typeid(unsigned long).hash_code();
const size_t _string_hash_code = typeid(FString).hash_code();

#define _BOOL_HASH_CODE		_bool_hash_code
#define _INT_HASH_CODE		_int_hash_code
#define _UINT_HASH_CODE		_uint_hash_code
#define _FLOAT_HASH_CODE	_float_hash_code
#define _CHAR_HASH_CODE		_char_hash_code
#define _UCHAR_HASH_CODE	_uchar_hash_code
#define _SHORT_HASH_CODE	_short_hash_code
#define _USHORT_HASH_CODE	_ushort_hash_code
#define _DOUBLE_HASH_CODE	_double_hash_code
#define _LONG_HASH_CODE		_long_hash_code
#define _ULONG_HASH_CODE	_ulong_hash_code
#define _FSTRING_HASH_CODE	_string_hash_code

enum EVariableFieldType
{
	VariableField_Bool,
	VariableField_Int,
	VariableField_Uint,
	VariableField_Float,
	VariableField_String,
	VariableField_Enum,
};

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Serialization
		{
			class FTransfer
			{
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR
					//_____________________
					FTransfer() = delete;

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY - TRANSFERT
					//_____________________
					/* Transfers the bytes and push forward the index according to the type. */
					template<typename T>
					static bool Transfer(UArchive& out_archiSrc, UArchive& out_archiDest);

					/* Transfers the bytes and push forward the index according to the given _bytes. */
					static bool TransferBytes(UArchive& out_archiSrc, UArchive& out_archiDest, uint _bytes);

					/* Transfers uint size of string + string value */
					static bool TransferString(UArchive& out_archiSrc, UArchive& out_archiDest);

					/* Skips the hash_codes */
					static bool TransferFundamentalType(size_t _hashCode, UArchive& out_archiSrc, UArchive&out_archiDest);

					static bool ReflectiveTransfer(UArchive& out_archiSrc, UArchive& out_archiDest);

					static bool TransferArchivable(UArchive& out_archiSrc, UArchive& out_archiDest);


				public:
					static bool ExportFromArchive(UArchive& out_archive, UAssetFile& out_assetFile);
			};

	
		}
	}
}
#include "FTransfer.inl"
typedef ParadigmEngine::Core::Serialization::FTransfer FTransfer;
#endif