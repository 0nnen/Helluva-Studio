#include "Managers/AudioManager.h"
#include <iostream>

float AudioManager::volume = 0.f;
float AudioManager::maxVolume = 0.f;
sf::Music* AudioManager::music = nullptr;
sf::Sound* AudioManager::sound = nullptr;
std::map<std::string, sf::Music*> AudioManager::musics;
std::map<std::string, sf::Sound*> AudioManager::sounds;
std::map<std::string, sf::SoundBuffer*> AudioManager::soundBuffers;

void AudioManager::SetVolume(float _volume)
{
	AudioManager::volume = _volume;

	if (AudioManager::music)
	{
		AudioManager::music->setVolume(_volume);
	}

	for (auto& sound : AudioManager::sounds)
	{
		if (sound.second)
		{
			sound.second->setVolume(_volume);
		}
	}

	for (auto& music : AudioManager::musics)
	{
		if (music.second)
		{
			music.second->setVolume(_volume);
		}
	}
}


void AudioManager::PlayMusic(const std::string& _key) 
{
	if (AudioManager::musics.find(_key) != AudioManager::musics.end())
	{
		AudioManager::Stop();
		AudioManager::music = AudioManager::musics.at(_key);
		AudioManager::music->setVolume(volume);
		AudioManager::music->play();
	}
	else
	{
		std::cout << "Music not found: " << _key << std::endl;
	}
}

void AudioManager::PlaySound(const std::string& _key)
{
	if (AudioManager::sounds.find(_key) != AudioManager::sounds.end())
	{
		AudioManager::sounds.at(_key)->play();
	}
	else
	{
		std::cout << "Sound not found: " << _key << std::endl;
	}
}

void AudioManager::AddMusic(const std::string& _key, const std::string& _fileName)
{
	if (AudioManager::musics.find(_key) == AudioManager::musics.end())
	{
		sf::Music* _music = new sf::Music();
		if (_music->openFromFile(_fileName))
		{
			AudioManager::musics[_key] = _music;
		}
		else
		{
			std::cout << "Music file not found: " << _fileName << std::endl;
			delete _music;
		}
	}
}

void AudioManager::AddSound(const std::string& _key, const std::string& _fileName)
{
	if (AudioManager::soundBuffers.find(_key) == AudioManager::soundBuffers.end())
	{
		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		if (buffer->loadFromFile(_fileName))
		{
			sf::Sound* sound = new sf::Sound();
			sound->setBuffer(*buffer);

			AudioManager::soundBuffers[_key] = buffer;
			AudioManager::sounds[_key] = sound;
		}
		else
		{
			std::cout << "Sound file not found: " << _fileName << std::endl;
			delete buffer;
		}
	}
}

void AudioManager::PauseMusic()
{
	if (AudioManager::music) {
		AudioManager::music->pause();
	}
}

void AudioManager::ResumeMusic()
{
	if (AudioManager::music) {
		AudioManager::music->play();
	}
}

void AudioManager::StopMusic()
{
	if (AudioManager::music) {
		AudioManager::music->stop();
	}
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
	for (auto& buffer : AudioManager::soundBuffers)
	{
		delete buffer.second;
	}
	AudioManager::sounds.clear();
	AudioManager::soundBuffers.clear();
	AudioManager::musics.clear();
}