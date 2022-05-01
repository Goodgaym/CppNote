#include<iostream>
using namespace std;

// ��ü ������ (Object Dependencies)
// ���� ��ü�� �ٸ� ��ü�� ��ȣ�ۿ�(����)�ϰ� �ִٸ� ���� ��ü�� �ٸ� ��ü�� �������� ������.

class Animal{
public:
    Animal(){}
    virtual ~Animal(){}
    virtual void speak()=0;
};

class Dog : public Animal{
public:
    Dog() : Animal() {}
    void speak(){
        cout << "�۸�" << endl;
    }
};

// PetOwner�� Dog�� �������� ������
class PetOwner{
    Animal *animal;

    public:
    PetOwner(){
        this->animal = new Dog(); // �ش� ���� ���� Dog�� ����
    }
    Animal* getAnimal(){
        return this->animal;
    }
};
// �̷��� �������� ���ҽ�Ű�°� DI(Dependency Injection).
// �����ӿ�ũ � ���� ��ü�� �������� ���ԵǴ� ���� ����.
// -> Ŭ���� A�� B,C�� �������� �� B,C�� �ܺο��� �����ϰ� A���� B,C�� ����϶�� �����ϴ� �� 

int main(){
    PetOwner owner;

    owner.getAnimal()->speak();

    return 0;
}