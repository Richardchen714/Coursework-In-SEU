#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

/* �����ֱ���*/
/*1-20Ϊ�ؼ����ֱ���*/
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

/*20Ϊ��ʶ���ֱ���*/
#define _ID 20   

/*30Ϊ�����ֱ���*/
#define _NUM 30    

/*31-40Ϊ������ֱ���*/
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

/*41-35Ϊ������ֱ���*/
#define _LP 41       // (
#define _RP 42       // )
#define _LBT 43      // [
#define _RBT 44      // ]
#define _LBS 45      // {
#define _RBS 46      // }
#define _COM 47      // ,
#define _COL 48      // :
#define _SEM 49      // ;

/*��-1��Ϊ�޷�ʶ����ַ���־��*/
#define _ERROR -1       
int errorNum = 0;    //���شʷ������������ 


/*�ж��Ƿ�Ϊ��ĸ*/
int IsLetter(char c) {
	if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A')))
		return 1;
	else
		return 0;
}

/*�ж��ǲ��ǹؼ���*/
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


/*�ж��Ƿ�Ϊ������������С������������*/
int IsNum(string str) {
	int i = 0, j = 0, k = 0;
	for (; i < str.size(); i++)
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			k++;
			if (k > j + 1)
			{
				cout << "�ó���" << str << "�Ĵʷ�����ȷ" << endl;
				return false;
			}
			else if (str[i] == '.')
			{
				j++;
				if (j > 1)
				{
					cout << "�ó���" << str << "�Ĵʷ�����ȷ" << endl;
					return false;
				}
			}
			else if ((str[i - 1] >= '0' && str[i - 1] <= '9') && (str[i] == 'E') && ((str[i + 1] >= '0' && str[i + 1] <= '9') || i == str.size() - 1))
			{
				continue;
			}
			else {
				cout << "�ó���" << str << "�Ĵʷ�����ȷ" << endl;
				return false;
			}
		}
	}
	return true;
}


