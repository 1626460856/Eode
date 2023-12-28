#include"main.h"
#include<iostream>
using namespace std;
#include<iomanip>
#include <string>
#include <ctime>
#include <chrono>//����������Լ�¼����ʱ��

struct shoppingcar {
	int id;
	string name;
	double price;
	int num;
	struct shoppingcar* next;
};
struct goods {
	int id;
	string name;
	double price;
	double trueprice;//�Ұ����������Ϊ�˽����۸�Ϊ�������˵���׼��
	int num;
	struct goods* next;
};
goods goodsbase[20];//����ȫ����Ʒ�ֿ⣬����Ϊ20��
struct user {
	string id;//�˺�
	string key;//����
	string identity;//���
};
user userbase[20];//�����û��⣬����Ϊ20��
struct records {
	string id;//�����˺�
	string name;//������Ʒ
	int num;//��������
	string time;
	double money;//���̵��Ӱ����
};
records recordsbase[100];//����������¼�⣬����Ϊ100��
double money;//�����̵���ܽ���
void first_show_goods();
void show_goods();
void add_goods(string id);
void buy_goods(string id);
void first_user_base();
void add_user_base();
void show_recordsbase();
void login();

void main() {
	first_user_base();
	first_show_goods();
	for (;;) {
		int x;
		cout << "��¼����1,�˳�����0,�����˺�����2,����3�ر��̵�ƽ̨" << endl;
		cin >> x;
		switch (x)
		{
		case 0: {
			break;
		}
		case 1: {
			login();
			break;
		}
		case 2: {
			add_user_base();
			break;
		}
		case 3: {
			return;
		}


		}

	}
	system("pause");
}

