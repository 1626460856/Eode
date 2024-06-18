#include <iostream>
#include <windows.h>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

mutex mtx; // ���ڿ��ƿ���̨����Ļ�����
char Ainto = 'W';//��¼&�ַ��ķ���
char Binto = 'I';//��¼@�ַ��ķ���
int A = 0;//��¼&�÷�
int B = 0;//��¼@�÷�
int x = 40; // &��ʼX����
int y = 10; // &��ʼY����

int i = 80; // @��ʼX����
int j = 10; // @��ʼY����
// ���庯��
void zeroXy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

// ����A�ӵ���
class ABullet {
public:
	int x, y;
	char direction;
	char symbol;
	ABullet(int x, int y, char direction, char symbol) : x(x), y(y), direction(direction), symbol(symbol) {}

	void move() {
		//mtx.lock();
		zeroXy(x, y);
		cout << " ";
		switch (direction) {
		case 'W': y--; break;
		case 'S': y++; break;
		case 'A': x--; break;
		case 'D': x++; break;
		}
		if (x >= 15 && x <= 99 && y >= 2 && y <= 27) {
			zeroXy(x, y);
			cout << symbol;
		}
		//mtx.unlock();
	}
};
// ����B�ӵ���
class BBullet {
public:
	int i, j;
	char direction;
	char symbol;
	BBullet(int i, int j, char direction, char symbol) : i(i), j(j), direction(direction), symbol(symbol) {}

	void move() {
		//mtx.lock();
		zeroXy(i, j);
		cout << " ";
		switch (direction) {
		case 'I': j--; break;
		case 'K': j++; break;
		case 'J': i--; break;
		case 'L': i++; break;
		}
		if (i >= 15 && i <= 99 && j >= 2 && j <= 27) {
			zeroXy(i, j);
			cout << symbol;
		}
		//mtx.unlock();
	}
};
vector<ABullet> bulletsA; // �洢A���ӵ�
vector<BBullet> bulletsB; // �洢B���ӵ�

