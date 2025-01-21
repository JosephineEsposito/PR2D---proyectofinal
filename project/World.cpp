
// editor
#include <litegfx.h>
#include <glfw3.h>
#include <stb_image.h>

#include <iostream>
#include <thread>
#include <chrono>

#include "World.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Mazzo.h"

#pragma region | World setup

World::World()
{
	clearRed = 0.15f;
	clearGreen = 0.15f;
	clearBlue = 0.15f;

	deck = nullptr; // the main deck to draw the cards from
	mano = nullptr; // the cards in the player's hand
	ottenute = nullptr; // the cards obtained by the player
	raccolte = nullptr; // the cards obtained by the player
	terra = nullptr; // the cards displayed on the floor
	dorso0 = nullptr; // back of the cards of deck
	dorso1 = nullptr; // back of the cards of the gained deck
	win_menu = nullptr;
	gameover_menu = nullptr;
	main_menu = nullptr;

	camera = Vec2(400, 400); // center of the screen
	player = nullptr;
}
World::~World() {
	delete deck;
	delete mano;
	delete ottenute;
	delete raccolte;
	delete terra;
	delete dorso0->sprite;
	delete dorso1->sprite;
	delete win_menu;
	delete gameover_menu;
	delete main_menu;
}


float World::getClearRed() const
{
	return clearRed;
}
float World::getClearGreen() const
{
	return clearGreen;
}
float World::getClearBlue() const
{
	return clearBlue;
}

const Vec2& World::getCameraPosition() const
{
	return camera;
}
void World::setCameraPosition(const Vec2& pos)
{
	camera = pos;
}

void World::addSprite(Sprite& sprite)
{
}
void World::removeSprite(Sprite& sprite)
{
	// remove cards here
}

#pragma endregion


