#include "Pipeset.h"

int Pipeset::s_gapDistance = 100;
sf::Texture Pipeset::s_pipeTexture;
Pipeset::Pipeset()
{
	m_top.setTexture(s_pipeTexture);
	m_bottom.setTexture(s_pipeTexture);

	srand(time(NULL));
	m_top.setRotation(180);
	const int lowest = 320;
	const int highest = 150;
	const float startX = 470.0f;
	float y = (float)(highest + (std::rand() % (lowest - highest + 1)));
	int choice = (std::rand() % 3);
	switch (choice)
	{
	case 0: y += 80.0f;
		break;
	case 1: y += 20.0f;
		break;
	case 2: y -= 45.0f;
		break;
	case 3: y -= 110.0f;
	default:
		y = y;
	}
	m_top.setPosition(startX, y);
	m_bottom.setPosition(startX - 52.0f, y + s_gapDistance);
}
void Pipeset::init()
{
	s_pipeTexture.loadFromFile("res/textures/bestpipe.png");
}
void Pipeset::draw(sf::RenderWindow& win)
{
	win.draw(m_top);
	win.draw(m_bottom);
}
void Pipeset::OnUpdate(int x)
{
	m_top.move(x, 0);
	m_bottom.move(x, 0);
}
std::tuple<sf::Vector2f, sf::Vector2f> Pipeset::getPipePositions() const
{
	return { m_top.getPosition(), m_bottom.getPosition() };
}