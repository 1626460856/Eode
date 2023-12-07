// ���Χ��.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <random>//�������ͷ�ļ�
using namespace std;

struct twoint  //Ϊ�������������������һ����ʾ��ֵ��������ʾ�ڰ��壬�ڶ���������ʾ�Ƿ�ɨ���
{
	int first;
	int second;
};
void luozi(twoint a[19][19], twoint b[19][19]){
	int n, m;
	// ʹ������豸��������
	std::random_device rd;

	// ʹ�� Mersenne Twister ��������������������mt1937��Ĭ������
	std::mt19937 gen(rd());

	// ����һ���ֲ�����ָ������int������ķ�Χ
	std::uniform_int_distribution<int> dis(0, 18);  // ����0��18֮����������
	n = dis(gen);
	m = dis(gen);
	if (a[m][n].first == 0 && b[m][n].first == 0){
		twoint* ptr = &a[m][n];
		ptr->first = 1;
	}
}
void binlian(twoint (*a)[19][19], int i, int j, int(*c)[19][19]){
	if ((*a)[i][j].first == 1 && (*c)[i][j] == 0){
		(*c)[i][j] = 1;
		(*a)[i][j].second = 1;
		if (j <= 17 && (*a)[i][j + 1].first == 1){
			binlian(a, i, j + 1, c);
		}
		if (j >= 1 && (*a)[i][j - 1].first == 1){
			binlian(a, i, j - 1, c);
		}
		if (i <= 17 && (*a)[i + 1][j].first == 1){
			binlian(a, i + 1, j, c);
		}
		if (i >= 1 && (*a)[i - 1][j].first == 1){
			binlian(a, i - 1, j, c);
		}
	}
}
void cheqi(twoint (*a)[19][19],twoint (*b)[19][19], int(*c)[19][19] ){
	int ok_number2 = 0;//��Ƭ�зǱ߷���������������
	int ok_number1 = 0;//�ұ߷�����
	int all_number = 0;//��Ƭ���ܵ�������
	int jilu = 0;
	for (int m = 0; m < 19; m++){
		for (int n = 0; n < 19; n++){
			if ((*c)[m][n] == 1){
				
				//���������ǹұ����
				if (m == 0 || m == 18 || n == 0 || n == 18){
					all_number += 1;
					jilu += 1;
					if ((m == 0 && n == 0) || (m == 0 && n == 18) || (m == 18 && n == 0) || (m == 18 && n == 18)){//����4���߽����
						jilu += 1;
					}

					if (n + 1 <= 18){
						if (((*c)[m][n + 1] == 1 || (*b)[m][n + 1].first == 1)){
							jilu += 1;//����������Է�����+1
						}
					}
					if (n - 1 >= 0){
						if (((*c)[m][n - 1] == 1 || (*b)[m][n - 1].first == 1)){
							jilu += 1;//����������Է�����+1
						}
					}
					if (m + 1 <= 18){
						if (((*c)[m + 1][n] == 1 || (*b)[m + 1][n].first == 1)){
							jilu += 1;//����������Է�����+1
						}
					}
					if (m - 1 >= 0){
						if (((*c)[m - 1][n] == 1 || (*b)[m - 1][n].first == 1)){
							jilu += 1;//����������Է�����+1
						}
					}
					ok_number1 += (jilu / 4);
					jilu = 0;
				}
				//�ұ��������Ϊֹ
				//���濼�ǲ��ұ����
				if (m != 0 && m != 18 && n != 0 && n != 18){
					all_number += 1;
					if ((*c)[m][n] == 1){
						if ((*c)[m + 1][n] == 1 || (*b)[m + 1][n].first == 1){
							jilu += 1;
						}
						if ((*c)[m - 1][n] == 1 || (*b)[m - 1][n].first == 1){
							jilu += 1;
						}
						if ((*c)[m][n + 1] == 1 || (*b)[m][n + 1].first == 1){
							jilu += 1;
						}
						if ((*c)[m][n - 1] == 1 || (*b)[m][n - 1].first == 1){
							jilu += 1;
						}
						ok_number2 += (jilu / 4);
						jilu = 0;
					}
				}
				//���ұ��������Ϊֹ	

			}//�жϵ������ݵ���Ϊֹ
		}
	}//�������ݵ���Ϊֹ
	std::cout << endl << "ok_number1:" << ok_number1 << "ok_number2:" << ok_number2 << "all:" << all_number << endl;
	if ((ok_number1 + ok_number2) == all_number){
		for (int m = 0; m < 19; m++){
			for (int n = 0; n < 19; n++){
				if ((*c)[m][n] == 1){
					(*a)[m][n].first = 0;//ֱ���޸�
				}

			}
		}
	}

}
void  chizi(twoint(*a)[19][19], twoint(*b)[19][19]){
	int c[19][19];//��ʱ��Ƭ
	for (int i = 0; i < 19; i++){
		for (int j = 0; j < 19; j++){
			if ((*a)[i][j].first == 1&&(*a)[i][j].second==0){
				c[i][j] = 0;
				binlian(a, i, j, &c);
				cheqi(a, b, &c);
				for (int i = 0; i < 19; i++){
					for (int j = 0; j < 19; j++){
						c[i][j] = 0;
					}
				}
			}
		
		}
	}
	for (int i = 0; i < 19; i++){
		for (int j = 0; j < 19; j++){
			(*a)[i][j].second = 0;
		}
	}
}
void main(){
	cout << "���������Զ�ģ��Χ����ģ�����������ɵ�Χ����ĵĻغ���" << endl;
	int k;
	cin >> k ;
	//��ʼ������a
	twoint a[19][19];//������
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			a[i][j].first = 0;
			a[i][j].second = 0;
		}
	}
	//��ʼ������b
	twoint b[19][19];//������
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			b[i][j].first = 0;
			b[i][j].second = 0;
		}
	}
	//��ʼ������show
	int show[19][19];//������
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			show[i][j] = 0;
		}
	}
	for (int i = 0; i < k; i++){//�����µĻغ���k
		luozi(a, b);
		std::cout << "�������ӣ�" << endl;
		for (int m = 0; m < 19; m++){
			std::cout << endl;
			for (int n = 0; n < 19; n++){
				std::cout << a[m][n].first << " ";
			}
		}
		std::cout << endl;
		chizi(&b,&a);
		std::cout << "��ǰ������ʽ��" << endl;
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				if (a[i][j].first == 1){
					show[i][j] = 6;
				}
				if (b[i][j].first == 1){
					show[i][j] = 9;
				}
				if (a[i][j].first == 0 && b[i][j].first == 0){
					show[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < 19; i++) {
			std::cout << endl;
			for (int j = 0; j < 19; j++) {
				if (show[i][j] == 0){
					std::cout << "*" << " ";
				}
				if (show[i][j] == 6){
					std::cout << "X" << " ";
				}
				if (show[i][j] == 9){
					std::cout << "O" << " ";
				}
			}
		}
		std::cout << endl;
		luozi(b, a);
		std::cout << "�������ӣ�" << endl;
		for (int m = 0; m < 19; m++){
			std::cout << endl;
			for (int n = 0; n < 19; n++){
				std::cout << b[m][n].first << " ";
			}
		}
		std::cout << endl;
		chizi(&a, &b);
		std::cout << "��ǰ������ʽ��" << endl;
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				if (a[i][j].first == 1){
					show[i][j] = 6;
				}
				if (b[i][j].first == 1){
					show[i][j] = 9;
				}
				if (a[i][j].first == 0 && b[i][j].first == 0){
					show[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < 19; i++) {
			std::cout << endl;
			for (int j = 0; j < 19; j++) {
				if (show[i][j] == 0){
					std::cout << "*" << " ";
				}
				if (show[i][j] == 6){
					std::cout << "X" << " ";
				}
				if (show[i][j] == 9){
					std::cout << "O" << " ";
				}
			}
		}
		std::cout << endl;
	}
	system("pause");
}
