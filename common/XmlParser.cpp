#include "XmlParser.h"


XmlParser::XmlParser()
{
    m_document = new tinyxml2::XMLDocument();
    m_rootElement = NULL;
    m_xmlTitle = new char[max_title];
    memset(m_xmlTitle,0,max_title);
    memcpy(m_xmlTitle,XMLTITLE,max_title);
}

XmlParser::~XmlParser()
{
    if(m_document)
    {
        delete m_document;
        m_document = NULL;
    }

    delete []m_xmlTitle;
}

tinyxml2::XMLElement* XmlParser::AddRootNode(const char* rootName)
{
    if(m_document)
    {
        m_rootElement = m_document->NewElement(rootName);
        m_document->LinkEndChild(m_rootElement);
    }

    return m_rootElement;
}

tinyxml2::XMLElement* XmlParser::InsertSubNode(tinyxml2::XMLElement* parentNode,const char* itemName,const char* value)
{
    if(!parentNode)
        return NULL;
    tinyxml2::XMLElement* insertNode = m_document->NewElement(itemName);
    parentNode->LinkEndChild(insertNode);

    if(strlen(value) != 0)
    {
        tinyxml2::XMLText* txt = m_document->NewText(value);
        insertNode->LinkEndChild(txt);
    }
    return insertNode;
}
void XmlParser::getXmlData(std::string& xmlBuf){
    return getXmlDataChar(const_cast<char*>(xmlBuf.data()));
}
void XmlParser::getXmlDataChar(char* xmlBuf)
{
    if(!xmlBuf)
        return;
    
    tinyxml2::XMLPrinter printer;
    if(m_document)
    {
        m_document->Accept(&printer);

        if(strlen(m_xmlTitle) != 0)
            strncpy(xmlBuf,m_xmlTitle,max_title);
        strcat(xmlBuf,(char*)printer.CStr());
    }
}