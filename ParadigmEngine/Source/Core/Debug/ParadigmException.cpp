#include <ParadigmException.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Debug
		{

			ParadigmException::ParadigmException(EParadigmExceptionCode _exception, const FString& _log, EParadigmDebugLevel niveau) throw()
				: m_ExceptionCode(_exception), m_DebugLevel(niveau), m_Sentence(_log)
			{}

			ParadigmException::~ParadigmException() throw() 
			{}

			const char* ParadigmException::what() const throw()
			{
				return "Paradigm exception. SumpUp for detail.";
			}

			FString ParadigmException::SumUp() const throw()
			{
				FString str{ m_Sentence + "\n| #Code : " };
				switch (m_ExceptionCode)
				{
					case ARGUMENT_ERROR:
						str += "ARGUMENT_ERROR";
						break;
					case DOMAIN_ERROR:
						str += "DOMAIN_ERROR";
						break;
					case RANGE_ERROR:
						str += "RANGE_ERROR";
						break;
					case LENGHT_ERROR:
						str += "LENGHT_ERROR";
						break;
					case OUT_OF_RANGE_ERROR:
						str += "OUT_OF_RANGE_ERROR";
						break;
					case NOT_IMPLEMENTED_ERROR:
						str += "NOT_IMPLEMENTED_ERROR";
						break;
					case RUNTIME_ERROR:
						str += "RUNTIME_ERROR";
						break;
					case SHADER_RUNTIME_COMPILATION_ERROR:
						return "\n| #Code : SHADER_RUNTIME_COMPILATION_ERROR\n" + m_Sentence;
					case NATIVE_IMPLEMENTATION_ERROR:
						str += "NATIVE_IMPLEMENTATION_ERROR";
						break;					
					default:
						str += "UNKNOW_ERROR";
						break;
				}				
				return str + ", (C)2018 Paradigm Engine.";
			}



			EParadigmExceptionCode ParadigmException::GetParadigmExceptionCode() const throw()
			{
				return m_ExceptionCode;
			}

			EParadigmDebugLevel ParadigmException::GetDebugLevel() const throw()
			{
				return m_DebugLevel;
			}
		}
	}
}