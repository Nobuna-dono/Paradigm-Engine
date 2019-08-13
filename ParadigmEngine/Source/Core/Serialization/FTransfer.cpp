#include <stdafx.h>
#include <iostream>

#include "Include/Core/Serialization/FTransfer.h"

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Serialization
		{
			bool FTransfer::TransferBytes(UArchive& out_archiSource, UArchive& out_archiDest, uint _bytes)
			{
				for (uint i = 0; i < _bytes; ++i)
					out_archiDest.Data.PushBack(out_archiSource.Data[out_archiSource.Index + i]);
				return true;
			}

			bool FTransfer::TransferString(UArchive& out_archiSource, UArchive& out_archiDest)
			{
				uint size;
				FArchive::Skip<size_t>(out_archiSource);
				FArchive::Deserialize<uint>(out_archiSource, size);
				TransferBytes(out_archiSource, out_archiDest, size);
				return true;
			}

			bool FTransfer::TransferFundamentalType(size_t _hashCode, UArchive& out_archiveSource, UArchive&out_archiveDest)
			{
				if (_hashCode == _CHAR_HASH_CODE)
				{
					FArchive::Skip<size_t>(out_archiveSource);
					return Transfer<char>(out_archiveSource, out_archiveDest);
				}
				else if (_hashCode == _UCHAR_HASH_CODE)
				{
					FArchive::Skip<size_t>(out_archiveSource);
					return Transfer<unsigned char>(out_archiveSource, out_archiveDest);
				}
				else if (_hashCode == _SHORT_HASH_CODE)
				{
					FArchive::Skip<size_t>(out_archiveSource);
					return Transfer<short>(out_archiveSource, out_archiveDest);
				}
				else if (_hashCode == _USHORT_HASH_CODE)
				{
					FArchive::Skip<size_t>(out_archiveSource);
					return Transfer<unsigned short>(out_archiveSource, out_archiveDest);
				}
				else if (_hashCode == _FLOAT_HASH_CODE)
				{
					FArchive::Skip<size_t>(out_archiveSource);
					return Transfer<float>(out_archiveSource, out_archiveDest);
				}
				else if (_hashCode == _INT_HASH_CODE)
				{
					FArchive::Skip<size_t>(out_archiveSource);
					return Transfer<int>(out_archiveSource, out_archiveDest);
				}
				else if (_hashCode == _UINT_HASH_CODE)
				{
					FArchive::Skip<size_t>(out_archiveSource);
					return Transfer<uint>(out_archiveSource, out_archiveDest);
				}
				else if (_hashCode == _DOUBLE_HASH_CODE)
				{
					FArchive::Skip<size_t>(out_archiveSource);
					return Transfer<double>(out_archiveSource, out_archiveDest);
				}
				else if (_hashCode == _LONG_HASH_CODE)
				{
					FArchive::Skip<size_t>(out_archiveSource);
					return Transfer<long>(out_archiveSource, out_archiveDest);
				}
				else if (_hashCode == _ULONG_HASH_CODE)
				{
					FArchive::Skip<size_t>(out_archiveSource);
					return Transfer<unsigned long>(out_archiveSource, out_archiveDest);
				}
				return false;
			}

			bool FTransfer::ReflectiveTransfer(UArchive& out_archiSource, UArchive& out_archiDest)
			{
				size_t typeinfo;
				FArchive::ReadOnly<size_t>(out_archiSource, typeinfo);

				if (TransferFundamentalType(typeinfo, out_archiSource, out_archiDest))
					return true;
				else if (typeinfo == _FSTRING_HASH_CODE)
					return TransferString(out_archiSource, out_archiDest);
				else if (TransferArchivable(out_archiSource, out_archiDest))
					return true;
				else
					return false;
			}

			bool FTransfer::TransferArchivable(UArchive& out_archiSource, UArchive& out_archiDest)
			{
				Transfer<size_t>(out_archiSource, out_archiDest); // hash_code transfer

				uint dataNumber = 0;
				FArchive::ReadOnly<uint>(out_archiSource, dataNumber);

				/* Transfers the number of Data */
				if (!Transfer<uint>(out_archiSource, out_archiDest))
					return false;

				for (uint i = 0; i < dataNumber; ++i)
				{
					ReflectiveTransfer(out_archiSource, out_archiDest);
					ReflectiveTransfer(out_archiSource, out_archiDest);
				}
				return true;
			}

			bool FTransfer::ExportFromArchive(UArchive& out_archive, UAssetFile& out_assetFile)
			{
				return TransferArchivable(out_archive, out_assetFile);
			}
		}
	}
}