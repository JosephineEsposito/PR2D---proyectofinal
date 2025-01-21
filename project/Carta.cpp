#include "Carta.h"

#include <iostream>
#include <string>

#include <stb_image.h>

using namespace std;


Carta::Carta() {
	numero = 0; // 1 - 10
	seme = 'D'; // C - coppe, D - denari, B - bastoni, S - spade
	textureName = "dorso.png"; // 1D, 2D etc
	sprite = nullptr;
	setSprite();
}
Carta::Carta(int num, char seed) {
	numero = num;
	seme = seed;
	textureName = to_string(numero) + seme +".png";
	sprite = nullptr;
	setSprite();
}

bool Carta::compare(Carta& _c)
{
	if (seme == _c.seme && numero == _c.numero)
	{
		return true;
	}
	return false;
}


void Carta::setSprite()
{
	sprite = new Sprite(textureName.c_str(), 1, 1);
	
	sprite->setBlend(BLEND_ALPHA);
	sprite->setColor(1.f, 1.f, 1.f, 1.f);
	sprite->setScale(Vec2(60.f, 100.f));
	sprite->setSize(Vec2(2.f, 2.f));
}

void Carta::update(float deltaTime)
{
	sprite->update(deltaTime);
}
void Carta::draw()
{
	sprite->draw();
}