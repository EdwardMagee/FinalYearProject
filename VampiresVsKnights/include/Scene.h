#pragma once

#include "SceneInterface.h"
#include <array>
#include <list>

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
	
public:

	sf::Vector2i aStar(sf::Vector2i p_startPos, sf::Vector2i p_endPos);
	void updateScene(float p_time) override;
	bool loadLevel(std::string p_level) override;
	std::vector<sf::Sprite*> getSpriteVector() override;
	float calculateFValue(sf::Vector2i p_currentNode, sf::Vector2i p_goalNode);
	
	Scene();
	~Scene();

};