void World::OnShuffle()
{
	std::cout << "Shuffling...\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// mischiamo il mazzo
	deck->shuffle();

	mano->pesca(*deck); // draw 3 cards for the hand
	terra->poggia(*deck); // draw the next 4 for the floor

	player->PS = player->fromhandselect; // ci muoviamo al prossimo stato
}
void World::OnRestart()
{
	if (deck->size() < 7) // non ci sono abbastanza carte per giocare(3 per la mano e 4 a terra), il gioco finisce
	{
		player->PS = player->counting;
	}
	else
	{
		// pesco 3 carte per la mano
		mano->pesca(*deck);
		// pesco 4 carte per terra
		terra->poggia(*deck);
		player->PS = player->fromhandselect;
	}
}
void World::OnHandSelect(void* _window)
{
	GLFWwindow* win = static_cast<GLFWwindow*>(_window);
	// il giocatore sceglie le carte dalla mano con input 1,2,3
	if (glfwGetKey(win, GLFW_KEY_A) == 1) // key pressed === 1
	{
		fromHand = Carta(mano->mazzo.at(0).numero, mano->mazzo.at(0).seme);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		mano->mazzo.at(0).sprite->setColor(.5f, .5f, 1.f, .8f);
		player->PS = player->fromtableselect;
	}
	if (glfwGetKey(win, GLFW_KEY_S) == 1) // key pressed === 2
	{
		fromHand = Carta(mano->mazzo.at(1).numero, mano->mazzo.at(1).seme); // la seconda carta
		mano->mazzo.at(1).sprite->setColor(.5f, .5f, 1.f, .8f);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		player->PS = player->fromtableselect;
	}
	if (glfwGetKey(win, GLFW_KEY_D) == 1) // key pressed === 3
	{
		fromHand = Carta(mano->mazzo.at(2).numero, mano->mazzo.at(2).seme); // la terza carta
		mano->mazzo.at(2).sprite->setColor(.5f, .5f, 1.f, .8f);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		player->PS = player->fromtableselect;
	}
}
void World::OnFloorSelect(void* _window)
{
	GLFWwindow* win = static_cast<GLFWwindow*>(_window);
	bool selected = false;
	// il giocatore sceglie le carte che stanno a terra con input 1,2,3,4
	if (glfwGetKey(win, GLFW_KEY_Q) == 1) // key pressed === 1
	{
		fromFloor = Carta(terra->mazzo.at(0).numero, terra->mazzo.at(0).seme); // la prima carta
		terra->mazzo.at(0).sprite->setColor(.5f, .5f, 1.f, .8f);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		selected = true;
	}
	if (glfwGetKey(win, GLFW_KEY_W) == 1) // key pressed === 1
	{
		fromFloor = Carta(terra->mazzo.at(1).numero, terra->mazzo.at(1).seme); // la seconda carta
		terra->mazzo.at(1).sprite->setColor(.5f, .5f, 1.f, .8f);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		selected = true;
	}
	if (glfwGetKey(win, GLFW_KEY_E) == 1) // key pressed === 1
	{
		fromFloor = Carta(terra->mazzo.at(2).numero, terra->mazzo.at(2).seme); // la terza carta
		terra->mazzo.at(2).sprite->setColor(.5f, .5f, 1.f, .8f);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		selected = true;
	}
	if (glfwGetKey(win, GLFW_KEY_R) == 1) // key pressed === 1
	{
		fromFloor = Carta(terra->mazzo.at(3).numero, terra->mazzo.at(3).seme); // la quarta carta
		terra->mazzo.at(3).sprite->setColor(.5f, .5f, 1.f, .8f);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		selected = true;
	}

	if (selected)
	{
		// controlliamo se le carte hanno lo stesso valore
		if (fromHand.numero == fromFloor.numero)
		{
			ottenute->ottieni(fromHand);
			mano->rimuovi(fromHand);
			fromHand = Carta();

			ottenute->ottieni(fromFloor);
			terra->rimuovi(fromFloor);

			selected = false;
		}

		// controlliamo se abbiamo carte in mano
		bool found = false;
		if (mano->size() != 0)
		{
			// ci sono ancora carte in mano
			// controlla se ci sono combinazioni possibili
			for (int i = 0; i < mano->size(); i++)
			{
				for (int j = 0; j < terra->size(); j++)
				{
					if (mano->mazzo.at(i).compare(terra->mazzo.at(j)))
					{
						// ci sta una combinazione possibile si continua
						player->PS = player->fromhandselect;
						found = true;
						break;
					}
				}
				if (found) break;
			}

			if (!found)
			{
				player->PS = player->restartround; // non ci sono combinazioni

				deck->shuffle();

				// Spostiamo la prima carta di terra in raccolte
				if (terra->size() > 0) {
					raccolte->ottieni(terra->mazzo.at(0)); // Otteniamo la prima carta
					terra->popSelected(0); // Rimuoviamo la carta dal mazzo terra
				}

				// Spostiamo la prima carta di mano in terra
				if (mano->size() > 0) {
					terra->ottieni(mano->mazzo.at(0)); // Otteniamo la prima carta
					mano->popSelected(0); // Rimuoviamo la carta dal mazzo mano
				}
			}
		}
	}
}
void World::OnCount()
{
	// contiamo il punteggio e mostriamo
	for (int i = 0; i < ottenute->size(); i++)
	{
		player->score += ottenute->mazzo.at(i).numero; // stiamo contando semplicemente i numeri e basta
	}

	std::cout << "Il tuo punteggio : " << player->score << "\n";

	endGame();
}


