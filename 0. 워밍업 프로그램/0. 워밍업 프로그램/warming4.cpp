#include <iostream>
#include <random>
#include <string>

#define RIGHTLIMIT 800
#define LEFTLIMIT 0
#define UPLIMIT 600
#define DOWNLIMIT 0

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> width(0, 8);
std::uniform_int_distribution<int> length(0, 6);

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

	virtual void printData() = 0;
};
void Shape::rightMove()
{
	if (x2 + 50 > RIGHTLIMIT) {
		std::cout << "error! 더 이상 오른쪽으로 이동할 수 없습니다." << std::endl;
	}
	else {
		x1 += 50;
		x2 += 50;
	}
}
void Shape::leftMove()
{
	if (x1 - 50 > LEFTLIMIT) {
		std::cout << "error! 더 이상 왼쪽으로 이동할 수 없습니다." << std::endl;
	}
	else {
		x1 -= 50;
		x2 -= 50;
	}
}
void Shape::upMove()
{
	if (y2 + 50 > UPLIMIT) {
		std::cout << "error! 더 이상 위쪽으로 이동할 수 없습니다." << std::endl;
	}
	else {
		y1 += 50;
		y2 += 50;
	}
}
void Shape::downMove()
{
	if (y1 - 50 > DOWNLIMIT) {
		std::cout << "error! 더 이상 아래쪽으로 이동할 수 없습니다." << std::endl;
	}
	else {
		y1 -= 50;
		y2 -= 50;
	}
}

class Rect : public Shape {
public:
	Rect() : Shape() {} 
	void printData() override {
		std::cout << "Rect: (" << x1 << ", " << y1 << ") (" << x2 << ", " << y2 << ")" << std::endl;
	}
};

class Line : public Shape {
public:
	Line() : Shape() {}
	void printData() override {
		std::cout << "Line: (" << x1 << ", " << y1 << ") (" << x2 << ", " << y2 << ")" << std::endl;
	}
};

