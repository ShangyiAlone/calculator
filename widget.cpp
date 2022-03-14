#include <widget.h>
#include <ui_widget.h>
#include <QString>
#include <string>
#include <string.h>
#include <QDebug>
#include <stack>
#include <vector>
#include <QtWidgets>
#include <QStack>
#include <QString>
#include <iostream>
using namespace std;
string expression;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    setWindowTitle("没啥用的计算器");//重命名窗口
    setFixedSize(681,346);//固定窗口大小
}

void Widget::showInfo(QString &s)
{
    ui->lineEdit_2->insert(s);
}

//计算过程
void processAnOperator(
    stack<int>& operandStack,stack<char>& operatorStack)
{
    char op = operatorStack.top();
    operatorStack.pop();

    int op1 = operandStack.top();
    operandStack.pop();

    int op2 = operandStack.top();
    operandStack.pop();

    if(op == '+')
        operandStack.push(op2 + op1);
    else if(op == '-')
        operandStack.push(op2 - op1);
    else if(op == '*')
        operandStack.push(op2 * op1);
    else if(op == '/')
        operandStack.push(op2 / op1);
    else if(op == '&')
        operandStack.push(op2 && op1);
    else if(op == '|')
        operandStack.push(op2 || op1);
}

//读取字符串，放到列表中
vector<string> split(const string& expression)
{

    vector<string> v;
    string numberString;

    for(unsigned i=0;i < expression.length();i++)
    {

        if(isdigit(expression[i]))
            numberString.append(1,expression[i]);
        else
        {
            if(numberString.size() > 0)
            {
                v.push_back(numberString);
                numberString.erase();
            }

            if(!isspace(expression[i]))
            {
                string s;
                s.append(1,expression[i]);
                v.push_back(s);
            }
         }
    }

    if(numberString.size() > 0)
        v.push_back(numberString);

    return v;
}

//具体计算
int evaluateExpression(const string& expression)
{
    //创建数据栈
    stack<int> operandStack;

    //创建计算符号栈
    stack<char>operatorStack;

    //读取输入的字符
    vector<string> tokens = split(expression);

    //开始遍历字符
    for(unsigned i = 0;i < tokens.size();i++)
    {
        //如果遍历到！，则计算！
        if(tokens[i][0]=='!')
        {
            //如果！之后是0，则在数字栈中加入1，否则加入0
            if(tokens[i+1][0]=='0')
            {
            operandStack.push(1);
            }
            else {
            operandStack.push(0);
            }
            i+=1;
            //如果此时运算符栈不为空，则根据运算符栈中的符号进行运算
            while(!operatorStack.empty() && (operatorStack.top() == '+'||operatorStack.top()
            == '-'|| operatorStack.top()=='*'||operatorStack.top() == '/'
            ||operatorStack.top() == '&'||operatorStack.top() == '|'))
             {
                    processAnOperator(operandStack,operatorStack);
             }
          }

        //如果遍历到+，-，则计算+，-。注意我们这里考虑运算符的优先级，所以在while中要判断+，-，*，/
        else if(tokens[i][0]== '+' || tokens[i][0] == '-')
        {
            while(!operatorStack.empty() && (operatorStack.top() == '+'||operatorStack.top()
            == '-'|| operatorStack.top()=='*'||operatorStack.top() == '/'
            ||operatorStack.top() == '&'||operatorStack.top() == '|'))
            {
                processAnOperator(operandStack,operatorStack);
            }

            operatorStack.push(tokens[i][0]);
        }

        //如果遍历到*，/，则计算*，/。注意我们这里考虑运算符的优先级，所以在while中只判断*，/
        else if(tokens[i][0] =='*'|| tokens[i][0] == '/')
        {
            while(!operatorStack.empty() && (operatorStack.top() == '*'
            ||operatorStack.top() =='/'||operatorStack.top() == '&'||operatorStack.top() == '|'))
            {
                processAnOperator(operandStack,operatorStack);
            }

            operatorStack.push(tokens[i][0]);
        }
        //进行&，|运算
        else if(tokens[i][0]== '&' || tokens[i][0] == '|' )
        {
            while(!operatorStack.empty() && (operatorStack.top() == '&'||operatorStack.top() == '|'))
            {
                processAnOperator(operandStack,operatorStack);
            }

            operatorStack.push(tokens[i][0]);
        }

        //如果读到（,把他压进运算符栈即可
        else if(tokens[i][0] == '(')
        {
            operatorStack.push('(');
        }

        //如果读到），就一直算，知道运算符栈中读到（
        else if(tokens[i][0] == ')')
        {
            while(operatorStack.top() != '(')
            {
                processAnOperator(operandStack,operatorStack);
            }

            operatorStack.pop();
        }
        //atio（）将字符串转化为整形，c_str()指针指向一个字符串数组
        //读入数字
        else
        {
            operandStack.push(atoi(tokens[i].c_str()));
        }
    }
    //运算符栈最后不为空，说明还需进行一次运算
    while(!operatorStack.empty())
    {
        processAnOperator(operandStack,operatorStack);
    }

    //返回最终答案，在下面20号按钮有调用
    int g;
    g=operandStack.top();
    operandStack.pop();
    return g;
}



Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_7_clicked()
{
    ui->lineEdit->insert("1");
    Q+='1';
}

