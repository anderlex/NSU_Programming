#include <iostream>
#include <locale.h>

using namespace std;

template <typename T> class List
{
private:
    struct ListElt
    {
        T data;
        ListElt* next;
    };
    ListElt* head;
    List(const List& orig);
    List& operator=(const List& orig);
public:
    List() 
    { 
        head = NULL; 
    }
    void addFirst(T x)
    {
        ListElt* cur = new ListElt;
        cur->data = x;
        cur->next = head;
        head = cur;
        cout << "Добавление элемента в начало:" << endl;
    }
    void deleteFirst()
    {
        if (head != NULL)
        {
            ListElt* cur = head;
            head = head->next;
            delete cur;
        }
        cout << "Удаление первого элемента:" << endl;
    }
    void addLast(T x)
    {
        if (head != NULL)
        {
            ListElt* cur = head;
            while (cur->next != NULL)
            {
                cur = cur->next;
            }
            cur->next = new ListElt;
            cur->next->data = x;
            cur->next->next = 0;
        }
        else
        {
            head = new ListElt;
            head->data = x;
            head->next = 0;
        }
        cout << "Добавление последнего элемента:" << endl;
    }
    void deleteLast()
    {
        if (head != NULL)
        {
            if (head->next == NULL)
            {
                delete head;
                head = NULL;
                cout << "Удаление последнего элемента:" << endl;
            }
            else
            {
                ListElt* cur = head;
                while (cur->next->next != NULL)
                {
                    cur = cur->next;
                }
                delete cur->next;
                cur->next = NULL;
                cout << "Удаление последнего элемента:" << endl;
            }
        }
    }
    ~List()
    {
        ListElt* del = head;
        while (del)
        {
            ListElt* temp = del;
            del = del->next;
            delete temp;
        }
        head = NULL;
        cout << "Деструктор:" << endl;
    }
    void printList()
    {
        ListElt* cur = head;
        while (cur)
        {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
    class Iterator
    {
    private:
        ListElt* head;
    public:
        Iterator(ListElt* head)
        {
            this->head = head;
        }
        Iterator operator ++ (T)
        {
            Iterator it = *this;
            head = head->next;
            return it;
        }
        T& operator*()
        {
            return head->data;
        }
        ListElt* operator->()
        {
            return head;
        }
        bool operator!=(const Iterator& it)
        {
            return !(*this == it);
        }
        bool operator==(const Iterator& it)
        {
            return head == it.head;
        }
    };
    Iterator begin() const 
    {
        Iterator it(head);
        return it;
    }
    Iterator end() const 
    {
        Iterator it(NULL);
        return it;
    }
};

int main()
{
    setlocale(LC_ALL, "russian");
    List<int> test;
    test.addFirst(2);
    test.addFirst(3);
    test.addFirst(4);
    test.addFirst(5);
    test.printList();
    for (List<int>::Iterator it = test.begin(); it != test.end(); it++)
    {
        cout << *it + 3 << " ";
        if (*it + 3 == 7)
        {
            cout << "равно 7 ";
        }
    }
    return 0;
}