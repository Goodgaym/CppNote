#include<iostream>
using namespace std;

// 1. �̻��� ��� ���ø� ���� (Curiously Recurring Template Pattern)
// �ڱ��ڽ��� ���̽��� ���ø� ���ڷ� ��ӹ޴� ����

// ���̽� Ŭ������ �����ο��� Ÿ���� ������ this �����͸� ����� �� ����
// ����Ŭ������ begin()/end() �������̽��� �����Ǿ� ���� ������ ���� �Ұ�
// CRTP�� �����ϸ� this�� ���� Ŭ���� Ÿ������ ĳ���� ����
template <typename Derived>
struct SomeBase{
    void foo(){
        for(auto& item : *static_cast<Derived*>(this)){
            //...
        }
    }
};

struct Foo : SomeBase<Foo>{
    //...
};

// 2. ÷��(Mixin) ���
// �ڱ� �ڽ��� ���ø� ���ڷ� �ϴ� ����
// ÷�� ����� �̿��ϸ� ���������� ���� Ÿ���� �ռ��� �� �ִ�.
template <typename T> struct Mixin : T{
    //...
};
// ���� Foo<Bar<Baz>> x; �� ���� ������ �����ϸ� ���ο� Ÿ���� �������� �ʰ� ������ �Ӽ��� ����

// 3. �Ӽ�
// get/set �޼��带 ������ Ŭ���� ���� ���� : �Ӽ�
// __declspec�� ����ϸ� �ڵ����� get/set �޼��� ȣ�� (VS community)
class person{
    int age_;
public:
    int get_age() const { return age_;}
    void set_age(int value) {age_ = value;}

    // MSǥ���̱� ������ VScommunity�̿�(ex G++)�� ���� �Ұ�
    //__declspec(property(get=get_age, put=set_age)) int age; 
};

int main(){

    return 0;
}