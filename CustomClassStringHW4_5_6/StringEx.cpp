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
    //strlen() считает количество символов в строке, которую мы передаем, пока не наткнется на '\0'(терминальный ноль она не учитывает)
    //для того, чтобы знать сколько места нам нужно будет выделить в динамической памяти под наш новый массив

    //присвоим значение, которое вернет функция strlen(), полю length 
    length = strlen(str);

    //создаем новый массив в динамической памяти на единицу больше массива который приняли чтобы учитывать '\0'
    this->str = new char[length + 1];

    //присваиваем поэлементно значения из принимаемого массива массиву объекта класса, находящемуся в private зоне
    for (int i = 0; i < length; i++)
    {
        this->str[i] = str[i];
    }

    //обьявление конца строки, чтобы знать где конец той строки, которая у нас теперь хранится в нашем объекте класса  
    this->str[length] = '\0';
}

StringEx::StringEx(const StringEx& other)
{
    //берем размер принемаемого массива и присваеиваем это значение полю length
    length = strlen(other.str);

    //выделяем новый динамический массив при копировании одного объекта в другой
    this->str = new char[length + 1];//выделяем место в динамической памяти для нового массива char

    //и поэлементно все это дело копируем чтобы при вызове деструктора не было проблем с динамической памятью
    for (int i = 0; i < length; i++)
    {
        this->str[i] = other.str[i];// проходим по элементам 2х массивов и из одного массива присваиваем поэлементно значения в другой массив
    }
    this->str[length] = '\0';//обьявление конца строки
}

StringEx StringEx::operator+(const StringEx& other)
{
    //создаем новый объект класса
    StringEx newStr;

    //так как нам нужно знать какого размера будет указатель который будет хранить строку,
    // нам будут нужны 2 переменные ,когда мы будем выделять место в нашем новом объекте в его указатель str через оператор new 

    //хранит длинну массива char, который в текущей строчке
    int thisLength = strlen(this->str);

    //определяем сколько места занимает строка, которую мы передаем
    int otherLength = strlen(other.str);

    //присваиваем значение длинны результирующего массива char (длины результирующей строки) полю length объекта newStr
    newStr.length = thisLength + otherLength;

    //с помощью оператора new выделяем в нашем новом массиве место равное сумме длин двух массивов + 1 для '\0'
    newStr.str = new char[newStr.length + 1];

    //теперь у нас есть новый массив, в котрый мы должны присвоить все элементы из двух массивов из которых мы складываем новую строчку
    //для этого используем два цикла

    //первый цикл переберет массив который находится в this и присвоить в наш новый объект все свои символы 
    //так как во втором цикле нужно дозаписать результирующий массив, то вынесем i перед первым for, чтобы i во втором for начиналась не с 0-ля 
    int i = 0;
    for (; i < thisLength; i++)
    {
        newStr.str[i] = this->str[i];
    }

    //второй цикл будет помещать обьекты второго массива в новую строку
    //мы должны здесь итерироваться с помощью оператора i
    for (int j = 0; j < otherLength; j++, i++)
    {
        newStr.str[i] = other.str[j];
    }
    //после того как все элементы помещены в новый массив, добавляем '\0' для обозначения конца строки
    newStr.str[newStr.length] = '\0';

    //теперь возвращаем объект, который мы создали, как результат работы оператора '+' (нашей функции)
    return newStr;
}

StringEx& StringEx::operator=(const StringEx& other)
{
    //если наш указатель не nullptr (значит в нем что-то есть)
    if (this->str != nullptr)
    {
        //то очищаем динамическую память
        delete[]str;
    }

    //берем размер принимаемого массива и присваиваем значение полю length 
    length = strlen(other.str);

    //выделяем место в динамической памяти для нового массива char
    this->str = new char[length + 1];

    //поэлементно присваиваем значения из принимаемой строки, строке объекта класса 
    for (int i = 0; i < length; i++)
    {
        this->str[i] = other.str[i];
    }
    //обьявление конца строки
    this->str[length] = '\0';

    //возвращаем разименованный указатель, потому что мы возвращаем ссылку на текущий объект нашего класса
    return *this;
}

char& StringEx::operator[](int index)
{
    return this->str[index];
}

