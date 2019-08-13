#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#define CONCATENATE2(pre, x) pre ## x
#define CONCATENATE(pre, x) CONCATENATE2(pre, x)


/** C# inspired property. exemple: CUSTOM_PROPERTY(int, Foo, { return m_OutVar; }, { m_OutVar = _value; }); */
#define CUSTOM_PROPERTY(TYPE, NAME, GET, SET)														\
		TYPE  CONCATENATE(_Get,NAME)() const GET;													\
		void CONCATENATE(_Set,NAME)(const TYPE& _value) SET;											\
		__declspec(property(get = CONCATENATE(_Get,NAME), put = CONCATENATE(_Set,NAME))) TYPE NAME;

/** C# inspired property for getter only. exemple: CUSTOM_GETTER_PROPERTY(int, Foo, { return m_OutVar; }); */
#define CUSTOM_GETTER_PROPERTY(TYPE, NAME, GET)														\
		TYPE  CONCATENATE(_Get,NAME)() const GET;													\
		__declspec(property(get = CONCATENATE(_Get,NAME))) TYPE NAME;

/** C# inspired property for setter only. exemple: CUSTOM_GETTER_PROPERTY(int, Foo, { return m_OutVar; }); */
#define CUSTOM_SETTER_PROPERTY(TYPE, NAME, SET)														\
		TYPE  CONCATENATE(_Set,NAME)() const SET;													\
		__declspec(property(put = CONCATENATE(_Set,NAME))) TYPE NAME;

/** C# inspired property. exemple: READONLY_PROPERTY(int, Foo, { return m_OutVar; }); */
#define READONLY_PROPERTY(TYPE, NAME, GET)								\
	private :															\
		TYPE CONCATENATE(m_, NAME);										\
	public :															\
		TYPE  CONCATENATE(_Get,NAME)() const GET;						\
		__declspec(property(get = CONCATENATE(_Get,NAME))) TYPE NAME;

/** C# inspired property. exemple: PROPERTY(int, Foo, { return m_Foo; }, { m_Foo = _value; }); */
#define PROPERTY(TYPE, NAME, GET, SET)			\
	protected :									\
		TYPE CONCATENATE(m_, NAME);				\
	public :									\
		CUSTOM_PROPERTY(TYPE, NAME, GET, SET)

/** C# inspired property. exemple: DEFAULTPROPERTY(int, Foo); */
#define DEFAULT_PROPERTY(TYPE, NAME)	PROPERTY(TYPE, NAME, { return CONCATENATE(m_, NAME); }, { CONCATENATE(m_, NAME) = _value; })

#define CUSTOM_DEFAULT_PROPERTY(TYPE, NAME)	CUSTOM_PROPERTY(TYPE, NAME, { return CONCATENATE(m_, NAME); }, { CONCATENATE(m_, NAME) = _value; })

/** C# inspired read-only property. exemple: DEFAULT_READONLY_PROPERTY(int, Foo); */
#define DEFAULT_READONLY_PROPERTY(TYPE, NAME) READONLY_PROPERTY(TYPE, NAME, { return CONCATENATE(m_, NAME); })		

#endif