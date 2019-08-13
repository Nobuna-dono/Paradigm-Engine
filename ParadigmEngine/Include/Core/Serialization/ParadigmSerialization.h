#ifndef _PARADIGMSERIALIZATION_H_
#define _PARADIGMSERIALIZATION_H_

#include <FParadigmEngine.h>
#include <Serialization/FEnumerator.h>

/* Serialize enum and add is data to the archive supervisor. */
#define SERIALIZE_ENUM(Enum)\
					if (!PARADIGM_ARCHIVE.IsEnum(typeid(Enum).hash_code()))\
						PARADIGM_ARCHIVE.AddEnum<Enum>(FENUMERATOR(Enum)::ValuesToString()); \

#define SERIALIZABLE_CLASS(ClassName)\
					class ClassName : public virtual IArchivable


#define SERIALIZABLE_STRUCT(StructName)\
					struct StructName : public virtual IArchivable


/** Allow to generate the replica for futur reflect. */
#define SERIALIZABLE_INSTANCE(ClassName)\
					const ClassName __Meta##ClassName##Instance;

/** Generate the default constructor (Only for base class (no inheritance)). */
#define DEFAULT_SERIALIZABLE_CONSTRUCTOR(ClassName)\
					public:\
						ClassName()\
						{ GENERATE_ARCHIVE_CLASS(this); }

