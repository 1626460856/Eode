#include <iostream>
#include <windows.h>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

mutex mtx; // 用于控制控制台输出的互斥量
char Ainto = 'W';//记录&字符的方向
char Binto = 'I';//记录@字符的方向
int A = 0;//记录&得分
int B = 0;//记录@得分
int x = 40; // &初始X坐标
int y = 10; // &初始Y坐标

int i = 80; // @初始X坐标
int j = 10; // @初始Y坐标
// 定义函数
void zeroXy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

// 定义A子弹类
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
// 定义B子弹类
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
vector<ABullet> bulletsA; // 存储A型子弹
vector<BBullet> bulletsB; // 存储B型子弹

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
// 线程函数：移动字符 &
void moveChar1(int &x, int &y) {
	while (true) {
		mtx.lock(); // 锁定互斥量，确保控制台输出不被打断
		// 清除上一个位置的字符
		cleanA(x, y);
		
		// 根据按键调整坐标
		if (GetAsyncKeyState('W') & 0x8000 && y > 2) { 
			Ainto = 'W';
			y--; }        // 向上
		if (GetAsyncKeyState('S') & 0x8000 && y < 27){ 
			Ainto = 'S';
			y++; }       // 向下
		if (GetAsyncKeyState('A') & 0x8000 && x > 16){ 
			Ainto = 'A';
			x--; }        // 向左
		if (GetAsyncKeyState('D') & 0x8000 && x < 98){ 
			Ainto = 'D';
			x++; }       // 向右

		// 输出字符到新位置
		coutA(x, y, Ainto);
		zeroXy(0, 0);
		cout << "&方积分：" << A;
		mtx.unlock(); // 解锁互斥量

		Sleep(50); // 短暂休眠，防止CPU占用过高
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
// 线程函数：移动字符 @
void moveChar2(int &i, int &j) {
	while (true) {
		mtx.lock(); // 锁定互斥量，确保控制台输出不被打断
		// 清除上一个位置的字符
		cleanB(i, j);
		
		// 根据按键调整坐标
		if (GetAsyncKeyState('I') & 0x8000 && j > 2){
			Binto = 'I';
			j--; }        // 向上
		if (GetAsyncKeyState('K') & 0x8000 && j < 27){ 
			Binto = 'K';
			j++; }       // 向下
		if (GetAsyncKeyState('J') & 0x8000 && i > 16){
			Binto = 'J';
			i--; }        // 向左
		if (GetAsyncKeyState('L') & 0x8000 && i < 98){
			Binto = 'L';
			i++; }       // 向右

		// 输出字符到新位置
		coutB(i, j, Binto);
		zeroXy(105, 0);
		cout << "@方积分：" << B;
		mtx.unlock(); // 解锁互斥量

		Sleep(50); // 短暂休眠，防止CPU占用过高
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
void drawBorder(){//绘制#框
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
	// 清空控制台
	system("cls");
	
	drawBorder();//绘制#框
	// 在控制台不同位置输出文本
	zeroXy(0, 0);
	cout << "&方积分："<<A;

	zeroXy(105, 0);
	cout << "@方积分："<<B;

	

	// 初始位置输出字符
	zeroXy(x, y);
	cout << "&";
	zeroXy(i, j);
	cout << "@";

	// 创建并启动线程
	thread t1(moveChar1, ref(x), ref(y));
	thread t2(moveChar2, ref(i), ref(j));
	thread t3(spawnBullets);
	thread t4(updateABullets);
	thread t5(updateBBullets);
	// 等待线程完成
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	system("pause");
	return 0;
}
