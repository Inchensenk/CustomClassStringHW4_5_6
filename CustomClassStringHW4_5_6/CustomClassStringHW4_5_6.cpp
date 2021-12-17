
#include "StringEx.h"
#include <string.h>

int main()
{
    //инициализация str строкой "Hello" при помощи конструктора с параметром
    StringEx str("");
    
    //инициализация str2 строкой "World" при помощи конструктора с параметром
    StringEx str2("lo");

    //конокотанация при помощи перегруженного оператора +
    //StringEx result = str + str2;

    ////вывод результирующей строки
    //result.print();

    ////вывод размера  строки
    //cout << str.Length() << endl;
    //cout << str2.Length() << endl;
    //cout << result.Length() << endl;
    


    //// "==" фактически означает: str.operator==(str2), str в данном случае это this объект, а other - это тот объект, который мередаем параметром (то есть str2)
    ////просто компилятор позволяет это все не писать: (bool equal = str.operator==(str2)), а просто можно писать так:  (bool equal = str == str2;) чтобы было проще
    //bool equal = str == str2;

   /* str.print();
    cout << endl;
    str[0] = 'S';
    str.print();

    cout<<StringEx::contains(str.getStr(), str2.getStr());

    cout << StringEx::insert(str.getStr(), str2.getStr(), 3);*/

    //StringEx strspl = "Royal/Never/Give/Up";
    //strspl.split('/');
    //StringEx res = str-str2;
    /*char** rezzzzz = strspl / '/';
    cout << endl;
    cout << str - str2;*/
    cout<<str.isEmpty();
    return 5;
}

