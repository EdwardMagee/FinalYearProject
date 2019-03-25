#include "..\include\GameOne.h"
#include "..\include\Scene.h"
#include "..\include\TextureHandler.h"
#include "..\include\HUD.h"
#include "..\include\FileReaderGameAssests.h"

#include<SFML\Graphics.hpp>


GameOne::GameOne(int p_level) {
    
	m_reader = new FileReaderGameAssests("Assests/Levels\\Textures.txt", "Assests/Levels\\LevelList.txt");
	m_Level = p_level;

	for (auto i : m_reader->getLevels()) {
		m_vectorLevels.push_back(i);
	}

	//m_vectorLevels.push_back("Assests/Levels\\LevelOne.txt");
  //  m_vectorLevels.push_back("Assests/Levels\\LevelTwo.txt");
	//m_vectorLevels.push_back("Assests/Levels\\LevelThree.txt");

	m_currentScene = new Scene(m_vectorLevels[m_Level].first, m_vectorLevels[m_Level].second);
	m_backgroundTexture = m_textureHandler->instance()->getTexture("space");
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(0.77, 0.77);
	//m_over = false;
	m_endState = EndState::Defualt;
}

GameOne::~GameOne()
{
	delete m_currentScene;
	m_currentScene = nullptr;
}



void GameOne::updateGame(float p_time)
{
	m_currentScene->updateScene(p_time);

	m_endState = m_currentScene->getEndState();
	
}

void GameOne::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_backgroundSprite);

	target.draw(m_currentScene->getHUD()->getBannerTwo());
	target.draw(m_currentScene->getHUD()->getBannerOne());

	target.draw(m_currentScene->getHUD()->getLevelText(m_Level + 1));
	target.draw(m_currentScene->getHUD()->getTime());
	target.draw(m_currentScene->getHUD()->getRound());

	for (auto object : m_currentScene->getSpriteVector())
	{
		target.draw(*object);
	}
	target.draw(m_currentScene->getSelector());
}

void GameOne::handleInput(int p_InputEvent)
{
	switch (p_InputEvent)
	{
	case sf::Keyboard::Left:
		
		m_currentScene->decreaseSelector(sf::Vector2i(1, 0));
		break;
	case sf::Keyboard::Right:

		m_currentScene->incrementSelector(sf::Vector2i(1, 0));
		break;
	case sf::Keyboard::Up:

		m_currentScene->decreaseSelector(sf::Vector2i(0, 1));
		break;
	case sf::Keyboard::Down:

		m_currentScene->incrementSelector(sf::Vector2i(0, 1));
		break;
	case sf::Keyboard::Enter:

		m_currentScene->PlayersMove();
		break;
	case sf::Keyboard::Space:
		
		m_Level++;
		

 		if (m_Level == 3)
		{
			m_Level = 0;
		}
		
		loadLevel();

		break;

	default:
		break;
	}

}

EndState GameOne::isOver()
{
	return m_endState;
}

void GameOne::loadLevel()
{
	delete m_currentScene;
	m_currentScene = nullptr;

	m_currentScene = new Scene(m_vectorLevels[m_Level].first, m_vectorLevels[m_Level].second);

}

Scene * GameOne::getScene()
{
	return m_currentScene;
}
