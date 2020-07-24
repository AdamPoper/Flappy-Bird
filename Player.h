#pragma once
#include <SFML/Graphics.hpp>
class Player
{
private:
	Player();
	Player(const Player&) = delete;
	static Player s_instance;
	sf::Sprite m_playerSprite;
	sf::Texture m_textures[3];
	sf::Vector2f m_playerSize = { 70.0f, 50.0f };
	float m_changeY = 0;
	uint32_t m_currentTexture;
	sf::Clock m_textureClock;
	bool m_isDead = false;
public:
	void handleTextures();
	const bool isDead() const;
	void die();
	void reserect();
	void moveUp(float);
	void moveDown(float);  // might change these later
	static Player& Get();
	const sf::Vector2f& getPosition() const;
	void setRotation(uint32_t);
	const sf::Sprite& Quad() { return m_playerSprite; }
};