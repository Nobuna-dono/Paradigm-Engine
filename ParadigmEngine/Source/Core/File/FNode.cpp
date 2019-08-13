#include "Include/Core/File/FNode.h"
#include <fstream>
#include <sstream>
#include <string>

namespace Core
{
	namespace File
	{
		FNode::FNode(std::string id, std::string value)
			: m_id{ id }, m_value{ value }
		{}

		FNode::~FNode()
		{
			for (const std::pair<std::string, FNode*>& pair : m_children)
				delete pair.second;
		}

		void FNode::AddChild(FNode* node)
		{
			m_children.insert({ node->Id(), node });
		}

		FNode* FNode::GetChild(std::string id)
		{
			FNode* result = m_children[id];
			if (result)
				return result;

			FNode* child = nullptr;
			for (const std::pair<std::string, FNode*>& pair : m_children)
			{
				child = pair.second->GetChild(id);
				if (child != nullptr)
					break;
			}
			return child;
		}

		std::string FNode::Id() const
		{
			return m_id;
		}

		std::string FNode::value() const
		{
			return m_value;
		}

		void FNode::value(std::string value)
		{
			m_value = value;
		}

		std::unordered_map<std::string, FNode*> FNode::Children() const
		{
			return m_children;
		}

		void FNode::Print(std::ofstream& stream, unsigned int depth)
		{
			for (unsigned int i = 0; i < depth; ++i)
				stream << '\t';

			stream << '\"';
			stream << m_id << '\"' << ": ";
			if (m_value != "")
				stream << "\"" << m_value << "\"";

			if (m_children.size() > 0)
			{
				stream << std::endl;
				for (unsigned int i = 0; i < depth; ++i)
					stream << '\t';
				stream << "{" << std::endl;

				for (const std::pair<std::string, FNode*>& pair : m_children)
				{
					pair.second->Print(stream, depth + 1);
					stream << std::endl;
				}

				for (unsigned int i = 0; i < depth; ++i)
					stream << '\t';
				stream << "}" << std::endl;
			}
		}

		std::ostream& File::operator<< (std::ostream& os, const FNode& node)
		{
			os << node.Id() << ": " + node.value() << std::endl;
			os << "{" << std::endl;

			for (const std::pair<std::string, FNode*>& pair : node.Children())
				os << *pair.second;

			os << "}" << std::endl;
			return os;
		}
	}
}