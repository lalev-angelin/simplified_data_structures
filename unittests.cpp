//
// Created by lalev on 17.09.22.
//

#include <string>
#include "jstyle_asserts.h"
#include "Stack.h"
#include "IntStack.h"
#include "IntQueue.h"
#include "Queue.h"

using namespace std;

#define ASSERTION_ERR_MSG "Assertion error in "s + __FILE__ +"at"s +" line: "s + to_string(__LINE__)

string str_global;
void concat(string &s) {
    str_global+=s;
}

int main() {
    // Test
    IntStack iStack;
    iStack.push(1);
    iStack.push(2);
    assertEquals(iStack.peek().value(), 2, ASSERTION_ERR_MSG);
    int a = iStack.pop().value();
    assertEquals(a, 2, ASSERTION_ERR_MSG);
    assert(iStack.pop().has_value(), ASSERTION_ERR_MSG);
    assert(!iStack.pop().has_value(), ASSERTION_ERR_MSG);

    // Test
    Stack<string> sStack;
    sStack.push("Alpha");
    sStack.push("Gamma");
    sStack.pop();
    sStack.push("Beta");
    str_global="";
    sStack.forEach(concat);
    assertEquals("BetaAlpha"s, str_global, ASSERTION_ERR_MSG);
    str_global="";

    //Test
    IntQueue iQueue;
    iQueue.pushLast(5);
    assertEquals(5, iQueue.peekFirst().value(), ASSERTION_ERR_MSG);
    iQueue.pushLast(10);
    assertEquals(5, iQueue.peekFirst().value(), ASSERTION_ERR_MSG);
    assertEquals(5, iQueue.popFirst().value(), ASSERTION_ERR_MSG);
    assertEquals(10, iQueue.peekFirst().value(), ASSERTION_ERR_MSG);
    assertEquals(10, iQueue.popFirst().value(), ASSERTION_ERR_MSG);
    bool throws = false;
    try {
        iQueue.peekFirst().value();
    } catch (exception &e) {
        throws = true;
    }
    assert(throws, ASSERTION_ERR_MSG);
    iQueue.pushLast(7);
    assertEquals(7, iQueue.peekFirst().value(), ASSERTION_ERR_MSG);

    // Test
    Queue<string> sQueue;
    sQueue.pushLast("Sofia");
    assertEquals("Sofia"s, sQueue.peekFirst().value(), ASSERTION_ERR_MSG);
    sQueue.pushLast("Varna");
    sQueue.pushLast("Plovdiv");
    assertEquals("Sofia"s, sQueue.popFirst().value(), ASSERTION_ERR_MSG);
    assertEquals("Varna"s, sQueue.popFirst().value(), ASSERTION_ERR_MSG);
    assertEquals("Plovdiv"s, sQueue.popFirst().value(), ASSERTION_ERR_MSG);
    throws = false;
    try {
        sQueue.peekFirst().value();
    } catch (exception &e) {
        throws = true;
    }
    assert(throws, ASSERTION_ERR_MSG);
}
