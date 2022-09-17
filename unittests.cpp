//
// Created by lalev on 17.09.22.
//

#include <string>
#include "jstyle_asserts.h"
#include "Stack.h"
#include "IntStack.h"
#include "IntQueue.h"
#include "Queue.h"

#define ASSERTION_ERR_MSG "Assertion error in "s + __FILE__ +"at"s +" line: "s + std::to_string(__LINE__)

std::string str_global;
void concat(std::string &s) {
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


}
