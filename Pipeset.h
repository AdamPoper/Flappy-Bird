#pragma once
#include <SFML/Graphics.hpp>
#include <tuple>
class Pipeset
{
public:
	Pipeset();
	void draw(sf::RenderWindow&);
	static void init();
	void OnUpdate(int);
	std::tuple<sf::Vector2f, sf::Vector2f> getPipePositions() const;
private:
	static int s_gapDistance;
	sf::Sprite m_top, m_bottom;
	static sf::Texture s_pipeTexture;
};