void first_show_goods() {//��Ʒ����,���ҽ���Ʒ�ֿ��ʼ��

	struct goods goods1, goods2, goods3, goods4, goods5, goods6, * head, * p;
	goods1.id = 101; goods1.name = "��������"; goods1.price = 2.00; goods1.num = 100;
	goods2.id = 102; goods2.name = "����ţ��"; goods2.price = 5.00; goods2.num = 210;
	goods3.id = 103; goods3.name = "��������"; goods3.price = 3.00; goods3.num = 110;
	goods4.id = 104; goods4.name = "������Ƭ"; goods4.price = 6.00; goods4.num = 120;
	goods5.id = 105; goods5.name = "�����  "; goods5.price = 3.50; goods5.num = 130;
	goods6.id = 107; goods6.name = "ϴ��Һ  "; goods6.price = 23.00; goods6.num = 150;
	cout << "****************************************************************" << endl;
	cout << endl;
	cout << setw(23) << internal << "��Ʒ���" << "  " << "��Ʒ��" << "    " << "�۸�" << "  " << "ʣ����" << endl;
	//���������г���Ʒ�� 
	head = &goods1;
	goods1.next = &goods2;
	goods2.next = &goods3;
	goods3.next = &goods4;
	goods4.next = &goods5;
	goods5.next = &goods6;
	goods6.next = NULL;
	p = head;//�Ҿ���������һ�����ޣ�ÿ�ζ��ǰ�������Ʒ��ȫ����Ϣ����ˣ�������Ȼ������û��Ҫչʾ�����ģ����Ժ����ҵ���д��һ��չʾ����
	int i = 0;//�����ֲ�������Ϊһ������
	while (p != NULL)
	{   //��������Ʒ����Ϣ������Ʒ�ֿ⣬��ʼ���ֿ�
		goodsbase[i].id = p->id;
		goodsbase[i].name = p->name;
		goodsbase[i].price = p->price;
		goodsbase[i].trueprice = p->price * 0.8;//��ʼ��һ������������Ϊ���۵�0.8
		goodsbase[i].num = p->num;
		//���������Ʒ�ṹ��
		cout << setw(23) << internal << p->id << "  " << p->name << "  " << fixed << setprecision(2) << p->price * 1.0 << "  " << p->num << endl;
		//������һ��
		p = p->next;
		//�ֲ�����iҲ��1
		i++;
	}
	cout << endl;
	cout << "****************************************************************" << endl;
}
void show_goods() {//���γ�����Ʒ�ֿ�
	cout << "****************************************************************" << endl;
	cout << endl;
	cout << setw(23) << internal << "��Ʒ���" << "  " << "��Ʒ��" << "    " << "�۸�" << "  " << "ʣ����" << endl;
	for (int i = 0; i < 20; i++) {
		if (goodsbase[i].name != "") {
			cout << setw(23) << internal << goodsbase[i].id << "  " << goodsbase[i].name << "  " << fixed << setprecision(2) << goodsbase[i].price * 1.0 << "  " << goodsbase[i].num << endl;
		}
	}
	cout << endl;
	cout << "****************************************************************" << endl;
}
void add_goods(string id) {//���ν���
	cout << endl << "��������Ʒ����" << endl;
	string name;
	cin >> name;
	cout << endl << "��������Ʒ����" << endl;
	double price;
	cin >> price;
	cout << endl << "��������Ʒ���۵���" << endl;
	double trueprice;
	cin >> trueprice;
	cout << endl << "��������Ʒ����" << endl;
	int num;
	cin >> num;
	for (int i = 0; i <= 20; i++) {
		if (i == 20) {
			cout << "��Ʒ�ֿ�����" << endl;
			break;
		}
		if (i < 20 && goodsbase[i].name == "") {
			goodsbase[i].id = goodsbase[i - 1].id + 1;
			goodsbase[i].name = name;
			goodsbase[i].price = price;
			goodsbase[i].trueprice = trueprice;
			goodsbase[i].num = num;
			money -= trueprice * num;//�ܽ��֧��
			cout << "�����ɹ���֧����" << trueprice * num << endl;
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
			money -= trueprice * num;//�ܽ��֧��
			cout << "�����ɹ���֧����" << trueprice * num << endl;
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
void first_user_base() {//���û����ʼ��
	//ʾ��������
	userbase[0].id = "123456";
	userbase[0].key = "123456";
	userbase[0].identity = "shopper";
	//ʾ���ϰ�
	userbase[1].id = "654321";
	userbase[1].key = "654321";
	userbase[1].identity = "boss";
}
void add_user_base() {//��������û����û���
	cout << endl << "����������ӵ���ݣ�boss����shopper" << endl;
	string identity;
	cin >> identity;
	if (identity == "boss" || identity == "shopper") {
		cout << endl << "����������˺�" << endl;
		string id;
		cin >> id;
		cout << endl << "�������������" << endl;
		string key;
		cin >> key;
		for (int i = 0; i <= 20; i++) {
			if (i == 20) {
				cout << "�û�������" << endl;
				break;
			}
			if (i < 20 && userbase[i].id == "") {
				userbase[i].id = id;
				userbase[i].key = key;
				userbase[i].identity = identity;
				cout << "�����ɹ�" << endl;
				break;
			}
		}
	}
	else {
		cout << "��������������" << endl;
	}
}
void buy_goods(string id) {
	int n = 0;//n��Ϊ��̬����ĵ��β�������
	goods* buycar = new goods[10];
starbuy:
	show_goods();
	cout << "���������빺����Ʒ�ı��,�㻹���Խ���" << 10 - n << "����ѡ����" << endl;
	int good_id;
	cin >> good_id;
	cout << "���������빺����Ʒ������" << endl;
	int num;
	cin >> num;
	buycar[n].id = good_id;
	for (int i = 0; i < 20; i++) {
		if (good_id == goodsbase[i].id) {
			if (num > goodsbase[i].num) {
				cout << "��Ʒ��������" << endl;
				break;
			}
			buycar[n].name = goodsbase[i].name;
			buycar[n].num = num;
			buycar[n].price = goodsbase[i].price;
			buycar[n].trueprice = goodsbase[i].trueprice;
			goodsbase[i].num -= num;//��Ʒ����������
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
	cout << "�Ƿ�������򣿼����������롰1���������������롰0��" << endl;
	int k;
	cin >> k;
	switch (k) {
	case 0: {
		cout << "���������ܵĹ������Ʒ��" << endl;
		cout << "****************************************************************" << endl;
		cout << endl;
		cout << setw(23) << internal << "��Ʒ���" << "  " << "��Ʒ��" << "    " << "�۸�" << "  " << "��������" << endl;
		double all_buy_money = 0;
		for (int i = 0; i < 10; i++) {
			if (buycar[i].name != "") {
				cout << setw(23) << internal << buycar[i].id << "  " << buycar[i].name << "  " << fixed << setprecision(2) << buycar[i].price * 1.0 << "  " << buycar[i].num << endl;
				money += buycar[i].price * buycar[i].num;
				all_buy_money += buycar[i].price * buycar[i].num;
			}
		}
		cout << endl;
		cout << "�ܼƣ�" << all_buy_money << "Ԫ" << endl;
		cout << "****************************************************************" << endl;
		delete[] buycar; // �ͷ��ڴ�
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
	cout << setw(23) << internal << "�����˺�" << "  " << "��Ʒ��" << "  " << "��������" << "  " << "���׽��" << "  " << "����ʱ��" << endl;
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
	cout << "�����������˺�" << endl;
	string id;
	cin >> id;
	cout << "����������" << endl;
	string key;
	cin >> key;
	for (int i = 0; i < 20; i++) {
		if (userbase[i].id == id && userbase[i].key == key) {
			if (userbase[i].identity == "boss") {
				cout << endl << "����0�˳�" << endl;
				cout << "����1��ѯ�̵����" << endl;
				cout << "����2��ѯ�̵���ˮ��Ŀ" << endl;
				cout << "����3��ѯ�̵���л���" << endl;
				cout << "����4Ϊ�̵����" << endl;
				int k;
				cin >> k;
				switch (k)
				{
				case 0: {
					break;
				}
				case 1: {
					cout << "Ŀǰ�̵������Ϊ��" << money << endl;
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
				cout << "��ӭ����ͺͷ�̵�?" << endl;
				cout << endl << "����0�˳�" << endl;
				cout << "����1����" << endl;
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