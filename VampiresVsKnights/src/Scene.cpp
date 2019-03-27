#include "../include/Scene.h"
#include "../include/TextureHandler.h"
#include "../include/StaticSprite.h"
#include "../include/NormalNode.h"
#include "../include/EmptyNode.h"
#include "../include/FileReader.h"
#include "../include/Graph.h"
#include "../include/SpriteState.h"
#include "../include/HUD.h"

Scene::Scene(std::string p_characters, std::string p_nodes)
{
	m_fileReader = new FileReader(p_characters);

	playerkilled = false;
	m_prevoiusNode = nullptr;
	m_gameState = GameState::PlayersTurn;
	currentEnemy = m_fileReader->getStartOfVamps();
	currentPlayer = 0;
	startofKnights = 0;
	startofVampires = m_fileReader->getStartOfVamps();
	newcurrentPlayer = false;

	m_Graph = new Graph(p_nodes);
	m_gameHud = new HUD();
	m_gameHud->setText(0.0f, 1);
	m_round = 1;
	m_time = 0.f;

	m_selectorTexture = m_textureHandler->instance()->getTexture("Selector");
	m_selector.setTexture(m_selectorTexture);
	m_selectorPos = sf::Vector2i(1, 1);
	m_selector.setPosition(m_selectorPos.x * 64 + 100, m_selectorPos.y * 64 + 50);

	//m_gameOver = false;
	m_gameOverState = EndState::Defualt;

	//m_fileReader = new FileReader("Assests/Levels\\LevelOne.txt");
	



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

	switch (m_gameState)
	{
	case GameState::PlayersTurn:
		m_selector.setPosition((m_selectorPos.x * 64) + 100, (m_selectorPos.y * 64) + 50);
		m_selectorTexture = m_textureHandler->instance()->getTexture("Selector");
		m_selector.setTexture(m_selectorTexture);
		m_time += p_time;
		m_gameHud->setText(m_time, m_round);
		break;

	
	case GameState::PlayersMoved:

		temp = m_Graph->getNode(sf::Vector2i(m_selectorPos.x,m_selectorPos.y));

		if (temp->checkNodeType() == "EmptyNode") {
			m_gameState = GameState::PlayersTurn;
			break;
		}

			for (int i = 0; i < startofVampires; i++)
			{
				
				if (m_vectorSprites[i]->getNode() == temp)
				{
					currentPlayer = i;
					m_gameState = GameState::PlayersTurn;
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


				m_gameState = GameState::PlayersMoving;
				break;

			}
		}

		if (m_gameState != GameState::PlayersMoving)
		{
			m_pathList = m_Graph->aStar(sf::Vector2i(m_vectorSprites[currentPlayer]->getNode()->getID().x, m_vectorSprites[currentPlayer]->getNode()->getID().y), temp->getID(), m_vectorSprites[currentPlayer]->getSpeed(), m_vectorSprites);
			//m_vectorSprites[0]->setNode(m_Graph[tempList.back()->getID().x][tempList.back()->getID().y]);
			m_gameState = GameState::PlayersMoving;
		}

		break;


	case GameState::PlayersMoving:

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
				m_round++;
				m_gameState = GameState::EnemyTurn;
			}
			movingCounter = 0.0f;
		}
		break;


	case GameState::EnemyTurn:

		//for (int j = 1; j < m_vectorSprites.size(); j++) {
		if (currentEnemy != m_vectorSprites.size() and playerkilled != true) {

			bool tempTargetFound = false;
			float tempLowestValue = 100.0f;
			int tempSize = startofVampires;

			if(m_vectorSprites[currentEnemy] != m_vectorSprites.back() and m_vectorSprites[currentEnemy]->getHealth() < 2.0f)
			{
				m_vectorSprites[currentEnemy]->message("Escape");
				Target = m_vectorSprites.back();
				tempTargetFound = true;
			}
			else {

				for (int i = 0; i < tempSize; i++) {

					if (3.3f > m_Graph->calculateHValue(sf::Vector2i(m_vectorSprites[currentEnemy]->getNode()->getID().x, m_vectorSprites[currentEnemy]->getNode()->getID().y),
						sf::Vector2i(m_vectorSprites[i]->getNode()->getID().x, m_vectorSprites[i]->getNode()->getID().y))) {

						if (m_vectorSprites[i]->getHealth() < tempLowestValue)
						{
							tempLowestValue = m_vectorSprites[i]->getHealth();
							Target = m_vectorSprites[i];
							tempTargetFound = true;
						}
						else continue;

					}
					else continue;


				}
			}


			if (tempTargetFound) {

				m_pathList = m_Graph->aStar(sf::Vector2i(m_vectorSprites[currentEnemy]->getNode()->getID().x, m_vectorSprites[currentEnemy]->getNode()->getID().y),
					m_Graph->getGoal(Target->getNode(), m_vectorSprites[currentEnemy]->getNode(), m_vectorSprites),
					m_vectorSprites[currentEnemy]->getSpeed(), m_vectorSprites);
				//m_vectorSprites[currentEnemy]->setNode(m_Graph[tempList.back()->getID().x][tempList.back()->getID().y]);

				if (m_Graph->isGoalReached() and m_vectorSprites[currentEnemy]->getState() != SpriteState::FleeingState)
					m_vectorSprites[currentEnemy]->message("Attack");
				else if (m_Graph->isGoalReached() and m_vectorSprites[currentEnemy]->getState() == SpriteState::FleeingState)
					m_vectorSprites[currentEnemy]->message("Heal");
				//m_vectorSprites[0]->setHealth(m_vectorSprites[currentEnemy]->getAttack());
			}
			m_gameState = GameState::EnemyMove;
			break;
		}
		else {
			playerkilled = false;
			currentEnemy = startofVampires;
			m_gameState = GameState::PlayersTurn;
			break;
		}
	
	case GameState::EnemyMove:
		
		if (m_pathList.empty()) {

			//if (reachedGoal)
			//	m_vectorSprites[0]->setHealth(m_vectorSprites[currentEnemy]->getAttack());

			if (m_vectorSprites[currentEnemy]->getState() == SpriteState::AttackingState) {
				Target->setHealth(m_vectorSprites[currentEnemy]->getAttack());
				m_vectorSprites[currentEnemy]->message("Wait");
			  // m_vectorSprites[currentEnemy]->doDamage(false);
		    }
			else if (m_vectorSprites[currentEnemy]->getState() == SpriteState::HealState)
			{
			
				m_vectorSprites[currentEnemy]->setHealth(-2);
				std::cout << m_vectorSprites[currentEnemy]->getHealth() << std::endl;
				m_vectorSprites[currentEnemy]->message("Wait");
			}

			m_gameState = GameState::EnemyTurn;
			currentEnemy++;
			break;
		}
		else {
			movingCounter += p_time;

			if (movingCounter > 0.34f)
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
		m_gameOverState = EndState::VampireWin;
	}

	int tempSize2 = startofVampires;
	for (int m = 1; m < tempSize2; m++) {

		if (m_vectorSprites[m]->getHealth() < 0)
		{
			sf::Vector2i temp;
			std::vector<SpriteInterface*>::iterator tempIt;

			temp = m_vectorSprites[m]->getNode()->getID();
			m_vectorSprites.erase(m_vectorSprites.begin() + m);
			currentPlayer = 0;
			startofVampires--;

			
			tempIt = m_vectorSprites.end(); tempIt--;
			
			int tempSize; tempSize = m_vectorSprites.size() - 1;
			m_vectorSprites.insert(tempIt, new StaticSprite(temp.x, temp.y, m_textureHandler->instance()->getTexture("Zombie"), 2.0f, 1.0f, 0.5f));
			m_vectorSprites[tempSize]->setNode(m_Graph->getNode(sf::Vector2i(temp.x, temp.y)));
			//m_vectorSprites.push_back(new StaticSprite(m_fileReader->getPositions().at(j).x, m_fileReader->getPositions().at(j).y, m_textureHandler->instance()->getTexture(m_fileReader->getTexture().at(j)), m_fileReader->getSpeedValues().at(j), m_fileReader->getHealth().at(j), m_fileReader->getAttack().at(j)));

			playerkilled = true;
			
			std::cout << m_vectorSprites[m]->getHealth() << std::endl;
			std::cout << m_vectorSprites[m]->getAttack() << std::endl;
		}
	}

	if (m_vectorSprites.back()->getHealth() < 0)
	{
		m_gameOverState = EndState::PlayerWin;
	}
	
	int tempSize = m_vectorSprites.size() - 1;
	for (int j = startofVampires; j < tempSize; j++) {

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



EndState Scene::getEndState()
{
	return m_gameOverState;
}

int Scene::getRound()
{
	return m_round;
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
	if (m_gameState == GameState::PlayersTurn)
	{
		m_gameState = GameState::PlayersMoved;
		std::cout << m_vectorSprites[currentPlayer]->getHealth() << std::endl;
		m_selectorTexture = m_textureHandler->instance()->getTexture("Cyan");
		m_selector.setTexture(m_selectorTexture);
		
	}
}

HUD * Scene::getHUD()
{
	return m_gameHud;
}




