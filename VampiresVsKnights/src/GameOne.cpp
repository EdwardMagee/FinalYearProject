#include "..\include\GameOne.h"
#include "..\include\Scene.h"
#include "..\include\TextureHandler.h"
#include "..\include\HUD.h"
#include "..\include\FileReaderGameAssests.h"

#include<SFML\Graphics.hpp>


GameOne::GameOne(){
    
	m_reader = new FileReaderGameAssests("Assests/Levels\\Textures.txt", "Assests/Levels\\LevelList.txt");
	insertTextures();
	m_Level = 0;

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
	m_over = false;
}

GameOne::~GameOne()
{
	delete m_currentScene;
	m_currentScene = nullptr;
}

void GameOne::insertTextures()
{
	for (auto j : m_reader->getTextures()){
		m_textureHandler->instance()->insertTexture(j.first, j.second);
	}

	//m_textureHandler->instance()->insertTexture("Harold", "../VampiresVsKnights/Assests/Sprites/Harold.png");
//	m_textureHandler->instance()->insertTexture("Owl", "../VampiresVsKnights/Assests/Sprites/Owl.jpg");
	//m_textureHandler->instance()->insertTexture("Normal", "../VampiresVsKnights/Assests/Sprites/Normal.png");
//	m_textureHandler->instance()->insertTexture("Empty", "../VampiresVsKnights/Assests/Sprites/Empty.png");
	//m_textureHandler->instance()->insertTexture("space", "../VampiresVsKnights/Assests/Sprites/space.jpg");
//	m_textureHandler->instance()->insertTexture("Bat", "../VampiresVsKnights/Assests/Sprites/Bat.png");
	//m_textureHandler->instance()->insertTexture("Micheal", "../VampiresVsKnights/Assests/Sprites/Micheal.png");
	//m_textureHandler->instance()->insertTexture("Slow", "../VampiresVsKnights/Assests/Sprites/Slow.png");
//	m_textureHandler->instance()->insertTexture("Speed", "../VampiresVsKnights/Assests/Sprites/Speed.png");
	//m_textureHandler->instance()->insertTexture("Splash", "../VampiresVsKnights/Assests/Sprites/Splash.png");
	//m_textureHandler->instance()->insertTexture("Vampire", "../VampiresVsKnights/Assests/Sprites/Vampire.png");
//	m_textureHandler->instance()->insertTexture("Selector", "../VampiresVsKnights/Assests/Sprites/Selector.png");
//	m_textureHandler->instance()->insertTexture("Cyan", "../VampiresVsKnights/Assests/Sprites/Cyan.png");
	//m_textureHandler->instance()->insertTexture("Knight", "../VampiresVsKnights/Assests/Sprites/KnightOne.png");
  //  m_textureHandler->instance()->insertTexture("Zombie", "../VampiresVsKnights/Assests/Sprites/ZombieKnight.png");
}

void GameOne::updateGame(float p_time)
{
	m_currentScene->updateScene(p_time);

	if (m_currentScene->getGameOver())
	{
		m_over = true;
	}
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

bool GameOne::isOver()
{
	return m_over;
}

void GameOne::loadLevel()
{
	delete m_currentScene;
	m_currentScene = nullptr;

	m_currentScene = new Scene(m_vectorLevels[m_Level].first, m_vectorLevels[m_Level].second);

}
