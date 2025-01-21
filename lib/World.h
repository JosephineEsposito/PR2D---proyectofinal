#pragma once

#include "Vec2.h"
#include "Sprite.h"
#include "Player.h"
#include "Mazzo.h"
#include "Carta.h"

#include <vector>

class World
{
public:
	float clearRed;
	float clearGreen;
	float clearBlue;


	Vec2 camera;
	Player* player;


	// mazzi
	Mazzo* deck; // the main deck to draw the cards from
	Mazzo* mano; // the cards in the player's hand
	Mazzo* ottenute; // the cards obtained by the player
	Mazzo* raccolte; // the cards obtained by the player
	Mazzo* terra; // the cards displayed on the floor

	Carta* dorso0; // dal mazzetto
	Carta* dorso1; // quelle ottenute

	Carta fromHand;
	Carta fromFloor;


	// fake ui
	Sprite* win_menu;
	Sprite* gameover_menu;
	Sprite* main_menu;


	enum gameState
	{
		menu, // ui
		gameover, // derrota
		playing, // jugando
		winning, // victoria
		quit,
	};
	gameState GS = menu;


	World();
	~World();

	float getClearRed() const;
	float getClearGreen() const;
	float getClearBlue() const;

	const Vec2& getCameraPosition() const;
	void setCameraPosition(const Vec2& pos);

	void addSprite(Sprite& sprite);
	void removeSprite(Sprite& sprite);


	void OnShuffle();
	void OnRestart();
	void OnHandSelect(void* _window);
	void OnFloorSelect(void* _window);
	void OnCount();


	void start(Player* _player);
	void update(float deltaTime, void* _window);
	void draw(const Vec2& screenSize);

	void startGame();
	void playGame();
	void endGame();
};