/*�ʷ���������*/
vector<pair<int, string> > analyse(vector<string> vec)
{
	vector<pair<int, string> > vectemp;
	int i = 0;
	for (; i < vec.size(); i++)
	{
		if (vec[i].size() == 1)
		{
			if (vec[i] == "=")    //�����"="
			{
				if (vec[i + 1] == "=")  //�����������"="�����������"=="
				{
					string s = vec[i];
					s.append(vec[++i], 0, 1);
					pair<int, string> pairIS(_EQ, s);
					vectemp.push_back(pairIS);       //��pair��ӵ�vector����β��
				}
				else    //�����������"="
				{
					pair<int, string> pairIS(_AS, vec[i]);
					vectemp.push_back(pairIS);
				}
			}
			else if (vec[i] == ">")   //�����">"
			{
				if (vec[i + 1] == "=")   //�����������"="�����������">="
				{
					string s = vec[i];
					s.append(vec[++i], 0, 1);
					pair<int, string> pairIS(_GE, s);
					vectemp.push_back(pairIS);
				}
				else     //�����������">"
				{
					pair<int, string> pairIS(_GT, vec[i]);
					vectemp.push_back(pairIS);
				}
			}
			else if (vec[i] == "<")   //�����"<"
			{
				if (vec[i + 1] == "=")   //�����������"="�����������"<="
				{
					string s = vec[i];
					s.append(vec[++i], 0, 1);
					pair<int, string> pairIS(_LE, s);
					vectemp.push_back(pairIS);
				}
				else   //�����������"<"
				{
					pair<int, string> pairIS(_LT, vec[i]);
					vectemp.push_back(pairIS);
				}
			}
			else if (vec[i] == "+")  //�����"+" 
			{
				if ((vec[i - 1] == "=" || vec[i - 1] == "(") && IsNum(vec[i + 1]))   //�ж��Ƿ����з��ų�����������
				{
					string s = vec[i];
					s.append(vec[++i]);
					pair<int, string> pairIS(_NUM, s);
					vectemp.push_back(pairIS);
				}
				else   //�����������"+"
				{
					pair<int, string> pairIS(_ADD, vec[i]);
					vectemp.push_back(pairIS);
				}
			}
			else if (vec[i] == "-")  //�����"-"
			{
				if ((vec[i - 1] == "=" || vec[i - 1] == "(") && IsNum(vec[i + 1]))   //�ж��Ƿ����з��ų�����������
				{
					string s = vec[i];
					s.append(vec[++i]);
					pair<int, string> pairIS(_NUM, s);
					vectemp.push_back(pairIS);
				}
				else    //�����������"-"
				{
					pair<int, string> pairIS(_SUB, vec[i]);
					vectemp.push_back(pairIS);
				}
			}
			else if (vec[i] == "*")  //�����"*" 
			{
				pair<int, string> pairIS(_MUL, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "/")   //�����"/" 
			{
				pair<int, string> pairIS(_DIV, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "(")  //�����"(" 
			{
				pair<int, string> pairIS(_LP, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == ")")  //�����")" 
			{
				pair<int, string> pairIS(_RP, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "[")  //�����"[" 
			{
				pair<int, string> pairIS(_LBT, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "]") //�����"]"  
			{
				pair<int, string> pairIS(_RBT, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "{")  //�����"{" 
			{
				pair<int, string> pairIS(_LBS, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == "}")  //�����"}" 
			{
				pair<int, string> pairIS(_RBS, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == ",")  //�����"," 
			{
				pair<int, string> pairIS(_COM, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == ":") //�����":"   
			{
				pair<int, string> pairIS(_COL, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i] == ";")  //�����";" 
			{
				pair<int, string> pairIS(_SEM, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (vec[i][0] >= '0' && vec[i][0] <= '9')   //�ж��Ƿ���һλ���ֳ���
			{
				pair<int, string> pairIS(_NUM, vec[i]);
				vectemp.push_back(pairIS);
			}
			else if (IsLetter(vec[i][0]))   //�ж��Ƿ���һλ��ĸ��ʶ�� 
			{
				pair<int, string> pairIS(_ID, vec[i]);
				vectemp.push_back(pairIS);
			}
			else
			{
				pair<int, string> pairIS(_ERROR, vec[i]);     //�������޷�ʶ����ַ�
				vectemp.push_back(pairIS);
				errorNum++;
			}
		}
		else if ((vec[i][0] <= '9' && vec[i][0] >= '0') || vec[i][0] == '.')  //�����ʳ��ȳ���1�����ж��Ƿ�����ȷ�ĳ���
		{
			if (!IsNum(vec[i]))     //�����ǳ����������޷�ʶ����ַ�
			{
				pair<int, string> pairIS(_ERROR, vec[i]);
				errorNum++;
			}
			else if ((vec[i + 1][0] == '+' || vec[i + 1][0] == '-') && IsNum(vec[i + 2])) //�ж��Ƿ����з��ŵĳ���
			{
				string s = vec[i];
				s.append(vec[++i]);
				s.append(vec[++i]);
				pair<int, string> pairIS(_NUM, s);
				vectemp.push_back(pairIS);
			}
			else   //�������޷��ŵĳ���
			{
				pair<int, string> pairIS(_NUM, vec[i]);
				vectemp.push_back(pairIS);
			}
		}
		else if (isKeyID(vec[i]))    //�ж��Ƿ�Ϊ�ؼ���
		{
			pair<int, string> pairIS(isKeyID(vec[i]), vec[i]);
			vectemp.push_back(pairIS);
		}
		else if (IsLetter(vec[i][0]) || vec[i][0] == '_')    //�ж��Ƿ�Ϊ��ʶ��������ĸ�����»��߿�ͷ��
		{
			pair<int, string> pairIS(_ID, vec[i]);
			vectemp.push_back(pairIS);
		}
		else    //�������޷�ʶ��ĵ���
		{
			pair<int, string> pairIS(_ERROR, vec[i]);
			vectemp.push_back(pairIS);
			errorNum++;
		}
	}
	return vectemp;
}

/*�ú�������ɾ�������Ŀո�ͻ��з����ҵ���Ч�ַ���λ�ã���һ������ΪĿ���ַ������ڶ�������Ϊ��ʼλ�ã�
  ����ֵΪ�����Ŀո�ͻ��к�ĵ�һ����Ч�ַ����ַ�����λ��*/
int getFirstChar(string str, int i)
{
	while (true) {
		if (str[i] != ' ' && str[i] != '\n')
			return i;
		i++;
	}
}

/*���һ�����ʷ���,��λ��i��ʼ���ң������ò���j����������������һ���ַ���ԭ�ַ�����λ��*/
string getWord(string str, int i, int& j)
{
	string s(" \n+-*\=()[]{},:;");  //�������ϵ��ʵ��ַ�����
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
	cout << "�����ļ�·����"<<endl;
	cin >> filename;
	ifstream infile(filename.c_str());
	if (!infile)
	{
		cerr << "�޷����ļ�" << filename.c_str() << endl;
		exit(-1);
	}
	cout << endl;
	char s1[1000];
	infile.getline(s1, 1000, EOF);
	infile.close();

	cout << "�����������£�\n" << s1 << endl;

	int a = 0, b = 0;   //�ֱ��ʾ���ʵĵ�һ�������һ���ַ�λ��
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
	cout << "\n�ʷ��������Խ�����£�\n< �����ֱ��룬 ���ʱ���  >         //�������" << endl;
	for (int i = 0; i < v.size(); i++)
	{
		cout << "<   " << left << setw(2) << v[i].first << "    ,    " << left << setw(10) << v[i].second << left << setw(10) << ">";
		if (v[i].first > 0 && v[i].first < 20)
		{
			cout << left << setw(20) << "//�ؼ���" << endl;
		}
		else if (v[i].first == 20)
		{
			cout << left << setw(20) << "//��ʶ��" << endl;
		}
		else if (v[i].first == 30)
		{
			cout << left << setw(20) << "//����" << endl;
		}
		else if (v[i].first > 30 && v[i].first <= 40)
		{
			cout << left << setw(20) << "//�����" << endl;
		}
		else if (v[i].first > 40 && v[i].first < 60)
		{
			cout << left << setw(20) << "//���޷�" << endl;
		}
		else if (v[i].first == -1)
		{
			cout << left << setw(30) << "//�޷�ʶ��ķ���" << endl;
		}
	}
	cout << "�ʷ������ɹ�����" << errorNum << "���޷�ʶ��ķ��š�" << endl;
	return 0;
}