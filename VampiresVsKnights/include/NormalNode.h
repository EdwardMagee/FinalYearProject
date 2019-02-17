#pragma once
#include "../include/NodeInterface.h"

class SpriteInterface;

class NormalNode : public NodeInterface
{
public:

    NormalNode(int p_cost);
	~NormalNode();
	void updateNode(float p_time) override;
    sf::Sprite* getSprite() override;
	void constructNode(int p_col, int p_row, sf::Texture p_T) override;
	SpriteInterface* getSpriteAttachedToNode() override;
	bool containSprite(SpriteInterface* p_sprite) override;
	void removeSprite() override;

	float getG() override;
	float getH() override;
    float getF() override;
	sf::Vector2i getID() override;

	void setG(float p_g) override;
    void setF(float p_f) override;
	void setH(float p_H) override;

private:

	sf::Sprite* m_sprite;
	sf::Texture m_texture;
	SpriteInterface* m_spriteUnit;
	
	sf::Vector2i id;
	float m_movementCost;
	float m_fValue;
	float m_gValue;

};