#pragma once
#include <iostream>
using namespace std;

#include "Sprite.h"

class Carta
{
public:
	int numero;
	char seme;
	string textureName;
	Sprite* sprite;

	Carta();
	Carta(int num, char seme);

	bool compare(Carta& _c);
	void setSprite();
	
	void update(float deltaTime);
	void draw();
};

