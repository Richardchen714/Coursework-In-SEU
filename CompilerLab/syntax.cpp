#include<stdio.h>
#include<iostream>
#include <iomanip>
#include<string>
#include<malloc.h>
using namespace std;
#define N 100

int ll1_table(int stackTop, int strTop);
char str[30];
char stack[30] = "";

struct Prod {
	char l_char;
	char r_char[15];
	char pro[20];
};

Prod productions[34];
void init();
int stackPush(int* top, Prod prod);
int matching(int* top, char* str);
int main()
{
	int len;
	int stackTop = 1;
	int strTop = 0;
	int i;
	char z[] = "#";
	int index = 0;
	init();//产生式初始化
	stack[0] = '#';
	stack[stackTop] = 'S';
	cout << "请输入语句：";
	cin >> str;


	len = strlen(str);
	str[len] = '#';
	while (stackTop >= 0)
	{
		cout << "第" << right << setw(2) << ++index << "步:  ";
		cout << right << setw(6) << "当前栈：" << left << setw(8) << stack;
		cout << left << setw(8) << "当前语句：" << right << setw(8) << str;

		if (matching(&stackTop, str)) {
			cout << endl;
		}
		else {
			i = ll1_table(stackTop, strTop);
			stackPush(&stackTop, productions[i]);//压栈
			cout << "  下一步所用产生式：" << productions[i].pro << endl;
		}
	}
	if (stackTop + 1 == 0)
	{
		cout << "语法分析成功" << endl;
	}

	return 0;
}

