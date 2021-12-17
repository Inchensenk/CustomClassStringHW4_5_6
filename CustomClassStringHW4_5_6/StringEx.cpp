#include "StringEx.h"

char* StringEx::getStr()
{
    return str;
}

int StringEx::getLength()
{
    return length;
}

StringEx::StringEx()
{
    str = nullptr;
    length = 0;
}

StringEx::StringEx(const char* str)
{
    //strlen() ������� ���������� �������� � ������, ������� �� ��������, ���� �� ��������� �� '\0'(������������ ���� ��� �� ���������)
    //��� ����, ����� ����� ������� ����� ��� ����� ����� �������� � ������������ ������ ��� ��� ����� ������

    //�������� ��������, ������� ������ ������� strlen(), ���� length 
    length = strlen(str);

    //������� ����� ������ � ������������ ������ �� ������� ������ ������� ������� ������� ����� ��������� '\0'
    this->str = new char[length + 1];

    //����������� ����������� �������� �� ������������ ������� ������� ������� ������, ������������ � private ����
    for (int i = 0; i < length; i++)
    {
        this->str[i] = str[i];
    }

    //���������� ����� ������, ����� ����� ��� ����� ��� ������, ������� � ��� ������ �������� � ����� ������� ������  
    this->str[length] = '\0';
}

StringEx::StringEx(const StringEx& other)
{
    //����� ������ ������������ ������� � ������������ ��� �������� ���� length
    length = strlen(other.str);

    //�������� ����� ������������ ������ ��� ����������� ������ ������� � ������
    this->str = new char[length + 1];//�������� ����� � ������������ ������ ��� ������ ������� char

    //� ����������� ��� ��� ���� �������� ����� ��� ������ ����������� �� ���� ������� � ������������ �������
    for (int i = 0; i < length; i++)
    {
        this->str[i] = other.str[i];// �������� �� ��������� 2� �������� � �� ������ ������� ����������� ����������� �������� � ������ ������
    }
    this->str[length] = '\0';//���������� ����� ������
}

StringEx StringEx::operator+(const StringEx& other)
{
    //������� ����� ������ ������
    StringEx newStr;

    //��� ��� ��� ����� ����� ������ ������� ����� ��������� ������� ����� ������� ������,
    // ��� ����� ����� 2 ���������� ,����� �� ����� �������� ����� � ����� ����� ������� � ��� ��������� str ����� �������� new 

    //������ ������ ������� char, ������� � ������� �������
    int thisLength = strlen(this->str);

    //���������� ������� ����� �������� ������, ������� �� ��������
    int otherLength = strlen(other.str);

    //����������� �������� ������ ��������������� ������� char (����� �������������� ������) ���� length ������� newStr
    newStr.length = thisLength + otherLength;

    //� ������� ��������� new �������� � ����� ����� ������� ����� ������ ����� ���� ���� �������� + 1 ��� '\0'
    newStr.str = new char[newStr.length + 1];

    //������ � ��� ���� ����� ������, � ������ �� ������ ��������� ��� �������� �� ���� �������� �� ������� �� ���������� ����� �������
    //��� ����� ���������� ��� �����

    //������ ���� ��������� ������ ������� ��������� � this � ��������� � ��� ����� ������ ��� ���� ������� 
    //��� ��� �� ������ ����� ����� ���������� �������������� ������, �� ������� i ����� ������ for, ����� i �� ������ for ���������� �� � 0-�� 
    int i = 0;
    for (; i < thisLength; i++)
    {
        newStr.str[i] = this->str[i];
    }

    //������ ���� ����� �������� ������� ������� ������� � ����� ������
    //�� ������ ����� ������������� � ������� ��������� i
    for (int j = 0; j < otherLength; j++, i++)
    {
        newStr.str[i] = other.str[j];
    }
    //����� ���� ��� ��� �������� �������� � ����� ������, ��������� '\0' ��� ����������� ����� ������
    newStr.str[newStr.length] = '\0';

    //������ ���������� ������, ������� �� �������, ��� ��������� ������ ��������� '+' (����� �������)
    return newStr;
}

StringEx& StringEx::operator=(const StringEx& other)
{
    //���� ��� ��������� �� nullptr (������ � ��� ���-�� ����)
    if (this->str != nullptr)
    {
        //�� ������� ������������ ������
        delete[]str;
    }

    //����� ������ ������������ ������� � ����������� �������� ���� length 
    length = strlen(other.str);

    //�������� ����� � ������������ ������ ��� ������ ������� char
    this->str = new char[length + 1];

    //����������� ����������� �������� �� ����������� ������, ������ ������� ������ 
    for (int i = 0; i < length; i++)
    {
        this->str[i] = other.str[i];
    }
    //���������� ����� ������
    this->str[length] = '\0';

    //���������� �������������� ���������, ������ ��� �� ���������� ������ �� ������� ������ ������ ������
    return *this;
}

char& StringEx::operator[](int index)
{
    return this->str[index];
}

