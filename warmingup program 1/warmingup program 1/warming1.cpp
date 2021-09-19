#include <iostream>
#include <random>
#include <string>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 1);

class Matrix {
	int element[4][4];
public:
	Matrix() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				element[i][j] = dis(gen);
			}
		}
	};
	int const getElement(int m, int n) {
		return element[m][n];
	}
	void putElement(int m, int n, int element) {
		this->element[m][n] = element;
	}
	void linePrint(int column, int row) {
		printf("|");
		for (int i = 0; i < row; i++) {
			printf("%3d", element[column][i]);
		}
		printf("|");
	}
};

class Matrix_Manager {
	Matrix** matrix_list;
	int row;
public:
	Matrix_Manager() {
		matrix_list = new Matrix*[2];
		matrix_list[0] = new Matrix;
		matrix_list[1] = new Matrix;
		row = 3;
	}
	void multiplication();		// 곱셈 (m)
	void addition();			// 덧셈 (a)
	void subtraction();			// 뺄셈 (d)
	void determinant();			// 행렬식 값 출력 (r)
	void transposed();			// 전치행렬 (t)
	void resize();				// 4x4 행렬로 변환 (h)
	void reset();				// 새로 설정 (s)

	~Matrix_Manager() {
		delete matrix_list[0];
		delete matrix_list[1];
		delete[] matrix_list;
		std::cout << "소멸자 호출" << std::endl;
	}
};
void Matrix_Manager::multiplication()
{
	std::cout << "행렬의 곱셈은 다음과 같습니다. " << std::endl;
	for (int i = 0; i < row; i++) {
		matrix_list[0]->linePrint(i, row);
		if (i == 1) {
			printf("  +  ");
		}
		else {
			printf("     ");
		}
		matrix_list[1]->linePrint(i, row);
		if (i == 1) {
			printf("  =  ");
		}
		else {
			printf("     ");
		}
		printf("|");
		for (int j = 0; j < row; j++) {
			printf("%3d", matrix_list[0]->getElement(i, 0) * matrix_list[1]->getElement(0, j) + matrix_list[0]->getElement(i, 1) * matrix_list[1]->getElement(1, j) + matrix_list[0]->getElement(i, 2) * matrix_list[1]->getElement(2, j));
		}
		printf("|\n");
	}
}
void Matrix_Manager::addition()
{
	std::cout << "행렬의 덧셈은 다음과 같습니다. " << std::endl;
	for (int i = 0; i < row; i++) {
		matrix_list[0]->linePrint(i, row);
		if (i == 1) {
			printf("  +  ");
		}
		else {
			printf("     ");
		}
		matrix_list[1]->linePrint(i, row);
		if (i == 1) {
			printf("  =  ");
		}
		else {
			printf("     ");
		}
		printf("|");
		for (int j = 0; j < row; j++) {
			printf("%3d", matrix_list[0]->getElement(i, j) + matrix_list[1]->getElement(i, j));
		}
		printf("|\n");
	}
}
void Matrix_Manager::subtraction()
{
	std::cout << "행렬의 뺄셈은 다음과 같습니다. " << std::endl;
	for (int i = 0; i < row; i++) {
		matrix_list[0]->linePrint(i, row);
		if (i == 1) {
			printf("  -  ");
		}
		else {
			printf("     ");
		}
		matrix_list[1]->linePrint(i, row);
		if (i == 1) {
			printf("  =  ");
		}
		else {
			printf("     ");
		}
		printf("|");
		for (int j = 0; j < row; j++) {
			printf("%3d", matrix_list[0]->getElement(i, j) - matrix_list[1]->getElement(i, j));
		}
		printf("|\n");
	}
}
int det2x2(int a, int b, int c, int d)
{
	return a * d - b * c;
}
int det3x3(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
	return a * det2x2(e, f, h, i) - b * det2x2(d, f, g, i) + c * det2x2(d, e, g, h);
}
int det4x4(int a, int b, int c, int d, int e, int f, int g, 
	int h, int i, int j, int k, int l, int m, int n, int o, int p)
{
	return a * det3x3(f, g, h, j, k, l, n, o, p) - b * det3x3(e, g, h, i, k, l, m, o, p) +
		c * det3x3(e, f, h, i, j, l, m, n, p) - d * det3x3(e, f, g, i, j, k, m, n, o);
}
void Matrix_Manager::determinant()
{
	std::cout << "행렬식은 다음과 같습니다. " << std::endl;
	if (row == 3) {
		for (int i = 0; i < row; i++) {
			matrix_list[0]->linePrint(i, row);
			if (i == 1) {
				printf("  =  %2d  ", det3x3(matrix_list[0]->getElement(0, 0), matrix_list[0]->getElement(0, 1), matrix_list[0]->getElement(0, 2),
					matrix_list[0]->getElement(1, 0), matrix_list[0]->getElement(1, 1), matrix_list[0]->getElement(1, 2),
					matrix_list[0]->getElement(2, 0), matrix_list[0]->getElement(2, 1), matrix_list[0]->getElement(2, 2)));
			}
			else {
				printf("         ");
			}
			matrix_list[1]->linePrint(i, row);
			if (i == 1) {
				printf("  =  %2d  ", det3x3(matrix_list[1]->getElement(0, 0), matrix_list[1]->getElement(0, 1), matrix_list[1]->getElement(0, 2),
					matrix_list[1]->getElement(1, 0), matrix_list[1]->getElement(1, 1), matrix_list[1]->getElement(1, 2),
					matrix_list[1]->getElement(2, 0), matrix_list[1]->getElement(2, 1), matrix_list[1]->getElement(2, 2)));
			}
			else {
				printf("         ");
			}
			printf("\n");
		}
	}
	else if (row == 4) {
		for (int i = 0; i < row; i++) {
			matrix_list[0]->linePrint(i, row);
			if (i == 1) {
				printf("  =  %2d  ", det4x4(matrix_list[0]->getElement(0, 0), matrix_list[0]->getElement(0, 1), matrix_list[0]->getElement(0, 2), matrix_list[0]->getElement(0, 3),
					matrix_list[0]->getElement(1, 0), matrix_list[0]->getElement(1, 1), matrix_list[0]->getElement(1, 2), matrix_list[0]->getElement(1, 3),
					matrix_list[0]->getElement(2, 0), matrix_list[0]->getElement(2, 1), matrix_list[0]->getElement(2, 2), matrix_list[0]->getElement(2, 3), 
					matrix_list[0]->getElement(3, 0), matrix_list[0]->getElement(3, 1), matrix_list[0]->getElement(3, 2), matrix_list[0]->getElement(3, 3)));
			}
			else {
				printf("         ");
			}
			matrix_list[1]->linePrint(i, row);
			if (i == 1) {
				printf("  =  %2d  ", det4x4(matrix_list[1]->getElement(0, 0), matrix_list[1]->getElement(0, 1), matrix_list[1]->getElement(0, 2), matrix_list[1]->getElement(0, 3),
					matrix_list[1]->getElement(1, 0), matrix_list[1]->getElement(1, 1), matrix_list[1]->getElement(1, 2), matrix_list[1]->getElement(1, 3),
					matrix_list[1]->getElement(2, 0), matrix_list[1]->getElement(2, 1), matrix_list[1]->getElement(2, 2), matrix_list[1]->getElement(2, 3),
					matrix_list[1]->getElement(3, 0), matrix_list[1]->getElement(3, 1), matrix_list[1]->getElement(3, 2), matrix_list[1]->getElement(3, 3)));
			}
			else {
				printf("         ");
			}
			printf("\n");
		}
	}
}
void Matrix_Manager::transposed()
{
	Matrix cmd;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			if (i != j) {
				cmd.putElement(j, i, matrix_list[0]->getElement(i, j));
			}
			else {
				cmd.putElement(j, i, matrix_list[0]->getElement(i, j));
			}
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			matrix_list[0]->putElement(i, j, cmd.getElement(i, j));
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			if (i != j) {
				cmd.putElement(j, i, matrix_list[1]->getElement(i, j));
			}
			else {
				cmd.putElement(j, i, matrix_list[1]->getElement(i, j));
			}
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			matrix_list[1]->putElement(i, j, cmd.getElement(i, j));
		}
	}
	std::cout << "교환 완료" << std::endl;
	this->determinant();
}
void Matrix_Manager::resize()
{
	if (row == 3) {
		row = 4;
		for (int i = 0; i < row; i++) {
			matrix_list[0]->putElement(i, 3, 0);
			matrix_list[0]->putElement(3, i, 0);

			matrix_list[1]->putElement(3, i, 0);
			matrix_list[1]->putElement(i, 3, 0);
		}
		matrix_list[0]->putElement(3, 3, 1);
		matrix_list[1]->putElement(3, 3, 1);
		std::cout << "4 x 4 행렬로 변환되었습니다." << std::endl;
		this->determinant();
	}
	else {
		row = 3;
		std::cout << "3 x 3 행렬로 변환되었습니다." << std::endl;
		this->determinant();
	}
}
void Matrix_Manager::reset()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			matrix_list[0]->putElement(i, j, dis(gen));
			matrix_list[1]->putElement(i, j, dis(gen));
		}
	}
	std::cout << "재설정 완료" << std::endl;
}

int main()
{

	Matrix_Manager matrix;
	char c;
	while (1) {
		std::cout << "명령어를 입력하세요 : ";
		std::cin >> c;
		switch (c) {
		case 'm':
			matrix.multiplication();
			break;
		case 'a':
			matrix.addition();
			break;
		case 'd':
			matrix.subtraction();
			break;
		case 'r':
			matrix.determinant();
			break;
		case 't':
			matrix.transposed();
			break;
		case 'h':
			matrix.resize();
			break;
		case 's':
			matrix.reset();
			break;
		case 'q':
			return 0;
		}

	}
}