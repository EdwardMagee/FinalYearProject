#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class SpriteInterface;

class NodeInterface 
{
public:
	virtual sf::Sprite* getSprite() = 0;
	virtual void constructNode(int p_row, int p_col, sf::Texture p_T) = 0;
	virtual void updateNode(float p_time) = 0;
	virtual SpriteInterface* getSpriteAttachedToNode() = 0;
	virtual bool containSprite(SpriteInterface* p_sprite) = 0;
	virtual void removeSprite() = 0;

	virtual float getG() = 0;
	virtual float getH() = 0;
	virtual float getF() = 0;	
	virtual float getTerrainCost() = 0;
	virtual sf::Vector2i getID() = 0;

	virtual void setG(float p_g) = 0;
	virtual void setF(float p_f) = 0; 
	virtual void setH(float p_H) = 0;
	virtual void setDiagonal(bool p_b) = 0;

	virtual NodeInterface* getPerant() = 0;
	virtual void setPerant(NodeInterface* p_NI) = 0;

	virtual std::string checkNodeType() = 0;
	virtual bool isDiagonal() = 0;
	

	

protected:
	
	


};