#pragma once

class Player
{
public:
	int score;
	enum playState
	{
		shuffling,
		fromhandselect,
		fromtableselect,
		restartround,
		counting,
	};
	playState PS = shuffling;

	Player();
};