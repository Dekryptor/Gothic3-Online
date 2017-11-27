#ifndef _XMLWRAPPER_H
#define _XMLWRAPPER_H
#include "TinyXML\tinyxml.h"
#define XML_PUSH_VARS(fileName)\
	TiXmlElement* _element = 0; \
	TiXmlDocument _doc(fileName); \
	bool _loadResult = _doc.LoadFile()

#define XML_PARAM(variable, paramName) \
	const char* ##variable = 0;\
	_element = 0;	\
	if( _loadResult ) \
	{					\
		TiXmlElement* _root = _doc.FirstChildElement( "Sative_g3mp" );\
		_element = _root->FirstChildElement( paramName );\
		if( _element ) \
		{ \
			##variable = _element->GetText();\
		}\
		else\
		{\
			##variable = "NULL";\
		}\
	}\
	else\
	{\
		MessageBoxA(NULL, "Cannot open XML file!", "Sative's XML Wrapper", MB_OK);\
		ExitProcess(0);\
	}
#endif