#pragma once
#include <array>
#include <SFML/Graphics.hpp>
class NumberSystem
{
private:
	class Number
	{
	public:
		Number() = default;
		Number(uint32_t num, sf::Texture* tex)
			: m_number(num), m_texture(tex)
		{
			m_sprite.setTexture(*m_texture);
		}
		void draw(sf::RenderWindow& win)
		{
			win.draw(m_sprite);
		}
		void setPosition(const sf::Vector2f& pos)
		{
			m_sprite.setPosition(pos);
		}		
	private:
		uint32_t m_number = 0;
		sf::Texture* m_texture;
		sf::Sprite m_sprite;
	};
public:
	NumberSystem();
	NumberSystem(const NumberSystem&) = delete;  // deleted for now
	~NumberSystem();
	void display(sf::RenderWindow&);	
	void operator++();
	void operator++(int);
	void reset();
private:	
	void clearNumbers();
	std::array<sf::Texture, 10> m_textures;
	sf::Vector2f m_defualtPos = { 90.0f, 25.0f };
	std::vector<Number*> m_numbers;
	uint32_t m_currentNumber = 0;
	sf::Clock m_incrementTimer;
};