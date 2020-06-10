#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Yadro.h"
#include "Pushka.h"
#define PI 3.14159265
using namespace sf;
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	float alpha;
	float V0;
	bool b = false;
	bool b1 = false;
	int n;
	int length = 1300;
	int height = 600;
	int i = 0;
	RenderWindow window(VideoMode(length, height), "SFML Works!");
	Image puhka1;
	Image puhka2;
	Image shell;
	Texture texture;
	Texture texture1;
	Texture texture2;
	Texture texture3;
	puhka1.loadFromFile("images\\Pushka.png");
	puhka1.createMaskFromColor(Color(255, 255, 255));
	puhka2.loadFromFile("images\\Pushka1.png");
	puhka2.createMaskFromColor(Color(255, 255, 255));
	shell.loadFromFile("images\\yadro.png");
	shell.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(puhka1);
	texture1.loadFromImage(puhka2);
	texture2.loadFromImage(shell);
	texture3.loadFromFile("images\\karta.png");
	Sprite sprite(texture3);
	Pushka *gun1;
	Pushka *gun2;
	gun1 = new Pushka(texture, 100, 500);
	gun2 = new Pushka(texture1, 1100, 500);
	Yadro  *yadro = NULL;
	while (1)
	{
		if (gun1->get_life() == false || gun2->get_life() == false)
		{
			cout << "Игра окончена. Желаете сыграть еще?" << endl;
			cout << "|1| - Да " << endl;
			cout << "|2| - Нет " << endl;
			cin >> n;
			if (n == 2)
			{
				cout << "Спасибо за игру !!!" << endl;
				system("pause");
				break;
			}
			if (n == 1)
			{
				gun1->set_life(true);
				gun2->set_life(true);
			}

		}
		if (i % 2 == 0)
		{
			cout << "Ход игрока №1 " << endl;
		}
		else
		{
			cout << "Ход игрока №2 " << endl;
		}
		cout << "Введите начальную скорость(м/c)" << endl;
		cin >> V0;
		cout << "Введите угол(в градусах)" << endl;
		cin >> alpha;
		while (window.isOpen())
		{
			window.clear(Color::White);
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					if (i % 2 == 0)
					{
						gun1->set_isShoot(true);
						yadro = new Yadro(texture2, (gun1->get_x() + 90), gun1->get_y(), V0, alpha);
					}
					else
					{
						gun2->set_isShoot(true);
						yadro = new Yadro(texture2, (gun2->get_x() - 40), gun2->get_y(), V0, alpha);
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					if (i % 2 == 0)
					{
						gun1->set_state(0);
						gun1->move();
					}
					else
					{
						gun2->set_state(0);
						gun2->move();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					if (i % 2 == 0)
					{
						gun1->set_state(1);
						gun1->move();
					}
					else
					{
						gun2->set_state(1);
						gun2->move();
					}
				}
			}
			b = gun1->fire(yadro, i, gun2);
			b1 = gun2->fire(yadro, i, gun1);
			window.draw(sprite);
			if (gun1->get_isShoot() || gun2->get_isShoot())
			{
				window.draw(yadro->sprite);
			}
			window.draw(gun1->sprite);
			window.draw(gun2->sprite);
			window.display();
			if (!(gun2->get_life()))
			{
				cout << "Попадание!!!" << endl;
				cout << "Игрок №1 победил" << endl;
				break;
			}
			if (!(gun1->get_life()))
			{
				cout << "Попадание!!!" << endl;
				cout << "Игрок №2 победил" << endl;
				break;
			}
			if (b || b1)
			{
				cout << "Промах" << endl;
				b = b1 = false;
				break;
			}
		}
		i++;
	}
	delete gun1;
	delete gun2;
	return 0;
}
