#include "tree.h"

string str = ""; // 保存后缀表达式的字符串

// 判断当前字符是否为数字
bool isNumber(char s)
{
	string opers = "1234567890.";
	for (int i = 0; i < opers.length(); i++)
	{
		if (s == opers.at(i))
		{
			return true;
		}
	}
	return false;
}

// 判断当前字符是否为操作符
bool isOperator(char s)
{
	string opers = "+-*/";
	for (int i = 0; i < opers.length(); i++)
	{
		if (s == opers.at(i))
		{
			return true;
		}
	}
	return false;
}

int my_pow(int e, int n)
{
	int i = 0;
	int Result = 1;
	for (i = 0; i < n; i++)
	{
		Result = Result * e;
	}
	return Result;
}

float caculator(float number1, float number2, char oper)
{
	float result = 0.0;
	switch (oper)
	{
	case '+':
		result = number1 + number2;
		break;
	case '-':
		result = number1 - number2;
		break;
	case '*':
		result = number1 * number2;
		break;
	case '/':
		result = number1 / number2;
		break;
	default:
		break;
	}
	return result;
}

float string_to_float(string &str)
{
	return atof(str.c_str());
}

// 计算后缀表达式的值
float getAnswer(string post_fix)
{
	int i = 0;
	// 一个字符一个字符地读取后缀表达式
	char temp = 0;
	// 先把读到的字符转化成字符串
	string temp_number_string = "";
	// 字符串转化成的浮点型数据
	float temp_number_float = 0.0;
	// 建立计算栈，遇到数字入栈，当有操作符就弹出最顶部的2个数字，然后计算，并将结果入栈
	stack<float> caculator_;
	for (i = 0; i < post_fix.length(); i++)
	{
		temp = post_fix.at(i);
		if (isNumber(temp))
		{
			// 把得到的数字或者小数点加在字符后面
			temp_number_string += temp;
		}
		else if (temp == ' ')
		{
			if (temp_number_string != "")
			{
				temp_number_float = string_to_float(temp_number_string);
				caculator_.push(temp_number_float);
				// cout << temp_number_float << endl;
			}
			// 将字符串清空
			temp_number_string.clear();
		}
		else
		{
			// 注意,第二位数字先弹出
			float secondVal = caculator_.top();
			caculator_.pop();
			float firstVal = caculator_.top();
			caculator_.pop();
			caculator_.push(caculator(firstVal, secondVal, temp));
			// cout << temp << endl;
		}
	}
	// 最后最顶部的数字自然就是我们需要的计算值
	return caculator_.top();
}

/***************
判断操作符的优先级
****************/
int judge_priority(char opr)
{
	if (opr == '+' || opr == '-')
		return 1;
	if (opr == '*' || opr == '/')
		return 2;
	return -1;
}

int judge_priorityII(string opr)
{
	if (opr == "+" || opr == "-")
		return 1;
	if (opr == "*" || opr == "/")
		return 2;
	return -1;
}

/***************
中缀表达式转成树
****************/
void infix_to_tree(string infix, Tree *&T)
{
	int i, id = -1;
	int len = infix.length();
	int bracket_priority = 0;
	int operator_priority = -1;
	int mi = MAX;
	for (i = 0; i < len; i++)
	{
		//记录最后计算的那个运算符位置
		if (infix[i] == '(')
		{
			bracket_priority += STEP;
		}
		else if (infix[i] == ')')
		{
			bracket_priority -= STEP;
		}
		else if (judge_priority(infix[i] == 1) && (i == 0 || infix[i - 1] == '('))
		{
			//正负号不是运算符
			continue;
		}
		else if ((operator_priority = judge_priority(infix[i])) > 0)
		{
			if (operator_priority + bracket_priority <= mi)
			{
				mi = operator_priority + bracket_priority;
				id = i;
			}
		}
	}
	T = new Tree; //创建子树
	if (id == -1)
	{
		//去除左右括号
		//定义左右括号的下标
		int left_bracket_sub, right_bracket_sub;
		for (left_bracket_sub = 0; left_bracket_sub < len && infix[left_bracket_sub] == '('; left_bracket_sub++)
			;
		for (right_bracket_sub = len - 1; right_bracket_sub >= 0 && infix[right_bracket_sub] == ')'; right_bracket_sub--)
			;
		T->expression = infix.substr(left_bracket_sub, right_bracket_sub - left_bracket_sub + 1);
		return;
	}
	T->expression = infix[id];
	infix_to_tree(infix.substr(0, id), T->left_child);				   //递归出左子树
	infix_to_tree(infix.substr(id + 1, len - id - 1), T->right_child); //递归出右子树
}

