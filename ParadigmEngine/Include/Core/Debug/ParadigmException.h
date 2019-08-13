#ifndef _PARADIGMEXCEPTION_H_
#define _PARADIGMEXCEPTION_H_

#include <exception>

#include <ParadigmDebugEnum.h>
#include <ParadigmKeyword.h>

#define THROW_PARADIGM_EXCEPTION(Text) throw ParadigmException(EParadigmExceptionCode::RUNTIME_ERROR, PARADIGM_TEMPORALITY_LOCATION_DETAILS + Text, EParadigmDebugLevel::ERROR_LEVEL)
#define THROW_PARADIGM_EXCEPTION_ARGUMENT(Text) throw ParadigmException(EParadigmExceptionCode::ARGUMENT_ERROR,  PARADIGM_TEMPORALITY_LOCATION_DETAILS + Text, EParadigmDebugLevel::ERROR_LEVEL)
#define THROW_PARADIGM_EXCEPTION_DOMAIN(Text) throw ParadigmException(EParadigmExceptionCode::DOMAIN_ERROR,  PARADIGM_TEMPORALITY_LOCATION_DETAILS + Text, EParadigmDebugLevel::ERROR_LEVEL)
#define THROW_PARADIGM_EXCEPTION_RANGE(Text) throw ParadigmException(EParadigmExceptionCode::RANGE_ERROR,  PARADIGM_TEMPORALITY_LOCATION_DETAILS + Text, EParadigmDebugLevel::ERROR_LEVEL)
#define THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE(Text) throw ParadigmException(EParadigmExceptionCode::OUT_OF_RANGE_ERROR,  PARADIGM_TEMPORALITY_LOCATION_DETAILS + Text, EParadigmDebugLevel::ERROR_LEVEL)
#define THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(Text) throw ParadigmException(EParadigmExceptionCode::NOT_IMPLEMENTED_ERROR,  PARADIGM_TEMPORALITY_LOCATION_DETAILS + Text, EParadigmDebugLevel::ERROR_LEVEL)
#define THROW_PARADIGM_EXCEPTION_RAII_ERROR(Text) throw ParadigmException(EParadigmExceptionCode::RAII_ERROR,  PARADIGM_TEMPORALITY_LOCATION_DETAILS + Text, EParadigmDebugLevel::ERROR_LEVEL)
#define THROW_PARADIGM_EXCEPTION_BAD_IMPLEMENTATION(SIGNATURE) throw ParadigmException(EParadigmExceptionCode::BAD_IMPLEMENTATION_ERROR, PARADIGM_TEMPORALITY_LOCATION_DETAILS + ", please contact " + SIGNATURE, EParadigmDebugLevel::ERROR_LEVEL)
#define THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(Text) throw ParadigmException(EParadigmExceptionCode::NATIVE_IMPLEMENTATION_ERROR,  PARADIGM_TEMPORALITY_LOCATION_DETAILS + Text, EParadigmDebugLevel::ERROR_LEVEL)

#define PARADIGM_CATCH_EXCEPTION catch(const ParadigmException& e) { FPrint::Print(e.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION); }
#define PARADIGM_CATCH_AND_CUSTOM_EXCEPTION(Message) catch(const ParadigmException&) { FPrint::Print(Message, EParadigmDebugLevel::CAUGHT_EXCEPTION); }

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Debug
		{			
			enum EParadigmExceptionCode
			{
				/** Invalid argument pass as argument. */
				ARGUMENT_ERROR,

				/** Mathematic domain error. */
				DOMAIN_ERROR,

				/** Domain error. */
				RANGE_ERROR,

				/** Invalid lenght error. */
				LENGHT_ERROR,

				/** Invalid index error. */
				OUT_OF_RANGE_ERROR,

				/** Attempt to call a not implemented method. */
				NOT_IMPLEMENTED_ERROR,

				/** Resource handle acquisition failure. */
				RAII_ERROR,

				/** An Obscure error appeared... */
				RUNTIME_ERROR,

				/** Specific error for the SRC feature. */
				SHADER_RUNTIME_COMPILATION_ERROR,

				/** "It's not my fault, I swear !" */
				BAD_IMPLEMENTATION_ERROR,

				/** Error of native implementation, contact the concerned person. */
				NATIVE_IMPLEMENTATION_ERROR,
			};

			class ParadigmException : std::exception
			{
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________		
					ParadigmException(EParadigmExceptionCode _exception = RUNTIME_ERROR, const FString& _log = "", EParadigmDebugLevel niveau = ERROR_LEVEL) throw();
					virtual ~ParadigmException() throw();


				public:
					////////////////////////////////////////////////
					// ELEMENTS ACCESS
					//____________________________________		
					virtual const char* what() const throw();
					
					FString SumUp() const throw();

					EParadigmExceptionCode GetParadigmExceptionCode() const throw();

					EParadigmDebugLevel GetDebugLevel() const throw();


				private:
					////////////////////////////////////////////////
					// DATA
					//____________________________________		
					EParadigmExceptionCode m_ExceptionCode;
					EParadigmDebugLevel m_DebugLevel;               
					FString m_Sentence;								
			};
		}
	}
}
typedef ParadigmEngine::Core::Debug::ParadigmException ParadigmException;
typedef ParadigmEngine::Core::Debug::EParadigmExceptionCode EParadigmExceptionCode;

#endif