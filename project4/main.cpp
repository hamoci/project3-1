#include <iostream>	//표준입출력 기능이 있는 헤더 iostream 포함
#include <string>	//string STL 기능이 있는 헤더 string 포함
#include <algorithm> //sort 기능이 있는 헤더 algorithm 포함
#include <vector>	//vector STL이 있는 헤더 vector 포함

class Info {
	public:
		int id;
		std::string name;
};

int StringCompare(const Info info1, const Info info2);	//비교함수에 대한 prototype 선언
int IDCompare(const Info info1, const Info info2);		//비교함수에 대한 prototype 선언

class Node {	//class Node에 대한 정의
	private:	
		Node* prev = NULL;	//멤버변수 prev 선언
		int ID;		//멤버변수 ID 선언
		std::string name;	//멤버변수 name 선언
		Node* next = NULL;	//멤버변수 next 선언
	public:	
		Node(int id, std::string name);	//생성자 선언
		Node() {}	//기본 생성자 선언
		Node* GetPrev() { return prev; }	//prev 반환하는 메소드
		Node* GetNext() { return next; }	//next 반환하는 메소드
		int GetID() { return ID; }	//ID 반환하는 메소드
		std::string GetName() { return name; }	//name 반환하는 메소드
		void SetPrev(Node* node) { prev = node; }	//prev 초기화 메소드
		void SetNext(Node* node) { next = node; }	//next 초기화 메소드
		void SetID(int id) { ID = id; } // id 초기화 메소드
		void SetName(std::string name) { this->name = name; } // name 초기화 메소드
};
Node::Node(int id, std::string name)	//생성자 정의
{
	this->ID = id;	//멤버변수 초기화
	this->name = name;
}

class List{	//class List 정의
	private:
		Node* head = NULL;//멤버변수 head 선언
		Node* tail = NULL;//멤버변수 tail 선언
		int size = 0;	//멤버변수 size 선언
	public:
		~List();	//소멸자 선언
		void InsertNode(int id, std::string name);	//InsertNode 메소드 선언
		void DeleteNode(int id);	//DeleteNode 메소드 선언
		void Print();	//Print 메소드 선언
		void PrintReverse();	//PrintReverse 메소드 선언
		void SortByName();	//SortByName 메소드 선언
		void SortByID();	//SortByID 메소드 선언
};

void List::InsertNode(int id, std::string name)	//InsertNode 메소드에 대한 정의
{
	if(size == 0)		//size가 0일 때
	{
		Node* new_node = new Node(id, name);	//새로운 Node 생성
		head = tail = new_node;	//head, tail이 전부 동일함
		head->SetNext(NULL);	//앞도, 뒤도 없기 때문에 NULL 대입
		head->SetPrev(NULL);	//위와 동일
		size++;	//size 1증가
		return;	//반환
	}
	else if (size == 1)	//size가 1일 때
	{
		if(head->GetID() > id)	//무조건 머리의 앞이거나 머리의 뒤이다.
		{	//머리의 앞에 와야할 때
			Node* new_node = new Node(id, name);	//Node 생성
			new_node->SetNext(head);	//Node의 다음 Node가 머리
			new_node->SetPrev(NULL);	//Node의 이전 Node는 없음
			head->SetPrev(new_node);	//머리의 이전 Node는 new_node
			tail = head;	//머리가 이제 tail임
			head = new_node;	//new_node가 이제 머리임
			size++;	//size 1 증가
		}
		else if(head->GetID() < id)		//new_node가 머리의 뒤일 때
		{
			Node* new_node = new Node(id, name);	//Node 생성	
			new_node->SetNext(NULL);	//new_node의 다음은 없음
			new_node->SetPrev(head);	//new_node의 이전 Node는 머리
			head->SetNext(new_node);	//head 다음이 new_node
			tail = new_node;	//new_node가 tail
			size++; //size 1 증가
		}
		return;
	}
	Node* temp = head;	//탐색을 위해 temp 선언
	while(temp != NULL)	//temp가 끝까지 도달할 때 까지
	{
		if(temp->GetID() == id)	//같으면 반환
			return;
		else if (temp->GetID() > id)	//temp의 ID가 id보다 크면
		{
			Node* new_node = new Node(id, name);	//Node 생성
			if(temp == head) //temp 가 head이면
			{
				new_node->SetPrev(NULL);	//new_node가 머리가 되어야한다
				new_node->SetNext(head);
				head = new_node;	
				new_node->GetNext()->SetPrev(new_node);	//머리의 다음 Node의 prev를 new_node로함
				size++;
				return;
			}
			new_node->SetPrev(temp->GetPrev());	//temp와 그 전 Node의 사이에 new_node를 넣음
			new_node->SetNext(temp);
			temp->SetPrev(new_node);	//temp의 이전 Node를 new_node로
			new_node->GetPrev()->SetNext(new_node);	//원래 temp의 이전 Node의 Next를 new_node로
			size++;
			return;
		}
		temp = temp->GetNext();	//다음 탐색을 위해 GetNext 대입
	}
	Node* new_node = new Node(id, name);	//Node 생성
	tail->SetNext(new_node);	//원래 tail의 next를 new_node로 함
	new_node->SetNext(NULL);	//new_node의 다음은 없음
	new_node->SetPrev(tail);	//new_node의 이전은 tail
	tail = new_node;	//이제부터 new_node가 tail
	size++;	
	return;
}

