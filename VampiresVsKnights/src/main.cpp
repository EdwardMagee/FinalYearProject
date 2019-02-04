#include <iostream>
#include <SFML\Graphics.hpp>
#include "..\include\GameOne.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Vampires Vs Knights");
	GameOne m_game;

	sf::Clock timer;
	float fFrameTime = 1.f / 60.f;
	float fElapsedTime = 0.f;


	while(window.isOpen())
	{

		sf::Event event;

		while (window.pollEvent(event))
		{

			switch (event.type) {
			case sf::Event::Closed:
					window.close();
					break;
			case sf::Event::KeyPressed:


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
	}

	system("pause");
	return 0;
}