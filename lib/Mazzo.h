#pragma once

#include <vector>
#include "Carta.h"

class Mazzo
{
public:
	vector<Carta> mazzo;
	bool flag;

	Mazzo();
	Mazzo(vector<Carta> _m);


	void shuffle();
	void reset();


	void printAll();
	vector<Carta> show();


	void pesca(Mazzo& m);
	void poggia(Mazzo& m);
	void popSelected(size_t i);
	void store(Mazzo& m);
	int size();
	void ottieni(Carta& _c);
	void rimuovi(Carta& _c);
	void clean();

	void loadTextures();

	void update(float deltaTime);
	void draw();
};

