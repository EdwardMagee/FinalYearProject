#include "../include/Graph.h"
#include "../include/NormalNode.h"
#include "../include/EmptyNode.h"
#include "../include/TextureHandler.h"
#include "../include/StaticSprite.h"
#include "../include/FileReaderNodes.h"

Graph::Graph(std::string p_Nodes)
{
	m_fileReader = new FileReaderNodes(p_Nodes);
	m_useCurrent = false;

	for (int i = 0; i < m_iCol; i++)
	{
		for (int j = 0; j < m_iRow; j++)
		{

			for (int k = 0; k < m_fileReader->getNodeID().size(); k++)
			{
				if (j == m_fileReader->getNodeID().at(k).x and i == m_fileReader->getNodeID().at(k).y)
				{
					tempCost = m_fileReader->getCost().at(k);
					tempString = m_fileReader->getNodeTypes().at(k);
					m_useCurrent = true;
					break;
				}
				else { m_useCurrent = false;  }
			}

			if (m_useCurrent)
			{

				if (tempString == "Empty") {
					m_Graph[j][i] = new EmptyNode(tempCost);
					m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Empty"));
				}
				else if (tempString == "Slow") {
					m_Graph[j][i] = new NormalNode(tempCost);
					m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Slow"));
				}
				else if (tempString == "Speed") {
					m_Graph[j][i] = new NormalNode(tempCost);
					m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Speed"));
				}
				else if (tempString == "Splash") {
					m_Graph[j][i] = new NormalNode(tempCost);
					m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Splash"));
				}

				//m_Graph[j][i] = new EmptyNode(1000);
				//m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Empty"));
			}
			else if (j == 0 or i == 0)
			{
				m_Graph[j][i] = new EmptyNode(1000);
				m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Empty"));

			}
			else if (j == m_iRow - 1 or i == m_iCol - 1) {

				m_Graph[j][i] = new EmptyNode(1000);
				m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Empty"));

			}
			
			
			else {

				m_Graph[j][i] = new NormalNode(1);
				m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Normal"));


			}
		}
	}

	for (int j = 0; j < m_fileReader->getNodeID().size(); j++)
	{
		
		//tempx = m_fileReader->getNodeID().at(j).x; tempy = m_fileReader->getNodeID().at(j).y;

		//delete m_Graph[tempx][tempy];
		//m_Graph[tempx][tempy] = nullptr;

		
	}



	
}

std::list<NodeInterface*> Graph::aStar(sf::Vector2i p_startPos, sf::Vector2i p_endPos, float p_speed, std::vector<SpriteInterface*> p_vectorSprites)
{
	m_reachedGoal = false;

	float tempSpeed = 0;
	float GValueTemp;
	NodeInterface* tempNode;

	m_openList.clear();
	m_closedList.clear();

	m_Graph[p_startPos.x][p_startPos.y]->setG(0.0f);
	m_Graph[p_startPos.x][p_startPos.y]->setF(0.0f);

	m_openList.push_back(m_Graph[p_startPos.x][p_startPos.y]);


	for (int i = 0; i < m_iCol; i++)
	{
		for (int j = 0; j < m_iRow; j++)
		{
			m_Graph[j][i]->setPerant(nullptr);

		}
	}

	while (!m_openList.empty())
	{
		tempNode = m_openList.front();

		for (auto* i : m_openList)
		{
			if (i->getF() < tempNode->getF())
			{
				tempNode = i;
			}
		}

		counter3++;
		m_openList.remove(tempNode);
		m_closedList.push_back(tempNode);

		if (tempNode->getID().x == p_endPos.x and tempNode->getID().y == p_endPos.y) {

			std::cout << "found GOAL NODE!!" << std::endl;
			m_reachedGoal = true;
			return getPath(m_Graph[p_startPos.x][p_startPos.y], m_Graph[p_endPos.x][p_endPos.y]);
		}

		if (tempSpeed > p_speed) {
			std::cout << "Too tired" << std::endl;
			m_reachedGoal = false;
			return getPath(m_Graph[p_startPos.x][p_startPos.y], tempNode);
		}

		for (auto* j : gatherChildren(tempNode))
		{
			if (j->checkNodeType() == "EmptyNode")
				continue;

			m_isInClosedList = false;
			for (auto* k : m_closedList)
			{
				if (k == j) {
					m_isInClosedList = true;
				}
			}

			m_isOccupied = false;
			for (auto* m : p_vectorSprites) {

				if (m->getNode() == j)
					m_isOccupied = true;
			}

			if (m_isOccupied)
				continue;

			if (m_isInClosedList)
				continue;


			if (j->isDiagonal()) {
				GValueTemp = tempNode->getG() + (j->getTerrainCost() * 1.4);
			}
			else if (!j->isDiagonal()) {
				GValueTemp = tempNode->getG() + (j->getTerrainCost() * 1);
			}


			m_isInOpenList = false;
			for (auto* l : m_openList)
			{
				if (l == j) {
					m_isInOpenList = true;
				}
			}

			if (GValueTemp < j->getG() or !m_isInOpenList) {

				j->setG(GValueTemp);

				j->setH(calculateHValue(tempNode->getID(), p_endPos));

				j->setF(j->getG() + j->getH());

				j->setPerant(tempNode);

				tempSpeed = +j->getG();

				if (!m_isInOpenList)
					m_openList.push_back(j);

			}

		}

	}
}

