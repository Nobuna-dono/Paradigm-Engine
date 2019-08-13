#ifndef _SUNITTEST_H_
#define _SUNITTEST_H_

#include <functional>
#include <string>
#include <unordered_map>
#include <sstream>

#define DEBUG
/** */

namespace Core
{
	namespace Debug
	{
		class SUnitTests
		{
			enum EUnitTestMode
			{
				NOCRASH,
				CRASH,
				COMPARE,
				COMPARE_scalarS,
				ISTRUE,
				ISFALSE,
				CLASS,
				END_CLASS
			};

			public:
					//Constructor
				SUnitTests();

					//Public Methods
				void WriteAndCompile(const unsigned int loopTimes = 1) const;
				void FindHeaders();
				void ParseHeaders();


			private:
					//Private Methods
				void AddPieceOfCode(EUnitTestMode, std::string Macro, std::string& className);
				std::string AddCrashRelativeCode(EUnitTestMode mode, std::string _funcname, std::string macro, unsigned int cursor);
				std::string AddCompareCode(EUnitTestMode mode, std::string _funcname, std::string macro, unsigned int cursor);
				std::string AddBooleanRelativeCode(EUnitTestMode mode, std::string _funcname, std::string macro, unsigned int cursor);
				std::string AddClassRelativeCode(EUnitTestMode mode, std::string& _classname, std::string macro, unsigned int& cursor);
				std::string TryCatch(std::string _tryPart, std::string _catchPart) const;

				void ParseHeader(std::string path);
				void ParseParams(std::string& line, unsigned int& index, std::string& _outParams);


					//Variables
				std::string includes, script;
				std::unordered_map<std::string,bool> functionList;
		};
	}
}

#endif