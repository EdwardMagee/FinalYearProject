#include "../include/Scene.h"
#include "../include/TextureHandler.h"
#include "../include/StaticSprite.h"
#include "../include/NormalNode.h"
#include "../include/EmptyNode.h"
#include "../include/FileReader.h"
#include "../include/Graph.h"

Scene::Scene()
{
	playerkilled = false;
	m_prevoiusNode = nullptr;
	m_gameState = PlayersTurn;
	currentEnemy = 3;
	currentPlayer = 0;
	startofKnights = 0;
	startofVampires = 3;
	newcurrentPlayer = false;

	m_Graph = new Graph();

	m_selectorTexture = m_textureHandler->instance()->getTexture("Selector");
	m_selector.setTexture(m_selectorTexture);
	m_selectorPos = sf::Vector2i(1, 1);
	m_selector.setPosition(m_selectorPos.x * 64 + 100, m_selectorPos.y * 64 + 50);

	m_gameOver = false;

	m_fileReader = new FileReader("Assests/Levels\\LevelOne.txt");

	counter2 = 0;

	totalCharacters = m_fileReader->getPositions().size();
	for (int j = 0; j < m_fileReader->getPositions().size(); j++) {

		m_vectorSprites.push_back(new StaticSprite(m_fileReader->getPositions().at(j).x, m_fileReader->getPositions().at(j).y, m_textureHandler->instance()->getTexture(m_fileReader->getTexture().at(j)), m_fileReader->getSpeedValues().at(j), m_fileReader->getHealth().at(j), m_fileReader->getAttack().at(j)));
		//m_vectorSprites.push_back(new StaticSprite(0, 0, m_textureHandler->instance()->getTexture("Harold")));
	}

	for (int k = 0; k < m_fileReader->getPositions().size(); k++) {

		//m_vectorSprites[k]->setNode(m_Graph[m_fileReader->getPositions().at(k).x][m_fileReader->getPositions().at(k).y]); // ->containSprite(m_vectorSprites[0]);
		m_vectorSprites[k]->setNode(m_Graph->getNode(sf::Vector2i(m_fileReader->getPositions().at(k).x, m_fileReader->getPositions().at(k).y)));
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

void Scene::updateScene(float p_time)
{
	//std::cout << m_vectorSprites[0]->getHealth() << std::endl;

	//m_selector.set

	if (test == true)
	{

	}

	switch (m_gameState)
	{
	case PlayersTurn:
		m_selector.setPosition((m_selectorPos.x * 64) + 100, (m_selectorPos.y * 64) + 50);
		break;

	
	case PlayersMoved:

		temp = m_Graph->getNode(sf::Vector2i(m_selectorPos.x,m_selectorPos.y));

		if (temp->checkNodeType() == "EmptyNode") {
			m_gameState = PlayersTurn;
			break;
		}

			for (int i = 0; i < startofVampires; i++)
			{
				if (i == 2)
				{

				}
				if (m_vectorSprites[i]->getNode() == temp)
				{
					currentPlayer = i;
					m_gameState = PlayersTurn;
					newcurrentPlayer = true;
					break;
					
				}

			}

		if (newcurrentPlayer == true)
		{
			newcurrentPlayer = false;
			break;
		}
		
		
		for (int i = startofVampires; i < m_vectorSprites.size(); i++)
		{
			if (m_vectorSprites[i]->getNode() == temp)
			{
				m_pathList = m_Graph->aStar(sf::Vector2i(m_vectorSprites[currentPlayer]->getNode()->getID().x, m_vectorSprites[currentPlayer]->getNode()->getID().y), m_Graph->getGoal(m_vectorSprites[i]->getNode(), m_vectorSprites[currentPlayer]->getNode(), m_vectorSprites),
					m_vectorSprites[currentPlayer]->getSpeed(), m_vectorSprites);
				//tempList = aStar(sf::Vector2i(m_vectorSprites[0]->getNode()->getID().x, m_vectorSprites[0]->getNode()->getID().y), sf::Vector2i(m_vectorSprites[i]->getNode()->getID().x, m_vectorSprites[i]->getNode()->getID().y), m_vectorSprites[0]->getSpeed());
				//m_vectorSprites[0]->setNode(m_Graph[tempList.back()->getID().x][tempList.back()->getID().y]);

				//if (reachedGoal) {
					//m_vectorSprites[i]->setHealth(m_vectorSprites[0]->getAttack());
				//	m_gameState = PlayersMoving;
				//	break;
				//}

				if (m_pathList.back() == m_vectorSprites[i]->getNode())
				{
					m_pathList.pop_back();
				}


				m_gameState = PlayersMoving;
				break;

			}
		}

		if (m_gameState != PlayersMoving)
		{
			m_pathList = m_Graph->aStar(sf::Vector2i(m_vectorSprites[currentPlayer]->getNode()->getID().x, m_vectorSprites[currentPlayer]->getNode()->getID().y), temp->getID(), m_vectorSprites[currentPlayer]->getSpeed(), m_vectorSprites);
			//m_vectorSprites[0]->setNode(m_Graph[tempList.back()->getID().x][tempList.back()->getID().y]);
			m_gameState = PlayersMoving;
		}

		break;


	case PlayersMoving:

		movingCounter += p_time;

		if (movingCounter > 0.61f)
		{
			if (!m_pathList.empty()) {

				m_vectorSprites[currentPlayer]->setNode(m_Graph->getNode(sf::Vector2i(m_pathList.front()->getID().x, m_pathList.front()->getID().y)));
				m_pathList.pop_front();
			}
			else {
				for (int i = startofVampires; i < m_vectorSprites.size(); i++)
				{
					if (m_vectorSprites[i]->getNode() == temp)
					{
						if (m_Graph->isGoalReached()) {
							m_vectorSprites[i]->setHealth(m_vectorSprites[currentPlayer]->getAttack());
						}
					}
				}
				m_gameState = EnemyTurn;
			}
			movingCounter = 0.0f;
		}
		break;


	case EnemyTurn:

		//for (int j = 1; j < m_vectorSprites.size(); j++) {
		if (currentEnemy != m_vectorSprites.size() and playerkilled != true) {
			if (4.2f > m_Graph->calculateHValue(sf::Vector2i(m_vectorSprites[currentEnemy]->getNode()->getID().x, m_vectorSprites[currentEnemy]->getNode()->getID().y), sf::Vector2i(m_vectorSprites[currentPlayer]->getNode()->getID().x, m_vectorSprites[currentPlayer]->getNode()->getID().y)))
			{
				m_pathList = m_Graph->aStar(sf::Vector2i(m_vectorSprites[currentEnemy]->getNode()->getID().x, m_vectorSprites[currentEnemy]->getNode()->getID().y), m_Graph->getGoal(m_vectorSprites[currentPlayer]->getNode(), m_vectorSprites[currentEnemy]->getNode(), m_vectorSprites), 
					m_vectorSprites[currentEnemy]->getSpeed(), m_vectorSprites);
				//m_vectorSprites[currentEnemy]->setNode(m_Graph[tempList.back()->getID().x][tempList.back()->getID().y]);

				if (m_Graph->isGoalReached())
					m_vectorSprites[currentEnemy]->doDamage(true);
				//m_vectorSprites[0]->setHealth(m_vectorSprites[currentEnemy]->getAttack());
			}
			m_gameState = EnemyMove;
			break;
		}
		else {
			playerkilled = false;
			currentEnemy = startofVampires;
			m_gameState = PlayersTurn;
			break;
		}
	
	case EnemyMove:
		
		if (m_pathList.empty()) {

			//if (reachedGoal)
			//	m_vectorSprites[0]->setHealth(m_vectorSprites[currentEnemy]->getAttack());

			if (m_vectorSprites[currentEnemy]->isDoingDamage()){
				m_vectorSprites[currentPlayer]->setHealth(m_vectorSprites[currentEnemy]->getAttack());
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

				m_vectorSprites[currentEnemy]->setNode(m_Graph->getNode(sf::Vector2i(m_pathList.front()->getID().x, m_pathList.front()->getID().y)));
				m_pathList.pop_front();
				movingCounter = 0.0f;
			}

			break;
		}
	}

	for (auto* i : m_vectorSprites)
	{			
		i->update(p_time);	
	}

	if (m_vectorSprites[0]->getHealth() < 0)
	{
		m_gameOver = true;
	}

	int tempSize2 = startofVampires;
	for (int m = 1; m < tempSize2; m++) {

		if (m_vectorSprites[m]->getHealth() < 0)
		{
			m_vectorSprites.erase(m_vectorSprites.begin() + m);
			currentPlayer = 0;
			startofVampires--;
			
			playerkilled = true;
			std::cout << test << std::endl;
			
			std::cout << m_vectorSprites[m]->getHealth() << std::endl;
			std::cout << m_vectorSprites[m]->getAttack() << std::endl;
		}
	}

	if (m_vectorSprites.back()->getHealth() < 0)
	{
		m_gameOver = true;
	}
	
	int tempSize = m_vectorSprites.size() - 1;
	for (int j = 3; j < tempSize; j++) {

		if (m_vectorSprites[j]->getHealth() < 0)
		{
			m_vectorSprites.erase(m_vectorSprites.begin() + j);
		}
	}
	////////////////std::cout << m_vectorSprites[1]->getHealth() << std::endl;

}


bool Scene::loadLevel(std::string p_level)
{
	return false;
}

std::vector<sf::Sprite*> Scene::getSpriteVector(){
	
	m_vectorTemp.clear();

	for (int i = 0; i < m_Graph->getColRow().first; i++) // m_iCol; i++)
	{
		for (int j = 0; j < m_Graph->getColRow().second; j++)
		{
			m_vectorTemp.push_back(m_Graph->getNode(sf::Vector2i(j, i))->getSprite());
		}
	}

	for (int j = 0; m_vectorSprites.size() > j; j++)
	{
		m_vectorTemp.push_back(m_vectorSprites.at(j)->getSprite());
	}

	return m_vectorTemp;
	
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
		std::cout << m_vectorSprites[currentPlayer]->getHealth() << std::endl;
		
	}
}




