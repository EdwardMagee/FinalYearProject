#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class FileReaderNodes
{
public:

	FileReaderNodes(std::string p_Nodes);
	std::vector<sf::Vector2i> getNodeID();
	std::vector<std::string> getNodeTypes();
	std::vector<float> getCost();


private:

	std::vector<sf::Vector2i> m_nodeID;
	std::vector<std::string> m_nodeTypes;
	std::vector<float> m_cost;

};