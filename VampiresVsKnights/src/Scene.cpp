#include "../include/Scene.h"
#include "../include/TextureHandler.h"
#include "../include/StaticSprite.h"
#include "../include/NormalNode.h"
#include "../include/EmptyNode.h"
#include "../include/FileReader.h"

Scene::Scene()
{
	m_prevoiusNode = nullptr;

	m_gameOver = false;

	m_fileReader = new FileReader("Assests/Levels\\LevelOne.txt");

	counter2 = 0;

	for (int j = 0; j < m_fileReader->getPositions().size(); j++) {

		m_vectorSprites.push_back(new StaticSprite(m_fileReader->getPositions().at(j).x, m_fileReader->getPositions().at(j).y, m_textureHandler->instance()->getTexture(m_fileReader->getTexture().at(j)), m_fileReader->getSpeedValues().at(j), m_fileReader->getHealth().at(j), m_fileReader->getAttack().at(j)));
		//m_vectorSprites.push_back(new StaticSprite(0, 0, m_textureHandler->instance()->getTexture("Harold")));
	}

	for (int i = 0; i < m_iCol; i++)
	{
		for (int j = 0; j < m_iRow; j++)
		{
			if (j == 0 or i == 0)
			{
				m_Graph[j][i] = new EmptyNode(1000);
				m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Empty"));
				
			}
			else if (j == m_iRow - 1 or i == m_iCol - 1) {

				m_Graph[j][i] = new EmptyNode(1000);
				m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Empty"));

			}
			else if (j == 6 and i == 6)
			{
				m_Graph[j][i] = new EmptyNode(1000);
				m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Empty"));
			}
			else {

				m_Graph[j][i] = new NormalNode(1);
				m_Graph[j][i]->constructNode(j, i, m_textureHandler->instance()->getTexture("Normal"));

				
			}
		}
	}

	for (int k = 0; k < m_fileReader->getPositions().size(); k++) {

		m_vectorSprites[k]->setNode(m_Graph[m_fileReader->getPositions().at(k).x][m_fileReader->getPositions().at(k).y]); // ->containSprite(m_vectorSprites[0]);
	}


}

Scene::~Scene()
{
	for (auto* i : m_vectorTemp)
	{
		delete i;
		i = nullptr;
	}

	m_vectorTemp.clear();

	for (auto* j : m_vectorSprites)
	{
		delete j;
		j = nullptr;
	}

	m_vectorSprites.clear();
}

std::list<NodeInterface*> Scene::aStar(sf::Vector2i p_startPos, sf::Vector2i p_endPos, float p_speed)
{
	reachedGoal = false;

	float tempSpeed = 0;
	float GValueTemp;
	NodeInterface* tempNode;

	openList.clear();
	closedList.clear();

	m_Graph[p_startPos.x][p_startPos.y]->setG(0.0f);
	m_Graph[p_startPos.x][p_startPos.y]->setF(0.0f);
	
	openList.push_back(m_Graph[p_startPos.x][p_startPos.y]);


	for (int i = 0; i < m_iCol; i++)
	{
		for (int j = 0; j < m_iRow; j++)
		{
			m_Graph[j][i]->setPerant(nullptr);

		}
	}

	while (!openList.empty())
	{
		tempNode = openList.front();

		for (auto* i : openList)
		{
			if (i->getF() < tempNode->getF())
			{
				tempNode = i;
			}
		}

		counter3++;
		openList.remove(tempNode);
		closedList.push_back(tempNode);

		if (tempNode->getID().x == p_endPos.x and tempNode->getID().y == p_endPos.y) {

			std::cout << "found GOAL NODE!!" << std::endl;
			reachedGoal = true;
			return getPath(m_Graph[p_startPos.x][p_startPos.y], m_Graph[p_endPos.x][p_endPos.y]);
		}

		if (tempSpeed > p_speed) {
			std::cout << "Too tired" << std::endl;
			return getPath(m_Graph[p_startPos.x][p_startPos.y], tempNode);
		}

		for (auto* j : gatherChildren(tempNode))
		{
			if (j->checkNodeType() == "EmptyNode")
				continue;

			isInClosedList = false;
			for (auto* k : closedList)
			{
				if (k == j) {
					isInClosedList = true;
				}
			}

			isOccupied = false;
			for (auto* m : m_vectorSprites) {

				if (m->getNode() == j)
					isOccupied = true;
			}

			if (isOccupied)
				continue;

			if (isInClosedList)
				continue;


			if (j->isDiagonal()) {
				GValueTemp = tempNode->getG() + (j->getTerrainCost() * 1.4);
			}
			else if (!j->isDiagonal()) {
				GValueTemp = tempNode->getG() + (j->getTerrainCost() * 1);
			}


			isInOpenList = false;
			for (auto* l : openList)
			{
				if (l == j) {
					isInOpenList = true;
				}
			}

			if (GValueTemp < j->getG() or !isInOpenList) {

				j->setG(GValueTemp);

				j->setH(calculateHValue(tempNode->getID(), p_endPos));

				j->setF(j->getG() + j->getH());

				j->setPerant(tempNode);

				tempSpeed =+ j->getG();
			
				if (!isInOpenList)
				openList.push_back(j);

			}

		}

	}
}