void List::DeleteNode(int id)	//Node삭제를 위한 DeleteNode 메소드 정의
{
	Node* temp = head;	//탐색을 위한 선언
	if(size == 0) return;	//size가 0이면 삭제할 것이 없음
	if(size == 1)	//size가 1일 때
	{
		if(head->GetID() == id)	//head의 ID와 id가 같다면
			delete head;	//head 동적할당 해제
		size--;	//size 1 감소
		head = tail = NULL;	//head, tail에 NULL 대입
		return;	//반환
	}
	if(head->GetID() == id)	//head의 ID와 id가 같다면
	{
		temp = head->GetNext();	//임시로 head의 다음 Node 저장
		delete head;	//head 동적할당 해제
		temp->SetPrev(NULL);	//이전 node를 NULL로함
		head = temp;	//temp가 이제 head임
		size--;
		return;
	}
	if(tail->GetID() == id)	//tail의 ID와 id가 같다면
	{
		temp = tail->GetPrev();	//tail의 이전 Node를 임시로 저장
		delete tail;	//tail 동적할당 해제
		temp->SetNext(NULL);	//temp의 다음 Node는 없음
		tail = temp;	//이제 temp가 tail임
		size--;
		return;
	}
	temp = temp->GetNext();	//temp는 head가 아닌 2번째 Node부터 확인
	while(temp->GetNext() != NULL)	//마지막 Node는 앞에서 확인했으니 바로 앞까지만 검사
	{
		if(temp->GetID() == id)	//temp와 ID가 같을 경우 삭제해야함
		{
			temp->GetPrev()->SetNext(temp->GetNext());	//삭제할 Node의 이전 Node가 next를 가리키도록
			temp->GetNext()->SetPrev(temp->GetPrev());	//삭제할 Node의 다음 Node가 prev를 가리키도록
			delete temp;	//동적할당 해제
			size--;
			return;
		}
		temp = temp->GetNext();	//다음 Node 탐색을 위한 대입
	}
	return;
}

void List::Print()	//List를 출력하는 Print 메소드 정의
{
	Node* temp = head;	//탐색을 위한 Node
	while(temp != NULL)	//끝에 도달하기 전까지
	{
		std::cout << temp->GetID() << " " << temp->GetName() << "\n";	//ID, Name 출력
		temp = temp->GetNext();	//탐색을 위해 다음 Node 대입
	}
	return;
}

void List::PrintReverse()	//List를 역으로 출력하는 PrintReverse 메소드 정의
{
	Node* temp = tail;	//탐색을 위한 Node
	while(temp != NULL)	//끝에 도달하기 전까지
	{
		std::cout << temp->GetID() << " " << temp->GetName() << "\n";	//ID, Name 출력
		temp = temp->GetPrev();	//탐색을 위해 이전 Node 대입
	}
	return;
}

