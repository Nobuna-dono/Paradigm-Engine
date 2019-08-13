#include "Include/Core/File/FJson.h"
#include <fstream>
#include <sstream>
#include <string>

namespace Core
{
	namespace File
	{
		FJson::~FJson()
		{
			if (m_root) delete m_root;
		}

		FNode* FJson::root()
		{
			return m_root;
		}

		std::string FJson::getString(std::string line)
		{
			std::string str;
			for (unsigned int i = 0; line[i] != '"'; ++i)
				str += line[i];

			return str;
		}

		void FJson::parser(std::string path)
		{
			std::ifstream inFile(path);
			std::string line, str;
			std::vector<FNode*>node;
			FNode* lastNode = nullptr;

			while (std::getline(inFile, line))
			{
				unsigned int i = 0;
				while (line[i] == '\t')
					++i;

				switch (line[i])
				{
				case '"':
					//Node//
					lastNode = new FNode(getString(line.substr(i + 1)));
					if (m_root == nullptr)
						m_root = lastNode;
					else
						node.back()->AddChild(lastNode);

					//Value//
					while (line[i] != ':')
						++i;
					++i;
					if (i < line.size() && line[i] == ' ')
					{
						++i;
						if (line[i] == '"')
						{
							++i;
							while (line[i] != '"')
							{
								str += line[i];
								++i;
							}
						}
					}
					lastNode->value(str);
					str = "";
					break;
				case '{':
					node.push_back(lastNode);
					break;
				case '}':
					node.pop_back();
					break;
				default:
					break;
				}
			}
		}

		void FJson::saveData(std::string path, FNode* node)
		{
			if (node)
			{
				std::ofstream outFile(path);
				node->Print(outFile, 0);
				delete node;
			}
		}
	}
}