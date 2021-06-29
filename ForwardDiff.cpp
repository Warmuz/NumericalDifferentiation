#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

double function(double x)
{
    //return exp(cos(x));
    return exp(x-1)+pow(x,2)-2;
    //return 10*pow(x,5)-4*pow(x,4)+24*pow(x,3)-190*pow(x,2)+4.5*x;
}


double function_derivative1(double x)
{
    //return (sin(x)*(-exp(cos(x))));
    return 1/(pow(x,2)+1);
    //return 50*pow(x,4)-16*pow(x,3)+72*pow(x,2)-380*x+4.5;
}

double function_derivative2(double x)
{
    //return (exp(cos(x)))*((sin(x)*sin(x))-cos(x));
    return -2/pow((1+pow(x,2)),2);
    //return 200*pow(x,3)-48*pow(x,2)+144*x-380;
}


double* difference_operators(int n, double h, double x0)
{
    double* x;
    double** operators;
    double* terms;
  
    
    
    x = new double[n+2];
    
    for (int i = 0; i < n+2; i++)
    {
        x[i] = x0 + i*h;
        cout<<"x"<<i<<":"<<x[i]<<endl;
    }
    
    operators = new double*[n+1];
    
    for(int i = 0; i < n+1; i++)
    {
        operators[i] = new double[n-i+1];
    }
    
    
    for(int i = 0; i < n+1; i++)
    {
        operators[0][i] = function(x[i+1])-function(x[i]);
    }
    
    
    for (int i = 1; i < n+1; i++)
    {
        for (int j = 0; j < n-i+1; j++)
        {
            operators[i][j] = operators[i-1][j+1]-operators[i-1][j];
        }
    }
    
    terms = new double[n+1];
    
    for (int i = 0; i < n+1; i++)
    {
        terms[i] = operators[i][0];
    }
    
    
    for (int i = 0; i < n+1; i++)
    {
        delete []operators[i];
    }
    
    delete []operators;
    
    
    delete []x;
    
    return terms;
}


double derivative1(double n, double h, double x0)
{
    double* terms;
    double value;
    double absolute_error=0;
    double relative_error=0;
  
   
    cout<<"-----------FIRST DERIVATIVE-----------"<<endl;
        value = 0;
        terms = difference_operators(n, h, x0);
        
    for (int i = 0; i < n; i++)
    {
        value += pow(-1,i)/(double)(i+1)*terms[i];
    }
        
        value = 1/h*value;
    
    
    cout<<"f'(x0) analytical: "<<function_derivative1(x0)<<endl;
    absolute_error=fabs((function_derivative1)(x0)-value);
    relative_error=fabs(absolute_error)/(fabs((function_derivative1)(x0)));
    
    cout<<"Absolute error "<<absolute_error<<endl;
    cout<<"Relative error "<<relative_error<<endl;
        
    delete []terms;
    
    cout<<"f'(x0) numerical: "<<value<<endl;
    cout<<endl;
    return value;
}

double derivative2(double n, double h, double x0){
    double* terms;
    double value=0;
    double absolute_error=0;
    double relative_error=0;
    cout<<"-----------SECOND DERIVATIVE-----------"<<endl;
    double* b;
    double* a;
    
    a = new double[n];
    a[0] = 1;
    
    for (int i = 1; i < n; i++)
    {
        b = new double[i+1];
        
        for (int j = 0; j < i+1; j++)
        {
            b[j] = pow(-1,j)/(j+1);
        }
        
        a[i] = 0;
        
        for (int j = 0; j <= i; j++)
        {
            a[i] += b[j]*b[i-j];
        }
        delete []b;
    }
    
    terms = difference_operators(n+1, h, x0);
    
    for (int i = 0; i < n; i++)
    {
        value += a[i]*terms[i+1];
    }
    
    value = 1/(h*h)*value;
    
    cout<<"f''(x0) analytical: "<<function_derivative2(x0)<<endl;
    absolute_error=fabs((function_derivative2)(x0)-value);
    relative_error=fabs(absolute_error)/(fabs((function_derivative2)(x0)));
    
    cout<<"Absolute error "<<absolute_error<<endl;
    cout<<"Relative error "<<relative_error<<endl;

    delete []terms;
    delete []a;
    cout<<"f''(x0) numerical: "<<value<<endl;
    return value;
}

int main()
{
    double n, x0, h;
    
    cout<<"Give point x0: ";
    cin>>x0;
    
    cout<<endl<<"Give steps n: ";
    cin>>n;
    
    cout<<endl<<"Give fixed step h: ";
    cin>>h;
    cout<<endl;
    
    derivative1(n, h, x0);
    derivative2(n, h, x0);
   
    
    return 0;
}
