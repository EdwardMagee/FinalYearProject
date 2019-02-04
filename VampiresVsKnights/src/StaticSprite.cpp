#include "../include/StaticSprite.h"

StaticSprite::StaticSprite(sf::Sprite * p_Sprite) : m_sprite(p_Sprite){
}

StaticSprite::~StaticSprite(){
}

void StaticSprite::update(float p_time)
{
}

void StaticSprite::message(const std::string p_message)
{
}

sf::Sprite* StaticSprite::getSprite(){
	return m_sprite;
}
