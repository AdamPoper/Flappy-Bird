#include "Player.h"

Player Player::s_instance;
	
Player::Player()
{
	m_playerSprite.setPosition({ 90.0f, 200.0f });
	m_currentTexture = 0;
	m_textures[0].loadFromFile("res/textures/yellowbird-upflap.png");
	m_textures[1].loadFromFile("res/textures/yellowbird-midflap.png");
	m_textures[2].loadFromFile("res/textures/yellowbird-downflap.png");
	m_playerSprite.setTexture(m_textures[m_currentTexture]);
	m_playerSprite.setOrigin(25.0f, 25.0f);
}
Player& Player::Get()
{
	return s_instance;
}
void Player::moveDown(float offsetY)
{
	m_playerSprite.move({ 0.0f, offsetY });
}
void Player::moveUp(float offsetY)
{
	m_playerSprite.move({ 0.0f, -offsetY });
}
const sf::Vector2f& Player::getPosition() const
{
	return m_playerSprite.getPosition();
}
void Player::handleTextures()
{
	if (m_textureClock.getElapsedTime().asSeconds() >= 0.2f && !m_isDead)
	{
		m_currentTexture++;
		if (m_currentTexture == 3)
			m_currentTexture = 0;
		m_playerSprite.setTexture(m_textures[m_currentTexture]);
		m_textureClock.restart();
	}
}
void Player::setRotation(uint32_t offset)
{
	m_playerSprite.setRotation(offset);
}
const bool Player::isDead() const
{
	return m_isDead;
}
void Player::die()
{
	m_isDead = true;
}
void Player::reserect()
{
	m_isDead = false;
	m_playerSprite.setPosition({ 90.0f, 200.0f });
}