void Post(Tree *T)
{
	// 后序遍历输出树 即后缀表达式
	if (!T)
		return;
	Post(T->left_child);
	Post(T->right_child);
	if (T->expression[0] == '+' && T->expression.length() > 1)
	{
		//去除正号
		//判断条件还可以为T->s[0]=='+'&&T->left==NULL&&T->right==NULL
		str = str + T->expression.substr(1, T->expression.length() - 1) + " ";
		return;
	}
	str = str + T->expression + " ";
}

void Inorder(Tree *T)
{
	// 后序遍历输出树 即后缀表达式
	if (!T)
		return;
	Inorder(T->left_child);
	if (T->expression[0] == '+' && T->expression.length() > 1)
	{
		//去除正号
		//判断条件还可以为T->s[0]=='+'&&T->left==NULL&&T->right==NULL
		str = str + T->expression.substr(1, T->expression.length() - 1) + " ";
		return;
	}
	str = str + T->expression + " ";
	Inorder(T->right_child);
}

void InorderII(Tree *root, int deep)
{
	if (root == NULL)
		return;
	else if (!root->left_child && !root->right_child)
	{
		cout << root->expression;
		str += root->expression;
	}
	else
	{
		if (deep > 1)
		{
			if (judge_priorityII(root->expression) > judge_priorityII(root->right_child->expression) ||
				judge_priorityII(root->expression) > judge_priorityII(root->left_child->expression))
			{
				cout << "(";
				str += "(";
			}
		}
		InorderII(root->left_child, deep + 1);
		cout << root->expression;
		InorderII(root->right_child, deep + 1);
		if (deep > 1)
		{
			if (judge_priorityII(root->expression) > judge_priorityII(root->right_child->expression) ||
				judge_priorityII(root->expression) > judge_priorityII(root->left_child->expression))
			{
				cout << ")";
				str += ")";
			}
		}
	}
}

void inOrderIII(Tree *p) //中序遍历
{
	if (p)
	{
		if (p->left_child)
		{
			if (judge_priorityII(p->left_child->expression) < judge_priorityII(p->expression))
			{
				cout << "(";
				inOrderIII(p->left_child);
				// cout << ")";
			}
			else
			{
				inOrderIII(p->left_child);
			}
		}
		cout << p->expression;
		if (p->right_child)
		{
			if (judge_priorityII(p->right_child->expression) <= judge_priorityII(p->expression))
			{
				// cout << "(";
				inOrderIII(p->right_child);
				cout << ")";
			}
			else
			{
				inOrderIII(p->right_child);
			}
		}
	}
}

void add_bracket()
{
	int len = str.length();
	int pos[20];
	int i = 0, j = 0, k = 0;
	int count = 0;
	for (i = 0; i < len; i++)
	{
		if (!isNumber(str[i]) && str[i] != ' ')
		{
			pos[j] = i;
			j++;
		}
	}
	for (i = 0; i < j - 1; i++)
	{
		if (judge_priority(str[pos[i + 1]]) > judge_priority(str[pos[i]]))
		{
			str[pos[i + 1] - 1] = ')';
			for (k = pos[i + 1] - 1; k >= 0; k--)
			{
				// cout << k << endl;
				if (str[k] == ' ')
				{
					count += 1;
					// str[k] = '(';
					if (count == 3)
					{
						str[k] = '(';
						count = 0;
						break;
					}
					// cout << "空格" << k<<endl;
				}
			}
		}
	}
}
int hasExcess(string s, int leftBracket, int rightBracket)
{
    int i, leftAcount;

    //判断"-(a+b)"类型
    if (s[leftBracket - 1] == '-')
    {

        i = leftBracket;
        leftAcount = 1;
        while (++i < rightBracket)
        {
            if (s[i] == '(')
                leftAcount++;
            if (s[i] == '+' && leftAcount == 1)
                return 0;
        }
    }
    if (s[leftBracket - 1] == '/')
        return 0;
    //判断"加或减(a 任意 b)加或减"类型
    if (s[leftBracket - 1] != '*' && s[leftBracket - 1] != '/' && s[rightBracket + 1] != '*' && s[rightBracket + 1] != '/')
        return 1;

    //判断"*(a*b)乘或除以"类型
    i = leftBracket;
    leftAcount = 1;
    while (++i < rightBracket)
    {
        if (s[i] == '(')
            leftAcount++;
        if (s[i] == '*' && leftAcount == 1)
            return 1;
    }

    return 0;
}

