#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

/* 单词种别码*/
/*1-20为关键字种别码*/
#define _BEGIN 1     // begin
#define _CHAR 2      // char
#define _INT  3      // int
#define _FLOAT 4     // float
#define _DOUBLE 5    // double
#define _CONST 6     // const
#define _IF 7        // if
#define _THEN 8      // then
#define _ELSE 9      // else
#define _WHILE 10    // while
#define _DO 11       // do
#define _FOR 12      // for
#define _BREAK 13    // break
#define _CONTINUE 14 // continue
#define _SIZEOF 15   // sizeof
#define _VOID 16     // void
#define _RETURN 17   // return
#define _END 18      // end

/*20为标识符种别码*/
#define _ID 20   

/*30为常量种别码*/
#define _NUM 30    

/*31-40为运算符种别码*/
#define _AS 31       // =
#define _EQ 32       // ==
#define _GT 33       // >
#define _LT 34       // <
#define _GE 35       // >=
#define _LE 36       // <=
#define _ADD 37      // + 
#define _SUB 38      // - 
#define _MUL 39      // * 
#define _DIV 40      // / 

/*41-35为运算符种别码*/
#define _LP 41       // (
#define _RP 42       // )
#define _LBT 43      // [
#define _RBT 44      // ]
#define _LBS 45      // {
#define _RBS 46      // }
#define _COM 47      // ,
#define _COL 48      // :
#define _SEM 49      // ;

/*将-1置为无法识别的字符标志码*/
#define _ERROR -1       
int errorNum = 0;    //记载词法分析错误个数 


/*判断是否为字母*/
int IsLetter(char c) {
	if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A')))
		return 1;
	else
		return 0;
}

/*判断是不是关键字*/
int isKeyID(string str)
{
	string keystr[18] = { "begin","char","int","float","double","const","if","then","else","while","do","for","break","continue","sizeof","void","return","end" };
	vector<string> vec(keystr, keystr + 18);
	int i;
	for (i = 0; i < vec.size(); i++)
	{
		if (!str.compare(vec[i]))
		{
			return i + 1;
		}
	}
	return 0;
}


/*判断是否为常量（整数、小数、浮点数）*/
int IsNum(string str) {
	int i = 0, j = 0, k = 0;
	for (; i < str.size(); i++)
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			k++;
			if (k > j + 1)
			{
				cout << "该常量" << str << "的词法不正确" << endl;
				return false;
			}
			else if (str[i] == '.')
			{
				j++;
				if (j > 1)
				{
					cout << "该常量" << str << "的词法不正确" << endl;
					return false;
				}
			}
			else if ((str[i - 1] >= '0' && str[i - 1] <= '9') && (str[i] == 'E') && ((str[i + 1] >= '0' && str[i + 1] <= '9') || i == str.size() - 1))
			{
				continue;
			}
			else {
				cout << "该常量" << str << "的词法不正确" << endl;
				return false;
			}
		}
	}
	return true;
}