//LL(1)预测分析表的构造
int ll1_table(int stackTop, int strTop)
{
	if (stack[stackTop] == 'S') {
		if (str[strTop] == 'i')
		{
			return 0;
		}
		else if (str[strTop] == 'd') {
			return 1;
		}
		else if (str[strTop] == 'f') {
			return 4;
		}
		else if (str[strTop] == 'w') {
			return 5;
		}
		else if (str[strTop] == '}') {
			return 6;
		}
		else if (str[strTop] == '#') {
			return 6;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'B') {
		if (str[strTop] == '(')
		{
			return 2;
		}
		else if (str[strTop] == '=') {
			return 3;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'L') {
		if (str[strTop] == 'd') {
			return 7;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'C') {
		if (str[strTop] == ';') {
			return 9;
		}
		else if (str[strTop] == ')') {
			return 9;
		}
		else if (str[strTop] == '}') {
			return 9;
		}
		else if (str[strTop] == '#') {
			return 9;
		}
		else if (str[strTop] == ',') {
			return 8;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'Q') {
		if (str[strTop] == '}') {
			return 11;
		}
		else if (str[strTop] == '#') {
			return 11;
		}
		else if (str[strTop] == 'e') {
			return 10;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'X') {
		if (str[strTop] == 'd') {
			return 12;
		}
		else if (str[strTop] == 'n') {
			return 12;
		}
		else if (str[strTop] == '+') {
			return 12;
		}
		else if (str[strTop] == '-') {
			return 12;
		}
		else if (str[strTop] == '(') {
			return 12;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'E') {
		if (str[strTop] == 'd') {
			return 13;
		}
		else if (str[strTop] == 'n') {
			return 13;
		}
		else if (str[strTop] == '(') {
			return 13;
		}
		else if (str[strTop] == '+') {
			return 14;
		}
		else if (str[strTop] == '-') {
			return 15;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'D') {
		if (str[strTop] == '+') {
			return 16;
		}
		else if (str[strTop] == '-') {
			return 16;
		}
		else if (str[strTop] == 'a') {
			return 17;
		}
		else if (str[strTop] == '<') {
			return 17;
		}
		else if (str[strTop] == 'b') {
			return 17;
		}
		else if (str[strTop] == 'c') {
			return 17;
		}
		else if (str[strTop] == 'g') {
			return 17;
		}
		else if (str[strTop] == ';') {
			return 17;
		}
		else if (str[strTop] == ')') {
			return 17;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'M') {
		if (str[strTop] == '+') {
			return 18;
		}
		else if (str[strTop] == '-') {
			return 19;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'T') {
		if (str[strTop] == 'd') {
			return 20;
		}
		else if (str[strTop] == 'n') {
			return 20;
		}
		else if (str[strTop] == '(') {
			return 20;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'H') {
		if (str[strTop] == '*') {
			return 21;
		}
		else if (str[strTop] == '/') {
			return 21;
		}
		else if (str[strTop] == '+') {
			return 22;
		}
		else if (str[strTop] == '-') {
			return 22;
		}
		else if (str[strTop] == '>') {
			return 22;
		}
		else if (str[strTop] == 'a') {
			return 22;
		}
		else if (str[strTop] == '<') {
			return 22;
		}
		else if (str[strTop] == 'b') {
			return 22;
		}
		else if (str[strTop] == 'c') {
			return 22;
		}
		else if (str[strTop] == 'g') {
			return 22;
		}
		else if (str[strTop] == ';') {
			return 22;
		}
		else if (str[strTop] == ')') {
			return 22;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'N') {
		if (str[strTop] == '*') {
			return 23;
		}
		else if (str[strTop] == '/') {
			return 24;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'F') {
		if (str[strTop] == 'd') {
			return 25;
		}
		else if (str[strTop] == 'n') {
			return 26;
		}
		else if (str[strTop] == '(') {
			return 27;
		}
		else {
			return -1;
		}
	}
	else if (stack[stackTop] == 'R') {
		if (str[strTop] == '>') {
			return 28;
		}
		else if (str[strTop] == 'a') {
			return 29;
		}
		else if (str[strTop] == '<') {
			return 30;
		}
		else if (str[strTop] == 'b') {
			return 31;
		}
		else if (str[strTop] == 'c') {
			return 32;
		}
		else if (str[strTop] == 'g') {
			return 33;
		}
		else {
			return -1;
		}
	}
	else {
		cout << "语法错误";
	}
	return -1;
}
void init()
{
	productions[0].l_char = 'S';	strcpy_s(productions[0].r_char, "iL;");		strcpy_s(productions[0].pro, "S ->int L;");
	productions[1].l_char = 'S';	strcpy_s(productions[1].r_char, "dB");			strcpy_s(productions[1].pro, "S ->d B");
	productions[2].l_char = 'B';	strcpy_s(productions[2].r_char, "(L);");		strcpy_s(productions[2].pro, "B ->(L);");
	productions[3].l_char = 'B';	strcpy_s(productions[3].r_char, "=E;"); 		strcpy_s(productions[3].pro, "B ->=E;");
	productions[4].l_char = 'S';	strcpy_s(productions[4].r_char, "f(X){S}Q");	strcpy_s(productions[4].pro, "S ->if(X){S}Q");
	productions[5].l_char = 'S';	strcpy_s(productions[5].r_char, "w(X){S}");	strcpy_s(productions[5].pro, "S ->while(X){S}");
	productions[6].l_char = 'S';	strcpy_s(productions[6].r_char, "ε");			strcpy_s(productions[6].pro, "S ->ε");
	productions[7].l_char = 'L';	strcpy_s(productions[7].r_char, "dC");			strcpy_s(productions[7].pro, "L ->dC");
	productions[8].l_char = 'C';	strcpy_s(productions[8].r_char, ",dC");		strcpy_s(productions[8].pro, "C->,dC");
	productions[9].l_char = 'C';	strcpy_s(productions[9].r_char, "ε");			strcpy_s(productions[9].pro, "C->ε");
	productions[10].l_char = 'Q';	strcpy_s(productions[10].r_char, "e{S}");		strcpy_s(productions[10].pro, "Q ->else{S}");
	productions[11].l_char = 'Q';	strcpy_s(productions[11].r_char, "ε");		strcpy_s(productions[11].pro, "Q ->ε");
	productions[12].l_char = 'X';	strcpy_s(productions[12].r_char, "ERE");		strcpy_s(productions[12].pro, "X ->ERE");
	productions[13].l_char = 'E';	strcpy_s(productions[13].r_char, "TD");		strcpy_s(productions[13].pro, "E ->TD");
	productions[14].l_char = 'E';	strcpy_s(productions[14].r_char, "+TD");		strcpy_s(productions[14].pro, "E ->+TD");
	productions[15].l_char = 'E';	strcpy_s(productions[15].r_char, "-TD");		strcpy_s(productions[15].pro, "E ->-TD");
	productions[16].l_char = 'D';	strcpy_s(productions[16].r_char, "MD");		strcpy_s(productions[16].pro, "D->MD");
	productions[17].l_char = 'D';	strcpy_s(productions[17].r_char, "ε");		strcpy_s(productions[17].pro, "D->ε");
	productions[18].l_char = 'M';	strcpy_s(productions[18].r_char, "+T");		strcpy_s(productions[18].pro, "M ->+T");
	productions[19].l_char = 'M';	strcpy_s(productions[19].r_char, "-T");		strcpy_s(productions[19].pro, "M ->-T");
	productions[20].l_char = 'T';	strcpy_s(productions[20].r_char, "FH");		strcpy_s(productions[20].pro, "T ->FH");
	productions[21].l_char = 'H';	strcpy_s(productions[21].r_char, "NH");		strcpy_s(productions[21].pro, "H->NH");
	productions[22].l_char = 'H';	strcpy_s(productions[22].r_char, "ε");		strcpy_s(productions[22].pro, "H->ε");
	productions[23].l_char = 'N';	strcpy_s(productions[23].r_char, "*F");		strcpy_s(productions[23].pro, "N ->*F");
	productions[24].l_char = 'N';	strcpy_s(productions[24].r_char, "/F");		strcpy_s(productions[24].pro, "N ->/F");
	productions[25].l_char = 'F';	strcpy_s(productions[25].r_char, "d");			strcpy_s(productions[25].pro, "F ->d");
	productions[26].l_char = 'F';	strcpy_s(productions[26].r_char, "n");			strcpy_s(productions[26].pro, "F ->n");
	productions[27].l_char = 'F';	strcpy_s(productions[27].r_char, "(E)");		strcpy_s(productions[27].pro, "F ->(E)");
	productions[28].l_char = 'R';	strcpy_s(productions[28].r_char, ">");			strcpy_s(productions[28].pro, "R ->>");
	productions[29].l_char = 'R';	strcpy_s(productions[29].r_char, "a");			strcpy_s(productions[29].pro, "R ->>=");
	productions[30].l_char = 'R';	strcpy_s(productions[30].r_char, "<");			strcpy_s(productions[30].pro, "R -><");
	productions[31].l_char = 'R';	strcpy_s(productions[31].r_char, "b");			strcpy_s(productions[31].pro, "R -><=");
	productions[32].l_char = 'R';	strcpy_s(productions[32].r_char, "c");			strcpy_s(productions[32].pro, "R ->==");
	productions[33].l_char = 'R';	strcpy_s(productions[33].r_char, "g");			strcpy_s(productions[33].pro, "R ->!=");

}
int stackPush(int* top, Prod prod)
{
	int len;
	int i;
	char c[] = "ε";
	len = strlen(prod.r_char);
	if (!strcmp(prod.r_char, c))
	{
		stack[(*top)] = '\0';
	}
	else {
		for (i = len - 1; i >= 0; i--)
		{
			stack[(*top)++] = prod.r_char[i];
		}

	}
	--(*top);
	return 0;
}
int matching(int* top, char* str)
{
	int len;
	int i;
	if (stack[(*top)] == str[0])
	{
		stack[(*top)--] = '\0';
		len = strlen(str);
		for (i = 0; i < len - 1; i++)
		{
			str[i] = str[i + 1];
		}
		str[i] = '\0';
		return 1;
	}
	else
	{
		return 0;
	}
}
