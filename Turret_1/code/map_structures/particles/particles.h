#pragma once
#ifndef PARTICLES_H
#define PARTICLES_H

#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>


class Particle
{
	private:
		
	//bool isFriendly;
	
	//float angleRad;
	//float angleDeg;
	
	float coordX;
	float coordY;
	
	//float lineMotionX;
	//float lineMotionY;
	
	int particlesLifeTime;
	
	bool isWasted;
	
	static inline sf::Image burstImage;
	static inline sf::Texture burstTexture;
	static inline sf::Sprite burstSprite;

	public:
		
		Particle(int particleType);
		Particle(int particleType ,float value_coordX, float value_coordY);
		~Particle() = default;

		float getCoordX();
		float getCoordY();
		bool getIsWasted();

		static void prepareSprites();
		void animate();
		void draw(sf::RenderWindow& window, int time);
		
};


extern std::list<Particle*> particlesList;


void moveParticlesList();

void drawParticlesList(sf::RenderWindow &window, int time);

void saveParticlesList(int saveFileNumber);

void cleanParticlesList();


#endif // PARTICLES_H