#include "XmlTree.h"

#include <fstream>
#include <sstream>
#include <stack>
#include <iomanip>
#include <iostream>
using namespace std;

static void travel(XmlNode* parent)
{
	cout << "Elemet: " << parent->element << '\n';
	if (parent->attribute_set.size() > 0)
	{
		cout << "Attribute: " << '\n';
		for (const pair<string, string>& attribure : parent->attribute_set)
		{
			cout << attribure.first << ' ' << attribure.second << '\n';
		}
		cout << '\n';
	}
	for (XmlNode* ite : parent->child)
	{
		cout << "Go to child :" << '\n';
		travel(ite);
	}
	cout << '\n';
	if (parent->next_sib != nullptr)
	{
		cout << "Go to next sibling:\n";
		travel(parent->next_sib);
	}

}

void XmlTree::parse(const char* file_name)
{
	ifstream fin(file_name);
	string s;
	getline(fin, s);

	vector<string> xml;
	while (getline(fin, s))
	{
		int i = 0;
		while (s[i] == ' ')
		{
			++i;
		}
		s.erase(0, i);
		xml.push_back(s);
	}

	//for update parent and sibling
	stack<XmlNode*> stack_XmlNode;

	for (size_t i = 0; i < xml.size(); ++i)
	{
		string temp = xml[i];
		temp.erase(remove(temp.begin(), temp.end(), '	'), temp.end());
		temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
		//cout << temp << '\n';

		if (temp.substr(0, 2) != "</")
		{
			stringstream ss(temp);
			char c;
			string t;
			ss >> c >> t;

			XmlNode* p_new_XmlNode = new XmlNode(t);
			if (stack_XmlNode.size() > 0)
			{
				XmlNode* parent = stack_XmlNode.top();
				if (parent->child.size() > 0)
				{
					XmlNode* last_child = parent->child.back();
					last_child->next_sib = p_new_XmlNode;
					p_new_XmlNode->prev_sib = last_child;
				}
				parent->child.push_back(p_new_XmlNode);
				p_new_XmlNode->parent = parent;
			}
			else
			{
				mRoot = p_new_XmlNode;
			}

			if (temp.back() == '/')
			{
				string attribute;
				while (ss >> attribute)
				{
					string::iterator ite = find(attribute.begin(), attribute.end(), '=');
					string property = string(attribute.begin(), ite);
					string value = string(++ite, attribute.end());
					value.erase(remove(value.begin(), value.end(), '"'), value.end());
					if (value.back() == '/')
					{
						value.pop_back();
					}

					//cout << property << ' ' << value << '\n';
					p_new_XmlNode->attribute_set[property] = value;
				}
			}
			else
			{
				stack_XmlNode.push(p_new_XmlNode);
			}

		}
		else
		{
			stack_XmlNode.pop();
		}
	}

	travel(mRoot);
}