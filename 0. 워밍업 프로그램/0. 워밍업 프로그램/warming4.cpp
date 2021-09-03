#include <iostream>
#include <random>
#include <string>
#include <math.h>

#define RIGHTLIMIT 800
#define LEFTLIMIT 0
#define UPLIMIT 600
#define DOWNLIMIT 0
#define MOVEPOINT 50

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> width(1, 8);
std::uniform_int_distribution<int> length(1, 6);

class Shape {
protected:
	int x1, y1, x2, y2;
public:
	Shape() {
		x1 = width(gen) * 50;
		y1 = length(gen) * 50;
		x2 = x1 + width(gen) * 50;
		y2 = y1 + length(gen) * 50;
	}
	void rightMove();
	void leftMove();
	void upMove();
	void downMove();

	int getx1() { return x1; }
	int getx2() { return x2; }
	int gety1() { return y1; }
	int gety2() { return y2; }

	virtual void printData() = 0;
};
void Shape::rightMove()
{
	if (x2 + MOVEPOINT > RIGHTLIMIT) {
		std::cout << "error! 더 이상 오른쪽으로 이동할 수 없습니다." << std::endl;
	}
	else {
		x1 += MOVEPOINT;
		x2 += MOVEPOINT;
	}
}
void Shape::leftMove()
{
	if (x1 - MOVEPOINT < LEFTLIMIT) {
		std::cout << "error! 더 이상 왼쪽으로 이동할 수 없습니다." << std::endl;
	}
	else {
		x1 -= MOVEPOINT;
		x2 -= MOVEPOINT;
	}
}
void Shape::upMove()
{
	if (y2 + MOVEPOINT > UPLIMIT) {
		std::cout << "error! 더 이상 위쪽으로 이동할 수 없습니다." << std::endl;
	}
	else {
		y1 += MOVEPOINT;
		y2 += MOVEPOINT;
	}
}
void Shape::downMove()
{
	if (y1 - MOVEPOINT < DOWNLIMIT) {
		std::cout << "error! 더 이상 아래쪽으로 이동할 수 없습니다." << std::endl;
	}
	else {
		y1 -= MOVEPOINT;
		y2 -= MOVEPOINT;
	}
}

class Rect : public Shape {
public:
	Rect() : Shape() { printData(); }
	void printData() override {
		printf("Rect: (%3d, %3d) (%3d, %3d)\n", x1, y1, x2, y2);
	}
};

class Line : public Shape {
public:
	Line() : Shape() { printData(); }
	void printData() override {
		printf("Line: (%3d, %3d) (%3d, %3d)\n", x1, y1, x2, y2);
	}
};

void colliderCheck(Rect rect, Line line)
{
	double distance[4];
	distance[0] = ((line.gety2() - line.gety1()) * rect.getx1() + (line.getx1() - line.getx2()) * rect.gety1() + (line.gety1() * line.getx2() - line.getx1() * line.gety2())) / 
		sqrt(pow((line.gety2() - line.gety1()), 2) + pow((line.getx1() - line.getx2()), 2));
	distance[1] = ((line.gety2() - line.gety1()) * rect.getx1() + (line.getx1() - line.getx2()) * rect.gety2() + (line.gety1() * line.getx2() - line.getx1() * line.gety2())) /
		sqrt(pow((line.gety2() - line.gety1()), 2) + pow((line.getx1() - line.getx2()), 2));
	distance[2] = ((line.gety2() - line.gety1()) * rect.getx2() + (line.getx1() - line.getx2()) * rect.gety1() + (line.gety1() * line.getx2() - line.getx1() * line.gety2())) /
		sqrt(pow((line.gety2() - line.gety1()), 2) + pow((line.getx1() - line.getx2()), 2));
	distance[3] = ((line.gety2() - line.gety1()) * rect.getx2() + (line.getx1() - line.getx2()) * rect.gety2() + (line.gety1() * line.getx2() - line.getx1() * line.gety2())) /
		sqrt(pow((line.gety2() - line.gety1()), 2) + pow((line.getx1() - line.getx2()), 2));

	if ((distance[0] > 0 && distance[1] > 0 && distance[2] > 0 && distance[3] > 0) || (distance[0] < 0 && distance[1] < 0 && distance[2] < 0 && distance[3] < 0)) {
		printf("%f %f %f %f\n", distance[0], distance[1], distance[2], distance[3]);
		std::cout << "No collide!!" << std::endl;
		return;
	}
	else {
		printf("%f %f %f %f\n", distance[0], distance[1], distance[2], distance[3]);
		std::cout << "Rectangle & Line collide!!" << std::endl;
		return;
	}
}

int main()
{
	Rect rect;
	Line line;
	colliderCheck(rect, line);

	char c;
	while (1) {
		std::cout << "input the command : ";
		std::cin >> c;
		switch (c) {
		case 'd':
			rect.rightMove();
			break;
		case 'a':
			rect.leftMove();
			break;
		case 'w':
			rect.upMove();
			break;
		case 's':
			rect.downMove();
			break;
		case 'l':
			line.rightMove();
			break;
		case 'j':
			line.leftMove();
			break;
		case 'i':
			line.upMove();
			break;
		case 'k':
			line.downMove();
			break;
		case 'q':
			return 0;
		}
		rect.printData();
		line.printData();
		colliderCheck(rect, line);
	}
}

