#include "Sprite.h"
#include "Vec2.h"

#include <string>

// those must be at the top always
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

// editor
#include <litegfx.h>
#include <glfw3.h>
#include <stb_image.h>

#include <iostream>


ltex_t* loadTexture(const char* filename)
{
	int x = 10;
	int y = 10;
	int* pX = &x;
	int* pY = &y;
	int* comp = nullptr;
	int req_comp = 4;
	unsigned char* image = stbi_load(filename, pX, pY, comp, req_comp);

	if (image == nullptr)
	{
		std::cout << "Unable to load image : " << filename << "\n";
	}

	ltex_t* img = ltex_alloc(x, y, 0);


	ltex_setpixels(img, image);
	stbi_image_free(image);

	return img;
}


Sprite::Sprite(const char* fileName, int _hframes, int _vframes)
{
	tex = loadTexture(fileName);

	hframe = _hframes;
	vframe = _vframes;

	callback = nullptr;

	userData = nullptr;

	position = Vec2();
	scale = Vec2(1, 1);
	pivot = Vec2(0.5f, 0.5f);
	size = Vec2(1, 1);

	angle = 0.f;
	red = 0.15f;
	green = 0.15f;
	blue = 0.15f;
	alpha = 0.f;

	fps = 0;
	currentFrame = 0;

	blend = BLEND_SOLID;
}

void Sprite::setCallback(CallbackFunc _func)
{
	callback = _func;
}
void Sprite::setUserData(void* _data)
{
	userData = _data;
}

const ltex_t* Sprite::getTexture() const
{
	return tex;
}
void Sprite::setTexture(const ltex_t* _tex, int _hframes, int _vframes)
{
	tex = _tex;
	hframe = _hframes;
	vframe = _vframes;
}

lblend_t Sprite::getBlend() const
{
	return blend;
}
void Sprite::setBlend(lblend_t _mode)
{
	blend = _mode;
}

float Sprite::getRed() const
{
	return red;
}
float Sprite::getGreen() const
{
	return green;
}
float Sprite::getBlue() const
{
	return blue;
}
float Sprite::getAlpha() const
{
	return alpha;
}
void Sprite::setColor(float r, float g, float b, float a)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;

	// set color here
}

const Vec2& Sprite::getPosition() const
{
	return position;
}
void Sprite::setPosition(const Vec2& _pos)
{
	position = _pos;
}

void Sprite::setRotation(float _angle)
{
	position.rotate(_angle, 1);
}

float Sprite::getAngle() const
{
	return angle;
}
void Sprite::setAngle(float _angle)
{
	angle = _angle;
}

const Vec2& Sprite::getScale() const
{
	return scale;
}
void Sprite::setScale(const Vec2& _scale)
{
	scale = _scale;
}

Vec2 Sprite::getSize() const
{
	return size;
}
void Sprite::setSize(const Vec2& _size)
{
	size = _size;
}

const Vec2& Sprite::getPivot() const
{
	return pivot;
}
void Sprite::setPivot(const Vec2& _pivot)
{
	pivot = _pivot;
}

int Sprite::getHframes() const
{
	return hframe;
}
int Sprite::getVframes() const
{
	return vframe;
}

int Sprite::getFps() const
{
	return fps;
}
void Sprite::setFps(int _fps)
{
	fps = _fps;
}

float Sprite::getCurrentFrame() const
{
	return currentFrame;
}
void Sprite::setCurrentFrame(int _frame)
{
	currentFrame = _frame;
}

void Sprite::update(float deltaTime)
{
	if (callback != nullptr)
	{
		callback(*this, deltaTime);
	}

	// update fps of animation
	if (fps != 0)
	{
		currentFrame += (fps * deltaTime); // incremento dei frame

		int tot = hframe * vframe;

		if (currentFrame >= tot)
		{
			currentFrame = 0; // we reset
		}
		else if (currentFrame < 0)
		{
			currentFrame = tot - 1; // we go the the last
		}
	}
}
void Sprite::draw() const
{
	// calcoliamo le coordinate
	int indx = static_cast<int>(currentFrame);
	int currentH = indx % hframe;
	int currentV = indx / hframe;

	float u0 = static_cast<float>(currentH) / hframe;
	float v0 = static_cast<float>(currentV) / vframe;

	float u1 = u0 + (1.0f / hframe);
	float v1 = v0 + (1.0f / vframe);

	// impostiamo il blend mode
	lgfx_setblend(blend);
	// impostiamo il colore
	lgfx_setcolor(red, green, blue, alpha);

	// disegnamo la sprite
	float width = size.x * scale.x;
	float height = size.y * scale.y;

	ltex_drawrotsized(tex, position.x, position.y, pivot.x, pivot.y, angle, width, height, u0, v0, u1, v1);
}