void Scene::updateScene(float p_time)
{
	std::cout << m_vectorSprites[0]->getHealth() << std::endl;

	if (m_vectorSprites[0]->getHealth() < 0)
	{
		m_gameOver = true;
	}

	if (counter2 == 2)
	{
		for (int j = 1; j < m_fileReader->getPositions().size(); j++) {
			tempList = aStar(sf::Vector2i(m_vectorSprites[j]->getNode()->getID().x, m_vectorSprites[j]->getNode()->getID().y), getGoal(), m_vectorSprites[j]->getSpeed());
			m_vectorSprites[j]->setNode(m_Graph[tempList.back()->getID().x][tempList.back()->getID().y]);

			if (reachedGoal)
				m_vectorSprites[0]->setHealth(m_vectorSprites[j]->getAttack());
			
		}

		counter2 = 0;
	}

	//m_gameOver = true;
	/*
	counter++;

	if (counter4 == 2)
	{
		std::cout << "yep" << std::endl;
		tempList = aStar(sf::Vector2i(1, 1), sf::Vector2i(6, 4), m_vectorSprites[0]->getSpeed());
		counter4 = 0;
	}

	if (counter == 2)
	{
		tempList = aStar(sf::Vector2i(m_vectorSprites[0]->getNode()->getID().x, m_vectorSprites[0]->getNode()->getID().y), sf::Vector2i(1, 1), m_vectorSprites[0]->getSpeed());

		std::cout << tempList.size() << std::endl;

		

	}
	if (counter2 == 2)
	{
		if (m_prevoiusNode != nullptr)
			m_prevoiusNode->removeSprite();

		m_prevoiusNode = nullptr;

		m_vectorSprites[0]->setNode(m_Graph[tempList.front()->getID().x][tempList.front()->getID().y]);
		std::cout << "X:" << tempList.front()->getID().x << "Y:" << tempList.front()->getID().y << std::endl;
		//m_Graph[tempList.front()->getID().x][tempList.front()->getID().y]->containSprite(m_vectorSprites[0]);
		//m_prevoiusNode = m_Graph[tempList.front()->getID().x][tempList.front()->getID().y];
		tempList.pop_front();
		counter2 = 0;

		

	}
	*/

	for (auto* i : m_vectorSprites)
	{			
		i->update(p_time);	
	}

	for (int i = 0; i < m_iCol; i++)
	{
		for (int j = 0; j < m_iRow; j++)
		{
			m_Graph[j][i]->updateNode(p_time);

		}
	}


	

}


bool Scene::loadLevel(std::string p_level)
{
	return false;
}

