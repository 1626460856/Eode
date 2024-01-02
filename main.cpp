#include"main.h"
#include<iostream>
using namespace std;
#include<iomanip>//使得输出更美观
#include <string>//采用string数据类型记录字符串
#include <ctime>
#include <chrono>//这两个库可以记录交易时间


struct goods {//这是定义单个商品的数据类型
	int id;//商品的编号，在后续添加商品的时候通过访问原来的商品的最后一个编号id，将新添加的商品编号设置为id+1，这样就使得编号有序，而且不用手动录入
	string name;//商品的名称
	double price;//商品的价格
	double trueprice;//我把这个量设置为了进货价格，为后面做账单做准备，那么对于一个商店来说进一批商品那么就会减去trueprice*num的资金
	int num;//数量
	struct goods* next;//第一次填入初始商品的时候采用链表输出，后续没继续使用这个参数
};
goods goodsbase[20];//创建全局商品仓库，容量为20件商品
struct user {
	string id;//用户账号
	string key;//用户密码
	string identity;//用户身份，在登录界面验证了账号和密码之后根据是购物者还是老板两种身份提供不同的服务选项
};
user userbase[20];//创建全局用户库，容量为20个
struct records {//这是定义一次交易记录的数据类型
	string id;//交易账号
	string name;//交易商品
	int num;//交易数量
	string time;//交易时间
	double money;//对商店的影响金额
};
records recordsbase[100];//创建交互记录库，容量为100次
double money;//创建商店的总金额库
void first_show_goods();//第一次填入商品并且展示商品
void show_goods();//展示商品库的所有商品
void add_goods(string id);//添加商品
void buy_goods(string id);//购买商品
void first_user_base();//第一次初始化两个用户，一个老板一个购物者
void add_user_base();//添加用户
void show_recordsbase();//展示交互记录库的交易记录
void login();//登录函数

void main() {
	first_user_base();//填入初始用户
	first_show_goods();//填入并展示初始商品
	for (;;) {//无限循环框架，在这个框架结束之前，全局数据库的内容将会保存，并可以进行使用
		int x;
		cout << "登录输入1,退出输入0,创建账号输入2,输入3关闭商店平台" << endl;
		cin >> x;
		switch (x)
		{
		case 0: {//仅退出当前的选择界面，回到最初始的界面
			break;
		}
		case 1: {
			login();//转到登录函数
			break;
		}
		case 2: {
			add_user_base();//转到新建用户函数
			break;
		}
		case 3: {
			return;//结束整个main函数，即结束所有程序
		}


		}

	}
	system("pause");
}

