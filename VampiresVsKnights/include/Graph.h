#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <list>
#include <math.h>


class NodeInterface;
class TextureHandler;
class SpriteInterface;
class FileReaderNodes;

class Graph {

public:

	Graph(std::string p_Nodes);
	std::list<NodeInterface*> aStar(sf::Vector2i p_startPos, sf::Vector2i p_endPos, float p_speed, std::vector<SpriteInterface*> p_vectorSprites);
	std::list<NodeInterface*> gatherChildren(NodeInterface* p_currentNode);
	float calculateHValue(sf::Vector2i p_startPos, sf::Vector2i p_endPos);
	std::list<NodeInterface*> getPath(NodeInterface* p_start, NodeInterface* p_end);
	sf::Vector2i getGoal(NodeInterface* p_Goal, NodeInterface* p_Start, std::vector<SpriteInterface*> p_vectorSprites);
	NodeInterface* getNode(sf::Vector2i p_getNode);
	std::pair<int, int> getColRow();
	bool isGoalReached();

protected:

	int counter3;
	static const int m_iCol = 8;
	static const int m_iRow = 16;

	float tempCost; 
	std::string tempString;

	std::array<std::array<NodeInterface*, m_iCol>, m_iRow> m_Graph;
	TextureHandler * m_textureHandler;
	FileReaderNodes * m_fileReader;

	std::list<NodeInterface*> m_closedList;
	std::list<NodeInterface*> m_openList;
	std::list<NodeInterface*> m_pathList;
	std::list<NodeInterface*> m_tempList;

	bool m_isInClosedList;
	bool m_isInOpenList;
	bool m_isOccupied;
	bool m_reachedGoal;
	bool m_useCurrent;


};