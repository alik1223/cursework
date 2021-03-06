#ifndef Yadro_h
#define Yadro_h
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Yadro
{
private:
	float x, y, dx, dy;
	float V0, alpha;
	float m;
	bool life = true;
	Yadro(Texture &texture);
	static Yadro *s;
public:
	static Yadro *getinstance(Texture &texture);//static function
	Sprite sprite;
	void set_x(float x);
	void set_y(float y);
	void set_dx(float dx);
	void set_dy(float dy);
	void set_V0(float V0);
	void set_alpha(float alpha);
	void set_m(float m);
	void set_life(bool life);
	float get_x();
	float get_y();
	float get_dx();
	float get_dy();
	float get_V0();
	float get_alpha();
	float get_m();
	bool get_life();
	FloatRect getRect();
	Sprite get_sprite();

};
#endif