void first_show_goods() {//商品陈列,并且将商品仓库初始化

	struct goods goods1, goods2, goods3, goods4, goods5, goods6, * head, * p;
	goods1.id = 101; goods1.name = "卫龙辣条"; goods1.price = 2.00; goods1.num = 100;
	goods2.id = 102; goods2.name = "旺仔牛奶"; goods2.price = 5.00; goods2.num = 210;
	goods3.id = 103; goods3.name = "百世可乐"; goods3.price = 3.00; goods3.num = 110;
	goods4.id = 104; goods4.name = "乐事薯片"; goods4.price = 6.00; goods4.num = 120;
	goods5.id = 105; goods5.name = "美年达  "; goods5.price = 3.50; goods5.num = 130;
	goods6.id = 106; goods6.name = "洗衣液  "; goods6.price = 23.00; goods6.num = 150;
	cout << "****************************************************************" << endl;
	cout << endl;
	cout << setw(23) << internal << "商品标号" << "  " << "商品名" << "    " << "价格" << "  " << "剩余库存" << endl;
	//利用链表列出商品。 
	head = &goods1;
	goods1.next = &goods2;
	goods2.next = &goods3;
	goods3.next = &goods4;
	goods4.next = &goods5;
	goods5.next = &goods6;
	goods6.next = NULL;
	p = head;//我觉得这里有一个局限，每次都是把整个商品的全部信息输出了，但是显然进价是没必要展示出来的，所以后面我单独写了一个展示函数
	int i = 0;//创建局部变量作为一次索引
	while (p != NULL)
	{   //将单个商品的信息填入商品仓库，初始化仓库
		goodsbase[i].id = p->id;
		goodsbase[i].name = p->name;
		goodsbase[i].price = p->price;
		goodsbase[i].trueprice = p->price * 0.8;//初始的一批进货价设置为定价的0.8
		goodsbase[i].num = p->num;
		//输出单个商品结构体
		cout << setw(23) << internal << p->id << "  " << p->name << "  " << fixed << setprecision(2) << p->price * 1.0 << "  " << p->num << endl;
		//链表到下一个
		p = p->next;
		//局部索引i也加1
		i++;
	}
	cout << endl;
	cout << "****************************************************************" << endl;
}
void show_goods() {//单次陈列商品仓库
	cout << "****************************************************************" << endl;
	cout << endl;
	cout << setw(23) << internal << "商品标号" << "  " << "商品名" << "    " << "价格" << "  " << "剩余库存" << endl;
	for (int i = 0; i < 20; i++) {
		if (goodsbase[i].name != "") {
			cout << setw(23) << internal << goodsbase[i].id << "  " << goodsbase[i].name << "  " << fixed << setprecision(2) << goodsbase[i].price * 1.0 << "  " << goodsbase[i].num << endl;
		}
	}
	cout << endl;
	cout << "****************************************************************" << endl;
}
void add_goods(string id) {//单次进货
	cout << endl << "请输入商品名称" << endl;
	string name;
	cin >> name;
	cout << endl << "请输入商品定价" << endl;
	double price;
	cin >> price;
	cout << endl << "请输入商品进价单价" << endl;
	double trueprice;
	cin >> trueprice;
	cout << endl << "请输入商品数量" << endl;
	int num;
	cin >> num;
	for (int i = 0; i <= 20; i++) {
		if (i == 20) {
			cout << "商品仓库已满" << endl;
			break;
		}
		if (i < 20 && goodsbase[i].name == "") {
			goodsbase[i].id = goodsbase[i - 1].id + 1;
			goodsbase[i].name = name;
			goodsbase[i].price = price;
			goodsbase[i].trueprice = trueprice;
			goodsbase[i].num = num;
			money -= trueprice * num;//总金额支出
			cout << "进货成功，支出：" << trueprice * num << endl;
			for (int j = 0; j <= 100; j++) {
				if (recordsbase[j].name == "") {
					recordsbase[j].id = id;
					recordsbase[j].money = -trueprice * num;
					recordsbase[j].name = name;
					recordsbase[j].num = num;
					auto now = chrono::system_clock::now();
					time_t now_c = chrono::system_clock::to_time_t(now);
					char timeStr[26];
					ctime_s(timeStr, sizeof(timeStr), &now_c);
					recordsbase[j].time = timeStr;
					break;
				}

			}
			break;
		}
		if (i < 20 && goodsbase[i].name == name) {
			goodsbase[i].num += num;
			money -= trueprice * num;//总金额支出
			cout << "进货成功，支出：" << trueprice * num << endl;
			for (int j = 0; j <= 100; j++) {
				if (recordsbase[j].name == "") {
					recordsbase[j].id = id;
					recordsbase[j].money = (-trueprice * num);
					recordsbase[j].name = name;
					recordsbase[j].num = num;
					auto now = chrono::system_clock::now();
					time_t now_c = chrono::system_clock::to_time_t(now);
					char timeStr[26];
					ctime_s(timeStr, sizeof(timeStr), &now_c);
					recordsbase[j].time = timeStr;
					break;
				}

			}
			break;
		}
	}
}
void first_user_base() {//将用户库初始化
	//示例购物者
	userbase[0].id = "123456";
	userbase[0].key = "123456";
	userbase[0].identity = "shopper";
	//示例老板
	userbase[1].id = "654321";
	userbase[1].key = "654321";
	userbase[1].identity = "boss";
}
void add_user_base() {//单次添加用户到用户库
	cout << endl << "请输入你添加的身份：boss或者shopper" << endl;
	string identity;
	cin >> identity;
	if (identity == "boss" || identity == "shopper") {
		cout << endl << "请输入你的账号" << endl;
		string id;
		cin >> id;
		cout << endl << "请输入你的密码" << endl;
		string key;
		cin >> key;
		for (int i = 0; i <= 20; i++) {
			if (i == 20) {
				cout << "用户库已满" << endl;
				break;
			}
			if (i < 20 && userbase[i].id == "") {
				userbase[i].id = id;
				userbase[i].key = key;
				userbase[i].identity = identity;
				cout << "创建成功" << endl;
				break;
			}
		}
	}
	else {
		cout << "创建身份输入错误" << endl;
	}
}
void buy_goods(string id) {
	int n = 0;//n作为动态数组的单次操作索引
	goods* buycar = new goods[10];
starbuy:
	show_goods();
	cout << "请输入你想购买商品的标号,你还可以进行" << 10 - n << "次挑选购买" << endl;
	int good_id;
	cin >> good_id;
	cout << "请输入你想购买商品的数量" << endl;
	int num;
	cin >> num;
	buycar[n].id = good_id;
	for (int i = 0; i < 20; i++) {
		if (good_id == goodsbase[i].id) {
			if (num > goodsbase[i].num) {
				cout << "商品数量不足" << endl;
				break;
			}
			buycar[n].name = goodsbase[i].name;
			buycar[n].num = num;
			buycar[n].price = goodsbase[i].price;
			buycar[n].trueprice = goodsbase[i].trueprice;
			goodsbase[i].num -= num;//商品数量被消耗
			for (int j = 0; j < 100; j++) {
				if (recordsbase[j].name == "") {
					recordsbase[j].money = goodsbase[i].price * num;
					recordsbase[j].name = goodsbase[i].name;
					recordsbase[j].num = (-num);
					recordsbase[j].id = id;
					auto now = chrono::system_clock::now();
					time_t now_c = chrono::system_clock::to_time_t(now);
					char timeStr[26];
					ctime_s(timeStr, sizeof(timeStr), &now_c);
					recordsbase[j].time = timeStr;
					break;
				}

			}
			break;
		}
	}
	cout << "是否继续购买？继续购买输入“1”，结束购买输入“0”" << endl;
	int k;
	cin >> k;
	switch (k) {
	case 0: {
		cout << "以下是你总的购买的商品：" << endl;
		cout << "****************************************************************" << endl;
		cout << endl;
		cout << setw(23) << internal << "商品标号" << "  " << "商品名" << "    " << "价格" << "  " << "购买数量" << endl;
		double all_buy_money = 0;
		for (int i = 0; i < 10; i++) {
			if (buycar[i].name != "") {
				cout << setw(23) << internal << buycar[i].id << "  " << buycar[i].name << "  " << fixed << setprecision(2) << buycar[i].price * 1.0 << "  " << buycar[i].num << endl;
				money += buycar[i].price * buycar[i].num;
				all_buy_money += buycar[i].price * buycar[i].num;
			}
		}
		cout << endl;
		cout << "总计：" << all_buy_money << "元" << endl;
		cout << "****************************************************************" << endl;
		delete[] buycar; // 释放内存
		break;
	}
	case 1: {
		n++;
		goto starbuy;

	}
	}

}
void show_recordsbase() {
	cout << "****************************************************************" << endl;
	cout << endl;
	cout << setw(23) << internal << "交易账号" << "  " << "商品名" << "  " << "交易数量" << "  " << "交易金额" << "  " << "交易时间" << endl;
	for (int i = 0; i < 20; i++) {
		if (recordsbase[i].name != "") {
			cout << setw(23) << internal << recordsbase[i].id << "  " << recordsbase[i].name << "  " << recordsbase[i].num;
			cout << "  " << recordsbase[i].money << "  " << recordsbase[i].time << endl;
		}
	}
	cout << endl;
	cout << "****************************************************************" << endl;
}
void login() {
	cout << "请输入您的账号" << endl;
	string id;
	cin >> id;
	cout << "请输入密码" << endl;
	string key;
	cin >> key;
	for (int i = 0; i < 20; i++) {
		if (userbase[i].id == id && userbase[i].key == key) {
			if (userbase[i].identity == "boss") {
				cout << endl << "输入0退出" << endl;
				cout << "输入1查询商店余额" << endl;
				cout << "输入2查询商店流水账目" << endl;
				cout << "输入3查询商店陈列货物" << endl;
				cout << "输入4为商店进货" << endl;
				int k;
				cin >> k;
				switch (k)
				{
				case 0: {
					break;
				}
				case 1: {
					cout << "目前商店总余额为：" << money << endl;
					break;
				}
				case 2: {

					show_recordsbase();
					break;
				}
				case 3: {
					show_goods();
					break;
				}
				case 4: {
					add_goods(id);
					break;
				}
				}
			}
			if (userbase[i].identity == "shopper") {
				cout << "欢迎光临秃头商店?" << endl;
				cout << endl << "输入0退出" << endl;
				cout << "输入1购物" << endl;
				int k;
				cin >> k;
				switch (k) {
				case 0: {
					break;
				}
				case 1: {
					buy_goods(id);
					break;
				}
				}
			}
		}

	}
	return;
}
