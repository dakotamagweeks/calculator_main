#include "calculator.h"
#include "mystack.cpp"
//---------------------------------------------------------------------------------
void Calculator::start()		//starts the calculator
{
	string exp;
	string postfix;
	char ans = 'n';

	Do
{
		cout<<"\nEnter an infix expression: ";	// asks for input
		getline(cin, exp);
		if(Calculator::check_match(exp)){
			postfix = infix_postfix(exp);
			cout<<postfix<<endl;
			evaluate_postfix(postfix);
			cout<<endl<<endl;
	
		}else{
			cout<<"Invalid Expression"<<endl;
			continue;
		}
		cout<<endl<<endl;
		cout<<"Run Again? [y or n]: ";
		cin >>ans;
		if(ans == 'y')
			continue;
		else
			break;

	}
while(true);
}
//----------------------------------------------------------------------------------
bool Calculator::check_match(string exp)		//Checks whether expression is valid
{
	int opencnt=0;					
	int closecnt=0;		
	int operandcnt=0;
	int operatorcnt=0;

	char ch;
	int n = exp.length();
	for(int i = 0; i<n;){
		ch = exp[i];
		if(ch == ' ')
			i++;
		else if( ch == '(' )
{
			i++;
			opencnt++;
		}
else if(ch == ')')
{
			i++;
			closecnt++;
		}
else if(ch == '+' || ch == '-' || ch == '*' || ch== '/')
{
			i++;
			operatorcnt++;
		}
Else
{
			while (isdigit(ch = exp[i]))
{
				i++;
			}
			operandcnt++;
		}
		
	}
	cout<<operandcnt<<" "<<operatorcnt<<endl;
	if((opencnt == closecnt) && (operandcnt == (operatorcnt + 1)))
 {
		return true;
	}
Else
{
		return false;
	}
}
//---------------------------------------------------------------------------------
string Calculator::infix_postfix(string str)		//passes the infix and converts to postfix
{
		mystack <char> s;
		string postfix;
		char ch;
		int n = str.length();
		int i;

		for(i = 0; i<n; i++)			//Checks the characters of the string
		{
			ch=str[i];		
			if(isdigit(ch))
{
				postfix += ch;
				while(isdigit(ch = str[i+1]))
{
					postfix += ch;
					i++;
				}
				postfix += " ";
			}
else if(ch == '(')
{
				s.push(ch);
			}
else if(ch == ')')
{
				while(!s.is_empty() && s.get_top() != '(')
{
					postfix += s.get_top();
					s.pop();
				}
				s.pop();
				postfix += " ";
			}
else if(ch == ' ')
				;
			Else
{
				if(Calculator::priority(ch) > Calculator::priority(s.get_top()))
{
					s.push(ch);
				}
				else if(s.is_empty())
{
					s.push(ch);
				}
				Else
{
					while(Calculator::priority(ch) <= Calculator::priority(s.get_top()) && !s.is_empty() && s.get_top() != '(')
{
						postfix += s.get_top();
						s.pop();
					}
					s.push(ch);
					postfix += " ";
				}
			}
		}
		while(!s.is_empty())
{
			postfix += s.get_top();
			s.pop();
		}
		return postfix;
}
//----------------------------------------------------------------------------------
void Calculator::evaluate_postfix(string post)		//evaluates the postfix expression
{
	mystack <int> s;
	int n = post.length();
	int i;
	int op1;
	int op2;
	int temp;
	cout <<"The postfix expression is: "<<post<<endl;

	for(i = 0; i < n;)
{
		if(post[i] == ' ')
			i++;
		else if(isdigit(post[i]))
{
			temp = post[i] - '0';
			while( isdigit(post[i+1]))
{
				temp = temp * 10 + post[i+1]-'0';
				i++;
			}
			s.push(temp);
			i++;
		}
Else
{
			cout<<"\nOperator: "<<post<<endl;	  // this makes the opeerations run 
			switch (post[i])
{
				case '-': op1 = s.get_top();
					s.pop();
					op2 = s.get_top();
					s.pop();
					s.push(op2-op1);
					break;
				case '+': op1 = s.get_top();
					s.pop();
					op2= s.get_top();
					s.pop();
					s.push(op2+op1);
					break;
				case '*': op1 = s.get_top();
					s.pop();
					op2 = s.get_top();
					s.pop();
					s.push(op2*op1);
					break;
				case '/': op1=s.get_top();
					s.pop();
					op2 = s.get_top();
					s.pop();
					s.push(op2/op1);
					break;
				default: cout<<"\nInvalid Expression\n";
			}
			i++;
		}
	}
	if(!s.is_empty())
		cout<<"\nThe Result is: "<<s.get_top()<<endl;
	Else
{
		cout<<"\nCalculation error.\n";
		cout<<endl<<endl;
	}
}
//---------------------------------------------------------------------------------
int Calculator::priority(char temp)	// this sets the ‘*’ and ‘/’ at a higher proirity then ‘+’ and ‘-’
{
	if(temp == '*' || temp == '/')
		return 1;
	else
		return 0;
}
//---------------------------------------------------------------------------------
