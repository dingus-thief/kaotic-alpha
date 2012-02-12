#include "XMLParser.h"
#include "GameLog.h"

Kaotic_Alpha::XMLParser::XMLParser()
{

}

Kaotic_Alpha::XMLParser::XMLParser(const char* fileName) //Allow the construction of the object and intialize the xml file simultaneously
{
	openXmlFile(fileName);
}

Kaotic_Alpha::XMLParser::~XMLParser()
{
}

bool Kaotic_Alpha::XMLParser::openXmlFile(const char* fileName)
{
	xmlFile = new TiXmlDocument(fileName);

	bool loadOkay = xmlFile->LoadFile();
	if (loadOkay)
	{
		WriteLog << fileName << " opened." <<std::endl;
		rootNode = xmlFile->FirstChildElement();
		return true;
	}
	else
	{
		WriteLog << "Error opening " << fileName << "." <<std::endl;
		return false;
	}
}

TiXmlElement* Kaotic_Alpha::XMLParser::SearchForElement(TiXmlElement* searchEle, char* nodeName)
{
   if (!searchEle) return NULL;
 
   TiXmlElement* pElement = searchEle->FirstChildElement();
   
   while (pElement)
   {
		if(strcmp(pElement->Value(), nodeName) == 0)
			return pElement;
		pElement = pElement->NextSiblingElement();
   }
   return NULL;
}

TiXmlElement* Kaotic_Alpha::XMLParser::SearchForElement(TiXmlElement* searchEle, char* nodeName, int id)
{
   if (!searchEle) return NULL;
 
   TiXmlElement* pElement = searchEle->FirstChildElement();
   
   while (pElement)
   {
		if( strcmp( pElement->Value(), nodeName ) == 0 )
		{
			if( strcmp( pElement->Attribute("ID"), intToString(id).c_str() ) == 0 )
				return pElement;
		}
		pElement = pElement->NextSiblingElement();
   }
   return NULL;
}

std::string Kaotic_Alpha::XMLParser::intToString(int intToConvert)
{
	std::string outputString;
	std::stringstream stringConverter;
	stringConverter << intToConvert;
	outputString = stringConverter.str();
	return outputString;
}
