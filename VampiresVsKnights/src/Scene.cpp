#include "../include/Scene.h"
#include "../include/TextureHandler.h"
#include "../include/StaticSprite.h"
#include "../include/NormalNode.h"
#include "../include/EmptyNode.h"
#include "../include/FileReader.h"

Scene::Scene()
{
	m_prevoiusNode = nullptr;
	m_gameState = PlayersTurn;
	currentEnemy = 1;

	m_selectorTexture = m_textureHandler->instance()->getTexture("Selector");
	m_selector.setTexture(m_selectorTexture);
	m_selectorPos = sf::Vector2i(1, 1);
	m_selector.setPosition(m_selectorPos.x * 64 + 100, m_selectorPos.y * 64 + 50);

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
			else if (j == 6 and i == 4)
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
	//std::cout << m_vectorSprites[0]->getHealth() << std::endl;

	//m_selector.set

	switch (m_gameState)
	{
	case PlayersTurn:
		m_selector.setPosition((m_selectorPos.x * 64) + 100, (m_selectorPos.y * 64) + 50);
		break;

	case PlayersMoving:

		movingCounter += p_time;

		if (movingCounter > 0.61f)
		{
			if (!tempList.empty()) {
				m_vectorSprites[0]->setNode(m_Graph[tempList.front()->getID().x][tempList.front()->getID().y]);
				tempList.pop_front();
			}
			else {
				for (int i = 1; i < m_vectorSprites.size(); i++)
				{
					if (m_vectorSprites[i]->getNode() == temp)
					{
						if (reachedGoal) {
							m_vectorSprites[i]->setHealth(m_vectorSprites[0]->getAttack());
						}
					}
				}
				m_gameState = EnemyTurn;
			}
			movingCounter = 0.0f;
		}
		break;

	case PlayersMoved:

		temp = m_Graph[m_selectorPos.x][m_selectorPos.y];

		if (temp->checkNodeType() == "EmptyNode") {
			m_gameState = PlayersTurn;
			break;
		}
		
		for (int i = 1; i < m_vectorSprites.size(); i++)
		{
			if (m_vectorSprites[i]->getNode() == temp)
			{
				tempList = aStar(sf::Vector2i(m_vectorSprites[0]->getNode()->getID().x, m_vectorSprites[0]->getNode()->getID().y), getGoal(m_vectorSprites[i]->getNode()), m_vectorSprites[0]->getSpeed());
				//m_vectorSprites[0]->setNode(m_Graph[tempList.back()->getID().x][tempList.back()->getID().y]);

				if (reachedGoal) {
					//m_vectorSprites[i]->setHealth(m_vectorSprites[0]->getAttack());
					m_gameState = PlayersMoving;
					break;
				}

				m_gameState = PlayersMoving;
				break;

			}
		}

		if (m_gameState != PlayersMoving)
		{
			tempList = aStar(sf::Vector2i(m_vectorSprites[0]->getNode()->getID().x, m_vectorSprites[0]->getNode()->getID().y), temp->getID(), m_vectorSprites[0]->getSpeed());
			//m_vectorSprites[0]->setNode(m_Graph[tempList.back()->getID().x][tempList.back()->getID().y]);
			m_gameState = PlayersMoving;
		}

		break;

	case EnemyTurn:

		//for (int j = 1; j < m_vectorSprites.size(); j++) {
		if (currentEnemy != m_vectorSprites.size()) {
			if (4.2f > calculateHValue(sf::Vector2i(m_vectorSprites[currentEnemy]->getNode()->getID().x, m_vectorSprites[currentEnemy]->getNode()->getID().y), sf::Vector2i(m_vectorSprites[0]->getNode()->getID().x, m_vectorSprites[0]->getNode()->getID().y)))
			{
				tempList = aStar(sf::Vector2i(m_vectorSprites[currentEnemy]->getNode()->getID().x, m_vectorSprites[currentEnemy]->getNode()->getID().y), getGoal(m_vectorSprites[0]->getNode()), m_vectorSprites[currentEnemy]->getSpeed());
				//m_vectorSprites[currentEnemy]->setNode(m_Graph[tempList.back()->getID().x][tempList.back()->getID().y]);

				if (reachedGoal)
					m_vectorSprites[currentEnemy]->doDamage(true);
				//m_vectorSprites[0]->setHealth(m_vectorSprites[currentEnemy]->getAttack());
			}
			m_gameState = EnemyMove;
			break;
		}
		else {
			currentEnemy = 1;
			m_gameState = PlayersTurn;
			break;
		}
	
	case EnemyMove:
		
		if (tempList.empty()) {

			//if (reachedGoal)
			//	m_vectorSprites[0]->setHealth(m_vectorSprites[currentEnemy]->getAttack());

			if (m_vectorSprites[currentEnemy]->isDoingDamage()){
				m_vectorSprites[0]->setHealth(m_vectorSprites[currentEnemy]->getAttack());
				m_vectorSprites[currentEnemy]->doDamage(false);
		}

			m_gameState = EnemyTurn;
			currentEnemy++;
			break;
		}
		else {
			movingCounter += p_time;

			if (movingCounter > 0.37f)
			{

				m_vectorSprites[currentEnemy]->setNode(m_Graph[tempList.front()->getID().x][tempList.front()->getID().y]);
				tempList.pop_front();
				movingCounter = 0.0f;
			}

			break;
		}
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

	if (m_vectorSprites[0]->getHealth() < 0)
	{
		m_gameOver = true;
	}

	if (m_vectorSprites.back()->getHealth() < 0)
	{
		m_gameOver = true;
	}
	
	int tempSize = m_vectorSprites.size() - 1;
	for (int j = 1; j < tempSize; j++) {

		if (m_vectorSprites[j]->getHealth() < 0)
		{
			m_vectorSprites.erase(m_vectorSprites.begin() + j);
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

	tempList.push_back(m_Graph[p_currentNode->getID().x - 1][p_currentNode->getID().y]); //Left (1)
	m_Graph[p_currentNode->getID().x - 1][p_currentNode->getID().y]->setDiagonal(false);

	tempList.push_back(m_Graph[p_currentNode->getID().x + 1][p_currentNode->getID().y]); //Right (2)
	m_Graph[p_currentNode->getID().x + 1][p_currentNode->getID().y]->setDiagonal(false); 

	tempList.push_back(m_Graph[p_currentNode->getID().x][p_currentNode->getID().y + 1]); //Up (3)
	m_Graph[p_currentNode->getID().x][p_currentNode->getID().y + 1]->setDiagonal(false);

	tempList.push_back(m_Graph[p_currentNode->getID().x][p_currentNode->getID().y - 1]); //Down (4)
	m_Graph[p_currentNode->getID().x][p_currentNode->getID().y - 1]->setDiagonal(false);

	tempList.push_back(m_Graph[p_currentNode->getID().x + 1][p_currentNode->getID().y + 1]); //RightUp (5)
	m_Graph[p_currentNode->getID().x + 1][p_currentNode->getID().y + 1]->setDiagonal(true);


	tempList.push_back(m_Graph[p_currentNode->getID().x - 1][p_currentNode->getID().y + 1]);//Left Up (6)
	m_Graph[p_currentNode->getID().x - 1][p_currentNode->getID().y + 1]->setDiagonal(true);

	

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

sf::Vector2i Scene::getGoal(NodeInterface* p_Node)
{
	sf::Vector2i temp;

	for (auto* i : gatherChildren(p_Node))
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

sf::Sprite Scene::getSelector()
{
	return m_selector;
}

void Scene::incrementSelector(sf::Vector2i p_newPos)
{
	if (m_selectorPos.x != 14)
	m_selectorPos.x += p_newPos.x;

	if (m_selectorPos.y != 6)
	m_selectorPos.y += p_newPos.y;
}

void Scene::decreaseSelector(sf::Vector2i p_newPos)
{
	if(m_selectorPos.x != 1)
	m_selectorPos.x -= p_newPos.x;

	if(m_selectorPos.y != 1)
	m_selectorPos.y -= p_newPos.y;
}

void Scene::PlayersMove()
{
	if (m_gameState == PlayersTurn)
	{
		m_gameState = PlayersMoved;
		std::cout << m_vectorSprites[0]->getHealth() << std::endl;
	}
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





