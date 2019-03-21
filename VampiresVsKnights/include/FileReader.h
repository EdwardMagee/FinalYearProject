#pragma once
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class FileReader
{
public:
	FileReader(std::string p_level);
	~FileReader();

	std::vector<float> getSpeedValues();
	std::vector<sf::Vector2i> getPositions();
	std::vector<float> getHealth();
	std::vector<float> getAttack();
	std::vector<std::string> getTexture();
	int getStartOfVamps();

protected:

	std::vector<float> m_speedValues;
	std::vector<sf::Vector2i> m_Positions;
	std::vector<float> m_health;
	std::vector<float> m_attack;
	std::vector<std::string> m_texture;	
	int m_startOfVampires;

};