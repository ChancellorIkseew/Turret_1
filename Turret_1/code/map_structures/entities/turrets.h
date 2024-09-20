#pragma once
#ifndef TURRETS_H
#define TURRETS_H

#include <fstream>
#include <SFML\Graphics.hpp>


class Turret
{
	protected:
	
	int turretType;	
	
	int coordX;
	int coordY;
	
	float angleRad;
	float angleDeg;
	
	float aimCoordX;
	float aimCoordY;
	
	int durability;
	short amooQuant;
	short maxAmoo;
	bool activity;

	int reloadTimer;
	int pixelRange;
	
	static inline sf::Image turretImage;
	static inline sf::Texture turretTexture;
	static inline sf::Sprite turretSprite;

	public:
		
		Turret(int turretType ,int tileX, int tileY, float curentAngle, short curentDurability);
		Turret();
		~Turret() = default;

		void save(std::ofstream& fout);
		void load(std::ifstream& fin);
		void set0();
		
		bool findAim();
		virtual void shooting();
		
		virtual bool needAmoo();
		virtual void takeAmoo(int resType);

		int getType();
		int getTileCoordX();
		int getTileCoordY();
		int getCoordX();
		int getCoordY();
		int getAngleDeg();
		int getAimCoordX();
		int getAimCoordY();
		int getDurability();
		short getAmooQuant();
		virtual int getAmooType();
		char getActivity();
		void setCoord(int v_coordX, int v_coordY);

		static Turret* setTurret(int turretType, int tileX, int tileY);

		// visual
		static void prepareSprites();
		virtual void draw(sf::RenderWindow& window);
		
};


#endif // TURRETS_H
