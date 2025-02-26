#pragma once
#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <SFML/Audio.hpp>

class GameSound
{
private:

	sf::Music soundTreak1;


public:

	GameSound()
	{

	}

	void loadSound()
	{
		soundTreak1.openFromFile("sounds/neutral_music.mp3");
		soundTreak1.setVolume(5);
	}

	void start()
	{
		soundTreak1.setLoop(true);
		soundTreak1.play();
	}



	~GameSound()
	{

	}

};









#endif // SOUND_SYSTEM_H