# АСПЗ

## Практична робота №4, Варіант 7

Був використаний запуск shell скриптів для швидкої компіляції та тестування програми.

---

### 4.1 — Ліміт виділеної пам'яті malloc(3) за виклик

#### Умова

Скільки пам’яті може виділити malloc(3) за один виклик?

Параметр malloc(3) є цілим числом типу даних size_t, тому логічно максимальне число, яке можна передати як параметр malloc(3), — це максимальне значення size_t на платформі (sizeof(size_t)). У 64-бітній Linux size_t становить 8 байтів, тобто 8 * 8 = 64 біти. Відповідно, максимальний обсяг пам’яті, який може бути виділений за один виклик malloc(3), дорівнює 2^64. Спробуйте запустити код на x86_64 та x86. Чому теоретично максимальний обсяг складає 8 ексабайт, а не 16?

#### Опис рішення

Програма виводить розмір size_t, максимальне значення цього типу ((size_t)-1) і оцінює відповідний обсяг пам’яті. Також виводить максимальні значення для 32- та 64-бітних систем (максимуми для UINT32_MAX та UINT64_MAX).

Теоретично, максимальне значення size_t на 64-бітній системі становить 2^64-1 байтів (близько 16 ексабайт), проте системи часто не підтримують виділення такої кількості пам’яті через апаратні й програмні обмеження. Також через те, що 64-бітний адресний простір практично не досягає 2^64 фізичних байтів (є розділ архітектури і практичних обмежень).

#### Відповідь на запитання

Максимальне число, яке можна передати до malloc(), — це максимальне значення size_t. На 64-бітній платформі це 2^64 - 1, тобто 16 ексабайт, але це теоретичний максимум, реально виділити стільки неможливо через обмеження ОС, фізичної пам’яті та системних ресурсів.

#### Скріншоти

