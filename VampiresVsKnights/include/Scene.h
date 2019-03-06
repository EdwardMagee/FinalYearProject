#pragma once

#include "SceneInterface.h"
#include <array>
#include <list>
#include <math.h>

class TextureHandler;
class SpriteInterface;
class StaticSprite;
class NodeInterface;
class FileReader;

class Scene : public SceneInterface
{
private:

	static const int m_iCol = 8;
	static const int m_iRow = 16;
	TextureHandler * m_textureHandler;
	FileReader * m_fileReader;
	enum gameState {PlayersTurn, PlayersMoved, PlayersMoving, EnemyTurn, EnemyMove};
	gameState m_gameState;

	sf::Sprite m_selector;
	sf::Texture m_selectorTexture;
	sf::Vector2i m_selectorPos;

	std::vector<SpriteInterface*> m_vectorSprites;
	std::vector<sf::Sprite*> m_vectorTemp;
	std::array<std::array<NodeInterface*, m_iCol>, m_iRow> m_Graph;
	std::list<NodeInterface*> closedList;
	std::list<NodeInterface*> openList;
	std::list<NodeInterface*> pathList;
	std::list<NodeInterface*> tempList;
	NodeInterface* m_prevoiusNode;
	NodeInterface * temp;
	int counter;
	int counter2;
	int counter3;
	int counter4;
	int currentEnemy;
	float movingCounter;
	bool isInClosedList;
	bool isInOpenList;
	bool isOccupied;

	bool m_gameOver;
	bool reachedGoal;
	
public:

	std::list<NodeInterface*> aStar(sf::Vector2i p_startPos, sf::Vector2i p_endPos, float p_speed);
	void updateScene(float p_time) override;
	bool loadLevel(std::string p_level) override;
	std::vector<sf::Sprite*> getSpriteVector() override;
	std::list<NodeInterface*> gatherChildren(NodeInterface* p_currentNode);
	float calculateHValue(sf::Vector2i p_startPos, sf::Vector2i p_endPos);
	void increaseCounter();
	std::list<NodeInterface*> getPath(NodeInterface* p_start, NodeInterface* p_end);
	void increaseOtherCounter();
	bool getGameOver();
	sf::Vector2i getGoal(NodeInterface* p_Node);
	sf::Sprite getSelector();
	void incrementSelector(sf::Vector2i p_newPos);
	void decreaseSelector(sf::Vector2i p_newPos);
	void PlayersMove();
	Scene();
	~Scene();

};