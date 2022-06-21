#include <iostream>
#include <string>
using namespace std;

struct elem {

	bool isInv = false;
	double value = 0;
	char opt = 'x';

};

template<class T> struct stack {

	T* data = new T[1024];
	int len = 0;
	void push(T e) {
		data[len] = e;
		len++;
	}
	T& pop() {
		len--;
		return data[len];
	}
	T& get(int i = -1) {
		if (i == -1) i = len - 1;
		return data[i];
	}

};

double calcExp(stack<elem> arr) {

	if (arr.len == 1) {
		elem &eA = arr.get(0);
		return (eA.isInv ? -1 : 1)*eA.value;
	}
	for (int i = arr.len - 1; i >= 0; i -= 2) {
		elem &eA = arr.get(i - 2);
		elem &eO = arr.get(i - 1);
		elem &eB = arr.get(i);
		if (eO.opt != '*' && eO.opt != '/') continue;

		double A = (eA.isInv ? -1 : 1)*eA.value;
		double B = (eB.isInv ? -1 : 1)*eB.value;

		if (eO.opt == '/')
			eA.value = A / B;
		if (eO.opt == '*')
			eA.value = A * B;
		eA.isInv = false;
		eO.opt = '+';
		eB.value = 0;
	}
	for (int i = arr.len - 1; i >= 0; i -= 2) {
		elem &eA = arr.get(i - 2);
		elem &eO = arr.get(i - 1);
		elem &eB = arr.get(i);

		double A = (eA.isInv ? -1 : 1)*eA.value;
		double B = (eB.isInv ? -1 : 1)*eB.value;

		if (eO.opt == '+') eA.value = A + B;
		if (eO.opt == '-') eA.value = A - B;
		eA.isInv = false;
	}
	return arr.get(0).value;

}

double calculate(string expression, string &error) {

	expression = "(" + expression + ")";
	//(8+6))(-2-(2*2-4*-568*-10))/2*5)

	//|s|
	//|s|
	//|-2 n| |- o| |s| 
	//|2 n| |* o| | 2 n| |- o| |4 n| |* o| |-5 n| |* o| |-10 n|
	stack<stack<elem>> lastsSt;
	stack<elem> st;
	elem el;

	string numBuff;
	char lastElem = 's';

	for (int i = 0; i < expression.length(); i++) {
		char ch = expression[i];
		if (ch == '(' && (lastElem != 'n' && lastElem != 'e')) {

			lastElem = 's';
			st.push(el);
			lastsSt.push(st);
			st = *(new stack<elem>);
			el = *(new elem);

		}
		else if (ch == '-' && (lastElem == 's' || lastElem == 'o')) {

			lastElem = 'i';
			el.isInv = true;

		}
		else if (ch >= '0' && ch <= '9' && (lastElem != 'e')) {

			lastElem = 'n';
			numBuff += ch;
		}
		else {
			if (lastElem == 'n') {

				el.value = stoi(numBuff);
				st.push(el);
				numBuff = "";
				el = *(new elem);

			}
			if (ch == ')' && (lastElem == 'n' || lastElem == 'e')) {

				if (st.len == 0) {
					error = "EMPTY EXPRESSION (POS: " + to_string(i) + ")";
					return 0;
				}
				if (lastsSt.len < 1 && i < expression.length() - 1) {
					error = "TOO MANY CLOSE EXPRESSION (POS: " + to_string(i) + ")";
					return 0;
				}

				lastElem = 'e';
				double r = calcExp(st);
				st = lastsSt.pop();
				st.get().value = r;
				el = *(new elem);

			}
			else if ((ch == '+' || ch == '-' || ch == '*' || ch == '/') && (lastElem == 'n' || lastElem == 'e')) {

				lastElem = 'o';
				el.opt = ch;
				st.push(el);
				el = *(new elem);

			}
			else if (lastElem == 'n' || lastElem == 'e') {
				error = "WAITING OPERATOR (POS: " + to_string(i) + ")";
				return 0;
			}
			else {
				error = "WAITING NUMBER OR EXPRESSION (POS: " + to_string(i) + ")";
				return 0;
			}
		}
	}
	if (lastsSt.len > 0) {
		error = "NOT ALL EXPRESSION CLOSE";
		return 0;
	}
	return st.get(0).value;

}

int main()
{
	while (true) {

		string error;
		string exp;
		cout << "Enter expression: ";
		cin >> exp;
		double res = calculate(exp, error);
		if (error == "") 
			cout << "Result: " << res << endl;
		else 
			cout << "Error: " << error << endl;
		cout << endl;

	}
	return 0;
}
