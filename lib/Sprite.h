#pragma once

#include "Vec2.h"
#include <string>


#include <litegfx.h>


//typedef void (*CallbackFunc)(Sprite&, float);
class Sprite
{
public:
	using CallbackFunc = void(*)(Sprite&, float);
private:
	const ltex_t* tex;

	int hframe;
	int vframe;

	CallbackFunc callback;
	void* userData;

	Vec2 position, scale, pivot, size;

	float angle, red, green, blue, alpha;

	int fps;
	float currentFrame;

	lblend_t blend;


public:
	Sprite(const char* _tex, int _hframes = 1, int _vframes = 1);

	void setCallback(CallbackFunc _func);
	void setUserData(void* _data);

	const ltex_t* getTexture() const;
	void setTexture(const ltex_t* _tex, int _hframes = 1, int _vframes = 1);

	lblend_t getBlend() const;
	void setBlend(lblend_t _mode);

	float getRed() const;
	float getGreen() const;
	float getBlue() const;
	float getAlpha() const;
	void setColor(float r, float g, float b, float a);

	const Vec2& getPosition() const;
	void setPosition(const Vec2& _pos);

	float getAngle() const;
	void setAngle(float _angle);

	void setRotation(float _angle);

	const Vec2& getScale() const;
	void setScale(const Vec2& _scale);

	Vec2 getSize() const; //tamaño de un frame multiplicado por la escala
	void setSize(const Vec2& _size);

	const Vec2& getPivot() const;
	void setPivot(const Vec2& _pivot);

	int getHframes() const;
	int getVframes() const;

	int getFps() const;
	void setFps(int _fps);

	float getCurrentFrame() const;
	void setCurrentFrame(int _frame);

	void update(float deltaTime);
	void draw() const;
};