StringEx::StringEx(StringEx&& other)
{
    //нашему текущему объекту присваиваем значение принимаемого параметра other.length
    this->length = other.length;

    /*далее просто берем и в наш указатель который указывает на массив в динамической памяти присваиваем адрес
     такого же самого массива только в объекте other, таким образом мы его не копируем поэлементно а просто говорим:
     "вон он теперь по тому адресу, ты теперь на него ссылайся и сним работай"*/
    this->str = other.str;

    /*Для того чтобы наш объект не уничтожился нам нужно запретить удалять эти данные, обращаемся к этому объекту к его указателю и присваиваем nullptr.
    Таким образом мы запрещаем удалять данные на которые он ссылается, так как нам нужно внести изменения в объект other то ключевое слово const в сигнатуре не нужно*/
    other.str = nullptr;
}

int StringEx::Length()
{
    //заботимся о том чтобы хранить заранее информацию о нашей строке, 
    //чтобы каждый раз при обращении к методу ленз заново не бежать и считаь это колличество
    //чтобы было меньще накладок на производительность
    return length;
}

int StringEx::size(char* str)
{
    //обьявляем переменную для подсчета символов и присваиваем ей 0
    int counter = 0;

    //пока значение индекса массива строк не будет равна '\0'
    while (str[counter] != '\0')
    {
        //увеличиваем счетчик на 1
        counter++;
    }

    //возвращаем количество символов в строке как результат работы метода size() 
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
        if (k == str[i])//если значение которое мы ищем совпадает с элементом массива
        {
            return i;//пщзиция искомого символа в массиве
        }
    }

    return -1;//символ в массиве не найден
}

int StringEx::find(char k)
{
    for (int i = 0; i < StringEx::size(str); i++)
    {
        if (k == str[i])//если значение которое мы ищем совпадает с элементом массива
        {
            return i;//пщзиция искомого символа в массиве
        }
    }

    return -1;//символ в массиве не найден
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
        //сохраняем индекс в переменную чтобы его вернуть, если не было ни одного вхождения
        int pos = i;
        //по умолчанию считаем что совпадений нет
        bool isMatches = false;
        for (size_t j = 0; j < StringEx::size(substr); j++)
        {
            //если есть совпадение
            if (str[i] == substr[j])
            {
                //то совпадает
                isMatches = true;
                //итерируем чтобы проверить следующий элемент на совпадение
                i++;
            }
            //иначе если они не совпадают
            else if (str[i] != substr[j])
            {
                //то не совпадают
                isMatches = false;
                //выходим из внутреннего цикла
                break;
            }

        }
        //если совпали
        if (isMatches)
        {
            //возвращаем позицию начала вхожденгия подстроки в строку
            return pos;
        }
        else
            //иначе если мы дошли до этой строки, то значит что текущая подстрока не совпала со строкой
            i = pos;
    }
    //если нет совпаденийй возвращаем -1
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
    //колличество строк зубчатого динамического массива
    int numrow = count(str, sep) + 1;
    //создания массива для хранения длинны строк у зубчатого массива
    int* numcol = new int[numrow];
    //стартовая позиция считывание для строки str
    int beg = 0;
    //вычисление длинн строк зубчатого массива
    for (int i = 0; i < numrow; i++)
    {
        //колличество столбцов для каждой строки
        int col = 0;

        for (int j = beg; j < StringEx::size(str); j++)
        {
            //если символ в строке не равен разделителю и нуль-терминатору
            if (str[j] != sep && str[j] != '\0')
            {
                //то увеличиваем счетчик столбцов строки зубчатого массива
                col++;
            }
            //иначе
            else
            {
                //увеличиваем счетчик на 1 для '\0'
                col++;
                //сдвигаем стартовую позицию считывания в строке на текущее положение +1 чтобы перепрышнуть разделитель
                beg = j + 1;
                break;
            }
        }
        //записываем длинну строки в i-тый элемент массива который хранит длинну строк
        numcol[i] = col;
    }
    //инициализируем двумерный зубчатый динамический массив
    char** spl = new char* [numrow];
    for (int i = 0; i < numrow; i++)
    {
        spl[i] = new char[numcol[i]];
    }
    //аналогично верхнему коду, только тут уже идет запись в зубчатый массив
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
    //если данный параметр true то выводим массив в консоль
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
       
        //возвращаем указатель на зубчатый массив
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