StringEx::StringEx(StringEx&& other)
{
    //������ �������� ������� ����������� �������� ������������ ��������� other.length
    this->length = other.length;

    /*����� ������ ����� � � ��� ��������� ������� ��������� �� ������ � ������������ ������ ����������� �����
     ������ �� ������ ������� ������ � ������� other, ����� ������� �� ��� �� �������� ����������� � ������ �������:
     "��� �� ������ �� ���� ������, �� ������ �� ���� �������� � ���� �������"*/
    this->str = other.str;

    /*��� ���� ����� ��� ������ �� ����������� ��� ����� ��������� ������� ��� ������, ���������� � ����� ������� � ��� ��������� � ����������� nullptr.
    ����� ������� �� ��������� ������� ������ �� ������� �� ���������, ��� ��� ��� ����� ������ ��������� � ������ other �� �������� ����� const � ��������� �� �����*/
    other.str = nullptr;
}

int StringEx::Length()
{
    //��������� � ��� ����� ������� ������� ���������� � ����� ������, 
    //����� ������ ��� ��� ��������� � ������ ���� ������ �� ������ � ������ ��� �����������
    //����� ���� ������ �������� �� ������������������
    return length;
}

int StringEx::size(char* str)
{
    //��������� ���������� ��� �������� �������� � ����������� �� 0
    int counter = 0;

    //���� �������� ������� ������� ����� �� ����� ����� '\0'
    while (str[counter] != '\0')
    {
        //����������� ������� �� 1
        counter++;
    }

    //���������� ���������� �������� � ������ ��� ��������� ������ ������ size() 
    return counter;
}

bool StringEx::operator==(const StringEx& other)
{
    if (this->length != other.length)
    {
        return false;
    }

    for (int i = 0; i < this->length; i++)
    {
        if (this->str[i] != other.str[i])
        {
            return false;
        }
    }
    return true;
}

bool StringEx::operator!=(const StringEx& other)
{
    return (!(this->operator==(other)));
}

void StringEx::print()
{
    cout << str << endl;
}

StringEx::~StringEx()
{
    delete[] this->str;
}

int StringEx::find(char* str, char k)
{
    for (int i = 0; i < StringEx::size(str); i++)
    {
        if (k == str[i])//���� �������� ������� �� ���� ��������� � ��������� �������
        {
            return i;//������� �������� ������� � �������
        }
    }

    return -1;//������ � ������� �� ������
}

int StringEx::find(char k)
{
    for (int i = 0; i < StringEx::size(str); i++)
    {
        if (k == str[i])//���� �������� ������� �� ���� ��������� � ��������� �������
        {
            return i;//������� �������� ������� � �������
        }
    }

    return -1;//������ � ������� �� ������
}

int StringEx::contains(char* str, char* substr)
{
    for (size_t i = 0; i < StringEx::size(str); i++)
    {
        int pos = i;
        bool isMatches = false;
        for (size_t j = 0; j < StringEx::size(substr); j++)
        {
            if (str[i] == substr[j])
            {
                isMatches = true;
                i++;
            }
            else if (str[i] != substr[j])
            {
                isMatches = false;
                break;
            }

        }
        if (isMatches)
        {
            return pos;
        }
        else
            i = pos;
    }

    return -1;
}

int StringEx::contains(char* substr)
{

    for (size_t i = 0; i < StringEx::size(str); i++)
    {
        //��������� ������ � ���������� ����� ��� �������, ���� �� ���� �� ������ ���������
        int pos = i;
        //�� ��������� ������� ��� ���������� ���
        bool isMatches = false;
        for (size_t j = 0; j < StringEx::size(substr); j++)
        {
            //���� ���� ����������
            if (str[i] == substr[j])
            {
                //�� ���������
                isMatches = true;
                //��������� ����� ��������� ��������� ������� �� ����������
                i++;
            }
            //����� ���� ��� �� ���������
            else if (str[i] != substr[j])
            {
                //�� �� ���������
                isMatches = false;
                //������� �� ����������� �����
                break;
            }

        }
        //���� �������
        if (isMatches)
        {
            //���������� ������� ������ ���������� ��������� � ������
            return pos;
        }
        else
            //����� ���� �� ����� �� ���� ������, �� ������ ��� ������� ��������� �� ������� �� �������
            i = pos;
    }
    //���� ��� ����������� ���������� -1
    return -1;
}

char* StringEx::insert(char* str, char* insertStr, int index)
{
    int size = StringEx::size(str) + StringEx::size(insertStr) + 1;
    char* resultStr = new char[size];
    for (int i = 0; i < index; i++)
    {
        resultStr[i] = str[i];
    }
    int j = index;
    for (int i = 0; i < StringEx::size(insertStr); j++, i++)
    {
        resultStr[j] = insertStr[i];
    }
    for (int i = index; i < StringEx::size(resultStr) - StringEx::size(insertStr); i++, j++)
    {
        resultStr[j] = str[i];
    }
    resultStr[size] = '\0';
    return resultStr;
}

