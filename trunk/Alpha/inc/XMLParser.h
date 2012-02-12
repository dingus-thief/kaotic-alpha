#ifndef XML_PARSER_H
#define XML_PARSER_H

#include "TinyXML/tinyxml.h"
#include <sstream>

namespace Kaotic_Alpha
{
	class XMLParser
	{
	protected:
		TiXmlDocument* xmlFile;
		TiXmlElement*  rootNode;
	private:
		std::string intToString(int intToConvert);
	public:
		XMLParser();
		XMLParser(const char* fileName);
		~XMLParser();

		bool openXmlFile(const char* fileName);
		TiXmlElement* SearchForElement(TiXmlElement* searchEle, char* nodeName);
		TiXmlElement* SearchForElement(TiXmlElement* searchEle, char* nodeName, int id);

		//Getters
		TiXmlElement* getXmlRootNode(){ return rootNode; }
	};
}
#endif
