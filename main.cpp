#include <iostream>
#include <string>
#include "Stack.h"
#include "IntStack.h"
#include "IntQueue.h"

using namespace std;

void intPrinter(int &value) {
    cout<<"Value: "<<value<<endl;
}

void stringPrinter(string &value) {
    cout<<"Value: "<<value<<endl;
}

int main() {
    auto iStack = IntStack();
    iStack.push(10); // 10
    iStack.push(20); // 20, 10
    iStack.pop();         // 10
    iStack.push(30); // 30, 10
    iStack.forEach(intPrinter);  //30, 10
    cout << iStack.pop().value()<<endl; //30
    cout << iStack.pop().value()<<endl; //10
    cout << iStack.pop().has_value()<<endl; // 0 / false

    auto stack = Stack<string>{};
    stack.push("Gamma");    // Gamma
    stack.push("Beta");     // Beta, Gamma
    stack.pop();                 // Gamma
    stack.push("Beta");     // Beta, Gamma
    stack.push("Alpha");    // Alpha, Beta, Gamma
    cout << stack.pop().value()<<endl; // Alpha
    stack.forEach(stringPrinter); // Beta, Gamma

    auto dStack = Stack<double>{};
    cout << dStack.pop().has_value() << endl;
    stack.push("Info");
    cout << stack.peek().value() << endl;


    auto iQueue = IntQueue{};

}
