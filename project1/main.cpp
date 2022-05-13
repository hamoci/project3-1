#include <iostream>	//표준입출력 기능이 있는 헤더 iostream 포함
#include <cmath>	//sqrt 함수를 사용하기 위해 헤더 cmath 포함

class Polygon {	//class Polygon 정의
private:
	int Area;	//멤버변수 Area 선언
	int Perimeter;	//멤버변수 Perimeter 선언
public:
	Polygon(int area, int perimeter);	//생성자 선언
	void print_Area();	//메소드 print_Area 선언
	void print_Perimeter();	//메소드 print_Perimeter 선언
};
Polygon::Polygon(int area, int perimeter)	//생성자 정의
{
	Area = area;	//멤버변수에 area 대입
	Perimeter = perimeter;	//멤버변수에 perimeter 대입
}

void Polygon::print_Area()	//print_Area 정의
{
	std::cout << "Area is " << Area << "\n";	//문자열 출력
}
void Polygon::print_Perimeter()	//print_Perimeter정의
{
	std::cout << "Perimeter is " << Perimeter << "\n";	//문자열 출력
}

class Triangle : public Polygon {	//class Triangle에 대한 정의 및 Polygon 상속
public:
	Triangle(int a, int b, int c);	//생성자 선언
private:
	int A;	//멤버변수 선언
	int B;	//멤버변수 선언
	int C;	//멤버변수 선언
};
Triangle::Triangle(int a, int b, int c) : Polygon(((double)1/4)*sqrt((a+b+c)*(-a+b+c)*(a-b+c)*(a+b-c)), a+b+c)	//Polygon Class 생성자 호출 및 멤버변수 초기화
{
	A = a, B = b, C = c;
}

class Square : public Polygon {	//class Square에 대한 정의 및 Polygon 상속
public:
	Square(int a, int b);	//생성자 선언
private:
	int A;	//멤버변수 선언
	int B;	//멤버변수 선언
};
Square::Square(int a, int b) : Polygon(a*b, (a+b)*2) //Polygon Class 생성자 호출 및 멤버변수 초기화
{
	A = a, B = b;	
}

int main(void)	//메인함수
{
	class Square A(5,4);	//Square Class A 선언 및 생성자호출
	class Triangle B(13, 14 ,15);	//Triangle Class B 선언 및 생성자호출
	
	std::cout << "--------Square--------" << "\n";	//문자열출력
	A.print_Area();	//메소드 호출
	A.print_Perimeter();	//메소드 호출
	std::cout << "----------------------" << "\n";	//문자열 출력
	std::cout << "-------Triangle-------" << "\n";	//문자열출력
	B.print_Area();	//메소드호출
	B.print_Perimeter();	//메소드 호출
	return 0;	//프로그램 정상종료
}
