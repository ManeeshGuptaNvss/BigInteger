#include <iostream>
#include <string>
using namespace std;
struct Node
{
	string data;
	struct Node *link;
	Node(string data)
	{
		this->data = data;
	}
};
class Stack
{
public:
	Node *top;
	Stack()
	{
		top = NULL;
	}
	void push(string data)
	{
		struct Node *temp;
		temp = new Node(data);

		if (!temp)
		{
			cout << "\nHeap Overflow";
			exit(1);
		}
		// Put top pointer reference into temp link
		temp->link = top;

		// Make temp as top of Stack
		top = temp;
	}

	// Utility function to check if
	// the stack is empty or not
	bool isEmpty()
	{
		return top == NULL;
	}

	// Utility function to return top element in a stack
	string peek()
	{

		// Check for empty stack
		if (!isEmpty())
			return top->data;
		else
			exit(1);
	}

	// Utility function to pop top
	// element from the stack
	void pop()
	{
		struct Node *temp;

		// Check for stack underflow
		if (top == NULL)
		{
			cout << "\nStack Underflow" << endl;
			exit(1);
		}
		else
		{
			temp = top;
			// Assign second node to top
			top = top->link;
			// Destroy connection between
			// first and second
			temp->link = NULL;
			// Release memory of top node
			delete temp;
		}
	}
	// Function to print all the
	// elements of the stack
	void display()
	{
		struct Node *temp;

		// Check for stack underflow
		if (top == NULL)
		{
			cout << "\nStack Underflow";
			exit(1);
		}
		else
		{
			temp = top;
			while (temp != NULL)
			{

				// Print node data
				cout << temp->data << "-> ";
				temp = temp->link;
			}
		}
	}
};
string addition(string a, string b)
{
	int a1, b1, sum1, carry = 0;
	string result;
	int diff = ((int)a.length() - (int)b.length());
	if (diff < 0)
		diff = -diff;
	string extra = "";
	while (diff--)
		extra += '0';
	if (a.length() > b.length())
	{
		b = extra + b;
		result = a;
	}
	else
	{
		a = extra + a;
		result = b;
	}
	for (int i = a.length() - 1; i >= 0; i--)
	{
		sum1 = (a[i] - '0') + (b[i] - '0') + carry;
		result[i] = '0' + (sum1 % 10);
		carry = sum1 / 10;
	}
	if (carry)
		result.insert(0, 1, '0' + carry);
	return result;
}

string mul(string a, string b)
{
	if (a == "1")
		return b;
	else if (b == "1")
		return a;
	string mr, md, res = "0";
	mr = (a.length() >= b.length()) ? b : a;
	md = (a.length() >= b.length()) ? a : b;
	for (int i = mr.length() - 1; i >= 0; i--)
	{
		string temp = md;
		int product = 0, carry = 0;
		for (int j = md.length() - 1; j >= 0; j--)
		{
			product = (mr[i] - '0') * (md[j] - '0') + carry;
			temp[j] = '0' + (product % 10);
			carry = product / 10;
		}
		if (carry)
			temp.insert(0, 1, (carry + '0'));
		else
			carry = 0;
		temp.append((mr.length() - i - 1), '0');
		res = addition(res, temp);
	}
	return res;
}
string sub(string a, string b)
{
	int a1, b1, sub1, carry = 0;
	string result;
	int diff = ((int)a.length() - (int)b.length());
	if (diff < 0)
		diff = -diff;
	string extra = "";
	while (diff--)
		extra += '0';
	if (a.length() > b.length())
	{
		b = extra + b;
		result = a;
	}
	else
	{
		a = extra + a;
		result = b;
	}
	for (int i = a.length() - 1; i >= 0; i--)
	{
		sub1 = (a[i] - '0') - (b[i] - '0');
		if (a[i] < b[i])
		{
			a[i - 1]--;
			sub1 += 10;
		}
		result[i] = '0' + (sub1 % 10);
	}
	while (result[0] == '0' && result.length() != 1)
		result.erase(0, 1);
	return result;
}
int prec(string c)
{

	if (c == "x")
		return 2;
	else if (c == "+" || c == "-")
		return 1;
	else
		return -1;
}

