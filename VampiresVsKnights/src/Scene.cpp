#include "../include/Scene.h"
#include "../include/TextureHandler.h"
#include "../include/StaticSprite.h"
#include "../include/NormalNode.h"
#include "../include/EmptyNode.h"

Scene::Scene()
{
	int temp1 = 7;
	int temp2 = 3;

	counter2 = 0;
	//int tempG1 = 6;
	//int tempG2 = 5;

	m_vectorSprites.push_back(new StaticSprite(temp1, temp2, m_textureHandler->instance()->getTexture("Harold")));
	//m_vectorSprites.push_back(new StaticSprite(0, 0, m_textureHandler->instance()->getTexture("Harold")));

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

				if (temp1 == j)
				{
					if (temp2 == i)
					{
						m_Graph[j][i]->containSprite(m_vectorSprites[0]);
					}
				}
			}
		}
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

std::list<NodeInterface*> Scene::aStar(sf::Vector2i p_startPos, sf::Vector2i p_endPos)
{
	std::list<NodeInterface*> closedList;
	std::list<NodeInterface*> openList;

	float GValueTemp;
	NodeInterface* tempNode;

	openList.empty();
	closedList.empty();

	m_Graph[p_startPos.x][p_startPos.y]->setG(0.0f);
	m_Graph[p_startPos.x][p_startPos.y]->setF(0.0f);
	
	openList.push_back(m_Graph[p_startPos.x][p_startPos.y]);

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
			return getPath(m_Graph[p_startPos.x][p_startPos.y], m_Graph[p_endPos.x][p_endPos.y]);
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
			
				if (!isInOpenList)
				openList.push_back(j);

			}

			

		/*	float lowestValue = tempNode->getF();
			if (j->getF() >= lowestValue)
				continue;

			pathList.push_back(tempNode);
			*/
			/*if (isInOpenList)
			{
				if (j->getG() > tempNode->getG())
				{
					continue;
				}
			}*/

		}

	}
}

void Scene::updateScene(float p_time)
{
	counter++;

	for (auto* i : m_vectorSprites)
	{
		if (counter == 101)
		{
			tempList = aStar(sf::Vector2i(7, 3), sf::Vector2i(1, 1));

			//for (auto* j : tempList)
		//	{
				//i->setSpritePos(j->getID().x, j->getID().y);#

			std::cout << tempList.size() << std::endl;

		}
				if (counter2 == 2)
				{
					std::cout << "X:" << tempList.front()->getID().x << "Y:" << tempList.front()->getID().y << std::endl;
					m_Graph[tempList.front()->getID().x][tempList.front()->getID().y]->containSprite(m_vectorSprites[0]);
					tempList.pop_front();
					counter2 = 0;
				}
				
		//	}

		

		i->update(p_time);

		
	}

	for (int i = 0; i < m_iCol; i++)
	{
		for (int j = 0; j < m_iRow; j++)
		{
			m_Graph[j][i]->updateNode(p_time);

			/*if (i == 0)
			{
				if (j == 6)
				{
					m_Graph[j][i]->containSprite(m_vectorSprites[1]);
				}
			}*/
			


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
	std::list<NodeInterface*> tempList;

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
}

std::list<NodeInterface*> Scene::getPath(NodeInterface * p_start, NodeInterface * p_end)
{
	std::list<NodeInterface*> pathList;
	NodeInterface* currentNode = p_end;

	while (currentNode != p_start)
	{
		pathList.push_front(currentNode);
		currentNode = currentNode->getPerant();
	}

	return pathList;
}