/*词法分析函数*/
vector<pair<int, string> > analyse(vector<string> vec)
{
	vector<pair<int, string> > vectemp;
	int i = 0;
	for (; i < vec.size(); i++)
	{
		if (vec[i].size() == 1)
		{
			if (vec[i] == "=")    //运算符"="
			{
				if (vec[i + 1] == "=")  //若后面跟的是"="，则是运算符"=="
				{
					string s = vec[i];
					s.append(vec[++i], 0, 1);
					pair<int, string> pairIS(_EQ, s);
					vectemp.push_back(pairIS);       //将pair组加到vector数组尾部
				}
				else    //否则是运算符"="
				{
					pair<int, string> pairIS(_AS, vec[i]);
					vectemp.push_back(pairIS);
				}
			}
			else if (vec[i] == ">")   //运算符">"
			{
				if (vec[i + 1] == "=")   //若后面跟的是"="，则是运算符">="
				{
					string s = vec[i];
					s.append(vec[++i], 0, 1);
					pair<int, string> pairIS(_GE, s);
					vectemp.push_back(pairIS);
				}
				else     //否则是运算符">"
				{
					pair<int, string> pairIS(_GT, vec[i]);
					vectemp.push_back(pairIS);
				}
			}
			else if (vec[i] == "<")   //运算符"<"
			{
				if (vec[i + 1] == "=")   //若后面跟的是"="，则是运算符"<="
				{
					string s = vec[i];
					s.append(vec[++i], 0, 1);
					pair<int, string> pairIS(_LE, s);
					vectemp.push_back(pairIS);
				}
				else   //否则是运算符"<"
				{
					pair<int, string> pairIS(_LT, vec[i]);
					vectemp.push_back(pairIS);
				}
			}
			else if (vec[i] == "+")  //运算符"+" 
			{
				if ((vec[i - 1] == "=" || vec[i - 1] == "(") && IsNum(vec[i + 1]))   //判断是否是有符号常量（正数）
				{
					string s = vec[i];
					s.append(vec[++i]);
					pair<int, string> pairIS(_NUM, s);
					vectemp.push_back(pairIS);
				}
				else   //否则是运算符"+"
				{
					pair<int, string> pairIS(_ADD, vec[i]);
					vectemp.push_back(pairIS);
				}
			}
			else if (vec[i] == "-")  //运算符"-"
			{
				if ((vec[i - 1] == "=" || vec[i - 1] == "(") && IsNum(vec[i + 1]))   //判断是否是有符号常量（负数）
				{
					string s = vec[i];
					s.append(vec[++i]);
					pair<int, string> pairIS(_NUM, s);
					vectemp.push_back(pairIS);
				}
				else    //否则是运算符"-"
				{
					pair<int, string> pairIS(_SUB, vec[i]);
					vectemp.push_back(pairIS);
				}
			}
			else if (vec[i] == "*")  //运算符"*" 
			{
				pair<int, string> pairIS(_MUL, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "/")   //运算符"/" 
			{
				pair<int, string> pairIS(_DIV, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "(")  //运算符"(" 
			{
				pair<int, string> pairIS(_LP, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == ")")  //运算符")" 
			{
				pair<int, string> pairIS(_RP, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "[")  //运算符"[" 
			{
				pair<int, string> pairIS(_LBT, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "]") //运算符"]"  
			{
				pair<int, string> pairIS(_RBT, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "{")  //运算符"{" 
			{
				pair<int, string> pairIS(_LBS, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "}")  //运算符"}" 
			{
				pair<int, string> pairIS(_RBS, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == ",")  //运算符"," 
			{
				pair<int, string> pairIS(_COM, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == ":") //运算符":"   
			{
				pair<int, string> pairIS(_COL, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == ";")  //运算符";" 
			{
				pair<int, string> pairIS(_SEM, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i][0] >= '0' && vec[i][0] <= '9')   //判断是否是一位数字常量
			{
				pair<int, string> pairIS(_NUM, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (IsLetter(vec[i][0]))   //判断是否是一位字母标识符 
			{
				pair<int, string> pairIS(_ID, vec[i]);
				vectemp.push_back(pairIS);
			}
			else
			{
				pair<int, string> pairIS(_ERROR, vec[i]);     //否则是无法识别的字符
				vectemp.push_back(pairIS);
				errorNum++;
			}
		}
		else if ((vec[i][0] <= '9' && vec[i][0] >= '0') || vec[i][0] == '.')  //若单词长度超过1，则判断是否是正确的常量
		{
			if (!IsNum(vec[i]))     //若不是常量，则是无法识别的字符
			{
				pair<int, string> pairIS(_ERROR, vec[i]);
				errorNum++;
			}
			else if ((vec[i + 1][0] == '+' || vec[i + 1][0] == '-') && IsNum(vec[i + 2])) //判断是否是有符号的常量
			{
				string s = vec[i];
				s.append(vec[++i]);
				s.append(vec[++i]);
				pair<int, string> pairIS(_NUM, s);
				vectemp.push_back(pairIS);
			}
			else   //否则是无符号的常量
			{
				pair<int, string> pairIS(_NUM, vec[i]);
				vectemp.push_back(pairIS);
			}
		}
		else if (isKeyID(vec[i]))    //判断是否为关键字
		{
			pair<int, string> pairIS(isKeyID(vec[i]), vec[i]);
			vectemp.push_back(pairIS);
		}
		else if (IsLetter(vec[i][0]) || vec[i][0] == '_')    //判断是否为标识符（以字母或者下划线开头）
		{
			pair<int, string> pairIS(_ID, vec[i]);
			vectemp.push_back(pairIS);
		}
		else    //否则是无法识别的单词
		{
			pair<int, string> pairIS(_ERROR, vec[i]);
			vectemp.push_back(pairIS);
			errorNum++;
		}
	}
	return vectemp;
}

/*该函数用来删除连续的空格和换行符，找到有效字符的位置（第一个参数为目标字符串，第二个参数为开始位置）
  返回值为连续的空格和换行后的第一个有效字符在字符串的位置*/
int getFirstChar(string str, int i)
{
	while (true) {
		if (str[i] != ' ' && str[i] != '\n')
			return i;
		i++;
	}
}

/*获得一个单词符号,从位置i开始查找，用引用参数j来返回这个单词最后一个字符在原字符串的位置*/
string getWord(string str, int i, int& j)
{
	string s(" \n+-*\=()[]{},:;");  //用来隔断单词的字符集合
	j = str.find_first_of(s, i);
	if (j == -1)
		return "";
	if (i != j)
		j--;
	return str.substr(i, j - i + 1);
}

int main()
{
	string str1 = " ";
	string str2 = "\n";
	string filename;
	cout << "输入文件路径："<<endl;
	cin >> filename;
	ifstream infile(filename.c_str());
	if (!infile)
	{
		cerr << "无法打开文件" << filename.c_str() << endl;
		exit(-1);
	}
	cout << endl;
	char s1[1000];
	infile.getline(s1, 1000, EOF);
	infile.close();

	cout << "测试用例如下：\n" << s1 << endl;

	int a = 0, b = 0;   //分别表示单词的第一个和最后一个字符位置
	vector<string> array;
	do {
		a = getFirstChar(s1, a);
		string s2 = getWord(s1, a, b);
		if (b == -1)
			break;
		if (s2.compare(str1) && s2.compare(str2))
			array.push_back(s2);
		a = b + 1;
	} while (true);

	vector<pair<int, string> >  v = analyse(array);
	cout << "\n词法分析测试结果如下：\n< 单词种别码， 单词本身  >         //所属类别" << endl;
	for (int i = 0; i < v.size(); i++)
	{
		cout << "<   " << left << setw(2) << v[i].first << "    ,    " << left << setw(10) << v[i].second << left << setw(10) << ">";
		if (v[i].first > 0 && v[i].first < 20)
		{
			cout << left << setw(20) << "//关键字" << endl;
		}
		else if (v[i].first == 20)
		{
			cout << left << setw(20) << "//标识符" << endl;
		}
		else if (v[i].first == 30)
		{
			cout << left << setw(20) << "//常量" << endl;
		}
		else if (v[i].first > 30 && v[i].first <= 40)
		{
			cout << left << setw(20) << "//运算符" << endl;
		}
		else if (v[i].first > 40 && v[i].first < 60)
		{
			cout << left << setw(20) << "//界限符" << endl;
		}
		else if (v[i].first == -1)
		{
			cout << left << setw(30) << "//无法识别的符号" << endl;
		}
	}
	cout << "词法分析成功！共" << errorNum << "个无法识别的符号。" << endl;
	return 0;
}