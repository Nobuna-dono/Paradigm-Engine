#ifndef _FJSON_H_
#define _FJSON_H_

#include "FNode.h"

namespace Core
{
	namespace File
	{
		class FJson
		{
			public:
				FJson() = default;
				FJson(FJson&) = default;
				~FJson();

				FNode* root();
				std::string getString(std::string);
				void parser(std::string);
				void saveData(std::string, FNode*);

			private:
				FNode* m_root {nullptr};
		};
	}
}

#endif