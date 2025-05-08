//Fibonacci
#include<iostream>
using namespace std;

// Recursive function to find nth Fibonacci
int fibonacci(int n) {
    if(n == 1) return 0;  // base case
    if(n == 2) return 1;  // base case
    return fibonacci(n - 1) + fibonacci(n - 2);  //recursive case
}

int main() {
    int n; cin >> n; // Number of nth fibonacci number
    cout << n << "th fibonacci number is: ";
    cout << fibonacci(n) << endl;
    return 0;
}