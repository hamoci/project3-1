#include <iostream>	//표준입출력 기능이 있는 iostream 헤더 포함

class mystring { //class mystring 정의
private:
	char* string = NULL;	//멤버변수 선언 및 초기화
public:
	mystring(const char* str);	//생성자 선언
	mystring(const mystring& str);	//복사생성자 선언
	mystring() {};	//기본생성자 선언
	~mystring() { if (string != NULL) delete string; } //소멸자 선언
	friend mystring& operator+=(mystring&, char*);	//+=연산자 오버로딩 선언
	friend mystring& operator-=(mystring&, char);	//-=연산자 오버로딩 선언
	friend mystring& operator--(mystring&, int);	//--연산자 오버로딩 선언
	friend mystring& operator&&(mystring&, char);	//&&연산자 오버로딩 선언
	void print();	//print 메소드 선언
};

mystring::mystring(const char* str)	//생성자 정의
{
	int length = 0;	//길이를 저장할 변수 선언
	while(str[length] != '\0') length++;	//길이 측정
	string = new char[length + 1];	//동적할당 새로함
	for(int i = 0; i < length; i++)	//parameter로 들어온 str 대입
		string[i] = str[i];
	string[length] = '\0';		//마지막에 NULL 넣어줌
}

mystring::mystring(const mystring& str)	//복사생성자 정의
{	//생성자와 구조 동일
	int length = 0;
	while(str.string[length] != '\0') length++;
	this->string = new char[length + 1];
	for(int i = 0; i < length; i++)
		this->string[i] = str.string[i];
	this->string[length] = '\0';	
}

mystring& operator+=(mystring& str, char* cat)	//+= 연산자 오버로딩에 대한 정의
{
	int length_str = 0;	//mystring의 string 길이를 저장할 변수
	int length_cat = 0;	//parameter인 cat의 길이를 저장할 변수
	int idx = 0;	//탐색을 위한 임시 변수
	char* new_string;	//동적할당 후 저장할 공간
	if(str.string != NULL) while(str.string[length_str] != '\0') length_str++;	//string 길이 측정
	while(cat[length_cat] != '\0') length_cat++; //cat 길이 측정
	new_string = new char[length_str + length_cat + 1];	//길이 + 1만큼 동적할당(NULL 공간 생각)
	for(int i = 0 ; i < length_str; i++, idx++)
		new_string[i] = str.string[i];	//새로 만든 배열에 str.string 대입
	for(int i = 0 ; i < length_cat; i++, idx++)	
		new_string[idx] = cat[i];	//str.string 뒤에 cat 대입
	new_string[length_str + length_cat] = '\0';	//마지막에 NULL문자 넣어줌
	if(str.string != NULL) delete str.string;	//str.string 동적할당 해제
	str.string = new_string;	//str.string에 new_string 대입
	return str;	//str 반환
}

mystring& operator-=(mystring& str, char ch)	//-= 연산자 오버로딩에 대한 정의
{
	if(str.string == NULL) return str;	//string이 비었으면 바로 함수 반환
	char* new_string;	//동적할당 후 저장할 공간
	int temp_length = 0;	//임시 길이 저장
	int length = 0;	//실제 문자열 길이  저장
	while(str.string[length] != '\0') length++, temp_length++;	//문자열 길이 측정
	for(int i = 0; i < temp_length; i++)
		if(str.string[i] == ch)
			length--;	//ch와 동일한 문자있으면 length 1감소

	new_string = new char[length + 1];	//NULL문자 포함하여 length+1만큼 동적할당
	for(int i = 0, idx = 0; i < temp_length; i++)
		if(str.string[i] != ch) //ch와 다른 글자일 경우 그 글자를 문자열에 넣음
			new_string[idx++] = str.string[i]; 
	new_string[length] = '\0'; //마지막에 NULL 붙여줌
	delete str.string;	//str.string 동적할당 해제
	str.string = new_string;	//str.string에 new_string 대입
	return str;	//str 반환
}

mystring& operator--(mystring& str, int dummy)	//--연산자 오버로딩에 대한 정의
{												//dummy를 넣는것으로 후위연산으로 인식하게함
	if(str.string == NULL) return str;	//string이 비었으면 바로 반환
	char* new_string;	//동적할당하고 저장할 문자열
	int length = 0;	//문자열의 길이 저장
	while(str.string[length] != '\0') length++;	//문자열 길이 측정
	new_string = new char[length];	//length만큼 동적할당
	for(int i = 0; i < length - 1; i++)
	{
		new_string[i] = str.string[i];	//length-1 만큼 반복하여 대입
	}
	new_string[length - 1] = '\0';	//마지막에 NULL 붙여줌
	delete str.string;	//str.string 동적할당 해제
	str.string = new_string;	//str.string에 new_string 대입
	return str;	//str 반환
}

mystring& operator&&(mystring& str, char ch)	//&&연산자 오버로딩에 대한 정의
{
	if(str.string == NULL) return str;	//string이 NULL이면 바로 반환
	int length = 0;	//길이를 저장할 변수
	while(str.string[length] != '\0')	//NULL을 만날때까지 반복
	{
		if(str.string[length] != ch) str.string[length] = '0';	//ch가 아니면 '0'으로 바꿈
		length++;	//length 1증가
	}
	return str;	//str반환
}

void mystring::print()	//print 메소드에 대한 정의
{
	std::cout << string << "\n";	//string 출력 및 개행
}

int main(void)
{
	char string2[101];	//string2가 최대 100칸이므로 NULL문자생각하여 101만큼 선언
	int command;	//커맨드를 입력할 변수 선언
	char ch;	//특정한 문자 입력할 변수 선언
	mystring str;	//mystring형 str 선언
	while(1)	//무한루프
	{
		std::cout << "Please Enter commmand(1 : add, 2 : delete_char, 3 : delete_lastchar, 4 : and_operator, 5 : print, 6 : exit) :";	//문자열 출력
		std::cin >> command;	//command 입력
		switch(command)
		{
			case 1:	//1일 경우
				std::cin >> string2;	//string2 입력
				str += string2;	//+= 연산수행
				break;
			case 2:	//2일 경우
				std::cin >> ch;	//ch 입력
				str -= ch;	//-= 연산 수행
				break;
			case 3:	//3일 경우
				str--;	//--연산 수행
				break;
			case 4:	//4일 경우
				std::cin >> ch;	//ch 입력
				str && ch;	//&& 연산 수행
				break;
			case 5:	//5일 경우
				str.print();	//메소드 호출을 통해 string 출력
				break;
			case 6:	//6일 경우
				return 0;	//프로그램 정상종료
				break;
		}
	}
	return 0;	//프로그램 정상 종료
}
