#include "Managers/AudioManager.h"
#include <iostream>

float AudioManager::volume = 100.f;
float AudioManager::maxVolume = 100.f;
sf::Music* AudioManager::music = nullptr;
sf::Music* AudioManager::sound = nullptr;
std::map<std::string, sf::Music*> AudioManager::musics;
std::map<std::string, sf::Music*> AudioManager::sounds;

void AudioManager::SetVolume(float _volume) 
{
	AudioManager::volume = _volume;
	if (AudioManager::music)
	{
		AudioManager::music->setVolume(_volume);
	}
	if (AudioManager::sound)
	{
		AudioManager::sound->setVolume(_volume);
	}
}

void AudioManager::Play(const std::string& _key) 
{
	if (AudioManager::musics.find(_key) != AudioManager::musics.end())
	{
		AudioManager::music = AudioManager::musics.at(_key);
		AudioManager::Stop();
		AudioManager::music->setVolume(volume);
		AudioManager::music->play();
	}
	else
	{
		std::cout << "no music" << std::endl;
	}
}

void AudioManager::PlaySound(const std::string& _key)
{
	if (AudioManager::sounds.find(_key) != AudioManager::sounds.end())
	{
		AudioManager::sound = AudioManager::sounds.at(_key);
		AudioManager::sound->setVolume(volume);
		AudioManager::sound->play();
	}
	else
	{
		std::cout << "no sound" << std::endl;
	}
}

void AudioManager::AddMusic(const std::string& _key, const std::string& _fileName)
{
	sf::Music* _music = new sf::Music();
	if (AudioManager::musics.find(_key) != AudioManager::musics.end()) 
	{
		if (!_music->openFromFile(_fileName))
		{
			std::cout << "Music introuvable" << std::endl;
		}
		else
		{
			AudioManager::musics.insert(std::make_pair(_key, _music));
		}
	}
	AudioManager::musics.insert(std::make_pair(_key, _music));
}

void AudioManager::AddSound(const std::string& _key, const std::string& _fileName)
{
	sf::Music* _sound = new sf::Music();
	_sound->openFromFile(_fileName);
	AudioManager::sounds.insert(std::make_pair(_key, _sound));
}

AudioManager::~AudioManager() 
{
	delete  AudioManager::music;
	delete  AudioManager::sound;
	for (auto& music : AudioManager::musics) 
	{
		delete music.second;
	}
	for (auto& sound : AudioManager::sounds) 
	{
		delete sound.second;
	}
	AudioManager::musics.clear();
	AudioManager::sounds.clear();
}
