#pragma once
#include "NodeInterface.h"

class SpriteInterface;

class EmptyNode : public NodeInterface
{
public:

	EmptyNode(int p_cost);
	~EmptyNode();
	void updateNode(float p_time) override;
	sf::Sprite* getSprite() override;
	void constructNode(int p_x, int p_y, sf::Texture p_T) override;
	SpriteInterface* getSpriteAttachedToNode() override;
	bool containSprite(SpriteInterface* p_sprite) override;
	void removeSprite() override;

	float getG() override;
	float getH() override;
	float getF() override;
	float getTerrainCost() override;
	sf::Vector2i getID() override;

	void setG(float p_g) override;
	void setF(float p_f) override;
	void setH(float p_H) override;
	void setDiagonal(bool p_b) override;

	NodeInterface* getPerant();
	void setPerant(NodeInterface* p_NI);

	std::string checkNodeType() override;
	bool isDiagonal() override;

private:

	sf::Sprite* m_sprite;
	sf::Texture m_texture;
	SpriteInterface* m_spriteUnit;
	NodeInterface* m_perant;

	sf::Vector2i m_id;
	float m_movementCost;
	float m_fValue;
	float m_gValue;
	float m_hValue;
	bool m_isDiagonal;

};