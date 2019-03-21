#include "..\include\FileReaderNodes.h"
#include <iostream>

FileReaderNodes::FileReaderNodes(std::string p_Nodes)
{

	std::fstream nodesFile(p_Nodes, std::ios_base::in);
	std::string nodesLine = "";

	if (nodesFile.is_open()) {

		while (getline(nodesFile, nodesLine))
		{
			std::string str;
			std::istringstream isstr(nodesLine);
			isstr >> str;

			std::string tempTag; sf::Vector2i tempID; float tempCost;

			if (str == "x:") { isstr >> tempID.x; }

			isstr >> str;

			if (str == "y:") { isstr >> tempID.y; }

			isstr >> str;

			if (str == "type:") { isstr >> tempTag; }

			isstr >> str;

			if (str == "cost:") { isstr >> tempCost; }

			m_nodeID.push_back(tempID);
			m_nodeTypes.push_back(tempTag);
			m_cost.push_back(tempCost);
		}
	}
	else {
		std::cout << "cannot open the File" << std::endl;
	}
}

std::vector<sf::Vector2i> FileReaderNodes::getNodeID()
{
	return m_nodeID;
}

std::vector<std::string> FileReaderNodes::getNodeTypes()
{
	return m_nodeTypes;
}

std::vector<float> FileReaderNodes::getCost()
{
	return m_cost;
}
