#include <iostream>
using namespace std;

// # Pimpl ����
/* Pimpl (Pointer to Implementation)
    �����θ� �����ͷ� �����ϴ� ����
*/

struct Person{
    string name;
    void greet();

    Person();
    ~Person();

    class PersonImpl;
    PersonImpl *impl; // gsl::owner<T>�� Ȱ���ϱ� ���� ���
};
// PersonImpl�� �����ΰ�?
// Ŭ������ �����θ� �ٸ� Ŭ����(PersonImpl)�� ������� �ϴ� �ǵ����� �߻��Ѵ�.
// ���� Ŭ���� PersonImpl�� ��������� �ƴ� .cpp ���Ͽ� �����ϴ� ���� �ٽ����̴�.

// PersonImpl�� ���Ǵ� �Ʒ��� ����.
struct Person::PersonImpl{
    void greet(Person* p);
};

// Person Ŭ������ PersonImpl�� ���� ����(forward-declare)�ϰ� �����ͷ� �����Ѵ�.
// Person�� �����ڿ� �Ҹ��ڿ����� PersonImpl�� �����͸� �ʱ�ȭ�ϰ� �����Ѵ�.

Person::Person() : impl(new PersonImpl){}
Person::~Person() {delete impl;}

// ���� greet�� �����Ѵ�.

void Person::greet(){
    impl->greet(this);
}

void Person::PersonImpl::greet(Person *p){
    cout << "hello " << p->name << endl;
}

/* Pimpl�� ����
 - Ŭ������ �������� ���κ��� ������ ������ �� �ִ�. �� �ʿ��� public �������̽��� ���� ����
 - ���̳ʸ� ȣȯ���� �����ϱ� ��������. ������ ���� Ŭ������ ���� ������ ���̳ʸ� ȣȯ���� ������ �ȹ�ģ��.
 - ��������� ��� ���� �ʿ��� ����鸸 ��Ŭ����ϰ� �� �� �ִ�.
*/