#define SERIALIZABLE_ASSET_CONSTRUCTOR(ClassName)\
					public:\
						ClassName()\
						{ GENERATE_ASSET_ARCHIVE(this,#ClassName); }

/** Allow to register the serializable class*/
#define REGISTER_ARCHIVE_CLASS GENERATE_ARCHIVE_CLASS(this);

/** Generate the replication method for reflection. */
#define REPLICA_GENERATION(ClassName)\
					virtual ClassName* Replicate() const override\
					{ return new ClassName(static_cast<const ClassName &>(*this)); }

/** Generate the replication method and meta data for reflection. */
#define META_SERIALIZABLE_ATTRIBUTES(Name)\
					protected:\
						TArray<IArchivable::UMetaData> __metaData;\
					public:\
						REPLICA_GENERATION(Name)\
						template<typename T>\
						bool SetValueFromName(const FString& _name, const T& _value)\
						{\
							auto it = __metaData.Find({ _name }); \
							if (it != __metaData.End())\
							{\
								*static_cast<T*>((*it).Data) = _value; \
								return true; \
							}\
							return false; \
						}



/** Automatic serialization of basic member class type to the standard archive format and generate is metadata. */
#define SERIALIZE_MEMBER(OutArchive, Value)\
						/** Is dearchivable only? */\
						FArchive::Serialize(OutArchive, false);\
						/** Name value */\
						FArchive::Serialize<size_t>(OutArchive, _FSTRING_HASH_CODE);\
						FArchive::Serialize(OutArchive, FString(#Value));\
						/** #Code value */\
						FArchive::Serialize(OutArchive, typeid(Value).hash_code());\
						/** Value */\
						FArchive::Serialize(OutArchive, Value);\
						{\
							TArray<IArchivable::UMetaData>::Iterator iterator = __metaData.Find({#Value});\
							if(iterator == __metaData.End())\
								__metaData.Add({#Value, &Value});\
							else\
								(*iterator).Data = &Value;\
						}


/** Automatic serialization of atomic member class type to the standard archive format and generate is metadata. 
	- Force type the template type of the atomic (or a wellknown derived as FVector3 and UVector3). 
	- FirstValueType is the type of the first value of the template type (same if fundamental but important to specifiy if the type is a struct or class). */
#define SERIALIZABLE_ATOMIC_MEMBER(ForceType, FirstValueType, OutArchive, Value)\
						/** Is dearchivable only? */\
						FArchive::Serialize(OutArchive, false);\
						/** Name value */\
						FArchive::Serialize<size_t>(OutArchive, _FSTRING_HASH_CODE);\
						FArchive::Serialize(OutArchive, FString(#Value));\
						FArchive::Serialize(OutArchive, typeid(ForceType).hash_code());\
						FArchive::Serialize<ForceType>(OutArchive, *static_cast<ForceType*>((void*)((FirstValueType*)&Value + sizeof(bool))));\
						{\
							TArray<IArchivable::UMetaData>::Iterator iterator = __metaData.Find({#Value});\
							if(iterator == __metaData.End())\
								__metaData.Add({#Value, ((FirstValueType*)&Value + sizeof(bool))});\
						}

/** Serialize a value in the engine format. This not generate meta data. This not generate meta data.
 - This is only for specific deserialization method value as key or properties which need a specific way to set the value. */
#define SERIALIZE_DATA_MEMBER(OutArchive, Value)\
						/** Is dearchivable only? */\
						FArchive::Serialize(OutArchive, true);\
						/** Name value */\
						FArchive::Serialize<size_t>(OutArchive, _FSTRING_HASH_CODE);\
						FArchive::Serialize(OutArchive, FString(#Value));\
						/** #Code value */\
						FArchive::Serialize(OutArchive, typeid(Value).hash_code());\
						/** Value */\
						FArchive::Serialize(OutArchive, Value);

/** Serialize a value in the engine format. This not generate meta data. 
-This is only for specific deserialization method value as key or properties which need a specific way to set the value. */
#define SERIALIZE_DATA(OutArchive, Name, Value)\
						/** Is dearchivable only? */\
						FArchive::Serialize(OutArchive, true);\
						/** Name value */\
						FArchive::Serialize<size_t>(OutArchive, _FSTRING_HASH_CODE);\
						FArchive::Serialize(OutArchive, Name);\
						/** #Code value */\
						FArchive::Serialize(OutArchive, FArchiveSupervisor::GetClassID(Value));\
						/** Value */\
						FArchive::Serialize(OutArchive, Value);

/** Deserialization of basic member class type to the standard archive format. */
#define DESERIALIZE_MEMBER(OutArchive, out_Value)\
						FArchive::Skip<bool>(OutArchive); \
						FArchive::SkipCode(OutArchive); \
						FArchive::SkipString(OutArchive); \
						FArchive::SkipCode(OutArchive); \
						FArchive::Deserialize(OutArchive, out_Value); 


/** Deserialization of atomic member class type to the standard archive format. */
#define DESERIALIZE_ATOMIC_MEMBER(ForceType, OutArchive, Value)\
			{\
				ForceType tmp; \
				DESERIALIZE_MEMBER(out_archive, tmp); \
				Value = tmp; \
			}

/** Deserialization of basic member class type to the standard archive format. */
#define DESERIALIZE_DATA(OutArchive, out_Value) DESERIALIZE_MEMBER(OutArchive, out_Value)


#define SERIALIZE(OutArchive, Value)\
					FArchive::Serialize(OutArchive, Value);

#define DESERIALIZE(OutArchive, Value)\
					FArchive::Deserialize(OutArchive, Value);


/** [Archive] Serialize the ID of the class. */
#define SERIALIZE_CLASS_ID(OutArchive) FArchive::Serialize<size_t>(OutArchive, typeid(*this).hash_code());
/** [Dearchive] Skip the ID of the class. */
#define SKIP_CLASS_ID(OutArchive) FArchive::Skip<size_t>(OutArchive);

/** Skip useless info for the dearchive. */
#define SKIP_ARCHIVE_INFO(OutArchive)\
	SKIP_CLASS_ID(OutArchive)\
	FArchive::SkipString(OutArchive); \
	SKIP_NUMBER_ELEMENT(OutArchive)

/** Serialize class ID's and the number of element to archive. */
#define ARCHIVE_MEMBER(ClassName, OutArchive, NumberOfMemberToSerialize)\
	SERIALIZE_CLASS_ID(OutArchive)\
	FArchive::Serialize(OutArchive, FString(#ClassName));\
	SERIALIZE_NUMBER_ELEMENT(OutArchive, NumberOfMemberToSerialize)

/** [Archive] Serialize the number of elements of the class. */
#define SERIALIZE_NUMBER_ELEMENT(OutArchive, NumberOfMemberToSerialize) FArchive::Serialize<uint>(OutArchive, NumberOfMemberToSerialize);
/** [Dearchive] Skip the number of elements of the class. */
#define SKIP_NUMBER_ELEMENT(OutArchive) FArchive::Skip<uint>(OutArchive);

#endif