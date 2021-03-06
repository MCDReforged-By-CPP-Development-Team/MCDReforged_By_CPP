#include"xmlfunc.h"

bool stdfuncallconv GetNodePointerByName(TiXmlElement* pRootEle, const char* strNodeName, TiXmlElement*& Node)    //https://blog.csdn.net/masikkk/article/details/14191933?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf
{
	if (0 == strcmp(strNodeName, pRootEle->Value()))
	{
		Node = pRootEle;
		return true;
	}

	TiXmlElement* pEle = pRootEle;
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())
	{
		if (0 != strcmp(pEle->Value(), strNodeName))
		{
			GetNodePointerByName(pEle, strNodeName, Node);
		}
		else
		{
			Node = pEle;
			return true;
		}
	}

	return false;
}