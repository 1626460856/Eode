#include <iostream>
#include <windows.h>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

mutex mtx; // 用于控制控制台输出的互斥量

// 定义函数
void zeroXy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
//子弹的类
class Bullet {
public:
	int x, y;//子弹自己的坐标
	char direction;//子弹的朝向
	char symbol;//特征形状
	Bullet(int x, int y, char direction, char symbol) : x(x), y(y), direction(direction), symbol(symbol) {}

	virtual void move() = 0;//这是一个纯虚函数，表示子弹类是一个抽象类，不能直接实例化
};

class ABullet : public Bullet {
public:
	ABullet(int x, int y, char direction, char symbol) : Bullet(x, y, direction, symbol) {}

	void move() override {
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
	}
};

class BBullet : public Bullet {
public:
	BBullet(int x, int y, char direction, char symbol) : Bullet(x, y, direction, symbol) {}

	void move() override {
		zeroXy(x, y);
		cout << " ";
		switch (direction) {
		case 'I': y--; break;
		case 'K': y++; break;
		case 'J': x--; break;
		case 'L': x++; break;
		}
		if (x >= 15 && x <= 99 && y >= 2 && y <= 27) {
			zeroXy(x, y);
			cout << symbol;
		}
	}
};

class Character {//表示游戏中的角色
public:
	int x, y;
	char direction;//朝向
	char symbol;//特征样式&和@
	int score;//这个整数变量表示角色的得分。
	vector<Bullet*> bullets;//这个向量存储了角色发射的子弹，Bullet* 是一个指向 Bullet 对象的指针。

	Character(int x, int y, char direction, char symbol) : x(x), y(y), direction(direction), symbol(symbol), score(0) {}

	virtual void move() = 0;//纯虚函数，表示角色的移动行为
	virtual void clean() = 0;//纯虚函数，表示清除角色当前显示的方法
	virtual void coutit() = 0;//输出飞机的虚函数
	virtual void spawnBullets() = 0;//纯虚函数，表示生成子弹的方法
	virtual void updateBullets(Character* otherCharacter) = 0;//纯虚函数，表示更新子弹状态的方法
};

class CharacterA : public Character {
public:
	CharacterA(int x, int y, char direction, char symbol) : Character(x, y, direction, symbol) {}

	void move() override {
		while (true)
		{
			mtx.lock(); // 锁定互斥量，确保控制台输出不被打断
			clean();
			if (GetAsyncKeyState('W') & 0x8000 && y > 2) {
				direction = 'W';
				y--;
			}
			if (GetAsyncKeyState('S') & 0x8000 && y < 27) {
				direction = 'S';
				y++;
			}
			if (GetAsyncKeyState('A') & 0x8000 && x > 16) {
				direction = 'A';
				x--;
			}
			if (GetAsyncKeyState('D') & 0x8000 && x < 98) {
				direction = 'D';
				x++;
			}
			coutit();
			zeroXy(0, 0);
			cout << "&方积分：" << score;
			mtx.unlock(); // 解锁互斥量

			Sleep(50); // 短暂休眠，防止CPU占用过高
		}
	}

	void clean() override {
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
	void coutit() override {
		zeroXy(x, y);
		cout << "&";
		if (direction == 'W') {
			zeroXy(x, y - 1);
			cout << "&";
			zeroXy(x - 1, y);
			cout << "&";
			zeroXy(x + 1, y);
			cout << "&";
		}
		if (direction == 'D') {
			zeroXy(x, y - 1);
			cout << "&";
			zeroXy(x, y + 1);
			cout << "&";
			zeroXy(x + 1, y);
			cout << "&";
		}
		if (direction == 'S') {
			zeroXy(x, y + 1);
			cout << "&";
			zeroXy(x - 1, y);
			cout << "&";
			zeroXy(x + 1, y);
			cout << "&";
		}
		if (direction == 'A') {
			zeroXy(x, y + 1);
			cout << "&";
			zeroXy(x, y - 1);
			cout << "&";
			zeroXy(x - 1, y);
			cout << "&";
		}
	}

	void spawnBullets() override {
		while (true) {
			mtx.lock();
			bullets.push_back(new ABullet(x, y, direction, '+'));
			mtx.unlock();
			Sleep(200);
		}
	}

	void updateBullets(Character* otherCharacter) override {
		while (true)
		{
			mtx.lock();
			for (auto it = bullets.begin(); it != bullets.end();) {
				(*it)->move();
				if ((*it)->x == 99 || (*it)->x == 15 || (*it)->y == 1 || (*it)->y == 28) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					it = bullets.erase(it);
				}
				else if ((*it)->x == otherCharacter->x && (*it)->y == otherCharacter->y) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					score++;
					it = bullets.erase(it);
				}
				else if ((*it)->x == otherCharacter->x - 1 && (*it)->y == otherCharacter->y) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					score++;
					it = bullets.erase(it);
				}
				else if ((*it)->x == otherCharacter->x + 1 && (*it)->y == otherCharacter->y) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					score++;
					it = bullets.erase(it);
				}
				