void World::start(Player* _player)
{
	player = _player;
	std::cout << "creating vars\n";

	deck = new Mazzo(); // the main deck to draw the cards from
	deck->reset(); // riempiamo il mazzo

	mano = new Mazzo(); // the cards in the player's hand
	ottenute = new Mazzo(); // the cards obtained by the player
	raccolte = new Mazzo(); // the cards obtained by the player
	terra = new Mazzo(); // the cards displayed on the floor

	dorso0 = new Carta();
	dorso1 = new Carta();



	main_menu = new Sprite("main_title.png", 1,1);
	main_menu->setBlend(BLEND_ALPHA);
	main_menu->setColor(1.f, 1.f, 1.f, 1.f);
	main_menu->setSize(Vec2(800,800));
	main_menu->setScale(Vec2(1.f, 1.f));
	main_menu->setPosition(Vec2(400,0));

	win_menu = new Sprite("win.png", 1, 1);
	win_menu->setBlend(BLEND_ALPHA);
	win_menu->setColor(1.f, 1.f, 1.f, 1.f);
	win_menu->setSize(Vec2(800, 800));
	win_menu->setScale(Vec2(1.f, 1.f));
	win_menu->setPosition(Vec2(400, 0));

	gameover_menu = new Sprite("gameover.png", 1, 1);
	gameover_menu->setBlend(BLEND_ALPHA);
	gameover_menu->setColor(1.f, 1.f, 1.f, 1.f);
	gameover_menu->setSize(Vec2(800, 800));
	gameover_menu->setScale(Vec2(1.f, 1.f));
	gameover_menu->setPosition(Vec2(400, 0));
}
void World::update(float deltaTime, void* _window) // logica qui
{
	GLFWwindow* win = static_cast<GLFWwindow*>(_window);

	switch (GS)
	{
	case menu:
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		if (glfwGetKey(win, GLFW_KEY_C) == 1)
		{
			playGame();
			GS = playing;
		}
		break;


	case gameover:
		std::this_thread::sleep_for(std::chrono::milliseconds(60));
		if (glfwGetKey(win, GLFW_KEY_M) == 1)
		{
			// usciamo
			endGame();
			GS = quit;
		}
		if (glfwGetKey(win, GLFW_KEY_N) == 1)
		{
			// riiniziamo la partita
			playGame();
		}
		break;


	case winning:
		std::this_thread::sleep_for(std::chrono::milliseconds(60));
		if (glfwGetKey(win, GLFW_KEY_M) == 1)
		{
			// usciamo
			endGame();
			GS = quit;
		}
		if (glfwGetKey(win, GLFW_KEY_N) == 1)
		{
			// riiniziamo la partita
			playGame();
		}
		break;


	case playing:
		std::this_thread::sleep_for(std::chrono::milliseconds(60));

		switch (player->PS)
		{
		case player->shuffling:
			OnShuffle();
			break;

		case player->restartround:
			OnRestart();
			break;

		case player->fromhandselect:
			OnHandSelect(_window);
			break;

		case player->fromtableselect:
			OnFloorSelect(_window);
			break;

		case player->counting:
			OnCount();
			break;

		default:
			break;
		}

		break;


	case quit:
	default:
		break;
	}
}







void drawCards(Mazzo* m, Vec2 startPos, float margin)
{
	if (m->size() > 0)
	{
		Vec2 pos = startPos;
		for (int i = 0; i < m->size(); i++) {
			m->mazzo.at(i).sprite->setPosition(pos);
			pos.x += margin;
			m->mazzo.at(i).draw();
		}
	}
}

void World::draw(const Vec2& screenSize) // render qui
{
	// background
	lgfx_setblend(BLEND_SOLID);
	lgfx_clearcolorbuffer(.5f, .67f, .5f); // >> cambiato a sfondo verde

	switch (GS)
	{
	case menu:
		lgfx_setcolor(.4f, .2f, .3f, .6f);
		lgfx_drawrect(0,0, 800, 800);
		main_menu->draw();
		break;

	case gameover:
		lgfx_setcolor(.4f, .2f, .3f, .6f);
		lgfx_drawrect(0, 0, 800, 800);
		gameover_menu->draw();
		break;

	case winning:
		lgfx_setcolor(.4f, .2f, .3f, .6f);
		lgfx_drawrect(0, 0, 800, 800);
		win_menu->draw();
		break;

	case playing:
		// deck at the right
		dorso0->sprite->setPosition(Vec2(700, 590));
		dorso0->draw();

		// cards at the bottom
		drawCards(mano, Vec2(80, 590), 140);

		// cards on the floor
		drawCards(terra, Vec2(80, 260), 140);

		// if present deck at the left
		if (ottenute->size() > 0) // ci sono carte presenti nel mazzo
		{
			// disegna dorso in posizione precisa
			dorso1->sprite->setPosition(Vec2(100, 20));
			dorso1->draw();
		}
		break;


	case quit:
	default:
		break;
	}
}








void World::startGame()
{
	GS = menu;
}
void World::endGame()
{
	GS = gameover;
}
void World::playGame()
{
	GS = playing;
	player->PS = player->shuffling;
}