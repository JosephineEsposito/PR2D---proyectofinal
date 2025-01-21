#include "Mazzo.h"
#include "Carta.h"
#include <vector>
#include <algorithm>
#include <random>



Mazzo::Mazzo()
{
	flag = false;
	mazzo.clear();
}

Mazzo::Mazzo(vector<Carta> _m)
{
	flag = false;
	mazzo = _m;
}



void Mazzo::shuffle()
{
	// qui mischiamo il mazzo
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(mazzo), std::end(mazzo), rng);
}

void Mazzo::reset()
{
	mazzo.clear();

	// riempiamo in ordine il mazzo
	// denari
	mazzo.push_back(Carta(1, 'D'));
	mazzo.push_back(Carta(2, 'D'));
	mazzo.push_back(Carta(3, 'D'));
	mazzo.push_back(Carta(4, 'D'));
	mazzo.push_back(Carta(5, 'D'));
	mazzo.push_back(Carta(6, 'D'));
	mazzo.push_back(Carta(7, 'D'));
	mazzo.push_back(Carta(8, 'D'));
	mazzo.push_back(Carta(9, 'D'));
	mazzo.push_back(Carta(10, 'D'));
	// coppe
	mazzo.push_back(Carta(1, 'C'));
	mazzo.push_back(Carta(2, 'C'));
	mazzo.push_back(Carta(3, 'C'));
	mazzo.push_back(Carta(4, 'C'));
	mazzo.push_back(Carta(5, 'C'));
	mazzo.push_back(Carta(6, 'C'));
	mazzo.push_back(Carta(7, 'C'));
	mazzo.push_back(Carta(8, 'C'));
	mazzo.push_back(Carta(9, 'C'));
	mazzo.push_back(Carta(10, 'C'));
	// bastoni
	mazzo.push_back(Carta(1, 'B'));
	mazzo.push_back(Carta(2, 'B'));
	mazzo.push_back(Carta(3, 'B'));
	mazzo.push_back(Carta(4, 'B'));
	mazzo.push_back(Carta(5, 'B'));
	mazzo.push_back(Carta(6, 'B'));
	mazzo.push_back(Carta(7, 'B'));
	mazzo.push_back(Carta(8, 'B'));
	mazzo.push_back(Carta(9, 'B'));
	mazzo.push_back(Carta(10, 'B'));
	// spade
	mazzo.push_back(Carta(1, 'S'));
	mazzo.push_back(Carta(2, 'S'));
	mazzo.push_back(Carta(3, 'S'));
	mazzo.push_back(Carta(4, 'S'));
	mazzo.push_back(Carta(5, 'S'));
	mazzo.push_back(Carta(6, 'S'));
	mazzo.push_back(Carta(7, 'S'));
	mazzo.push_back(Carta(8, 'S'));
	mazzo.push_back(Carta(9, 'S'));
	mazzo.push_back(Carta(10, 'S'));
}



void Mazzo::printAll() {
	for (size_t i = 0; i < mazzo.size(); i++)
	{
		cout << "Carta\t" << mazzo.at(i).numero << " " << mazzo.at(i).seme << "\n";
	}
}

vector<Carta> Mazzo::show()
{
	return mazzo;
}



void Mazzo::pesca(Mazzo& m)
{
	mazzo.clear(); // puliamo per sicurezza // dovrebbe essere vuoto!!

	for (int i = 0; i < 3; i++)
	{
		mazzo.push_back(m.mazzo.at(i));
	}
	for (int i = 0; i < 3; i++)
	{
		m.mazzo.erase(m.mazzo.begin()); // eliminiamo i primi 3 elementi
	}
}

void Mazzo::poggia(Mazzo& m)
{
	mazzo.clear(); // puliamo per sicurezza // dovrebbe essere vuoto!!

	// prendiamo le prime 4 carte
	for (int i = 0; i < 4; i++)
	{
		mazzo.push_back(m.mazzo.at(i));
	}

	// controlla se presenti 3 o piu re
	int count = 0;
	int shuffles = 0; // tentativi di mischia, dopo 1 poggia
	for (int i = 0; i < mazzo.size(); i++)
	{
  	Carta card = mazzo.at(i);
		if (card.numero == 10)
		{
			count++;
		}
	}
	if (count >= 3)
	{
		if (flag == true) // abbiamo giá mischiato una volta
		{
			shuffle();
		}
		else
		{
			flag = true;
			shuffle();
			poggia(m);
		}
	}

	// nel caso in cui non ci siano 3 re a terra
	for (int i = 0; i < 4; i++)
	{
		m.mazzo.erase(m.mazzo.begin()); // eliminiamo i primi 3 elementi
	}
}

void Mazzo::popSelected(size_t i)
{
	mazzo.erase(mazzo.begin() + i); // per il primo elemento i sarebbe 0!!
}

void Mazzo::store(Mazzo& m)
{
	for (int i = 0; i < m.mazzo.size(); i++)
	{
		mazzo.push_back(m.mazzo.at(i));
	}
}
int Mazzo::size()
{
	return mazzo.size();
}

void Mazzo::ottieni(Carta& _c)
{
	mazzo.push_back(_c);
}

void Mazzo::rimuovi(Carta& _c)
{
	for (int i = 0; i < mazzo.size(); i++)
	{
		if (mazzo.at(i).numero == _c.numero && mazzo.at(i).seme == _c.seme)
		{
			popSelected(i);
			return;
		}
	}
}

void Mazzo::clean()
{
	mazzo.clear();
}

void Mazzo::loadTextures()
{
	for (int i = 0; i < mazzo.size(); i++)
	{
		mazzo.at(i).setSprite();
	}
}

void Mazzo::update(float deltaTime)
{
	for (int i = 0; i < mazzo.size(); i++)
	{
		mazzo.at(i).update(deltaTime);
	}
}

void Mazzo::draw()
{
	for (int i = 0; i < mazzo.size(); i++)
	{
		mazzo.at(i).draw();
	}
}

