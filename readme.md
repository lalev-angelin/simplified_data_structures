# Simplified Data Structures in C++

###### This project was designed for educational purposes as coursework on C++ and Data Structures at University of Ruse. Documentation is in Bulgarian.

# Опростени структури от данни 

В настоящия проект се опитах да разработя собствена библиотека за работа с елементарни структури от данни, а 
именно стекове, опашки, двойно-свързани опашки и сортирани двоични дървета. 
Освен като упражнение за по-добро овладяване на C++, имах за цел да проверя дали следните принципи на дизайна могат да работят. 

###### 1. Пълно или частично елиминиране на указателите 

Като идващ от Java бекграунд, продължавам да се отнасям с екстремно подозрение към указателите, особено когато се използват 
за "общоцелево" програмиране. При работа с класически указатели програмистът постоянно трябва да следи за тяхното освобождаване 
когато вече не се използват. Освен това е лесно да се направят грешки в тяхната "аритметика", които водят до сериозни проблеми 
с програмата. 

###### 2. Максимална читаемост на кода 

Cинтаксисът на C++ е доста тежък и това, според мен, усложнява "разкодирането" на смисъла зад операциите 
със структури от данни. Ето защо се опитах да приложа каквито хитринки се сетих за опростяване на кода.

#### Резултати

По отношение на пълното елиминиране на указателите, успехът в най-добрият случай може да се определи като "частичен". 
Изпробвах различни подходи. Един от тях например включваше всички обекти да се копират при извикване на методи и присвояване. 
Този метод не е ефективен, и което е по-лошо - не работи както бихме очаквали, особено ако мислим в понятията на Java.
Компилаторът на C++ няма да позволи създаването на класове като следния: 

```c++
class Node {
    int value;
    Node left;
    Node right;
};
```

Това обезсмисля опитите за програмиране на структури от данни по този начин. 

Ако заменим променливите с референции, т.е. 

```c++
class Node {
    int value;
    Node &left;
    Node &right;
};
```

декларацията ще работи. Но още остава проблемът как ще създаваме нови инстанции на Node в методите на различни класове 
без да използваме указатели и без да предаваме референции към локални обекти, които, предполага се, ще бъдат презаписани в 
стека на програмата след излизане от метода, в който са създадени като локална променлива. 

В Java описаният по-горе подход работи, просто защото референтните типове действат като контролирани от виртуалната машина указатели
към хийпа на програмата.

В хода на търсенето открих <memory> и std::unique_ptr и std::shared_ptr. Те обещаваха да доставят еквивалентно поведение на 
референтните типове при Java - т.е. паметта на указателя **автоматично** да се освободи, когато той вече не се използва.

(Вж. https://cplusplus.com/reference/memory/unique_ptr/ и https://cplusplus.com/reference/memory/shared_ptr/)

Идеята изглежда гениално проста - истинският указател да се инкапсулира в клас и да се овърлоуднат операторите на 
класа така, че те да са почти идентични с тези за работа с указатели. Така можем да се възползваме от деструктора на класа, 
който да освободи истинския указател с delete, когато променливата от този клас вече не се използва. За целта
std::unique_ptr овърлоудва операторите *, -> и = (а може би и други). 

Недостатък на този подход обаче е, че когато една променлива от тип unique_ptr се присвои на друга променлива от същия тип.
Така стойността на инстинския указател вътре в обекта ще бъде копирана в новия обект и изведнъж ще имаме два (и евентуално повече)
указателя към един и същи заделен регион в паметта. Когато един от двата обекта бъде унищожен, неговият деструктор ще 
освободи този регион с delete и ще остави указателя на другия обект да сочи на същото място, където вече може да се намират 
съвсем други данни. 

За да се избегне този проблем, std::shared_ptr брои референции, вероятно чрез статична променлива на класа. При всяко 
копиране, броят на референциите нараства с едно. При всяко извикване на деструктор, броят на референциите се намалява 
с едно. delete в деструктора се вика само когато този брой стигне нула, което се случва точно когато последният обект 
с дадения указател прекрати съществуването си. 

std::shared_ptr вкарва някакъв много минимален овърхед, който е повече от добре дошъл, щом елиминира опасността от грешки. 
И тъй като при структурите от данни много често много различни сочат към един и същи регион от паметта, той е използван 
в нашия код. 

По отношение на четливостта обаче това решение върви точно в обратната посока, тъй като процесът с деклариране на такъв 
указател изглежда така: 

```c++
std::shared_ptr<тип_на_данните> v = std::make_shared<тип_на_данните>
```

Оказва се обаче, че този синтаксис може да се замени с препроцесорна директива от рода на 

```c++
#define Pointer std::shared_ptr<IntDequeElement>
#define newIntDequeElement(X) (std::make_shared<IntDequeElement>(X))
```

Това означава, че резервирането на указател може да се направи в кода просто с: 
```c++
Pointer tmp = newIntDequeElement(value);
```

Което напомня повече за старите дни на Pascal. 

**За нещастие** не успях да приложа същата техника за указатели към указатели, тъй като вероятно загубих 
логиката. Директиви от рода на 

```c++
#define РPointer std::shared_ptr<Pointer>
#define newIntDequePPointer(X) (std::make_shared<Pointer>(X))
```

са възможни и успях да компилирам програма с тях. Те обаче не се държаха както очаквах, за което по-големи детайли ще дам 
при коментара на сортираните двоични дървета. 

Като обобщение мога да кажа, че този препроцесорен трик работи добре когато нивото на 
индирекция е едно и имаме указател директно към обекта. В същото време работи незадоволително, когато става въпрос за 
указатели към указатели. 

В допълнение на опитите ми да направя указателите по-леки за четене, направих и други модификации, които считам за улеснение 
при четенето на кода. Обектите, които представляват отделните елементи/възли имат публично видими членове и полета вместо 
типичните аксесори и мутатори. 

Освен това всеки клас, който използва шаблони има и "близнак", който извършва същата програмна 
логика върху типа от данни int. 


### Списък на файловете с основните класове на програмата

1. [IntStack.h](/docs/IntStack.md) - целочислен стек
2. [Stack.h](/docs/Stack.md) - стек
3. [IntQueue.h](/docs/IntQueue.md) - целочислена опашка
4. [Queue.h](/docs/Queue.md) - опашка
5. [IntDeque.h](/docs/IntDeque.md) - целочислена двойно-свързана опашка /списък/
6. [Deque.h](/docs/Deque.md) - двойно свързана опашка /списък/
7. [SortedIntBinTree.h](/docs/SortedIntBinTree.h) - целочислено двоично сортирано дърво
8. [SortedBinTree.h](/docs/SortedBinTree.h) - сортирано двоично дърво
9. [jstyle_asserts.h]() - опит да "скалъпя" близък до Java и JUnit начин за правене на юнит тестове
10. [unittests.cpp]() - юнит тестове
11. [main.cpp]() - демонстрация на изполването на различни класове