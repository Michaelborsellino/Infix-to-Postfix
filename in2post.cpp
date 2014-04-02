/*
Michael Borsellino

Project description:
In this program, we were asked to implement a stack using
any STL container of our choice. Also, we were asked to 
use this stack to create a program that converts any 
entered infix expression to postfix and solve it.
Specifics:
- Must be able to accept functions as space separated entities
- Must be able to do error checking on formula
- Must be able to calculate double values
- Must be able to accept information via command line 
  file redirection
*/

#include<iostream>
//#include<stack>
#include<sstream>
#include<string>
#include<vector>
#include<cctype>
#include<cmath>
#include"stack.h"
using namespace std;
using namespace cop4530;

double convertSolve (vector<string>invect);

int main()
{
  double total;
  int parect1 = 0, parect2 = 0;
  string exit, input, proxy, proxy2;
  vector<string> validation, invect;
  bool sbserror = false, baderror = false, size1 = false;
    cout<<"Please enter an infix expression ('exit' to quit):\n";
  while((exit != "exit") && (getline(cin,input)))
  {
    //Pushing space separated strings onto vector for data validation
    if(input == "exit")
      break;
    istringstream inputstream(input);
  //*********storing data***************
    while(inputstream>>proxy)
    {
      validation.push_back(proxy);
    }

//first error check for empty line
if(validation.empty())
  cout<<"\nEmpty Expression\n";
else
{
    //case for sole operand
    if(validation.size() == 1)
    {
      proxy == validation.at(0);
      if(isalnum(proxy[0]))
        size1 = true;
    }
    //checks parentheses count to verify later in error checking block
    for(unsigned int i = 0; i < validation.size(); ++i)
    {
      proxy = validation.at(i);
      if(proxy == "(")
        ++parect1;
      else if(proxy == ")")
        ++parect2;
    }
    //**********error checking block***************
    //checks for side by side operators or operands that would invalidate the expression
    for(unsigned int i = 0, j = 1; j < validation.size(); ++i, ++j)
    {
      proxy = validation.at(i);
      proxy2 = validation.at(j);
      if((proxy == "(")&&(!isalnum(proxy2[0])))
        sbserror = true;
      else if((!isalnum(proxy[0])&&(proxy2 == ")")))
        sbserror = true;
      else if ((!isalnum(proxy[0])&&(!isalnum(proxy2[0])))&&((proxy != ")")&&
              (proxy != "(") && (proxy2 !=")") && (proxy2 !="(")))
        sbserror = true; 
      else if(((!isalnum(proxy[0]))&&(!isalnum(proxy2[0])))&&(proxy != ")"))
        sbserror = false;//here
      else if(((!isalnum(proxy[0]))&&(!isalnum(proxy2[0])))&&(proxy2 != "("))
        sbserror = false;//here
      else if((isalnum(proxy[0]))&&(isalnum(proxy2[0])))
        sbserror = true;
      else if((!isalnum(proxy[0]))&&(!isalnum(proxy2[0])))
        sbserror = true;
    }
     //case where size = 1
     if(size1 == true)
     {
       cout<<"Postfix conversion: "<<validation.at(0)<<endl;
       baderror = true;
     }
     //side by side error message
     else if(sbserror == true)
     {
       cout<<"Error: side by side operator/operand\n";   
       baderror = true;
     }
     //missing parentheses error message
     else if(parect1 != parect2)
     {
       cout<<"Error: Missing parentheses\n";
       baderror = true;
     }
     //checks for an incomplete expression
     proxy = validation.at(validation.size() - 1);
     if((!isalnum(proxy[0]) && (proxy != ")"))&&(baderror == false))
     {
       cout<<"Error: infix expression left open\n";
       baderror = true;
     }
     proxy = validation.at(0);
      if((!isalnum(proxy[0]) && (proxy != "("))&&(baderror == false))//herer
     {
       cout<<"Error: infix expression left open\n";
       baderror = true;
     }
  //**********Output block (ouputs the expression in postfix notation)***********
  if(baderror == false)
  {
    cout<<"Postfix Conversion: ";
    Stack<string> instack; 
    unsigned int counter = 0;
    while(counter < validation.size())
    {
     //if proxy is a ( or operand, push it onto the stack
      proxy = validation.at(counter);
      if((proxy == "(")||(isalnum(proxy[0])))
        instack.push(proxy);
      //if it is a lower level operator, output and
      // pop everything, then push it on top
      else if((proxy =="+")||(proxy =="-"))
      {
        while((!instack.empty())&&(instack.top() != "("))
        {
          cout<<instack.top()<<" ";
          invect.push_back(instack.top());
          instack.pop();
        }
        instack.push(proxy);
      }
      //if it is a higher level operator, output and
      // pop everything, till you hit a lower one
      //then put it on top
      else if(((proxy =="*")||(proxy =="/")))
      {
        while( (!instack.empty())&&((instack.top() != "("))
                &&(instack.top() != "-")&&(instack.top() != "+"))
        {
          cout<<instack.top()<<" ";
          invect.push_back(instack.top());
          instack.pop();
        }
        instack.push(proxy);
      }
      //if it is a ) pop and display everything till ( is found
      else if(proxy == ")")
      {
        while(instack.top() != "(")
        {
          cout<<instack.top()<<" ";
          invect.push_back(instack.top());
          instack.pop();
        }
      }
      ++counter;
    
    }//control while loop
     //display anything trapped in the loop    
     while(!instack.empty())
     {
       if(instack.top() == "(")
         instack.pop();
       else
       {
         cout<<instack.top()<<" ";
          invect.push_back(instack.top());
         instack.pop();
       }
     }
     //**********End of infix to postfix conversion*******
     //grabs the total in function below
     total = convertSolve(invect);
     cout<<"\nSolution: ";
     //takes into account any variables in function
     if(total == 0.00000000093)
     {
       for(unsigned int i = 0; i < invect.size(); i++)
       {
         cout<<invect.at(i);
         cout<<" ";
       }
       cout<<endl;
     }
     else
       cout<<total<<endl;
   
  }//big if end
}//mega big else check
   //resets all values for the next run through
   invect.clear();
   size1 = false;
   baderror = false;
   sbserror = false;
   parect1 = 0;
   parect2 = 0;
   validation.clear();
   //prompts user for next line of text
    cout<<"Please enter an infix expression ('exit' to quit):\n";

  }//end massive while loop

}
    
