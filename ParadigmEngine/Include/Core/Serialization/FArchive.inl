namespace ParadigmEngine
{
	namespace Core
	{
		namespace Serialization
		{

			////////////////////////////////////////////////
			// FUNCTIONALITY - SERIALIZATION
			//_____________________
			/* Simple Type */
			template<typename T>
			void FArchive::Serialize(UArchive& out_archive, const T& _data)
			{
				if (std::is_base_of<IArchivable, T>::value)
				{
					((IArchivable*)(&_data))->Archive(out_archive);
				}
				else if (typeid(T).hash_code() == typeid(FString).hash_code())
					return Serialize(out_archive, _data);
				else
				{
					char buff[sizeof(T) + 1];

					*((T*)(&buff)) = _data;
					buff[sizeof(T)] = 0;

					for (int i = 0; i < sizeof(T); i++)
						out_archive.Data.PushBack(buff[i]);
					out_archive.Index = out_archive.Index + sizeof(T);
				}
			}
			
			template<typename T>
			void FArchive::Serialize(UArchive& out_archive, const TArray<T>& _archivable)
			{
				if (std::is_base_of<IArchivable, T>::value)
				{
					TArray<const T*> outArray = ArrayToPointerArray(_archivable);
					Serialize<int>(out_archive, outArray.Count());
					for (TArray<const T*>::Const_Iterator it = outArray.Const_Begin(); it != outArray.Const_End(); ++it)
						((IArchivable*)(*it))->Archive(out_archive);
				}
				else
				{
					Serialize<int>(out_archive, _archivable.Count());
					for (TArray<T>::Const_Iterator it = _archivable.Const_Begin(); it != _archivable.Const_End(); ++it)
						Serialize<T>(out_archive, *it);
				}
			}
			
			template<typename T>
			void FArchive::Serialize(UArchive& out_archive, const TArray<T*>& _archivable)
			{
				if (std::is_base_of<IArchivable, T>::value)
				{
					Serialize<int>(out_archive, _archivable.Count());
					for (TArray<T*>::Const_Iterator it = _archivable.Const_Begin(); it != _archivable.Const_End(); ++it)
						((IArchivable*)(*it))->Archive(out_archive);
				}
				else
				{
					Serialize<int>(out_archive, _archivable.Count());
					for (TArray<T*>::Const_Iterator it = _archivable.Const_Begin(); it != _archivable.Const_End(); ++it)
						Serialize<T>(out_archive, *(*it));
				}
			}


			////////////////////////////////////////////////
			// FUNCTIONALITY - DESERIALIZATION
			//_____________________
			template<typename T>
			bool FArchive::Deserialize(UArchive& _archive, T& out_data)
			{
				if (std::is_base_of<IArchivable, T>::value || std::is_polymorphic<T>::value)
				{
					return ((IArchivable*)(&out_data))->Dearchive(_archive);
				}
				else if (typeid(T).hash_code() == typeid(FString).hash_code())
					return Deserialize(_archive, out_data);
				else
				{
					if (_archive.Index + sizeof(T) > _archive.Data.Capacity())
						return false;

					out_data = *((T*)(&_archive.Data.Get(_archive.Index)));
					_archive.Index = _archive.Index + sizeof(T);
					return true;
				}
			}

			template<>
			bool FArchive::Deserialize<char>(UArchive& _archive, char& out_data)
			{
				if (_archive.Index + 1 > _archive.Data.Capacity())
					return false;

				out_data = _archive.Data.Get(_archive.Index);
				_archive.Index = _archive.Index + 1;
				return true;				
			}
					
			template<typename T>
			bool FArchive::Deserialize(UArchive& _archive, TArray<T>& out_array)
			{
				if (std::is_base_of<IArchivable, T>::value)
				{
					int buff = 0;
					if (!Deserialize<int>(_archive, buff))
						return false;

					T t;
					out_array.Clear();
					out_array.Reserve(buff);
					for (int i = 0; i < buff; i++)
					{
						if (!((IArchivable*)&t)->Dearchive(_archive))
							return false;
						out_array.Add(t);
					}
				}
				else
				{
					int buff = 0;
					T t;
					if (!Deserialize<int>(_archive, buff))
						return false;
					out_array.Clear();
					out_array.Reserve(buff);
					for (int i = 0; i < buff; i++)
					{
						if (!Deserialize<T>(_archive, t))
							return false;
						out_array.Add(t);
					}
				}
				return true;
			}

			template<typename T>
			bool FArchive::Deserialize(UArchive& _archive, TArray<T*>& out_data)
			{
				if (std::is_base_of<IArchivable, T>::value)
				{
					int buff = 0;
					T* t;
					if (!Deserialize<int>(_archive, buff))
						return false;

					out_data.Clear();
					out_data.Reserve(buff);
					for (int i = 0; i < buff; i++)
					{
						t = new T();
						if (!((IArchivable*)t)->Dearchive(_archive))
							return false;
						out_data.Add(t);
					}
				}
				else
				{
					int buff = 0;
					T* t = 0;
					if (!Deserialize<int>(_archive, buff))
						return false;
					out_data.Clear();
					out_data.Reserve(buff);
					for (int i = 0; i < buff; i++)
					{
						t = new T();
						if (!Deserialize<T>(_archive, *t))
							return false;
						out_data.Add(t);
					}
				}
				return true;
			}			
						

			////////////////////////////////////////////////
			// FUNCTIONALITY - HELPER
			//_____________________
			template <typename T>
			void FArchive::ReadOnly(const UArchive& _archive, T& out_data)
			{				
				if (_archive.Index + sizeof(T) > _archive.Data.Count())
					return;
				out_data = *((T*)(&_archive.Data.Get(_archive.Index)));
			}

			template <typename T>
			void FArchive::Skip(UArchive& out_archive)
			{
				if (typeid(T).hash_code() == _string_hash_code)
					SkipString(out_archive);
				else
					out_archive.Index = out_archive.Index + sizeof(T);
			}

			template<typename T>
			bool FArchive::ReplaceValueInGear(UArchive& out_gearArchive, const FString& _name, T _value)
			{
				out_gearArchive.ResetIndex();
				UArchive newArchive;
				// Set link
				out_gearArchive.LinkArchive(&newArchive);
				
				if (FArchive::FindNameValueFromGear(out_gearArchive, _name))
				{
					// Break link
					out_gearArchive.LinkArchive(nullptr);
					FArchive::Skip<T>(out_gearArchive);
					FArchive::Serialize(newArchive, _value);
					
					// Set link
					out_gearArchive.LinkArchive(&newArchive);
					uint valueToSkip = out_gearArchive.Data.Count() - out_gearArchive.Index;
					FArchive::SkipBytes(out_gearArchive, valueToSkip);

					// Break link
					out_gearArchive.LinkArchive(nullptr);
					out_gearArchive = newArchive;
					out_gearArchive.ResetIndex();

					return true;
				}
				out_gearArchive.ResetIndex();
				return false;
			}
		}
	}
}

/* Data Struct unordered_map */
/*template<typename T, typename U>
static void FArchive::Serialize(UArchive& out_archive, std::unordered_map<T, U>& _umap)
{
Serialize<int>(out_archive, _umap.size());
for (std::unordered_map<T, U>::iterator it = _umap.begin(); it != _umap.end(); ++it)
{
Serialize<T>(out_archive, it->first);
Serialize<U>(out_archive, it->second);
}
}*/


/* Data Struct unordered_map */
/*template<typename T, typename U>
bool FArchive::Deserialize(UArchive& _archive, std::unordered_map<T, U>& out_umap)
{
int buff = 0;
std::pair<T, U> pair;

if (!Deserialize<int>(_archive, buff))
return false;
out_umap.clear();
out_umap.reserve(buff);

for (int i = 0; i < buff; i++)
{
if (!Deserialize<T>(_archive, pair.first) || !Deserialize<U>(_archive, pair.second))
return false;
out_umap.emplace(pair);
}
return true;
}
*/