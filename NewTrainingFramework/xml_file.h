#pragma once
#include "../Utilities/rapidxml.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace rapidxml;

class xml_file
{
public:
	xml_document<> doc;
	std::string content;
	void xmlLoad (const char*);
	
	xml_node<>* getRootNode ()
	{
		return doc.first_node ();
	}
	void getChildrenNodes (const xml_node<>* node)
	{
		
	}
};