void coutA(int x, int y, char Ainto){
	zeroXy(x, y);
	cout << "&";
	if (Ainto == 'W'){
		zeroXy(x, y - 1);
		cout << "&";
		zeroXy(x - 1, y);
		cout << "&";
		zeroXy(x + 1, y);
		cout << "&";
	}
	if (Ainto == 'D'){
		zeroXy(x, y - 1);
		cout << "&";
		zeroXy(x, y + 1);
		cout << "&";
		zeroXy(x + 1, y);
		cout << "&";
	}
	if (Ainto == 'S'){
		zeroXy(x, y + 1);
		cout << "&";
		zeroXy(x - 1, y);
		cout << "&";
		zeroXy(x + 1, y);
		cout << "&";
	}
	if (Ainto == 'A'){
		zeroXy(x, y + 1);
		cout << "&";
		zeroXy(x, y - 1);
		cout << "&";
		zeroXy(x - 1, y);
		cout << "&";
	}
}
void cleanA(int x, int y){
	zeroXy(x, y);
	cout << " ";
	zeroXy(x-1, y);
	cout << " ";
	zeroXy(x+1, y);
	cout << " ";
	zeroXy(x, y-1);
	cout << " ";
	zeroXy(x, y+1);
	cout << " ";
}
// �̺߳������ƶ��ַ� &
void moveChar1(int &x, int &y) {
	while (true) {
		mtx.lock(); // ������������ȷ������̨����������
		// �����һ��λ�õ��ַ�
		cleanA(x, y);
		
		// ���ݰ�����������
		if (GetAsyncKeyState('W') & 0x8000 && y > 2) { 
			Ainto = 'W';
			y--; }        // ����
		if (GetAsyncKeyState('S') & 0x8000 && y < 27){ 
			Ainto = 'S';
			y++; }       // ����
		if (GetAsyncKeyState('A') & 0x8000 && x > 16){ 
			Ainto = 'A';
			x--; }        // ����
		if (GetAsyncKeyState('D') & 0x8000 && x < 98){ 
			Ainto = 'D';
			x++; }       // ����

		// ����ַ�����λ��
		coutA(x, y, Ainto);
		zeroXy(0, 0);
		cout << "&�����֣�" << A;
		mtx.unlock(); // ����������

		Sleep(50); // �������ߣ���ֹCPUռ�ù���
	}
}
void coutB(int i, int j, char Binto){
	zeroXy(i, j);
	cout << "@";
	if (Binto == 'I'){
		zeroXy(i, j - 1);
		cout << "@";
		zeroXy(i - 1, j);
		cout << "@";
		zeroXy(i + 1, j);
		cout << "@";
	}
	if (Binto == 'L'){
		zeroXy(i, j- 1);
		cout << "@";
		zeroXy(i, j + 1);
		cout << "@";
		zeroXy(i + 1, j);
		cout << "@";
	}
	if (Binto == 'K'){
		zeroXy(i, j+ 1);
		cout << "@";
		zeroXy(i - 1, j);
		cout << "@";
		zeroXy(i + 1, j);
		cout << "@";
	}
	if (Binto == 'J'){
		zeroXy(i, j + 1);
		cout << "@";
		zeroXy(i, j - 1);
		cout << "@";
		zeroXy(i - 1, j);
		cout << "@";
	}
}
void cleanB(int x, int y){
	zeroXy(x, y);
	cout << " ";
	zeroXy(x - 1, y);
	cout << " ";
	zeroXy(x + 1, y);
	cout << " ";
	zeroXy(x, y - 1);
	cout << " ";
	zeroXy(x, y + 1);
	cout << " ";
}
// �̺߳������ƶ��ַ� @
void moveChar2(int &i, int &j) {
	while (true) {
		mtx.lock(); // ������������ȷ������̨����������
		// �����һ��λ�õ��ַ�
		cleanB(i, j);
		
		// ���ݰ�����������
		if (GetAsyncKeyState('I') & 0x8000 && j > 2){
			Binto = 'I';
			j--; }        // ����
		if (GetAsyncKeyState('K') & 0x8000 && j < 27){ 
			Binto = 'K';
			j++; }       // ����
		if (GetAsyncKeyState('J') & 0x8000 && i > 16){
			Binto = 'J';
			i--; }        // ����
		if (GetAsyncKeyState('L') & 0x8000 && i < 98){
			Binto = 'L';
			i++; }       // ����

		// ����ַ�����λ��
		coutB(i, j, Binto);
		zeroXy(105, 0);
		cout << "@�����֣�" << B;
		mtx.unlock(); // ����������

		Sleep(50); // �������ߣ���ֹCPUռ�ù���
	}
}
void spawnBullets() {
	while (true) {
		mtx.lock();
		bulletsA.push_back(ABullet(x, y, Ainto, '+'));
		bulletsB.push_back(BBullet(i, j, Binto, '*'));

		mtx.unlock();
		Sleep(200);
	}
}
void drawBorder(){//����#��
	int y = 0;
	for (int x = 14; x <= 100; x++){
		zeroXy(x, y);
		cout << "#";
	}
	y = 29;
	for (int x = 14; x <= 100; x++){
		zeroXy(x, y);
		cout << "#";
	}
	int x = 14;
	for (int y = 0; y <= 29; y++){
		zeroXy(x, y);
		cout << "#";
	}
	x = 101;
	for (int y = 0; y <= 29; y++){
		zeroXy(x, y);
		cout << "#";
	}

}
void updateABullets() {
	while (true) {
		mtx.lock();
		for (auto it = bulletsA.begin(); it != bulletsA.end();) {
			it->move();
			if (it->x == 99 || it->x == 15 || it->y == 1 || it->y == 28) {
				zeroXy(it->x, it->y);
				cout << " ";
				it = bulletsA.erase(it);
			}
			else if (it->x == i && it->y == j) {
				zeroXy(it->x, it->y);
				cout << " ";
				A++;
				it = bulletsA.erase(it);
			}
			else if (it->x == i-1 && it->y == j) {
				zeroXy(it->x, it->y);
				cout << " ";
				A++;
				it = bulletsA.erase(it);
			}
			else if (it->x == i + 1 && it->y == j) {
				zeroXy(it->x, it->y);
				cout << " ";
				A++;
				it = bulletsA.erase(it);
			}
			else if (it->x == i  && it->y == j+1) {
				zeroXy(it->x, it->y);
				cout << " ";
				A++;
				it = bulletsA.erase(it);
			}
			else if (it->x == i  && it->y == j-1) {
				zeroXy(it->x, it->y);
				cout << " ";
				A++;
				it = bulletsA.erase(it);
			}
			else {
				++it;
			}
		}
		mtx.unlock();
		Sleep(50);
	}
}
void updateBBullets() {
	while (true) {
		mtx.lock();
		for (auto it = bulletsB.begin(); it != bulletsB.end();) {
			it->move();
			if (it->i == 99 || it->i == 15 || it->j == 1 || it->j == 28) {
				zeroXy(it->i, it->j);
				cout << " ";
				it = bulletsB.erase(it);
			}
			else if (it->i == x && it->j == y) {
				zeroXy(it->i, it->j);
				cout << " ";
				B++;
				it = bulletsB.erase(it);
			}
			else if (it->i == x-1 && it->j == y) {
				zeroXy(it->i, it->j);
				cout << " ";
				B++;
				it = bulletsB.erase(it);
			}
			else if (it->i == x+1 && it->j == y) {
				zeroXy(it->i, it->j);
				cout << " ";
				B++;
				it = bulletsB.erase(it);
			}
			else if (it->i == x && it->j == y-1) {
				zeroXy(it->i, it->j);
				cout << " ";
				B++;
				it = bulletsB.erase(it);
			}
			else if (it->i == x && it->j == y+1) {
				zeroXy(it->i, it->j);
				cout << " ";
				B++;
				it = bulletsB.erase(it);
			}
			else {
				++it;
			}
		}
		mtx.unlock();
		Sleep(50);
	}
}
int main() {
	// ��տ���̨
	system("cls");
	
	drawBorder();//����#��
	// �ڿ���̨��ͬλ������ı�
	zeroXy(0, 0);
	cout << "&�����֣�"<<A;

	zeroXy(105, 0);
	cout << "@�����֣�"<<B;

	

	// ��ʼλ������ַ�
	zeroXy(x, y);
	cout << "&";
	zeroXy(i, j);
	cout << "@";

	// �����������߳�
	thread t1(moveChar1, ref(x), ref(y));
	thread t2(moveChar2, ref(i), ref(j));
	thread t3(spawnBullets);
	thread t4(updateABullets);
	thread t5(updateBBullets);
	// �ȴ��߳����
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	system("pause");
	return 0;
}
