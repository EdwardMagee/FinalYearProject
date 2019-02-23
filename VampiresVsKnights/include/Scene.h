#pragma once

#include "SceneInterface.h"
#include <array>
#include <list>
#include <math.h>

class TextureHandler;
class SpriteInterface;
class StaticSprite;
class NodeInterface;

class Scene : public SceneInterface
{
private:

	static const int m_iCol = 8;
	static const int m_iRow = 16;
	TextureHandler * m_textureHandler;
	std::vector<SpriteInterface*> m_vectorSprites;
	std::vector<sf::Sprite*> m_vectorTemp;
	std::array<std::array<NodeInterface*, m_iCol>, m_iRow> m_Graph;
	std::list<NodeInterface*> tempList;
	int counter;
	int counter2;
	
public:

	std::list<NodeInterface*> aStar(sf::Vector2i p_startPos, sf::Vector2i p_endPos);
	void updateScene(float p_time) override;
	bool loadLevel(std::string p_level) override;
	std::vector<sf::Sprite*> getSpriteVector() override;
	std::list<NodeInterface*> gatherChildren(NodeInterface* p_currentNode);
	float calculateHValue(sf::Vector2i p_startPos, sf::Vector2i p_endPos);
	void increaseCounter();
	
	Scene();
	~Scene();

};