std::list<NodeInterface*> Graph::gatherChildren(NodeInterface * p_currentNode)
{
	m_tempList.clear();

	auto getCloseNode = [&](std::list<NodeInterface*> p_TempList, int x = 0, int y = 0) {
		m_tempList.push_back(m_Graph[p_currentNode->getID().x + x][p_currentNode->getID().y + y]); //Left (1)
		m_Graph[p_currentNode->getID().x + x][p_currentNode->getID().y + y]->setDiagonal(false);
	};
	getCloseNode(m_tempList, -1, 0);
	getCloseNode(m_tempList, 1, 0);
	getCloseNode(m_tempList, 0, 1);
	getCloseNode(m_tempList, 0, -1);
	getCloseNode(m_tempList, 1, 1);
	getCloseNode(m_tempList, -1, 1);
	getCloseNode(m_tempList, -1, -1);
	getCloseNode(m_tempList, 1, -1);


	return m_tempList;
}

float Graph::calculateHValue(sf::Vector2i p_startPos, sf::Vector2i p_endPos)
{
	float tempx;
	float tempy;
	float tempH;

	tempx = (float)p_startPos.x - p_endPos.x;
	tempy = (float)p_startPos.y - p_endPos.y;
	tempH = sqrt((tempx * tempx) + (tempy * tempy));

	if (tempH < 0)
	{
		tempH = tempH * -1;
	}

	return tempH;

	
}

std::list<NodeInterface*> Graph::getPath(NodeInterface * p_start, NodeInterface * p_end)
{
	m_pathList.clear();
	NodeInterface* currentNode = p_end;

	while (currentNode != p_start)
	{
		m_pathList.push_front(currentNode);
		currentNode = currentNode->getPerant();
	}

	return m_pathList;
}

sf::Vector2i Graph::getGoal(NodeInterface * p_Goal, NodeInterface * p_Start, std::vector<SpriteInterface*> p_vectorSprites)
{
	std::vector<sf::Vector2i> tempVector;
	sf::Vector2i temp2i;
	int totalcounter;
	totalcounter = 0;
	float lowestH;
	lowestH = 100.f;

	for (auto* i : gatherChildren(p_Goal))
	{


		if (i->checkNodeType() == "EmptyNode")
			continue;

		m_isOccupied = false;
		for (auto* m : p_vectorSprites) {

			if (m->getNode() == i)
				m_isOccupied = true;
		}

		if (m_isOccupied)
			continue;

		totalcounter++;

		tempVector.push_back(sf::Vector2i(i->getID().x, i->getID().y));

		//temp.x = i->getID().x;
		//temp.y = i->getID().y;

		//return temp;

	}

	for (int j = 0; j < tempVector.size(); j++)
	{
		if (calculateHValue(sf::Vector2i(p_Start->getID().x, p_Start->getID().y), tempVector[j]) < lowestH)
		{
			lowestH = calculateHValue(sf::Vector2i(p_Start->getID().x, p_Start->getID().y), tempVector[j]);
			temp2i = tempVector[j];
		}

	}



	return temp2i;
}


NodeInterface* Graph::getNode(sf::Vector2i p_getNode)
{
	return m_Graph[p_getNode.x][p_getNode.y];
}

std::pair<int, int> Graph::getColRow()
{
	return std::make_pair(m_iCol, m_iRow);
}

bool Graph::isGoalReached()
{
	return m_reachedGoal;
}