std::vector<sf::Sprite*> Scene::getSpriteVector(){
	
	m_vectorTemp.clear();

	for (int i = 0; i < m_iCol; i++)
	{
		for (int j = 0; j < m_iRow; j++)
		{
			m_vectorTemp.push_back(m_Graph[j][i]->getSprite());
		}
	}

	for (int j = 0; m_vectorSprites.size() > j; j++)
	{
		m_vectorTemp.push_back(m_vectorSprites.at(j)->getSprite());
	}

	return m_vectorTemp;
	
}

std::list<NodeInterface*> Scene::gatherChildren(NodeInterface * p_currentNode)
{
	//std::list<NodeInterface*> tempList;
	tempList.clear();

	tempList.push_back(m_Graph[p_currentNode->getID().x + 1][p_currentNode->getID().y]); //Right (1)
	m_Graph[p_currentNode->getID().x + 1][p_currentNode->getID().y]->setDiagonal(false); 

	tempList.push_back(m_Graph[p_currentNode->getID().x][p_currentNode->getID().y + 1]); //Up (2)
	m_Graph[p_currentNode->getID().x][p_currentNode->getID().y + 1]->setDiagonal(false);

	tempList.push_back(m_Graph[p_currentNode->getID().x + 1][p_currentNode->getID().y + 1]); //RightUp (3)
	m_Graph[p_currentNode->getID().x + 1][p_currentNode->getID().y + 1]->setDiagonal(true);

	tempList.push_back(m_Graph[p_currentNode->getID().x - 1][p_currentNode->getID().y]); //Left (4)
	m_Graph[p_currentNode->getID().x - 1][p_currentNode->getID().y]->setDiagonal(false);

	tempList.push_back(m_Graph[p_currentNode->getID().x - 1][p_currentNode->getID().y + 1]);//Left Up (5)
	m_Graph[p_currentNode->getID().x - 1][p_currentNode->getID().y + 1]->setDiagonal(true);

	tempList.push_back(m_Graph[p_currentNode->getID().x][p_currentNode->getID().y - 1]); //Down (6)
	m_Graph[p_currentNode->getID().x][p_currentNode->getID().y - 1]->setDiagonal(false);

	tempList.push_back(m_Graph[p_currentNode->getID().x - 1][p_currentNode->getID().y - 1]); // Down Left (7)
	m_Graph[p_currentNode->getID().x - 1][p_currentNode->getID().y - 1]->setDiagonal(true);

	tempList.push_back(m_Graph[p_currentNode->getID().x + 1][p_currentNode->getID().y - 1]); // Down Right (8)
	m_Graph[p_currentNode->getID().x + 1][p_currentNode->getID().y - 1]->setDiagonal(true);

	return tempList;
}

float Scene::calculateHValue(sf::Vector2i p_startPos, sf::Vector2i p_endPos)
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

void Scene::increaseCounter()
{
	counter2++;
	//cout << m_vectorSprites[0]->
}

void Scene::increaseOtherCounter() {
	counter4++;

}

bool Scene::getGameOver()
{
	return m_gameOver;
}

sf::Vector2i Scene::getGoal()
{
	sf::Vector2i temp;

	for (auto* i : gatherChildren(m_vectorSprites[0]->getNode()))
	{
		if (i->checkNodeType() == "EmptyNode")
			continue;

		isOccupied = false;
		for (auto* m : m_vectorSprites) {

			if (m->getNode() == i)
				isOccupied = true;
		}

		if (isOccupied)
			continue;

		temp.x = i->getID().x;
		temp.y = i->getID().y;

		return temp;
	}

	return sf::Vector2i();
}

std::list<NodeInterface*> Scene::getPath(NodeInterface * p_start, NodeInterface * p_end)
{
	
	pathList.clear();
	NodeInterface* currentNode = p_end;

	while (currentNode != p_start)
	{
		pathList.push_front(currentNode);
		currentNode = currentNode->getPerant();
	}

	return pathList;
}





