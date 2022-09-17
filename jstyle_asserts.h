//
// Created by lalev on 01.09.22.
//

#ifndef MEDICATION_JSTYLE_ASSERTS_HPP
#define MEDICATION_JSTYLE_ASSERTS_HPP

#include <iostream>
#include <string>

/**
 * Реализира Java-подобен assert. Ако изразът не е true, извежда съобщение и прекъсва програмата.
 * @param expr
 * @param message
 */

void assert(bool expr, const std::string &message) {
    if (!expr) {
        std::cerr<<"Assert failed!"<<std::endl<<message<<std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * Реализира Java-подобен assertEquals. Ако двете стойности не са равни, извежда съобщение и
 * прекъсва програмата.
 *
 * @tparam T - тип на очакваната и действителната стойност
 * @param expected - очаквана стойност
 * @param actual - действителна стойност
 * @param message - пояснително съобщение
 */

// XXX: ЗАЩО template функциите трябва да са имплементирани в хедъра??? Ако извадя тази функция в cpp файл
// линкера фвърля грешка! Вж. https://stackoverflow.com/questions/10632251/undefined-reference-to-template-function

template<typename T> void assertEquals(const T &expected, const T &actual, const std::string &message) {
    if (expected != actual) {
        std::cerr << "Assert failed! Expected: " << expected << " Got: " << actual << std::endl << message << std::endl;
        exit(EXIT_FAILURE);
    }
}

#endif //MEDICATION_JSTYLE_ASSERTS_HPP
