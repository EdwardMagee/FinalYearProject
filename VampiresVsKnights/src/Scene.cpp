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

	m_gameOverState = EndState::Defualt;

	totalCharacters = m_fileReader->getPositions().size();
	for (int j = 0; j < m_fileReader->getPositions().size(); j++) {

		m_vectorSprites.push_back(new StaticSprite(m_fileReader->getPositions().at(j).x, m_fileReader->getPositions().at(j).y, m_textureHandler->instance()->getTexture(m_fileReader->getTexture().at(j)), m_fileReader->getSpeedValues().at(j), m_fileReader->getHealth().at(j), m_fileReader->getAttack().at(j)));
	}

	for (int k = 0; k < m_fileReader->getPositions().size(); k++) {

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

	delete m_playerTemp;
	m_playerTemp = nullptr;

	delete m_Graph;
	m_Graph = nullptr;

	delete m_gameHud;
	m_gameHud = nullptr;

	delete m_prevoiusNode;
	m_prevoiusNode = nullptr;

	for (auto * i : m_pathList) { delete i; i = nullptr; }

	//delete Target;
	//Target = nullptr;

	delete m_fileReader;
	m_fileReader = nullptr;

	delete m_textureHandler;
	m_textureHandler = nullptr;
}

void Scene::updateScene(float p_time)
{
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

		temp = m_Graph->getNode(sf::Vector2i(m_selectorPos.x,m_selectorPos.y)); //Gets the node that was selected

		if (temp->checkNodeType() == "EmptyNode") {
			m_gameState = GameState::PlayersTurn;
			break;
		}

			for (int i = 0; i < startofVampires; i++) //Loops through the player untill it reaches the last (start of vampires would indicate end of loop)
			{
				
				if (m_vectorSprites[i]->getNode() == temp) //if enemy
				{
					currentPlayer = i;
					m_gameState = GameState::PlayersTurn; //This makes it so the player that is clicked on will become the focus
					newcurrentPlayer = true;
					break;
					
				}

			}

		if (newcurrentPlayer == true)
		{
			newcurrentPlayer = false;
			break;
		}
		
		
		for (int i = startofVampires; i < m_vectorSprites.size(); i++) //This will loop through the enemy units
		{
			if (m_vectorSprites[i]->getNode() == temp) // if it is equal to the enemy, temp is the selected area
			{
				if (!m_Graph->isTargetANeighbour(m_vectorSprites[currentPlayer]->getNode(), temp)) //I keep getting a error when a unit struggles to get to a blocked objective
				{                                                                                  //Fixed it by adding to the end of the a star however this is better as it reduces the need to use the alogrith every time

					m_pathList = m_Graph->aStar(sf::Vector2i(m_vectorSprites[currentPlayer]->getNode()->getID().x, m_vectorSprites[currentPlayer]->getNode()->getID().y),
						m_Graph->getGoal(m_vectorSprites[i]->getNode(), m_vectorSprites[currentPlayer]->getNode(), m_vectorSprites),
						m_vectorSprites[currentPlayer]->getSpeed(), m_vectorSprites); //This could of been reduced better its asking for the x, y of the player, enemy, player speed and a list of all units so it knows which nodes to avoid

					if (m_pathList.back() == m_vectorSprites[i]->getNode())
					{
						m_pathList.pop_back();
					}


					m_gameState = GameState::PlayersMoving;
					break;
				}
				else
				{
					m_vectorSprites[i]->setHealth(m_vectorSprites[currentPlayer]->getAttack());
					m_gameState = GameState::EnemyTurn;
				}
			}
		}

		if (m_gameState != GameState::PlayersMoving and m_gameState != GameState::EnemyTurn) 
		{
			m_pathList = m_Graph->aStar(sf::Vector2i(m_vectorSprites[currentPlayer]->getNode()->getID().x, m_vectorSprites[currentPlayer]->getNode()->getID().y), temp->getID(), m_vectorSprites[currentPlayer]->getSpeed(), m_vectorSprites);
			m_gameState = GameState::PlayersMoving;
		}

		break;


	case GameState::PlayersMoving:

		movingCounter += p_time;

		if (movingCounter > 0.61f) //To create the illusion of movement
		{
			if (!m_pathList.empty()) {

				if(m_pathList.front() != nullptr)
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

		if (currentEnemy != m_vectorSprites.size() and playerkilled != true) {

			bool tempTargetFound = false;
			float tempLowestValue = 100.0f;
			int tempSize = startofVampires;
			static const float rangeOfSight = 3.5f;
			static const float healthCheck = 2.0f;

			if(m_vectorSprites[currentEnemy] != m_vectorSprites.back() and m_vectorSprites[currentEnemy]->getHealth() < healthCheck)
			{
				m_vectorSprites[currentEnemy]->message("Escape");
				Target = m_vectorSprites.back();
				tempTargetFound = true;
			}
			else {

				for (int i = 0; i < tempSize; i++) {

					if (rangeOfSight > m_Graph->calculateHValue(sf::Vector2i(m_vectorSprites[currentEnemy]->getNode()->getID().x, m_vectorSprites[currentEnemy]->getNode()->getID().y),
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

				if (m_Graph->isGoalReached() and m_vectorSprites[currentEnemy]->getState() != SpriteState::FleeingState)
					m_vectorSprites[currentEnemy]->message("Attack");
				else if (m_Graph->isGoalReached() and m_vectorSprites[currentEnemy]->getState() == SpriteState::FleeingState)
					m_vectorSprites[currentEnemy]->message("Heal");
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

			if (m_vectorSprites[currentEnemy]->getState() == SpriteState::AttackingState) {
				Target->setHealth(m_vectorSprites[currentEnemy]->getAttack());
				m_vectorSprites[currentEnemy]->message("Wait");
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
}


bool Scene::loadLevel(std::string p_level)
{
	return false;
}

std::vector<sf::Sprite*> Scene::getSpriteVector(){
	
	m_vectorTemp.clear();

	for (int i = 0; i < m_Graph->getColRow().first; i++) 
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
		std::cout << "(Current Unit : " + std::to_string(currentPlayer) << ") Health is : " <<  m_vectorSprites[currentPlayer]->getHealth() << std::endl;
		m_selectorTexture = m_textureHandler->instance()->getTexture("Cyan");
		m_selector.setTexture(m_selectorTexture);
		
	}
}

void Scene::checkStats()
{
	NodeInterface * temp = m_Graph->getNode(sf::Vector2i(m_selectorPos.x, m_selectorPos.y));

	for (auto * i : m_vectorSprites)
	{
		if (i->getNode() == temp)
		{
			std::cout << "This Unit has : " << i->getHealth() << " Health Points " << std::endl;
			std::cout << "This Unit has : " << i->getSpeed() << " Speed Points " << std::endl;
			std::cout << "This Unit has : " << i->getAttack() << " Attack Points " << std::endl;
			std::cout << std::endl;

		}
	}

}

HUD * Scene::getHUD()
{
	return m_gameHud;
}




