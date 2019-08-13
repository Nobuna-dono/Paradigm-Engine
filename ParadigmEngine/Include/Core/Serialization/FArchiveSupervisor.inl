

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Serialization
		{
			template<typename T>
			void FArchiveSupervisor::AddEnum(TArray<FString> _values)
			{
				if (m_Enums.find(typeid(T).hash_code()) == m_Enums.end())
					m_Enums.emplace(typeid(T).hash_code(), _values);
			}

			template<typename T>
			size_t FArchiveSupervisor::GetClassID(const T& value)
			{
				return  typeid(T).hash_code();
			}
			template<typename T>
			size_t FArchiveSupervisor::GetClassID(const TArray<T>& value)
			{
				return  typeid(T).hash_code();
			}
			template<typename T>
			size_t FArchiveSupervisor::GetClassID(const TArray<T*>& value)
			{
				return  typeid(T).hash_code();
			}


			////////////////////////////////////////////////
			// FUNCTIONALITY - SERIALIZATION
			//_____________________
			/* Simple Type */
			template<typename T>
			void FArchiveSupervisor::Serialize(UArchive& out_archive, const T& _data)
			{
				if (std::is_base_of<IArchivable, T>::value)
				{
					((IArchivable*)(&_data))->Archive(out_archive);
				}
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
			void FArchiveSupervisor::Serialize(UArchive& out_archive, const TArray<T>& _archivable)
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
			void FArchiveSupervisor::Serialize(UArchive& out_archive, const TArray<T*>& _archivable)
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
			bool FArchiveSupervisor::Deserialize(UArchive& _archive, T& out_data)
			{
				if (std::is_base_of<IArchivable, T>::value || std::is_polymorphic<T>::value)
				{
					return ((IArchivable*)(&out_data))->Dearchive(_archive);
				}
				else
				{
					if (_archive.Index + sizeof(T) >= _archive.Data.Count())
						return false;

					out_data = *((T*)(&_archive.Data.Get(_archive.Index)));
					_archive.Index += sizeof(T);
					return true;
				}
			}

			template<typename T>
			bool FArchiveSupervisor::Deserialize(UArchive& _archive, TArray<T>& out_array)
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
			bool FArchiveSupervisor::Deserialize(UArchive& _archive, TArray<T*>& out_data)
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
			void FArchiveSupervisor::ReadOnly(const UArchive& _archive, T& out_data)
			{
				if (_archive.Index + sizeof(T) >= _archive.Data.Count())
					return;
				out_data = *((T*)(&_archive.Data.Get(_archive.Index)));
			}

			template <typename T>
			void FArchiveSupervisor::Skip(UArchive& out_archive)
			{
				out_archive.Index = out_archive.Index + sizeof(T);
			}
		}
	}
}