#include<iostream>
#include<memory>
#include<boost/serialization/access.hpp>
using namespace std;
using namespace boost;

struct Address;
/* # ��ü ����
    �Ʒ��� �� ��ü�� �ߺ��� �κ��� �ִ�.
    contact john{ "John Doe", Address{"123 East Dr", "London", 10}};
    contact jane{ "Jane Doe", Address{"123 East Dr", "London", 11}};
    
    john�� jane�� �繫�� �游 �ٸ��� ���� �ǹ����� ���ϰ� �ִ�. (�ٸ� ����鵵)
    ������ ��ü�� ���� ������ �ߺ��ǰ� �ʱ�ȭ �Ǵ� �۾��� �߻��Ѵ�.
    
    ������Ÿ�� ������ ��ü�� ������ �ֿ����̴�.
*/

/* # ����� �ߺ�ó��
    ������ ������ ���� ����ϴ� �Ϳ� �ְ�, ���� ��� ��ü�� ��� �׸��� �����θ� �Ǿ��ִٸ�
    �����ϴµ� ���� �� ���� ����. ���� ����ó�� �ּҰ� ������ ���� ���ǵǾ� �ִٸ�,

struct Address{
    string street, city;
    int suite;
};
struct Contact{
    string name;
    Address address;  
};
*/
// �Ʒ��� ���� �ڵ带 ����ϴµ� ������ ����.
// <1><main code>

// ������ �̷��� ���� ���� �幰��.
// �Ʒ� �ڵ�� ���� Address�� ���ΰ�ü�� �����ͷ� �� ��찡 ����.

// �� �κ��� ������ �ִ�. Contact john = prototype �ڵ尡 ����� �� �����Ͱ� �����Ǳ� ������
// �Ѵ� ���� ��ü�� ������ �ȴ�.

// # ���� �����ڸ� ���� �ߺ�ó��

// ���� �����ڸ� �����ϴµ� �ΰ��� ����� �ִ�. ���Դ� �Ʒ��� ���� �����Ѵ�.
struct Contact{
    string name;
    shared_ptr<Address> address;  

    /* 
    Contact(const Contact& other)
        : name{other.name}{
            address = make_shared<Address>(
                other.address->street,
                other.address->city,
                other.address->suite
            );
        }
    */// �ּ��� �׸��� ����Ǹ� ����� �� �����Ƿ� �� �ڵ�� ���������� �ʴ�.
    // Address�� ��������ڸ� �����ϰ� Contact�� �����ڸ� ��Ȱ���Ͽ� ����� �� �ִ�.

    Contact(const Contact& other)
        : name{name}, address{make_shared<Address>(*other.address)}{
    }
    Contact& operator=(const Contact& other){
        if(this == &other)
            return *this;
        name = other.name;
        address = other.address;
        return *this;
    }
    Contact(const string name, const shared_ptr<Address> address)
        : name{name}, address{address}{
    }
};
struct Address{
    string street, city;
    int suite;
    Address(const string& street, const string& city, const int suite)
        : street{street}, city{city}, suite{suite}{}
};

int main(){
    /* <1>
    // ������Ÿ�� ��ü
    Contact worker{"", Address{"123 East Dr", "London", 0}};

    // ������Ÿ�� �����ϰ� �Ϻ� ����
    Contact john = worker;

    john.name = "John Doe";
    john.address.suite = 10;
    */
   
    // ������ ���� ������Ÿ���� �����ϸ鼭�� �����ϰ� ������ �����ϴ�.
    Contact worker{"", make_shared<Address>("123 East Dr", "London", 0)};
    Contact john{worker}; // or Contact john = worker;
    john.name = "John";
    john.address->suite = 10;
    
    // �� ����� ������ ������ �°� ���� �����ڸ� �ϳ��ϳ� �����ϴµ� �����ɸ��ٴ� ���̴�.
    // ���� ��� ������ ���� �ڵ尡 �ۼ��Ǿ��ٰ� ����.

    // Contact john = worker;

    // �׸��� Address�� ���� �����ڿ� ���� �������� ������ �����Ǿ��ٰ� ����(�� Contact�� �����Ǿ� �ִ�).
    // �� �ڵ�� �����ϵǴµ� �ƹ��� ������ ����. 
    // ��������ڸ� ���ȴٸ� ��Ȳ�� ���� ����. �������� �ʴ� ����������� ȣ���� ������ ������ �߻��Ͽ� ������ ������ �� �ִ�.
    // ������ ���� �����ڴ� ����Ʈ ������ ������ �����Ƿ� ������ ���Կ����ڸ� �������� �ʾҴ��� �����ϵǾ� ����ȴ�.

    // �� �ٸ� ������ ���� ������ �Ǵ� unique_ptr�� ����Ѵٸ� �ڵ� �ڵ������� ����� �ÿ� ������ ���� �� �ִ�.
    return 0;
}