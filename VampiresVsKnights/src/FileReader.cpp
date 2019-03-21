#include "..\include\FileReader.h"
#include <iostream>

FileReader::FileReader(std::string p_level)
{
	std::fstream fFile(p_level, std::ios_base::in);

	std::string sLine = "";

	std::vector<sf::Vector2f> vectorTemp;

	if (fFile.is_open()) {

		while (getline(fFile, sLine))
		{
			std::string str;
			std::istringstream isstr(sLine);
			isstr >> str;
			sf::Vector2i tempPos;
			float tempAtk;
			float tempHp;
			float tempSpd;
			std::string tempId;

			if (str == "startofvamps:")
			{
				isstr >> m_startOfVampires;
				continue;
			}

			if (str == "x") {
				isstr >> tempPos.x;
				
			}

			isstr >> str;

			if (str == "y") {
				isstr >> tempPos.y;
			}

			isstr >> str;

			if (str == "atk")
			{
				isstr >> tempAtk;
			}

			isstr >> str;

			if (str == "Hp")
			{
				isstr >> tempHp;
			}

			isstr >> str;

			if (str == "spd")
			{
				isstr >> tempSpd;
			}

			isstr >> str;

			if (str == "id")
			{
				isstr >> tempId;
			}

			m_Positions.push_back(tempPos);
			m_speedValues.push_back(tempSpd);
			m_health.push_back(tempHp);
			m_attack.push_back(tempAtk);
			m_texture.push_back(tempId);
		}
	}
	else {
		std::cout << "cannot open the File" << std::endl;
	}

}

FileReader::~FileReader()
{
}

std::vector<float> FileReader::getSpeedValues()
{
	return m_speedValues;
}

std::vector<sf::Vector2i> FileReader::getPositions()
{
	return m_Positions;
}

std::vector<float> FileReader::getHealth()
{
	return m_health;
}

std::vector<float> FileReader::getAttack()
{
	return m_attack;
}

std::vector<std::string> FileReader::getTexture()
{
	return m_texture;
}

int FileReader::getStartOfVamps()
{
	return m_startOfVampires;
}
