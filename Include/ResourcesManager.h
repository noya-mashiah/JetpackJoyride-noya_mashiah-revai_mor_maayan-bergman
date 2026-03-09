/**
 * ResourcesManager.h
 *  Singleton class for managing all game resources (textures, sounds, music, fonts).
 *
 * The ResourcesManager class loads, stores, and provides access to textures, sounds, music, and fonts.
 * Ensures efficient resource management and prevents redundant loading.
 * Use getInstance() to access the singleton instance.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class ResourcesManager
{
public:
	static ResourcesManager& getInstance();
	const sf::Texture& getTexture(const std::string name) const;

	const sf::Font& getFont() const;
	const sf::Image& getIconImage() const;

	// has to be non const for muting and replaying
	sf::Music& getMusic(const std::string name);
	sf::SoundBuffer& getSound(const std::string name);

private:
	ResourcesManager();
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
	void loadTextures();
	void loadFont();
	void setSounds();
	void setMusic();
	void setIconImage();

	std::unordered_map<std::string, sf::Texture> m_textures;
	std::unordered_map<std::string, sf::SoundBuffer> m_sounds;
	std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_music;
	
	sf::Font m_font;
	sf::Image m_iconImage;
};
