#include <iostream>
#include <SFML\Graphics.hpp>
#include "..\include\GameOne.h"
#include "..\include\MenuOne.h"
#include "..\include\EndScreen.h"
#include "..\include\Scene.h"

int main()
{
	sf::RenderWindow menuWindow(sf::VideoMode(600, 800), "Pick A Level, FOR THIS FIGHT!!"); 
	
	sf::Clock timer; MenuOne menu;   //This part creates the first window 
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

		if (menu.isOver() == EndState::EndMenu)
		{
            menuWindow.close(); //Once this is over it will move onto the game using the int it gets from the menu
		}

		menuWindow.clear();
		menuWindow.draw(menu);
		menuWindow.display();
	}

	sf::RenderWindow window(sf::VideoMode(64 * 16 + 200, 64 * 8 + 100), "Vampires Vs Knights");
		GameOne * game; game = new GameOne(menu.getLevel()); //Game object, this is were all the game code is

	float fFrameTime = 1.f / 60.f; 	float fElapsedTime = 0.f; float totalTime; totalTime = 0;

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
			totalTime += fFrameTime;
			timer.restart();
		}

		window.clear();
		window.draw(*game);
		window.display();

		if (game->isOver() != EndState::Defualt)
			gameOver = true;
		

	}

	sf::RenderWindow endWindow(sf::VideoMode(600, 800), "GAME OVER!!!");//Displays diffrent endings
	EndScreen * endScreen;

	if (game->getScene()->getEndState() == EndState::PlayerWin) 
	{
		endScreen = new EndScreen("Rounds took to Win : " + std::to_string(game->getScene()->getRound()), "Time Played: " + std::to_string((int)totalTime), "Knights Prevailed, the Vampires \n have been fought back");
	}
	else if(game->getScene()->getEndState() == EndState::VampireWin)
	{
		endScreen = new EndScreen("Round took to Lose : " + std::to_string(game->getScene()->getRound()), "Time Played: " + std::to_string((int)totalTime), "You have been converted to the \n Vampire army!!!!!, \n Knights have lost");
	}
	else {
		endScreen = new EndScreen("Rounds : " + std::to_string(game->getScene()->getRound()), "Time Played: " + std::to_string((int)totalTime), "Thank you for playing");
	}

	window.close();

	while (endWindow.isOpen())
	{
		sf::Event event;

		while (endWindow.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				endWindow.close();
				
				break;
			case sf::Event::KeyPressed:
				endScreen->handleInput(event.key.code);
				break;

			}

		}

		if (endScreen->isOver() == EndState::EndMenu)
		{
			endWindow.close();
		}

		endWindow.clear();
		endWindow.draw(*endScreen);
		endWindow.display();
	}


	delete game;
	game = nullptr;
	

	std::cout << "Game Over" << std::endl;
	system("pause");
	return 0;
}