int delExcessBracket(string s, int index)
{
    int leftBracket, rightBracket;
    int len = s.length();
    while (index != len)
    {

        if (s[index] == ')')
            return index;
        if (s[index] == '(')
        {

            leftBracket = index;
            index = rightBracket = delExcessBracket(s, index + 1);

            if (hasExcess(s, leftBracket, rightBracket))
                s[leftBracket] = s[rightBracket] = ' ';
        }
        index++;
    }
}

string return_(string infix)
{
    delExcessBracket(infix, 0);
    return infix;
}

int Depth_tree(Tree *t)
{
	int depthval, depthleft, depthright;
	if (t == NULL)
		depthval = 0;
	else
	{
		depthleft = Depth_tree(t->left_child);
		depthright = Depth_tree(t->right_child);
		depthval = 1 + (depthleft > depthright ? depthleft : depthright);
	}
	return depthval;
}

void Print_tree(Tree *p)
{
	int height = Depth_tree(p);
	int h = 0;
	int i;
	queue<Tree *> aQueue;
	Tree *pointer = p;
	Tree *lastpointer;
	if (pointer)
	{
		pointer->s = 1;
		pointer->t = 1;
		aQueue.push(pointer);
	}
	while (!aQueue.empty())
	{
		lastpointer = pointer;
		pointer = aQueue.front();
		aQueue.pop();
		if (pointer->s > h)
		{
			cout << endl;
			h = pointer->s;
		}
		if (pointer->t == 1)
		{
			for (i = 0; i < my_pow(2, height - pointer->s) - 1; i++)
				cout << " ";
		}
		else if (lastpointer->s != pointer->s)
		{
			for (i = 0; i < (pointer->t - 1) * (my_pow(2, height - pointer->s + 1) - 1) + (pointer->t - 1) - 1 + my_pow(2, height - pointer->s); i++)
				cout << " ";
		}
		else
		{
			for (i = 0; i < (pointer->t - lastpointer->t) * (my_pow(2, height - pointer->s + 1) - 1) + (pointer->t - lastpointer->t) - 1; i++)
				cout << " ";
		}
		cout << pointer->expression;
		if (pointer->left_child != NULL)
		{
			pointer->left_child->s = pointer->s + 1;
			pointer->left_child->t = pointer->t * 2 - 1;
			aQueue.push(pointer->left_child);
		}
		if (pointer->right_child != NULL)
		{
			pointer->right_child->s = pointer->s + 1;
			pointer->right_child->t = pointer->t * 2;
			aQueue.push(pointer->right_child);
		}
	}
}

void print_tree(string infix)
{
	str.clear(); //每次运行前均初始化一次
	Tree *T = NULL;
	infix_to_tree(infix, T);
	Print_tree(T);
	cout << "\n\n\n";
}

string output_postfix(string infix)
{
	str.clear(); //每次运行前均初始化一次
	Tree *T = NULL;
	infix_to_tree(infix, T);
	Post(T);
	int len = str.length();
	str.erase(len - 1, 1); //去除末尾空格
	return str;
}

string foo(string infix)
{
	str.clear(); //每次运行前均初始化一次
	str += " ";
	Tree *T = NULL;
	infix_to_tree(infix, T);
	Inorder(T);
	// add_bracket();
	int len = str.length();
	str.erase(len - 1, 1); //去除末尾空格
	return str;
}

string bar(string infix)
{
	// str.clear(); //每次运行前均初始化一次
	// str += " ";
	// Tree *T = NULL;
	// // infix_to_tree(infix, T);
	// // cout << T->expression << endl;
	// // cout << T->left_child->expression << endl;
	// // cout << T->right_child->expression << endl;
	// // string test = T->expression;
	// // string testII = T->left_child->expression;
	// // cout << judge_priorityII(test) > ;
	// InorderII(T, Depth_tree(T));
	// add_bracket();
	// int len = str.length();
	// str.erase(len - 1, 1); //去除末尾空格
	// return str;

	delExcessBracket(infix, 0);
	cout << infix << endl;
}

void shabi(string infix)
{
	str.clear(); //每次运行前均初始化一次
	str += " ";
	Tree *T = NULL;
	infix_to_tree(infix, T);
	inOrderIII(T);
}