//converts from string to double and totals up the result.
double convertSolve (vector<string>invect)
{
  string proxy2;
  int decimaltracker = 0;
  Stack<double> opperandstack;//here
  vector<double> convect(invect.size());
  double total;
  
  
  for(unsigned int i = 0; i < invect.size(); ++i)
  {
    
    string proxy = invect.at(i);
    
    //if the base character is a number or letter it enters into the conversion
    //sequence, else it goes down for operator cases 
    if(isalnum(proxy[0]))
    {
      for(unsigned int p = 0; p < proxy.length(); ++p)
      {
        //if it is a variable, the function returns to main
        if(isalpha(proxy[0]))
          return 0.00000000093;
        else if(isdigit(proxy[p]))
        {
          //if there hasn't been a decimal read yet, the digit is adjusted
          //based on it's char ascii value and then slotted with base 10 rules
          if(decimaltracker == 0)
          {
            convect[i] = convect[i] +
                   ((proxy[p] - 48)* pow(10.0,proxy.length() - (p + 1)));
          }
          //if there has, then the function slots the digit by dividing with
          //powers of 10
          else
          {
	    convect[i] = convect[i] + 
                        ((proxy[p] - 48) / pow(10.0,(proxy.length() - p)));
          }
        }
        //checks for decimal
        else if(proxy[p] == '.')
        {
          decimaltracker = p;
          convect[i] = convect[i] / pow(10.0, (proxy.length() - p));
        }
          
      }
      //reset values and push total onto the stack
        decimaltracker = 0;
      opperandstack.push(convect[i]);
    }

    //block of statements that solve for total using stack and given rules
    else if(proxy == "+")
    {
      total = opperandstack.top();
      opperandstack.pop();
      total = total + opperandstack.top();
      opperandstack.pop();
      opperandstack.push(total);
    }
    else if(proxy == "-")
    {
      total = opperandstack.top();
      opperandstack.pop();
      total = opperandstack.top() - total;
      opperandstack.pop();
      opperandstack.push(total);
    }   
    else if(proxy == "*")
    {
      total = opperandstack.top();
      opperandstack.pop();
      total = total * opperandstack.top();
      opperandstack.pop();
      opperandstack.push(total);
    }
    else if(proxy == "/")
    {
      total = opperandstack.top();
      opperandstack.pop();
      total = opperandstack.top()/ total;
      opperandstack.pop();
      opperandstack.push(total);
    }
  }
  return total;
}
 
