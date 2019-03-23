#include <iostream>
#include <SFML\Graphics.hpp>
#include "..\include\GameOne.h"
#include "..\include\MenuOne.h"

int main()
{


	sf::RenderWindow menuWindow(sf::VideoMode(600, 800), "Pick A Level, FOR THIS FIGHT!!");
	

	sf::Clock timer; MenuOne menu;
	bool gameOver(false);

	while (menuWindow.isOpen())
	{
		sf::Event event;
		
		while (menuWindow.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				menuWindow.close();
				gameOver = true;
				break;
			case sf::Event::KeyPressed:
				menu.handleInput(event.key.code);
				break;

			}

		}

		if (menu.isOver())
		{
            menuWindow.close();
		}

		menuWindow.clear();
		menuWindow.draw(menu);
		menuWindow.display();
	}

		GameOne * game; game = new GameOne(menu.getLevel()); 
    sf::RenderWindow window(sf::VideoMode(64 * 16 + 200, 64 * 8 + 100), "Vampires Vs Knights");
	float fFrameTime = 1.f / 60.f; 	float fElapsedTime = 0.f; 

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
				game->handleInput(event.key.code);
				break;

			}

		}

		fElapsedTime = timer.getElapsedTime().asSeconds();
		if (fElapsedTime > fFrameTime){
			game->updateGame(fFrameTime);
			timer.restart();
		}

		window.clear();
		window.draw(*game);
		window.display();

		if (game->isOver())
		{
			gameOver = true;
		}

	}

	delete game;
	game = nullptr;
	window.close();

	std::cout << "Game Over" << std::endl;
	system("pause");
	return 0;
}
