#include <iostream>

using namespace std;

class String
{
private:
    char* data;
    int len;
public:
    String()
    {
        len = 0;
        data = new char[1];
        data[0] = '\0';
        cout << "Конструктор по умолчанию:" << endl;
    }
    String(const char* str)
    {
        len = getlen(str);
        data = new char[len + 1];
        for (int i = 0; i <= len; i++)
        {
            data[i] = str[i];
        }
        cout << "Конструктор с параметром char*:" << endl;
    }
    String(const String& orig)
    {
        len = orig.len;
        data = new char[len + 1];
        for (int i = 0; i <= len; i++)
        {
            data[i] = orig.data[i];
        }
        cout << "Конструктор копирования:" << endl;
    }
    ~String()
    {
        cout << "Деструктор:" << endl;
        delete[] data;
    }
    String& operator=(const String& orig)
    {
        delete[] data;
        len = orig.len;
        data = new char[len + 1];
        for (int i = 0; i <= len; i++)
        {
            data[i] = orig.data[i];
        }
        return *this;
        cout << "Оператор присваивания:" << endl;
    }
    operator const char* () const
    {
        cout << "Оператор приведения к типу const char*:" << endl;
        return(const char*)data;
    }
    String operator+(const String& second) const // Оператор +
    {
        int sumlen = len + second.len;
        char* sumdata = new char[sumlen + 1];
        for (int i = 0; i <= len; i++)
        {
            sumdata[i] = data[i];
        }
        for (int i = len; i <= sumlen; i++)
        {
            sumdata[i] = second.data[i - len];
        }
        String result(sumdata);
        cout << "Оператор +:" << endl;
        return result;
    }
    String& operator+=(const String& other) // Оператор +=
    {
        int sumlen = len + other.len;
        data = (char*)realloc(data, sumlen + 1);
        for (int i = len; i <= sumlen; i++)
        {
            data[i] = other.data[i - len];
        }
        cout << "Оператор +=:" << endl;
        return *this;
    }
    char& operator[](const int index) // Обращение по индексу с дальнейшим изменением
    {
        cout << "Обращение по индексу с дальнейшим изменением:" << endl;
        if (index >= 0 && index < len)
        {
            return data[index];
        }
        else
        {
            return data[0];
        }
    }
    char operator[](const int index) const // Константное обращение по индексу
    {
        cout << "Константное обращение по индексу:" << endl;
        if (index >= 0 && index < len)
        {
            return data[index];
        }
        else
        {
            return data[0];
        }
    }
    int getlen(const char* str)
    {
        const char* cur = str;
        for (; *cur; ++cur);
        return cur - str;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    /*
    String test1; // Проверка конструктора по умолчанию
    cout << test1 << endl;

    String test2("12345678");  // Проверка конструктора с параметром char *
    cout << test2 << endl;

    String test3 = test2; // Проверка конструктора копирования
    cout << test3 << endl;

    String test4("00001111"); // Проверка оператора присваивания
    test4 = test2;
    cout << test4 << endl;

    const char* test5 = test4;  // Проверка оператора приведения к const char *
    cout << test5 << endl;

    String test6("11111111"); // Проверка оператора +
    String test7 = test6 + test2;
    cout << test7 << endl;

    //test3 = ('00000000')

    test3 += test6; // Проверка оператора +=
    cout << test3 << endl;

    //test2 = ('12345678')
    */

    const String testlast("123456789a009876543");
    cout << testlast[-3] << endl;
    String testlast2("4672348216471");
    testlast2[5] = 'a';
    cout << testlast2 << endl;
    return 0;
}
