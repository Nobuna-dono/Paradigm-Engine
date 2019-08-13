#ifndef _FNODE_H_
#define _FNODE_H_

#include <iostream>
#include <vector>
#include <unordered_map>

namespace Core
{
	namespace File
	{
		class FNode
		{
			public:
					//Constructor
				FNode() = default;
				FNode(const FNode&) = delete;
				FNode(std::string, std::string = "");

					//Destructor
				~FNode();


			public:
				void AddChild(FNode*);
				FNode* GetChild(std::string);

				std::string Id() const;
				std::string value() const;
				void value(std::string);

				std::unordered_map<std::string, FNode*> Children() const;

				void Print(std::ofstream&, unsigned int);


			private:
				std::string m_id;
				std::string m_value;
				std::unordered_map<std::string, FNode*> m_children;
		};

		std::ostream& operator<< (std::ostream&, const FNode&);
	}
}

#endif