// 设计围棋.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <random>//随机数的头文件
using namespace std;

struct twoint  //为数组设计两个参数，第一个表示数值，用来表示黑白棋，第二个参数表示是否被扫描过
{
	int first;
	int second;
};
void luozi(twoint a[19][19], twoint b[19][19]){
	int n, m;
	// 使用随机设备生成种子
	std::random_device rd;

	// 使用 Mersenne Twister 引擎生成随机数，这里的mt1937是默认引擎
	std::mt19937 gen(rd());

	// 创建一个分布对象，指定生成int随机数的范围
	std::uniform_int_distribution<int> dis(0, 18);  // 生成0到18之间的随机整数
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
	int ok_number2 = 0;//切片中非边符合条件的棋子数
	int ok_number1 = 0;//挂边符合数
	int all_number = 0;//切片中总的棋子数
	int jilu = 0;
	for (int m = 0; m < 19; m++){
		for (int n = 0; n < 19; n++){
			if ((*c)[m][n] == 1){
				
				//接下来考虑挂边情况
				if (m == 0 || m == 18 || n == 0 || n == 18){
					all_number += 1;
					jilu += 1;
					if ((m == 0 && n == 0) || (m == 0 && n == 18) || (m == 18 && n == 0) || (m == 18 && n == 18)){//考虑4个边角情况
						jilu += 1;
					}

					if (n + 1 <= 18){
						if (((*c)[m][n + 1] == 1 || (*b)[m][n + 1].first == 1)){
							jilu += 1;//并联或者与对方并联+1
						}
					}
					if (n - 1 >= 0){
						if (((*c)[m][n - 1] == 1 || (*b)[m][n - 1].first == 1)){
							jilu += 1;//并联或者与对方并联+1
						}
					}
					if (m + 1 <= 18){
						if (((*c)[m + 1][n] == 1 || (*b)[m + 1][n].first == 1)){
							jilu += 1;//并联或者与对方并联+1
						}
					}
					if (m - 1 >= 0){
						if (((*c)[m - 1][n] == 1 || (*b)[m - 1][n].first == 1)){
							jilu += 1;//并联或者与对方并联+1
						}
					}
					ok_number1 += (jilu / 4);
					jilu = 0;
				}
				//挂边情况到此为止
				//下面考虑不挂边情况
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
				//不挂边情况到此为止	

			}//判断单个数据到此为止
		}
	}//遍历数据到此为止
	std::cout << endl << "ok_number1:" << ok_number1 << "ok_number2:" << ok_number2 << "all:" << all_number << endl;
	if ((ok_number1 + ok_number2) == all_number){
		for (int m = 0; m < 19; m++){
			for (int n = 0; n < 19; n++){
				if ((*c)[m][n] == 1){
					(*a)[m][n].first = 0;//直接修改
				}

			}
		}
	}

}
void  chizi(twoint(*a)[19][19], twoint(*b)[19][19]){
	int c[19][19];//临时切片
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
	cout << "这个程序会自动模拟围棋对弈，请输入你想成的围棋对弈的回合数" << endl;
	int k;
	cin >> k ;
	//初始化数组a
	twoint a[19][19];//黑棋盘
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			a[i][j].first = 0;
			a[i][j].second = 0;
		}
	}
	//初始化数组b
	twoint b[19][19];//白棋盘
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			b[i][j].first = 0;
			b[i][j].second = 0;
		}
	}
	//初始化数组show
	int show[19][19];//总棋盘
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			show[i][j] = 0;
		}
	}
	for (int i = 0; i < k; i++){//控制下的回合数k
		luozi(a, b);
		std::cout << "黑棋落子：" << endl;
		for (int m = 0; m < 19; m++){
			std::cout << endl;
			for (int n = 0; n < 19; n++){
				std::cout << a[m][n].first << " ";
			}
		}
		std::cout << endl;
		chizi(&b,&a);
		std::cout << "当前棋盘形式：" << endl;
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
		std::cout << "白棋落子：" << endl;
		for (int m = 0; m < 19; m++){
			std::cout << endl;
			for (int n = 0; n < 19; n++){
				std::cout << b[m][n].first << " ";
			}
		}
		std::cout << endl;
		chizi(&a, &b);
		std::cout << "当前棋盘形式：" << endl;
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
