#include "xml_file.h"


void xml_file::xmlLoad (const char* path)
{
	std::ifstream file (path);
	std::stringstream buffer;
	buffer << file.rdbuf ();
	file.close ();
	content = buffer.str ();
	doc.parse<0> (&content[0]);
}