string convert(string input)
{
	int operators = 0;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '+' || input[i] == '-' || input[i] == 'x')
		{
			operators++;
		}
	}
	string arr[2 * operators + 1];
	Stack opr;
	int start = 0, arr_index = 0;
	for (int i = 0; i < input.size(); i++)
	{
		string c;
		c += input[i];
		if (c == "+" || c == "-" || c == "x")
		{

			arr[arr_index++] = input.substr(start, i - start);
			start = i + 1;
			while (!opr.isEmpty() && (prec(c) <= prec((opr.peek()))))
			{
				arr[arr_index++] = opr.peek();
				opr.pop();
			}
			opr.push(c);
		}
	}
	arr[arr_index++] = input.substr(start);
	while (!opr.isEmpty())
	{
		arr[arr_index++] = opr.peek();
		opr.pop();
	}
	   for(int i=0;i<arr_index;i++){
	       cout<<arr[i]<<" ";
	   }
	   cout<<'\n';
	   opr.display();
	Stack operands;
	string result, op1, op2;
	for (int i = 0; i < arr_index; i++)
	{
		if (arr[i] == "+" || arr[i] == "-" || arr[i] == "x")
		{
			op2 = operands.peek();
			operands.pop();
			op1 = operands.peek();
			if (arr[i] == "+")
			{
				result = addition(op1, op2);
			}
			else if (arr[i] == "-")
			{
				result = sub(op1, op2);
			}
			else if (arr[i] == "x")
			{
				result = mul(op1, op2);
			}
			operands.push(result);
		}
		else
		{
			operands.push(arr[i]);
		}
	}
	return result;
}
string mod(string a, string b)
{
	if (b.length() > a.length() || (b.length() == a.length() && b.compare(a) > 0))
		a.swap(b);
	Stack s;
	while (a.length() > b.length() || (b.length() == a.length() && a.compare(b) > 0))
	{
		s.push(b);
		b = mul(b, "2");
	}
	string res;
	while (!s.isEmpty())
	{
		b = s.peek();
		if (a.length() > b.length() || (b.length() == a.length() && a.compare(b) > 0))
			a = sub(a, s.peek());
		s.pop();
	}
	return a;
}

string gcd(string a, string b)
{
	if (a == "0")
		return b;
	else if (b == "0")
		return a;
	else if (a.compare(b) == 0)
		return a;
	else if (a == "1" || b == "1")
		return "1";
	else
		return gcd(b, mod(a, b));
}

string exponent(string a, long long int n)
{
	string result = "1";
	while (n)
	{
		if (n & 1)
			result = mul(result, a);
		a = mul(a, a);
		n >>= 1;
	}
	// result="";
	return result;
}

string factorial(long long int n)
{
	string result = "1";
	if (n == 1 || n == 0)
	{
		return "1";
	}
	for (int i = 2; i <= n; i++)
	{
		result = mul(result, to_string(i));
	}
	return result;
}

// Driver Code
int main()
{

	/*
		1.Exponentiation
		2.GCD
		3. Factorial
		4. Expression Evaluation 
	*/
	int t, opr;
	t = 1;
	while (t--)
	{
		cin >> opr;

		if (opr == 1)
		{
			string num;
			int exp;
			cin >> num >> exp;
			cout << exponent(num, exp);
		}
		else if (opr == 2)
		{
			string a, b;
			cin >> a >> b;
			cout << gcd(a, b);
		}
		else if (opr == 3)
		{
			long long int n;
			cin >> n;
			cout << factorial(n);
		}
		else if (opr == 4)
		{
			string expr;
			cin >> expr;
			cout << convert(expr);
		}
	}

	return 0;
}