				else if ((*it)->x == otherCharacter->x && (*it)->y == otherCharacter->y + 1) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					score++;
					it = bullets.erase(it);
				}
				else if ((*it)->x == otherCharacter->x && (*it)->y == otherCharacter->y - 1) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					score++;
					it = bullets.erase(it);
				}
				else {
					++it;
				}
			}
			mtx.unlock();
			Sleep(50);
		}
	}
};
class CharacterB : public Character {
public:
	CharacterB(int x, int y, char direction, char symbol) : Character(x, y, direction, symbol) {}

	void move() override {
		while (true) {
			mtx.lock(); // 锁定互斥量，确保控制台输出不被打断
			clean();
			if (GetAsyncKeyState('I') & 0x8000 && y > 2) {
				direction = 'I';
				y--;
			}
			if (GetAsyncKeyState('K') & 0x8000 && y < 27) {
				direction = 'K';
				y++;
			}
			if (GetAsyncKeyState('J') & 0x8000 && x > 16) {
				direction = 'J';
				x--;
			}
			if (GetAsyncKeyState('L') & 0x8000 && x < 98) {
				direction = 'L';
				x++;
			}
			coutit();
			zeroXy(105, 0);
			cout << "@方积分：" << score;
			mtx.unlock(); // 解锁互斥量

			Sleep(50); // 短暂休眠，防止CPU占用过高
		}
	}

	void clean() override {
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

	void coutit() {
		zeroXy(x, y);
		cout << "@";
		if (direction == 'I') {
			zeroXy(x, y - 1);
			cout << "@";
			zeroXy(x - 1, y);
			cout << "@";
			zeroXy(x + 1, y);
			cout << "@";
		}
		if (direction == 'L') {
			zeroXy(x, y - 1);
			cout << "@";
			zeroXy(x, y + 1);
			cout << "@";
			zeroXy(x + 1, y);
			cout << "@";
		}
		if (direction == 'K') {
			zeroXy(x, y + 1);
			cout << "@";
			zeroXy(x - 1, y);
			cout << "@";
			zeroXy(x + 1, y);
			cout << "@";
		}
		if (direction == 'J') {
			zeroXy(x, y + 1);
			cout << "@";
			zeroXy(x, y - 1);
			cout << "@";
			zeroXy(x - 1, y);
			cout << "@";
		}
	}

	void spawnBullets() override {
		while (true) {
			mtx.lock();
			bullets.push_back(new BBullet(x, y, direction, '*'));
			mtx.unlock();
			Sleep(200);
		}
	}

	void updateBullets(Character* otherCharacter) override {
		while (true) {
			mtx.lock();
			for (auto it = bullets.begin(); it != bullets.end();) {
				(*it)->move();
				if ((*it)->x == 99 || (*it)->x == 15 || (*it)->y == 1 || (*it)->y == 28) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					it = bullets.erase(it);
				}
				else if ((*it)->x == otherCharacter->x && (*it)->y == otherCharacter->y) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					score++;
					it = bullets.erase(it);
				}
				else if ((*it)->x == otherCharacter->x - 1 && (*it)->y == otherCharacter->y) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					score++;
					it = bullets.erase(it);
				}
				else if ((*it)->x == otherCharacter->x + 1 && (*it)->y == otherCharacter->y) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					score++;
					it = bullets.erase(it);
				}
				else if ((*it)->x == otherCharacter->x && (*it)->y == otherCharacter->y + 1) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					score++;
					it = bullets.erase(it);
				}
				else if ((*it)->x == otherCharacter->x && (*it)->y == otherCharacter->y - 1) {
					zeroXy((*it)->x, (*it)->y);
					cout << " ";
					score++;
					it = bullets.erase(it);
				}
				else {
					++it;
				}
			}
			mtx.unlock();
			Sleep(50);
		}
	}
};


class Game {
public:
	Character* characterA;
	Character* characterB;

	Game(Character* characterA, Character* characterB) : characterA(characterA), characterB(characterB) {}
	void drawBorder() {
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
	void start() {
		system("cls");
		drawBorder();
		thread t1(&Character::move, characterA);
		thread t2(&Character::move, characterB);
		thread t3(&Character::spawnBullets, characterA);
		thread t4(&Character::spawnBullets, characterB);
		// 使用 lambda 表达式传递参数给成员函数
		std::thread t5([this]() { characterA->updateBullets(characterB); });
		std::thread t6([this]() { characterB->updateBullets(characterA); });

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();
	}
};

int main() {
	CharacterA characterA(40, 10, 'W', '&');
	CharacterB characterB(80, 10, 'I', '@');
	Game game(&characterA, &characterB);
	game.start();
	system("pause");
	return 0;
}