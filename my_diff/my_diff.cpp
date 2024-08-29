#include <iostream>
#include <string>

using namespace std;

class Expression
{
public:
	virtual Expression* diff() = 0;
	virtual void print() = 0;
};

class Number : public Expression
{
	double num;
public:
	Number(double k)
	{
		num = k;
	}
	Expression* diff()
	{
		return new Number(0);
	}
	void print()
	{
		cout << num;
	}
};

class Variable : public Expression
{
	char var;
public:
	Variable(char x) : var(x) {}
	Expression* diff()
	{
		return new Number(1);
	}
	void print()
	{
		cout << var;
	}
};

class Add : public Expression
{
	Expression* a;
	Expression* b;
public:
	Add(Expression* a1, Expression* b1)
	{
		a = a1;
		b = b1;
	}
	Expression* diff()
	{
		return new Add(a->diff(), b->diff());
	}
	void print()
	{
		cout << '(';
		a->print();
		cout << '+';
		b->print();
		cout << ')';
	}
};

class Sub : public Expression
{
	Expression* a;
	Expression* b;
public:
	Sub(Expression* a1, Expression* b1)
	{
		a = a1;
		b = b1;
	}
	Expression* diff()
	{
		return new Sub(a->diff(), b->diff());
	}
	void print()
	{
		cout << '(';
		a->print();
		cout << '-';
		b->print();
		cout << ')';
	}
};

class Mul : public Expression
{
	Expression* a;
	Expression* b;
public:
	Mul(Expression* a1, Expression* b1)
	{	
		a = a1;
		b = b1;
	}
	Expression* diff()
	{
		return new Add(new Mul(a->diff(), b), new Mul(a, b->diff()));
	}
	void print()
	{
		a->print();
		cout << "*";
		b->print();
	}
};

class Div : public Expression
{
	Expression* a;
	Expression* b;
public:
	Div(Expression* a1, Expression* b1)
	{
		a = a1;
		b = b1;
	}
	Expression* diff()
	{
		return new Div((new Sub(new Mul(a->diff(), b), new Mul(a, b->diff()))), (new Mul(b, b)));
	}
	void print()
	{
		a->print();
		cout << '/';
		cout << '(';
		b->print();
		cout << ')';
	}
};

Expression* read_expression(string h)
{
	int j;
	int flag = 0;
	if (h[0] == '-')
	{
		string right = h.substr(1, sizeof(h));
		return new Sub(new Number(0), read_expression(right));
	}
	else if (h[0] == '(')
	{
		string left, right;
		for (j = 1; j < sizeof(h) - 1; j++)
		{
			if (h[j] == '(')
			{
				flag++;
			}
			else if (h[j] == ')')
			{
				flag--;
			}
			else if ((h[j] == '+' || h[j] == '-' || h[j] == '*' || h[j] == '/') && (flag == 0))
			{
				left = h.substr(1, j);
				right = h.substr(j + 1, sizeof(h) - 1);
				if (h[j] == '+')
				{
					return new Add(read_expression(left), read_expression(right));
				}
				else if (h[j] == '-')
				{
					return new Sub(read_expression(left), read_expression(right));
				}
				else if (h[j] == '*')
				{
					return new Mul(read_expression(left), read_expression(right));
				}
				else if (h[j] == '/')
				{
					return new Div(read_expression(left), read_expression(right));
				}
			}
		}
	}
	else if (h[0] >= 'a' && h[0] <= 'z')
	{
		return new Variable(h[0]);
	}
	else if (h[0] >= '0' && h[0] <= '9')
	{
		double num = atof(h.c_str());
		return new Number(num);
	}
}

int main()
{
	Expression* e = read_expression("(3*(x+5))");
	e->print();
	cout << "\n";
	Expression* de = e->diff();
	de->print();
	delete e;
	delete de;
}
