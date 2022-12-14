# Stack.h

### Обяснение на кода

Инклуд гардове
```c++
#ifndef SIMPLIFIED_DATA_STRUCTURES_STACK_H
#define SIMPLIFIED_DATA_STRUCTURES_STACK_H
```

Тези две директиви служат за предотвратяване на включването на един .h файл повече от един път в даден проект.
Преди компилацията на програмата include директивите събират всички файлове със сорс в един "суперфайл". Проблемът със
суперфайла е това, че някои инклуднати файлове могат да се повтарят множество пъти.
Това е нежелателно и почти сигурно води до грешки. В нашия случай, където имаме template класове с техните дефиниции
в .h файла /това изглежда е задължително за класовете-шаблони/, двойното включване си е сигурна грешка.

Затова - инклуд гардове. Ако даден файл бъде включен два пъти, тези два реда ще гарантират, че второто, третото и пр.
включване ще бъдат игнорирани при компилацията.

Директивата на препроцесора ifndef работи като if конструкцията в езика C++. Нейният "блок от код" е затворен отдолу,
в края на файла, със

```c++

#endif

```

Благодарение на двете define директиви

```c++

#define Pointer std::shared_ptr<StackElement<T>>
#define newStackElement(X) (std::make_shared<StackElement<T>>(X))

```

препроцесорът на C++ просто ще замени текста Pointer навсякъде във
файла със std::shared_ptr<StackElement<T>> **преди** файлът да се подаде на същинския компилатор.
По същия начин newStackElement(X), където X е произволен текст, ще се замени със std::make_shared<StackElement<T>>(X).

Двете директиви ни позволяват да пишем
```c++
Pointer node = newStackElement(value);
```
вместо

```c++
std::shared_ptr<StackElement<T>> node = std::make_shared<StackElement<T>>(value);
```

Тъй като Pointer във всеки файл на проекта е дефиниран различно (защото сочи към различен тип елемент),
се налага в края на всеки файл да кажем на препроцесора да спре заместването. В противен случай, когато препроцесорът
срещне следващата #define Pointer директива във обединения "суперфайл", той "ще се стресне" и ще генерира грешка.

Това е направено в края на файла с:

```c++
#undef Pointer
#undef newStackElement
```

По-нататък:

```c++
template <class T> class StackElement {
public:
    T data;
    Pointer next;
    explicit StackElement(T value);
};
```

Класът е основен елемент на стека и има две полета. Полето data съдържа данните, които се съхраняват в елемента (в случая
те са от още неуточнения тип T), а next е указател към следващия елемент. В случай, че няма следващ елемент, този указател е nullptr.

Обектът има и прост конструктор, който инициализира data полето със стойността, която елементът ще съхранява, и next полето
с nullptr.

По-нататък:

```c++
template <class T> class Stack {
protected:
    Pointer top;
public:
    Stack();
    void push(T data);
    optional<T> pop();
    optional<T> peek() const;
    void forEach(void (*consumer)(T& element));
};
```

Класът Stack представлява самия стек. Той има едно поле - top - което е указател към връха на стека, т.е. първият елемент в него.

Конструктурът Stack е тривиален и инициализира top с nullptr, което обозначава началното състояние на стека - празно.

```c++
template<class T>
void Stack<T>::push(T data) {
    Pointer tmp = newStackElement(data);
    tmp->next = top;
    top = tmp;
}
```

Методът **push** вмъква нов елемент в стека. При стековете новият елемент отива на върха, а предишният първи елемент отива "зад" новия.
Това се реализира като предишния връх на стека се сложи в полето next на новия.

Операцията push прилича на прикачане на вагони към влакова композиция, при която новият вагон отива най-отпред.

```c++
template<class T>
optional<T> Stack<T>::pop() {
    if (top==nullptr) return {};
    Pointer tmp = top;
    top = top->next;
    return tmp->data;
}
```

Операцията pop "вади" елемента на върха на стека, като следващия елемент става новия връх на стека. За целта указателят
към върха на стека се връща на потребителя, докато стойността на неговото поле next става стойност на полето top.

Операцията прилича на откачане на първия вагон на една влакова композиция.

За да избегнем използването на указатели, трябва да имаме начин да укажем, че нямаме стойност, когато потребителят се опита
да извади нещо с pop от празен стек. Ако бяхме реализирали стека напълно с указатели, това беше опция.
Ние обаче връщаме само int стойности, които определено не са указатели, поради което нямаме лесен начин, да кажем,
че стойността липсва.

За щастие C++, като всички модерни езици поддържа класа-шаблон optional който позволява да "инкапсулираме" стойност.
optional има методи като has_value с които можем да проверим дали всъщност имаме стойност.

Редът
```c++
if (top==nullptr) return {};
```
създава и връща празен обект от тип optional ако стекът е празен.

```c++
return tmp->data;
```

също създава optional обект имплицитно /защото връщаната стойност на pop е декларирана като optional/


Методът **peek** позволява да видим какво има на върха на стека без да вадим елемента от него.
```c++
template<class T>
optional<T> Stack<T>::peek() const {
    if (top==nullptr) return {};
    return top->data;
}
```

Методът forEach позволява потребителят на стека да укаже метод, който ще се изпълни върху всеки един елемент,
намиращ се понастоящем в структурата от данни. За целта forEach прави обход на стека от първия към последния
елемент, използвайки next указателите на всеки елемент.

Последният елемент, разбира се, се познава по това, че неговият next елемент е празен.

```c++
template<class T>
void Stack<T>::forEach(void (*consumer)(T& data)) {
    Pointer tmp = top;
    while (tmp!=nullptr) {
        consumer(tmp->data);
        tmp = tmp->next;
    }
}
```

Забележете, че декларираният единствен параметър на forEach - void (*consumer)(int &) - всъщност е функция. Компилаторът
се ориентира в това благодарение на звездата преди consumer и скобите, които го обхващат. Подадената функция може да е
метод на обект или самостоятелна функция, а може и да е специален ламбда израз. Незанвисимо как се казва и задава
действителната функция, която се подава на метода forEach, вътре във forEach ние се обръщаме към нея като consumer.
consumer всъщност е повлияно от Java, където наричаме функции, които вземат един параметър и не връщат нищо "консуматори".

consumer всъщност взема референция към data полето на всеки елемент и следователно може да променя стойностите в стека,
ако пожелае това.

