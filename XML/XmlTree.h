#ifndef __XMLTREE__
#define __XMLTREE__

#include <map>
#include <string>
#include <vector>


struct XmlNode
{
	std::string element;
	std::map<std::string, std::string> attribute_set;
	std::vector<XmlNode*> child;
	XmlNode* parent;
	XmlNode* next_sib;
	XmlNode* prev_sib;

	XmlNode(const std::string& s) : element(s)
	{
		next_sib = nullptr;
		prev_sib = nullptr;
		parent = nullptr;
	}
};

class XmlTree
{
public:
	XmlTree()
	{
		mRoot = nullptr;
	}
	~XmlTree()
	{

	}

	void parseXmlFile(const char* file_name)
	{
		parse(file_name);
	}
	void parseXmlFile(const std::string& file_name)
	{
		parse(file_name.c_str());
	}

private:
	void parse(const char* fileName);

	XmlNode* mRoot;
};

#endif

