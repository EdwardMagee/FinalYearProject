#include "../include/Scene.h"
#include "../include/TextureHandler.h"
#include "../include/StaticSprite.h"
#include "../include/NormalNode.h"

Scene::Scene()
{
	int temp1 = 0;
	int temp2 = 3;

	m_vectorSprites.push_back(new StaticSprite(temp1, temp2, m_textureHandler->instance()->getTexture("Harold")));
	//m_vectorSprites.push_back(new StaticSprite(0, 0, m_textureHandler->instance()->getTexture("Harold")));

	for (int i = 0; i < m_iCol; i++)
	{
		for (int j = 0; j < m_iRow; j++)
		{
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

sf::Vector2i Scene::aStar(sf::Vector2i p_startPos, sf::Vector2i p_endPos)
{
	std::list<NodeInterface*> closedList;
	std::list<NodeInterface*> openList;

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
			if (i->getF() > tempNode->getF())
			{
				tempNode = i;
			}
		}

		openList.remove(tempNode);
		closedList.push_back(tempNode);

		if (tempNode->getID().x == p_endPos.x and tempNode->getID().y == p_endPos.y) {

			std::cout << "found GOAL NODE!!" << std::endl;
		}




	}

	return sf::Vector2i();
}

void Scene::updateScene(float p_time)
{
	for (auto* i : m_vectorSprites)
	{
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

float Scene::calculateFValue(sf::Vector2i p_currentNode, sf::Vector2i p_goalNode)
{
	for (int i = p_currentNode.x; i == p_goalNode.x;)
	{
		if (p_currentNode.x < p_goalNode.x)
		{

		}

	}
}


