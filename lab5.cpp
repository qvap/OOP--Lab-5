#include <iostream>
#include <memory>
using namespace std;

class Base{
    public:
        // Конструкторы
        Base(){
            printf("Base-конструктор\n");
        }
        Base(Base* obj){
            printf("Base-конструктор с указателем на объект Base\n");
        }
        Base(Base& obj){
            printf("Base-конструктор с ссылкой на объект Base\n");
        }
        // Деструктор
        virtual ~Base(){
            printf("Base-деструктор (виртуальный)\n");
        }

        // Методы 1 (перекрытие и виртуальность)
        void method1(){
            printf("Метод 1 Base (перекрытие)\n");
        }
        virtual void method1virtual(){
            printf("Метод 1 Base (виртуальный)\n");
        }

        // Проверка типа
        virtual string classname(){
            return "Base";
        }
        virtual bool isA(string className){
            return className == "Base";
        }
};

class Desc : public Base{
    public:
        // Конструкторы
        Desc(){
            printf("Desc-конструктор\n");
        }
        Desc(Desc* obj){
            printf("Desc-конструктор с указателем на объект Desc\n");
        }
        Desc(Desc& obj){
            printf("Desc-конструктор с ссылкой на объект Desc\n");
        }
        // Деструктор
        ~Desc(){
            printf("Desc-деструктор\n");
        }

        // Перекрытие метода 1
        void method1(){
            printf("Метод 1 Desc (перекрытие)\n");
        }
        // Переопределение виртуального метода 1
        void method1virtual() override{
            printf("Метод 1 Desc (виртуальный)\n");
        }
        
        // Переопределение методов проверки типа
        string classname() override{
            return "Desc";
        }
        bool isA(string className) override{
            return className == "Desc" || Base::isA(className);
        }

};

// Передача параметров
void func1(Base obj){
    printf("Передача в функцию по значению func1\n");
}
void func2(Base* obj){
    printf("Передача в функцию по указателю func2\n");
}
void func3(Base& obj){
    printf("Передача в функцию по ссылке func3\n");
}

// Возврат значений
Base func4(){
    Base obj;
    printf("Возврат статического объекта func4\n");
    return obj;
}
Base* func5(){
    Base* obj = new Base();
    printf("Возврат динамического объекта func5\n");
    return obj;
}
Base& func6(){
    static Base obj;
    printf("Возврат статичной ссылки на объект func6\n");
    return obj;
}

int main(){
    cout << "------ Виртуальные методы ------\n";
    Base* baseptr = new Desc();
    baseptr->method1(); // Вызывает метод Base (т. к. указатель на Base)
    baseptr->method1virtual(); // Вызывает метод Desc (override)
    delete baseptr;

    cout << "\n------ Проверка типов ------\n";
    Base* obj = new Desc();
    cout << "classname: " << obj->classname() << endl;
    cout << "Base isA: " << obj->isA("Base") << endl;
    cout << "Desc isA: " << obj->isA("Desc") << endl;
    delete obj;

    cout << "\n------ Приведение типов ------\n";
    Base* obj2 = new Desc();
    if (dynamic_cast<Desc*>(obj2)){
        cout << "Приведение dynamic_cast успешно\n";
    }
    if (obj2->isA("Desc")){
        cout << "Ручное приведение успешно\n";
    }
    delete obj2;

    cout << "\n------ Передача параметров ------\n";
    Desc obj3;
    cout << "------ func1 (по значению)\n";
    func1(obj3);
    cout << "------ func2 (указатель)\n";
    func2(&obj3);
    cout << "------ func3 (ссылка)\n";
    func3(obj3);

    cout << "\n------ Возврат значений ------\n";
    Base returnedobj = func4();
    Base* returnedptr = func5();
    Base& returnedref = func6();
    delete returnedptr;

    cout << "\n------ Умные указатели ------\n";
    {
        unique_ptr<Base> uptr = make_unique<Desc>();
        cout << "unique_ptr -> выход за область видимости\n";
    }
    {
        shared_ptr<Base> sptr_1 = make_shared<Desc>();
        {
            shared_ptr<Base> sptr_2 = sptr_1;
            cout << "Кол-во использований: " << sptr_1.use_count() << endl;
            cout << "Выход sptr_2 за область видимости\n";
        }
        cout << "Кол-во использований: " << sptr_1.use_count() << endl;
        cout << "Выход sptr_1 за область видимости\n";
    }

    return 0;
}