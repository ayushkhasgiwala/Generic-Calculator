#include<iostream>
#include<climits>
#include<cmath>
#include <iomanip>
#define MAX LLONG_MAX 
using namespace std;

template<class T>
class stack
{
    public: long long int index;
            T *a;
    public: stack(long long int n)
            {
                a=new T[n];
                index=-1;
            }

            void push(T x)
            {
               index++;
               a[index]=x; 
            }

            T pop()
            {
                T z = a[index];
                index--;
                return z;
            }

            bool isEmpty()
            {
                if(index==-1)
                    return true;
                else return false;
            }

            int size()
            {
                return index;
            }

            T top()
            {
                return a[index];
            }
};


int precedence(char c)
{
    if(c=='+' || c=='-')
    {
        return 1;
    }
        
    else if (c=='*' || c=='/' || c=='%')
    {
        return 2;
    }
    return 0;
}

double calci(string s)
{
    long long int n=s.length();
    stack<char> st1(n);   //stack for storing operators
    stack<double> st2(n);  //stack for storing values

    for(long long int i=0;i<n;i++)
    {
        if(s[i]=='(')  // if the input is (
        {
            //cout<<s[i]<<" ";
            st1.push(s[i]);
            //cout<<st1.top()<<" ";
        }

        //for the int or double value
        if((s[i]>='0' && s[i]<='9')|| s[i]=='.')
        {
            double num=0;
            //cout<<s[i]<<" ";
            //calculating the integral part
            while(i<n && (s[i]>='0' && s[i]<='9'))
            {
                num=num*10 + (s[i]-'0');
                i++;
            }
            //check if decimal part is there 
            double count=0,dec=0;
            if(i<n && s[i]=='.')
            {
                i++;
                while(i<n && (s[i]>='0' && s[i]<='9'))
                {
                    dec=dec*10 + (s[i]-'0');
                    i++;
                    count++;
                }
            }

            double val=num+(dec/pow(10,count));
            //cout<<val<<" ";
            st2.push(val);   // pushing the int/double in the second stack
            //cout<<st2.top()<<" ";
        }

        // if the current character int the string is operator
        if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='%')
        {
            //cout<<"hello"<<" ";
            if(st1.isEmpty()==true || precedence(s[i])>precedence(st1.top()))
            {
                //cout<<s[i];
                st1.push(s[i]);
                //cout<<st1.top();
            }
            else
            {
                while(st1.isEmpty()!=true && precedence(s[i])<=precedence(st1.top()))
                {
                    double v1=st2.pop();
                    double v2=st2.pop();
                    char op=st1.pop();
                    double res;
                    if(op=='+') res=v1+v2;
                    else if(op=='-') res=v2-v1;               
                    else if(op=='*') res=v1*v2;
                    else if(op=='/') res=v2/v1;
                    else if(op=='%')
                    {
                        //res=(long long int)(v2)%(long long int)(v1);
                        res=fmod(v2,v1);
                    }
                    st2.push(res);
                }
                st1.push(s[i]);
            }
        }

        //if the current element is a closing parenthesis i.e. ')'
        if(s[i]==')')
        {
            while(st1.isEmpty()!=true && st1.top()!='(')
            {
                double v1=st2.pop();
                double v2=st2.pop();
                char op=st1.pop();
                double res;
                if(op=='+') res=v1+v2;
                else if(op=='-') res=v2-v1;               
                else if(op=='*') res=v1*v2;
                else if(op=='/') res=v2/v1;
                else if(op=='%')
                {
                    //res=(long long int)(v2)%(long long int)(v1);
                    res=fmod(v2,v1);
                }
                st2.push(res);
            }
            if(st1.isEmpty()!=true)
                char temp=st1.pop();
        }
    }

    //once the string is completely traversed we will now perform calculations one by one by emptying the stack;
    while(st1.isEmpty()!=true)
    {
        double v1=st2.pop();
        double v2=st2.pop();
        char op=st1.pop();
        double res;
        if(op=='+') res=v1+v2;
        else if(op=='-') res=v2-v1;               
        else if(op=='*') res=v1*v2;
        else if(op=='/') res=v2/v1;
        else if(op=='%')
        {
            //res=(long long int)(v2)%(long long int)(v1);
            res=fmod(v2,v1);
        }
        st2.push(res);
    }

    return st2.top();
}

int main()
{
    string s;
    cin>>s;
    double res= calci(s);
    //cout<<res;
    if(ceil(res)==floor(res))
    {
        long long int r=res;
        cout<<r;
    }
    else cout<<fixed <<setprecision(5)<<res;
    
}