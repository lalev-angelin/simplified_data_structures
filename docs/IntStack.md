# IntStack.h

### Обяснение на кода

```c++
#define Pointer std::shared_ptr<IntStackElement>
#define newIntStackElement(X) (std::make_shared<IntStackElement>(X))
```
Благодарение на двете define директиви, препроцесорът на C++ просто ще замени текста Pointer навсякъде във 
файла с std::shared_ptr<IntStackElement> **преди** файлът да се подаде на същинския компилатор.
По същия начин newIntStackElement(X), където X е произволен текст ще се замени със std::make_shared<IntStackElement>(X).

Двете директиви ни позволяваме да пишем
```c++
Pointer node = newIntStackElement(value);
```
вместо 

```c++
std::shared_ptr<IntStackElement> node = std::make_shared<IntStackElement>(value);
```

По-нататък: 

```c++
class IntStackElement {
public:
    int data;
    Pointer next;
    explicit IntStackElement(int newData);
};
```

Основен елемент на опашката. Класът има две полета. Полето data съдържа данните, които се съхраняват н елемента (в случая
число от тип int), а next е указател към следващия елемент. В случай, че няма следващ елемент, този указател е nullptr.

