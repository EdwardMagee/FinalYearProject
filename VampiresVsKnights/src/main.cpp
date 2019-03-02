#include <iostream>
#include <SFML\Graphics.hpp>
#include "..\include\GameOne.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(64 * 16 + 200, 64 * 8 + 100), "Vampires Vs Knights");
	GameOne m_game;

	sf::Clock timer;
	float fFrameTime = 1.f / 60.f;
	float fElapsedTime = 0.f;

	bool gameOver(false);

	while(window.isOpen() and !gameOver)
	{

		sf::Event event;

		while (window.pollEvent(event))
		{

			switch (event.type) {
			case sf::Event::Closed:
					window.close();
					break;
			case sf::Event::KeyPressed:

				m_game.handleInput(event.key.code);
				break;

			}

		}

		fElapsedTime = timer.getElapsedTime().asSeconds();
		if (fElapsedTime > fFrameTime)
		{
			m_game.updateGame(fFrameTime);
			timer.restart();
		}

		window.clear();
		window.draw(m_game);
		window.display();

		if (m_game.isOver())
		{
			gameOver = true;
		}

	}

	window.close();

	std::cout << "Game Over" << std::endl;
	system("pause");
	return 0;
}