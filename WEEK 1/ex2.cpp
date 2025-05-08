//Factorial
#include<iostream>
using namespace std;

//Recursive function to find a factorial of a number n
int factorial(int n) {
    if(n == 0 || n == 1) return 1;   // base case
    return n * factorial(n - 1);   // recursive case  (n! = n * (n - 1)!)
}

int main() {
    int n; cin >> n; // value of n
    cout << "Factorial of " << n << " is: ";
    cout << factorial(n) << endl;
    return 0;
}