void List::SortByID()	//ID로 정렬하는 SortByID 메소드 정의
{
	std::vector<Info> info;	//info를 저장하기 위한 vector 선언
	Info temp_info;	//
	Node* temp = head;	//탐색을 위한 Node pointer 선언
	int iter = 0;	//반복자 iter 선언
	while(temp != NULL)	//연결리스트의 끝까지 탐색
	{
		temp_info.id = temp->GetID();	//정보를 모두 info 구조체에 넣음
		temp_info.name = temp->GetName();
		info.push_back(temp_info);
		iter++;	//반복자 증가
		temp = temp->GetNext();	//다음 Node 탐색을 위해 다음 Node 대입
	}
	std::sort(info.begin(), info.end(), IDCompare);
	temp = head;	//정렬이 끝났으니 리스트에 그대로 넣어주기 위함
	iter = 0;	//반복자도 초기화
	while(temp != NULL)	//연결리스트의 끝까지 탐색
	{
		temp->SetID(info[iter].id);	//구조체에 저장된 정보를 Node로 대입
		temp->SetName(info[iter].name);
		iter++;	//반복자 증가
		temp = temp->GetNext();	//다음 Node 탐색을 위해 다음 Node 대입
	}
}

void List::SortByName()
{
	std::vector<Info> info;
	Info temp_info;
	Node* temp = head;	//탐색을 위한 Node pointer 선언
	int iter = 0;	//반복자 iter 선언
	while(temp != NULL)	//연결리스트의 끝까지 탐색
	{
		temp_info.id = temp->GetID();	
		temp_info.name = temp->GetName();
		info.push_back(temp_info);
		iter++;	//반복자 증가
		temp = temp->GetNext();	//다음 Node 탐색을 위해 다음 Node 대입
	}
	std::sort(info.begin(), info.end(), StringCompare);
	temp = head;	//정렬이 끝났으니 리스트에 그대로 넣어주기 위함
	iter = 0;	//반복자도 초기화
	while(temp != NULL)	//연결리스트의 끝까지 탐색
	{
		temp->SetID(info[iter].id);	//구조체에 저장된 정보를 Node로 대입
		temp->SetName(info[iter].name);
		iter++;	//반복자 증가
		temp = temp->GetNext();	//다음 Node 탐색을 위해 다음 Node 대입
	}
}

List::~List()	//소멸자를 통해 연결리스트 전체 할당 해제
{
	Node* temp = head;
	while(temp != NULL)	//연결리스트의 끝까지 반복
	{
		head = temp->GetNext();	//다음 Node를 머리로 만듬
		std::cout << " Free[" << temp->GetID() << "]\n";
		delete temp;	//그 이후 그 전 Node 동적할당 해제
		temp = head;	//다음 Node를 head로 만듬
	}
}

int main(void)
{
	List list;	//list 선언
	int command;	//command 선언
	int id;	//id입력을 위해 id 선언
	std::string name;	//name 입력을 위해 name 선언
	while(1)
	{
		std::cout << "Please Enter command(1 : insert, 2 : print, 3 : print_reverse, 4 : sort_by_name, 5 : sort_by_ID, 6 : delete, 7 : exit) : ";
		std::cin >> command;
		switch(command)
		{
			case 1:
				std::cin >> id >> name;	//id, name 입력
				list.InsertNode(id, name);	//Node 추가
				break;
			case 2:
				list.Print();	//연결리스트 출력
				break;
			case 3:
				list.PrintReverse();	//연결리스트 거꾸로 출력
				break;
			case 4:
				list.SortByName();	//연결리스트 이름으로 정렬
				break;
			case 5:
				list.SortByID();	//연결리스트 ID로 정렬
				break;
			case 6:
				std::cin >> id;	//특정 id를 가진 Node 삭제
				list.DeleteNode(id);
				break;
			case 7:
				return 0;	//프로그램 정상종료
				break;
			default:
				break;
		}
	}
	return 0;
}

int StringCompare(const Info info1, const Info info2)	//비교함수에 대한 정의
{
	return info1.name < info2.name;
}

int IDCompare(const Info info1, const Info info2)	//비교함수에 대한 정의
{
	return info1.id < info2.id;
}
