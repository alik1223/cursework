#include <iostream>
#include "Yadro.h"
using namespace std;

Yadro::Yadro(Texture & texture)
{
	sprite.setTexture(texture);
}

Yadro * Yadro::getinstance(Texture & texture)
{
	if (!s)
	{
		s = new Yadro(texture);
	}
	return s;
}
//setting parameters
void Yadro::set_x(float x)
{
	this->x = x;
}

void Yadro::set_y(float y)
{
	this->y = y;
}

void Yadro::set_dx(float dx)
{
	this->dx = dx;
}

void Yadro::set_dy(float dy)
{
	this->dy = dy;
}

void Yadro::set_V0(float V0)
{
	this->V0 = V0;
}

void Yadro::set_alpha(float alpha)
{
	this->alpha = alpha;
}

void Yadro::set_life(bool life)
{
	this->life = life;
}
//getting parameters
float Yadro::get_x()
{
	return x;
}

float Yadro::get_y()
{
	return y;
}

float Yadro::get_dx()
{
	return dx;
}

float Yadro::get_dy()
{
	return dy;
}

float Yadro::get_V0()
{
	return V0;
}

float Yadro::get_alpha()
{
	return alpha;
}

bool Yadro::get_life()
{
	return life;
}

FloatRect Yadro::getRect()
{
	return FloatRect(x, y, 30, 28);
}

Sprite Yadro::get_sprite()
{
	return sprite;
}
