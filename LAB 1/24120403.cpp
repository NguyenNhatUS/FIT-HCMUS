#include<iostream>
#include<stack>
#include<fstream>
#include<string.h>
#include<sstream>
#include<algorithm>

using namespace std;

string addBigNumber(string a,string b) {
    if(a.size() < b.size()) swap(a,b);
    string res = "";
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    int carry = 0;
    for(int i = 0;i < b.size();i++) {
        int sum = carry;
        sum = sum + (a[i] - '0') + (b[i] - '0');
        res += (sum % 10) + '0';
        carry = sum / 10;
    }
    for(int i = b.size();i < a.size();i++) {
        int sum = carry;
        sum = sum + (a[i] - '0');
        res += (sum % 10) + '0';
        carry = sum / 10;
    }
    if(carry) {
        res += '1';
    }
    reverse(res.begin(),res.end());
    return res;
}

string substractBigNumber(string a,string b) {
    bool flag = true;
    if(a.size() < b.size() || (a.size() == b.size() && a < b)) {
        swap(a,b);
        flag = false;
    }
    string res = "";
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    int borrow = 0;
    for(int i = 0;i < b.size();i++) {
        int diff = (a[i] - '0') - borrow - (b[i] - '0');
        if(diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        res += (diff + '0');
    }
    for(int i = b.size();i < a.size();i++) {
        int diff = (a[i] - '0') - borrow;
        if(diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        res += (diff + '0');
    }
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(res.begin(), res.end());
    if(!flag) {
        res = '-' + res;
    }
    return res;
}

string subtractStrings(string a, string b) {
    string res = "";
    int borrow = 0;
    int i = a.length() - 1, j = b.length() - 1;
    while (i >= 0) {
        int diff = a[i] - '0' - borrow;
        if (j >= 0) diff -= (b[j--] - '0');
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else borrow = 0;
        res += (diff + '0');
        i--;
    }
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

string multiplySmallNumber(string a,string b) {
    return to_string(stoi(a) * stoi(b));
}

string shiftLeft(string s, int n) {
    return s + string(n, '0');
}

void makeEqualLength(string& a,string& b) {
    int n = max(a.size(),b.size());
    if(n % 2) n++;
    if(a.size() != n) {
        a = string(n - a.size(),'0') + a;
    }
    if(b.size() != n) {
        b = string(n - b.size(),'0') + b;
    }
}               

string deleteLeadingZeros(string s) {
    int i = 0;
    while (i < s.size() - 1 && s[i] == '0') i++;
    return s.substr(i);
}

string Karatsuba(string x,string y) {
    makeEqualLength(x,y);
    int n = x.size();
    if(n <= 2) return multiplySmallNumber(x,y);
    int m = n / 2;
    string xL = x.substr(0, m);
    string xR = x.substr(m);
    string yL = y.substr(0, m);
    string yR = y.substr(m); 

    string P1 = Karatsuba(xL,yL);
    string P2 = Karatsuba(xR,yR);
    string xLplusxR = addBigNumber(xL,xR);
    string yLplusyR = addBigNumber(yL,yR);
    string P3 = Karatsuba(xLplusxR,yLplusyR);
    string middle = subtractStrings(subtractStrings(P3,P1),P2);

    string res = addBigNumber(addBigNumber(shiftLeft(P1, 2 * (n - m)), shiftLeft(middle, n - m)), P2);
    return res;
}

string divideBigNumber(string a,string b) {
    string res = "";
    string curr = "";
    for(char digit : a) {
        curr += digit;
        curr = deleteLeadingZeros(curr);
        int cnt = 0;
        while(curr.size() > b.size() || (curr.size() == b.size() && curr >= b)) {
            curr = substractBigNumber(curr,b);
            cnt++;
        }
        res += (cnt + '0');
    }
    return deleteLeadingZeros(res);
}

bool isNegative(string s) {
    return s[0] == '-';
}

string solveOperator(string num1,string num2,char op) {
    string res = "";
    if(op == '+') {
        if(isNegative(num1) && isNegative(num2)) {
            num1 = num1.substr(1);
            num2 = num2.substr(1);
            res = addBigNumber(num1,num2);
            res = '-' + res;
        }
        else if(isNegative(num1)) {
            num1 = num1.substr(1);
            res = substractBigNumber(num2,num1);
        }
        else if(isNegative(num2)) {
            num2 = num2.substr(1);
            res = substractBigNumber(num1,num2);
        }
        else {
            res = addBigNumber(num1,num2);
        }
    }
    else if(op == '/') {
        bool flag = true;
        if(isNegative(num1) && isNegative(num2)) {
            num1 = num1.substr(1);
            num2 = num2.substr(1);
        }
        else if(isNegative(num1) || isNegative(num2)) {
            if(isNegative(num1)) {
                num1 = num1.substr(1);
            }
            else {
                num2 = num2.substr(1);
            }
            flag = false;
        }
        if(num2 == "0") return "Error";
        if(num1.size() < num2.size()) return "0";
        else if(num1.size() == num2.size()) {
            if(num1 < num2) return "0";
        }
        res = divideBigNumber(num1,num2);
        if(!flag) res = '-' + res;
    }
    else if(op == '*') {
        bool flag = true;
        if(isNegative(num1) && isNegative(num2)) {
            num1 = num1.substr(1);
            num2 = num2.substr(1);
        }
        else if(isNegative(num1) || isNegative(num2)) {
            if(isNegative(num1)) {
                num1 = num1.substr(1);
            }
            else {
                num2 = num2.substr(1);
            }
            flag = false;
        }
        res = deleteLeadingZeros(Karatsuba(num1,num2));
        if(!flag) res = '-' + res;
    }
    else {
        if(isNegative(num1) && isNegative(num2)) {
            num1 = num1.substr(1);
            num2 = num2.substr(1);
            res = substractBigNumber(num2,num1);
        }
        else if(isNegative(num1)) {
            num1 = num1.substr(1);
            res = addBigNumber(num1,num2);
            res = '-' + res;
        }
        else if(isNegative(num2)) {
            num2 = num2.substr(1);
            res = addBigNumber(num1,num2);
        }
        else {
            res = substractBigNumber(num1,num2);
        }
    }
    return res;
}

int prec(char c) {
    if(c == '*' || c == '/') return 2;
    if(c == '+' || c == '-') return 1;
    return 0;
}

string removeSpaces(string s) {
    string res = "";
    for(char c : s) {
        if(c != ' ') res += c;
    }
    return res;
}

string solve(string s) {
    s = removeSpaces(s);
    stack<string> nums;
    stack<char> ops;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (isdigit(c) || (c == '-' && (i == 0 || s[i - 1] == '('))) {
            string num = "";
            if (c == '-') num += c, i++;
            while (i < n && isdigit(s[i])) {
                num += s[i++];
            }
            nums.push(num);
            i--; 
        }

        else if (c == '(') {
            ops.push(c);
        }

        else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                if (nums.size() < 2) return "Error";
                string b = nums.top(); nums.pop();
                string a = nums.top(); nums.pop();
                char op = ops.top(); ops.pop();

                string res = solveOperator(a, b, op);
                if (res == "Error") return res;
                nums.push(res);
            }
            if (ops.empty()) return "Error";
            ops.pop(); 
        }

        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!ops.empty() && ops.top() != '(' && prec(ops.top()) >= prec(c)) {
                if (nums.size() < 2) return "Error";
                string b = nums.top(); nums.pop();
                string a = nums.top(); nums.pop();
                char op = ops.top(); ops.pop();

                string res = solveOperator(a, b, op);
                if (res == "Error") return res;
                nums.push(res);
            }
            ops.push(c);
        }
        else return "Error";
    }

    while (!ops.empty()) {
        if (nums.size() < 2) return "Error";
        string b = nums.top(); nums.pop();
        string a = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();

        string res = solveOperator(a, b, op);
        if (res == "Error") return res;
        nums.push(res);
    }
    if(nums.size() != 1) return "Error";
    return nums.top();
}

// g++ 24120403.cpp -o 24120403.exe
// 24120403.exe tests.txt output_24120403.txt 
int main(int argc, char* argv[]) { 
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }
    string fileInput = argv[1];
    string fileOutput = argv[2];
    string line;
    ifstream fin(fileInput);
    ofstream fout(fileOutput);
    while (getline(fin, line)) {
        fout << solve(line) << endl;
    }
    fin.close();
    fout.close();
    return 0;
}