void Widget::on_pushButton_8_clicked()
{
    ui->lineEdit->insert("2");
    Q+='2';
}

void Widget::on_pushButton_9_clicked()
{
    ui->lineEdit->insert("3");
    Q+='3';
}

void Widget::on_pushButton_4_clicked()
{
    ui->lineEdit->insert("4");
    Q+='4';
}

void Widget::on_pushButton_5_clicked()
{
    ui->lineEdit->insert("5");
    Q+='5';
}

void Widget::on_pushButton_6_clicked()
{
    ui->lineEdit->insert("6");
    Q+='6';
}

void Widget::on_pushButton_clicked()
{
    ui->lineEdit->insert("7");
    Q+='7';
}

void Widget::on_pushButton_2_clicked()
{
    ui->lineEdit->insert("8");
    Q+='8';
}

void Widget::on_pushButton_3_clicked()
{
    ui->lineEdit->insert("9");
    Q+='9';
}

void Widget::on_pushButton_17_clicked()
{
    ui->lineEdit->insert("0");
    Q+='0';
}

void Widget::on_pushButton_16_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

void Widget::on_pushButton_18_clicked()
{
    ui->lineEdit->backspace();
}

void Widget::on_pushButton_14_clicked()
{
    ui->lineEdit->insert("+");
    Q+='+';
}

void Widget::on_pushButton_20_clicked()//
{

    ui->lineEdit_2->clear();
    if(Q.size() < 3)
        ui->lineEdit_2->insert("输入格式有误");
    else
        {
            expression = ui->lineEdit->text().toStdString();
            Q+='#';
            int x;
            x=evaluateExpression(expression);
            QString str=QString::number(x,10);
            ui->lineEdit_2->insert(str);
        }

}

void Widget::on_pushButton_10_clicked()//
{
    ui->lineEdit->insert("/");
    Q+='/';
}

void Widget::on_pushButton_12_clicked()
{
    ui->lineEdit->insert("(");
    Q+='(';
}

void Widget::on_pushButton_13_clicked()//
{
    ui->lineEdit->insert(")");
    Q+=')';
}

void Widget::on_pushButton_11_clicked()
{
    ui->lineEdit->insert("&");
    Q+='&';
}

void Widget::on_pushButton_22_clicked()
{
    ui->lineEdit->insert("|");
    Q+='|';
}

void Widget::on_pushButton_21_clicked()
{
    ui->lineEdit->insert("!");
    Q+='!';
}

void Widget::on_pushButton_19_clicked()//
{
    ui->lineEdit->insert("*");
    Q+='*';
}

void Widget::on_pushButton_15_clicked()//gaiguo
{
    ui->lineEdit->insert("-");
    Q+='-';
}