char* StringEx::insert(char* insertStr, int index)
{
    int size = StringEx::size(str) + StringEx::size(insertStr) + 1;
    char* resultStr = new char[size];
    for (int i = 0; i < index; i++)
    {
        resultStr[i] = str[i];
    }
    int j = index;
    for (int i = 0; i < StringEx::size(insertStr); j++, i++)
    {
        resultStr[j] = insertStr[i];
    }
    for (int i = index; i < StringEx::size(resultStr) - StringEx::size(insertStr); i++, j++)
    {
        resultStr[j] = str[i];
    }
    resultStr[size] = '\0';
    return resultStr;
}

int StringEx::count(char* str, char sep)
{
    int size = 0;
    for (int i = 0; i < StringEx::size(str); i++)
    {
        if (str[i] == sep)
            size++;
    }
    return size;
}

int StringEx::count(char sep)
{
    int size = 0;
    for (int i = 0; i < StringEx::size(str); i++)
    {
        if (str[i] == sep)
            size++;
    }
    return size;
}

char** StringEx::split(char* str, char sep, bool print)
{
    int numrow = count(str, sep) + 1;

    int* numcol = new int[numrow];
    int beg = 0;
    for (int i = 0; i < numrow; i++)
    {
        int col = 0;

        for (int j = beg; j < StringEx::size(str); j++)
        {
            if (str[j] != sep && str[j] != '\0')
            {
                col++;
            }
            else
            {
                col++;
                beg = j + 1;
                break;
            }
        }
        numcol[i] = col;
    }

    char** spl = new char* [numrow];
    for (int i = 0; i < numrow; i++)
    {
        spl[i] = new char[numcol[i]];
    }
    beg = 0;
    for (int i = 0; i < numrow; i++)
    {
        for (int j = 0, k = beg; j < StringEx::size(str); j++, k++)
        {
            if (str[k] != sep && str[k] != '\0')
            {
                spl[i][j] = str[k];
            }
            else
            {
                spl[i][j] = '\0';
                beg = k + 1;
                break;
            }
        }
    }

    if (print)
        for (int i = 0; i < numrow; i++)
        {
            for (int j = 0; j < StringEx::size(spl[i]); j++)
            {
                cout << spl[i][j];
            }
            cout << endl;
        }

    return spl;
}

char** StringEx::split(char sep, bool print)
{
    //����������� ����� ��������� ������������� �������
    int numrow = count(str, sep) + 1;
    //�������� ������� ��� �������� ������ ����� � ��������� �������
    int* numcol = new int[numrow];
    //��������� ������� ���������� ��� ������ str
    int beg = 0;
    //���������� ����� ����� ��������� �������
    for (int i = 0; i < numrow; i++)
    {
        //����������� �������� ��� ������ ������
        int col = 0;

        for (int j = beg; j < StringEx::size(str); j++)
        {
            //���� ������ � ������ �� ����� ����������� � ����-�����������
            if (str[j] != sep && str[j] != '\0')
            {
                //�� ����������� ������� �������� ������ ��������� �������
                col++;
            }
            //�����
            else
            {
                //����������� ������� �� 1 ��� '\0'
                col++;
                //�������� ��������� ������� ���������� � ������ �� ������� ��������� +1 ����� ������������ �����������
                beg = j + 1;
                break;
            }
        }
        //���������� ������ ������ � i-��� ������� ������� ������� ������ ������ �����
        numcol[i] = col;
    }
    //�������������� ��������� �������� ������������ ������
    char** spl = new char* [numrow];
    for (int i = 0; i < numrow; i++)
    {
        spl[i] = new char[numcol[i]];
    }
    //���������� �������� ����, ������ ��� ��� ���� ������ � �������� ������
    beg = 0;
    for (int i = 0; i < numrow; i++)
    {
        for (int j = 0, k = beg; j < StringEx::size(str); j++, k++)
        {
            if (str[k] != sep && str[k] != '\0')
            {
                spl[i][j] = str[k];
            }
            else
            {
                spl[i][j] = '\0';
                beg = k + 1;
                break;
            }
        }
    }
    //���� ������ �������� true �� ������� ������ � �������
    if (print) 
    {
        for (int i = 0; i < numrow; i++)
        {
            for (int j = 0; j < StringEx::size(spl[i]); j++)
            {
                cout << spl[i][j];
            }
            cout << endl;
        }
       
        //���������� ��������� �� �������� ������
        return spl;
    }
        
}

int StringEx::operator-(const StringEx& other)
{

   return StringEx::contains(this->str, other.str);
       
}

char** StringEx::operator/(char sep)
{
    StringEx result = *this;

    return result.split(sep);
}

bool StringEx::isEmpty()
{
    if(str == "" || str == "\0" || str == nullptr || size(str) == 0) return true;
      
    else return false;
}

void StringEx::clean()
{
   str == nullptr;
}