![screenshot](https://github.com/KostyaKindaluk/practice-4/blob/master/task1/screenshot.png)

---

### 4.2 — Надавання malloc(3) негативного аргументу

#### Умова

Що станеться, якщо передати malloc(3) від’ємний аргумент? Напишіть тестовий випадок, який обчислює кількість виділених байтів за формулою num = xa * xb. Що буде, якщо num оголошене як цілочисельна змінна зі знаком, а результат множення призведе до переповнення? Як себе поведе malloc(3)? Запустіть програму на x86_64 і x86.

#### Опис рішення

Якщо передати malloc() від’ємне число, через перетворення типів аргумент стає великим беззнаковим значенням (через підписане-до-unsigned приведення), що призводить до спроби виділення дуже великого блоку пам’яті або негайного провалу.

Якщо змінна num переповнюється (наприклад, 1<<30 * 4 = 2^32, що виходить за межі int), то буде неочікувана поведінка - від'ємне значення, 0, чи позитивне.

#### Відповідь на запитання

malloc() приймає аргумент типу size_t (беззнаковий). Передача від’ємного числа викликає його конвертацію у великий беззнаковий розмір, що часто призводить до помилки виділення. Якщо використовувати знакові змінні для розміру та вони переповнюються, результат буде некоректним, і виклик malloc() працюватиме неправильно або аварійно.

#### Скріншоти

![screenshot](https://github.com/KostyaKindaluk/practice-4/blob/master/task2/screenshot.png)

---

### 4.3 — Надавання malloc(3) аргументу з нульовим значенням

#### Умова

Що станеться, якщо використати malloc(0)? Напишіть тестовий випадок, у якому malloc(3) повертає NULL або вказівник, що не є NULL, і який можна передати у free(). Відкомпілюйте та запустіть через ltrace. Поясніть поведінку програми.

#### Опис рішення

Програма виділяє пам'ять за допомогою malloc(3), і повідомляє про те, що повернулося - NULL або вказівник.

#### Відповідь на запитання

Стандарт C дозволяє malloc(0) повертати або NULL, або унікальний валідний вказівник, який можна звільнити. Реалізація залежить від бібліотеки. У будь-якому разі виклик free() з таким вказівником є коректним.

#### Скріншоти

![screenshot](https://github.com/KostyaKindaluk/practice-4/blob/master/task3/screenshot.png)

---

### 4.4 — Виправлення помилки з повторним malloc та free змінної

#### Умова

Чи є помилки у такому коді?

```c
void *ptr = NULL;
while (<some-condition-is-true>) {
	if (!ptr)
		ptr = malloc(n);
	[... <використання 'ptr'> ...]
	free(ptr);
}
```

Напишіть тестовий випадок, який продемонструє проблему та правильний варіант коду.

#### Опис рішення

Помилка — після першої ітерації вказівник ptr звільняється, але не обнуляється, тому при наступній ітерації if (!ptr) не спрацює і буде використовуватися вже звільнений указівник — це призведе до помилки.

Правильний варіант — розраховувати на це і не перевіряти на нуль після використання free().

#### Відповідь на запитання

Щоб цього уникнути, треба не перевіряти вказівник на нуль після використання free().

#### Скріншоти

![screenshot](https://github.com/KostyaKindaluk/practice-4/blob/master/task4/screenshot.png)

---

### 4.5 — Демонстрація помилки виділення пам'яті realloc(3)

#### Умова

Що станеться, якщо realloc(3) не зможе виділити пам’ять? Напишіть тестовий випадок, що демонструє цей сценарій.

#### Опис рішення

У коді виділяється початковий блок пам’яті (malloc), після чого виконується спроба розширити його до максимально можливого розміру ((size_t)-1), яка навмисно має провалитися. Після невдачі перевіряється, що початковий вказівник залишився дійсним.

#### Відповідь на запитання

При невдачі realloc() повертає NULL, не змінюючи початковий вказівник. Цю ситуацію потрібно правильно обробляти, щоб уникнути втрати пам’яті.

#### Скріншоти

![screenshot](https://github.com/KostyaKindaluk/practice-4/blob/master/task5/screenshot.png)

---

### 4.6 — Демонстрація виклика realloc(3) з аргументом з нульовим значенням

#### Умова

Якщо realloc(3) викликати з NULL або розміром 0, що станеться? Напишіть тестовий випадок.

#### Опис рішення

realloc(NULL, size) поводиться як malloc(size) — виділяє нову пам’ять.

realloc(ptr, 0) поводиться як free(ptr) та повертає NULL.

#### Відповідь на запитання

Функція realloc() із NULL працює безпечно як malloc. А з 0 — як free, тому результат потрібно завжди перевіряти.

#### Скріншоти

![screenshot](https://github.com/KostyaKindaluk/practice-4/blob/master/task6/screenshot.png)

---

### 4.7 — Переписання коду за допомогою reallocarray(3)

#### Умова

Перепишіть наступний код, використовуючи reallocarray(3):

```c
struct sbar *ptr, *newptr;
ptr = calloc(1000, sizeof(struct sbar));
newptr = realloc(ptr, 500*sizeof(struct sbar));
```

Порівняйте результати виконання з використанням ltrace.

#### Опис рішення

Функція reallocarray(ptr, nmemb, size) безпечніша за realloc(ptr, nmemb * size), оскільки перевіряє на переповнення добутку nmemb * size.

#### Скріншоти

![screenshot](https://github.com/KostyaKindaluk/practice-4/blob/master/task7/screenshot.png)

---

### Варіант 7 — Перевірка cache locality

#### Умова

Напишіть програму, яка перевіряє ефективність cache locality для розподіленої пам’яті.

#### Опис рішення

Створено два великі масиви:

- array — дані
- indices — випадкове переставлення індексів
 
Далі виконується підрахунок суми в циклі по array[i] і по array[indices[i]] з вимірюванням часу.

#### Висновок

Послідовний доступ до пам’яті набагато швидший завдяки кешуванню. Випадковий доступ значно уповільнюється через часті кеш-промахи.

#### Скріншоти

![screenshot](https://github.com/KostyaKindaluk/practice-4/blob/master/variant7/screenshot.png)