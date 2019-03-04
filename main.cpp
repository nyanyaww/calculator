#include "tree.h"

#define MENU_INFO "1.输入表达式\n2.输出中缀表达式\n3.输出后缀表达式\n4.计算后缀表达式\n5.输出树形结构\n\
按q退出\n"

void menu()
{
    char cmd = 0;
    cout << MENU_INFO << endl;
    scanf("%c", &cmd);
    string infix_expression = "";
    string postfix_expression = "";
    while (cmd != 'q')
    {
        switch (cmd)
        {
        case '1':
            cout << "输入表达式" << endl;
            cin >> infix_expression;
            break;
        case '2':
            cout << "中缀表达式" << endl;
            cout << foo(infix_expression) << endl;
            break;
        case '3':
            cout << "后缀表达式" << endl;
            postfix_expression = output_postfix(infix_expression);
            cout << postfix_expression << endl;
            break;
        case '4':
            cout << "计算" << endl;
            cout << getAnswer(postfix_expression) << endl;
            break;
        case '5':
            cout << "输出树型结构" << endl;
            print_tree(infix_expression);
            break;
        default:
            break;
        }
        scanf("%c", &cmd);
    }
}

int main(void)
{
    // menu();
    string infix_str = "1+(2*3)+4+5+6+7";
    cout << "原表达式" << infix_str << endl;
    cout << "网上算法";
    cout<<return_(infix_str);
    cout << endl;
    shabi(infix_str);

    return 0;
}
