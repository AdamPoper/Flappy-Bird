#include "NumberSystem.h"

NumberSystem::NumberSystem()
{
	m_textures[0].loadFromFile("res/textures/0.png");
	m_textures[1].loadFromFile("res/textures/1.png");
	m_textures[2].loadFromFile("res/textures/2.png");
	m_textures[3].loadFromFile("res/textures/3.png");
	m_textures[4].loadFromFile("res/textures/4.png");
	m_textures[5].loadFromFile("res/textures/5.png");
	m_textures[6].loadFromFile("res/textures/6.png");
	m_textures[7].loadFromFile("res/textures/7.png");
	m_textures[8].loadFromFile("res/textures/8.png");
	m_textures[9].loadFromFile("res/textures/9.png");
	
	m_numbers.push_back(new Number(0, &m_textures[0]));	
}
NumberSystem::~NumberSystem()
{
	for (auto& n : m_numbers)
		delete n;
}
void NumberSystem::display(sf::RenderWindow& win)
{
	float margin = 22.0f;
	sf::Vector2f pos(m_defualtPos);	
	for (auto& n : m_numbers)
	{
		pos.x += margin;
		n->setPosition(pos);
		n->draw(win);
	}
}
void NumberSystem::clearNumbers()
{
	for (auto& n : m_numbers)
		delete n;
	m_numbers.clear();
}
void NumberSystem::operator++()
{
	if (m_incrementTimer.getElapsedTime().asSeconds() >= 1.0f)
	{
		m_currentNumber++;
		if (m_currentNumber < 10)
		{
			clearNumbers();
			m_numbers.push_back(new Number(m_currentNumber, &m_textures[m_currentNumber]));
		}
		else if (m_currentNumber < 100)
		{
			clearNumbers();
			uint32_t tensPlace = m_currentNumber / 10;
			uint32_t onesPlace = m_currentNumber - (tensPlace * 10);
			m_numbers.reserve(2);
			m_numbers.emplace_back(new Number(tensPlace, &m_textures[tensPlace]));
			m_numbers.emplace_back(new Number(onesPlace, &m_textures[onesPlace]));
		}
		else if (m_currentNumber < 1000)
		{
			clearNumbers();
			uint32_t hundredsPlace = m_currentNumber / 100;
			uint32_t remainder = m_currentNumber - (hundredsPlace * 100);
			uint32_t tensPlace = remainder / 10;
			uint32_t onesPlace = remainder - (tensPlace * 10);
			m_numbers.reserve(3);
			m_numbers.emplace_back(new Number(hundredsPlace, &m_textures[hundredsPlace]));
			m_numbers.emplace_back(new Number(tensPlace, &m_textures[tensPlace]));
			m_numbers.emplace_back(new Number(onesPlace, &m_textures[onesPlace]));
		}
		m_incrementTimer.restart();
	}
}
void NumberSystem::operator++(int)
{
	if (m_incrementTimer.getElapsedTime().asSeconds() >= 1.0f)
	{
		m_currentNumber++;
		if (m_currentNumber < 10)
		{
			clearNumbers();
			m_numbers.push_back(new Number(m_currentNumber, &m_textures[m_currentNumber]));
		}
		else if (m_currentNumber < 100)
		{
			clearNumbers();
			uint32_t tensPlace = m_currentNumber / 10;
			uint32_t onesPlace = m_currentNumber - (tensPlace * 10);
			m_numbers.reserve(2);
			m_numbers.emplace_back(new Number(tensPlace, &m_textures[tensPlace]));
			m_numbers.emplace_back(new Number(onesPlace, &m_textures[onesPlace]));
		}
		else if (m_currentNumber < 1000)
		{
			clearNumbers();
			uint32_t hundredsPlace = m_currentNumber / 100;
			uint32_t remainder = m_currentNumber - (hundredsPlace * 100);
			uint32_t tensPlace = remainder / 10;
			uint32_t onesPlace = remainder - (tensPlace * 10);
			m_numbers.reserve(3);
			m_numbers.emplace_back(new Number(hundredsPlace, &m_textures[hundredsPlace]));
			m_numbers.emplace_back(new Number(tensPlace, &m_textures[tensPlace]));
			m_numbers.emplace_back(new Number(onesPlace, &m_textures[onesPlace]));
		}
		m_incrementTimer.restart();
	}
}
void NumberSystem::reset()
{
	m_currentNumber = 0;
	clearNumbers();
}