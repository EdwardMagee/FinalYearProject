#include "..\include\MenuOne.h"
#include "..\include\TextureHandler.h"
#include "..\include\FileReaderGameAssests.h"

MenuOne::MenuOne()
{
	m_currentLevel = 0;
	m_over = EndState::Defualt;

	if (!m_font.loadFromFile("../VampiresVsKnights/Assests/Fonts/ariblk.ttf"))
	{
		std::cout << "Unable to load Font" << std::endl;
	}

	m_reader = new FileReaderGameAssests("Assests/Levels\\Textures.txt", "Assests/Levels\\LevelList.txt");

	for (auto j : m_reader->getTextures()) {
			m_textures->instance()->insertTexture(j.first, j.second);
	}

	//m_Time.setFont(m_Font); m_Round.setFont(m_Font); m_Level.setFont(m_Font);
    //	m_Time.setCharacterSize(19), m_Round.setCharacterSize(19); m_Level.setCharacterSize(19);
	//m_Time.setPosition(20, 20), m_Round.setPosition(270, 20); m_Level.setPosition(140, 20);

	//m_bannerOne.setSize(sf::Vector2f(392, 50)); m_bannerTwo.setSize(sf::Vector2f(400, 60));
	//m_bannerOne.setPosition(sf::Vector2f(0, 13)); m_bannerTwo.setPosition(sf::Vector2f(0, 9));
	//m_bannerOne.setFillColor(sf::Color::Black); m_bannerTwo.setFillColor(sf::Color::Cyan);

	m_tBackground = m_textures->instance()->getTexture("Menu");
	m_sBackground.setTexture(m_tBackground);
	m_sBackground.setPosition(sf::Vector2f(0, 0));
	m_sBackground.scale(sf::Vector2f(0.25, 0.334));


	for (int i = 0; i < 3; i++) {
	    m_tButtons = m_textures->instance()->getTexture("Button");
		m_sButtons.push_back(new sf::Sprite);
		m_sButtons[i]->setTexture(m_tButtons);
		m_sButtons[i]->setPosition(sf::Vector2f(200, 260 + (i * 150)));
		m_buttonText.push_back(new sf::Text);
		m_buttonText[i]->setFont(m_font);
		m_buttonText[i]->setCharacterSize(23);
		m_buttonText[i]->setPosition(245, 291 + (i * 150));
		m_buttonText[i]->setString("Level : " + std::to_string(i + 1));
		
	}

	m_tSelector = m_textures->instance()->getTexture("Blue");
	m_sSelector.setTexture(m_tSelector);
	m_sSelector.setPosition(sf::Vector2f(200, 260));

	m_menuText.setFont(m_font);
	m_menuText.setCharacterSize(32);
	m_menuText.setPosition(100, 100);
	m_menuText.setString("VAMPIRES VS KNIGHTS");


}

MenuOne::~MenuOne()
{
	for (auto * i : m_sButtons) {
		delete i;
		i = nullptr;
	}

	m_sButtons.clear();

	for (auto * j : m_buttonText) {
		delete j;
		j = nullptr;
	}

	m_buttonText.clear();
}

void MenuOne::updateGame(float p_time)
{
}

void MenuOne::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sBackground);
	target.draw(m_menuText);

	for (auto * i : m_sButtons){
		target.draw(*i);
	}

	for(auto * j : m_buttonText){
		target.draw(*j);
	}

	target.draw(m_sSelector);
}

void MenuOne::handleInput(int p_InputEvent)
{
	switch (p_InputEvent)
	{
	case sf::Keyboard::Up:
		if (m_currentLevel != 0)
		{
			m_currentLevel--;
			m_sSelector.move(0, -150);

		}

		break;

	case sf::Keyboard::Down:

		if (m_currentLevel != 2)
		{
			m_currentLevel++;
			m_sSelector.move(0, 150);

		}

		break;

	case sf::Keyboard::Enter:
		
		m_over = EndState::EndMenu;
		break;

	}
}

EndState MenuOne::isOver()
{
	return m_over;
}

void MenuOne::loadLevel()
{
}

int MenuOne::getLevel()
{
	return m_currentLevel;
}

