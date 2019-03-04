#ifndef TREEINFIX2POSTFIX_H
#define TREEINFIX2POSTFIX_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <queue>
#include <stack>
#include<stdlib.h>

using namespace std;

#define STEP 3
#define MAX 99999



/****************
定义树的数据结构
*****************/
struct Tree
{
	string expression;
	Tree *left_child, *right_child;
	int s;
	int t;
	Tree()
	{
		left_child = right_child = NULL;
		expression = "";
	}

	~Tree()
	{
		delete left_child;
		delete right_child;
	}
};

// 判断当前字符是否为数字
bool isNumber(char s);


// 判断当前字符是否为操作符
bool isOperator(char s);



int my_pow(int e, int n);


float caculator(float number1, float number2, char oper);
float string_to_float(string &str);

// 计算后缀表达式的值
float getAnswer(string post_fix);

/***************
判断操作符的优先级
****************/
int judge_priority(char opr);
int judge_priorityII(string opr);

/***************
中缀表达式转成树
****************/
void infix_to_tree(string infix, Tree *&T);

void Post(Tree *T);

void Inorder(Tree *T);
void InorderII(Tree *root, int deep);
void inOrderIII(Tree *p); //中序遍历
void add_bracket();

int hasExcess(string s, int leftBracket, int rightBracket);
int delExcessBracket(string s, int index);
string return_(string infix);

int Depth_tree(Tree *t);
void Print_tree(Tree *p);
void print_tree(string infix);
string output_postfix(string infix);
string foo(string infix);
string bar(string infix);
void shabi(string infix);
#endif //TREEINFIX2POSTFIX_H
