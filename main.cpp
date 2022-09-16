#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"
#include "IntStack.h"
#include "IntQueue.h"
#include "SortedBinTree.h"

using namespace std;

void intPrinter(int &value) {
    cout<<value<<" ";
}

void stringPrinter(string &value) {
    cout<<value<<" ";
}

void decreaseByOne(int &value) {
    value--;
}

int main() {
    auto iStack = IntStack();  // iStack: empty
    iStack.push(10); // iStack: 10
    iStack.push(20); // iStack: 20, 10
    iStack.pop();         // iStack: 10
    iStack.push(30); // iStack: 30, 10
    iStack.forEach(intPrinter);  //Prints: 30, 10
    cout<<endl;
    cout << iStack.pop().value()<<endl; //Prints: 30  iStack: 10
    cout << iStack.pop().value()<<endl; //Prints: 10  iStack: empty
    cout << iStack.pop().has_value()<<endl; //Prints: 0 /false/

    auto stack = Stack<string>{}; // Stack: empty
    stack.push("Gamma");     // Stack: Gamma
    stack.push("Beta");      // Stack: Beta, Gamma
    stack.pop();                  // Stack: Gamma
    stack.push("Beta");      // Stack: Beta, Gamma
    stack.push("Alpha");     // Stack: Alpha, Beta, Gamma
    cout << stack.pop().value()<<endl; // Prints: Alpha   Stack: Beta, Gamma
    stack.forEach(stringPrinter); // Prints: Beta, Gamma
    cout<<endl;

    auto dStack = Stack<double>{};  // dStack: empty;
    cout << dStack.pop().has_value() << endl; // Prints: 0 /false/
    stack.push("Info");        // dStack: Info
    cout << stack.peek().value() << endl; //Prints: Info


    auto iQueue = IntQueue{};
    iQueue.pushLast(1);    // iQueue: 1
    iQueue.pushLast(5);    // iQueue: 1, 5
    iQueue.pushLast(10);   // iQueue: 1, 5, 10
    iQueue.pushLast(20);   // iQueue: 1, 5, 10, 20
    iQueue.forEach(decreaseByOne);  // iQueue: 0, 4, 9, 19
    iQueue.forEach(intPrinter);     // Prints: 0, 4, 9, 19
    cout<<endl;
    cout<<iQueue.peekFirst().value()<<endl;  // Prints: 0
    cout<<iQueue.popFirst().value()<<endl;   // Prints: 0   iQueue: 4, 9, 19
    iQueue.forEach(intPrinter);     // Prints: 4, 9, 19
    cout<<endl;
    iQueue.popFirst();                       // iQueue:  9, 19
    iQueue.popFirst();                       // iQueue:  19
    cout<<iQueue.popFirst().value()<<endl;   // Prints: 19   iQueue: empty
    cout<<iQueue.popFirst().has_value()<<endl;  // Prints: 0   /false/

    auto queue = Queue<string>();   //Queue: empty
    queue.pushLast("Alpha");  //Queue: Alpha
    queue.pushLast("Beta");   //Queue: Alpha Beta
    queue.pushLast("Gamma");  //Queue: Alpha Beta Gamma
    queue.forEach(stringPrinter); // Prints: Alpha Beta Gamma
    cout<<endl;
    cout<<queue.popFirst().value()<<endl;  // Prints: Alpha  Queue: Beta Gamma
    cout<<queue.popFirst().value()<<endl;  // Prints: Beta   Queue: Gamma
    cout<<queue.peekFirst().value()<<endl; // Prints: Gamma  Queue: Gamma
    cout<<queue.popFirst().value()<<endl;  // Prints: Gamma  Queue: empty
    cout<<queue.popFirst().has_value()<<endl; // Prints: 0   /false/

    auto tree = SortedBinTree<int>();
    tree.insert(2);
    tree.insert(5);
    tree.insert(1);
    tree.insert(2);


}
