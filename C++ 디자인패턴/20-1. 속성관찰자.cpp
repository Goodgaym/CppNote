#include<iostream>
#include<vector>
#include<algorithm>
#include<any>
using namespace std;

/* # �Ӽ� ������
struct Person{
    int age;
    Person(int age) : age{age}{}
}
    ������ �Ͽ� ����� ���̰� ����Ǵ� ���� �� �� ������ 
    �� 100msec���� ���糪�̸� �о� ������ ���̿� ���ϴ� ���� ����� ��ȿ�����̴�.

struct Person {
    int get_age() const {return age;}
    void set_age(const int value) {age= value;}

private:
    int age;
};

    ���� set_age()�� ȣ��Ǿ� ���� �ٲ𶧸��� � �˸��� ������ �ȴ�. �׷��� ��� ���� �� ������

*/

// # Observer<T>
// Person�� ��ȭ�� ������ ������ �ʿ��� ����� �� �ֵ��� �ݹ� �Լ��� �����Ͽ� ���̽� Ŭ������ �δ� ���̴�.
/*
struct Personlistener{
    virtual void person_changed(Person& p, const string& property_name, const any new_value) = 0;
};
*/// ������ �̷��� ���� ����� Person Ÿ�Կ� �����Ǿ� �ִ�.
// �Ʒ��� Observer ���Ƿ� ���� Ÿ���� Ŭ������ ����͸� �� �� �ִ�.
template<typename T> struct Observer{
    virtual void field_changed(T& source, const string& field_name) = 0;
};

/* ���� ��� ���� �۾��� ���������� �ֿܼ� �޼����� ����ϰ� �ʹٸ� �Ʒ��� ���� �ۼ��Ѵ�.
struct ConsolePersonObserver : Observer<Person>{
    void field_changed(Person& source, const string& field_name) override{
        cout << "Person's "<< field_name << " has changed to " << source.get_age() << ".\n";
    }
};

struct Creature;
// ������ Ŭ�������� �ʵ尪�� ����͸� �ϱ� ���ؼ� �Ʒ��� ���� �ۼ��Ѵ�.
struct ConsolePersonObserver : Observer<Person>, Observer<Creature>{
    void field_changed(Person& source, const string& field_name) override{...}
    void field_changed(Creature& source, const string& field_name) override{...}
};
*/

// # Observerable<T>
//Person�� ����͸��� ������ Observable Ŭ������ ����� ����. 
/* Observable�� ������ ���� å���� ���� �ȴ�.
    - Person�� ������ ����͸� �Ϸ��� �����ڵ��� private ����Ʈ�� �����Ѵ�.
    - �����ڰ� Person�� ���� �̺�Ʈ�� ���� ��� �Ǵ� ����(subscribe()/unsubscribe())�� �� �ְ� �Ѵ�.
    - notify()�� ���� ���� �̺�Ʈ�� �߻����� �� ��� �����ڿ��� ������ ���޵ǵ��� �Ѵ�.
*/

template<typename T> struct Observable{
    void notify(T& source, const string& name);
    void subscribe(Observer<T>* f) { 
        observers.push_back(f);
    }
    void unsubscribe(Observer<T>* f){
        //...
    }
private:
    vector<Observer<T>*> observers;
};
// private�� ������ ����� ���Ƿ� �����Ǵ� ���� ���´�.
// �������� notify�� �����Ѵ�. ��� �����ڸ� ��ȸ�ϸ� �������� field_changed()�� ���ʷ� ȣ���Ѵ�.

template<typename T>
void Observable<T>::notify(T& source, const string& name){
    for(auto obs : observers){
        obs->field_changed(source, name);       
    }
}

// Observable<T> �� ��ӹ޴� �͸����δ� �����ϴ�. 
// ���� �޴� Ŭ���������� �ڽ��� �ʵ尡 ����� ������ notify()�� ȣ�����־�� �Ѵ�.
/* set_age() ����Լ��� ������ ���� ������ å���� �־�����.
    - �ʵ��� ���� ������ �ٲ������ �˻��ؾ� �Ѵ�.
    - �ʵ��� ������ ���� �����Ǿ�� �Ѵ�.
    - �ʵ��� ���� �ٲ���� �� �ùٸ� ���ڷ� notify()�� ȣ���Ѵ�.
*/

struct Person : Observable<Person>{
    Person(int age) : age{age}{}
    int get_age(){return this->age;}
    void set_age(const int age){
        if(this->age == age) return;
        this->age = age;
        notify(*this, "age");
    }
private:
    int age;
};

/* ������(Observer)�� �������(Observable)�� ����
    �˸��� �ޱ� ���� �����ڴ� ������ ���� ���ǵȴ�.
*/
struct ConsolePersonObserver : Observer<Person>{
    void field_changed(Person& source, const string& field_name) override{
        cout << "Person's "<< field_name << " has changed to " << source.get_age() << ".\n";
    }
};

// �Ӽ��� ���Ӽ�, ������ ������, ������ �������� ���� �������� ����� �ʿ䰡 ���ٸ� ��������� �������� ����ص� ������.

int main(){
    Person p{20};
    ConsolePersonObserver cpo;
    p.subscribe(&cpo);
    p.set_age(21);
    p.set_age(22);

    return 0;
}