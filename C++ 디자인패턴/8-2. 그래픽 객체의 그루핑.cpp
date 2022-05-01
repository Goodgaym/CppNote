#include <iostream>
#include <vector>
using namespace std;

// ���� �׷��� ��ü�� �������� ���� �ְ� ���� ���� ������ �ϳ��� �׷����� �������� ���� �ִ�.
// ������ ���� �������̽� �ϳ��� ����ϴ�.

struct GraphicObject{
    virtual void draw() = 0;
};

// �������� �簢���� ������ ���� �׷��� ��ü�鵵 ���������� �ϳ��� �׷��� ��ü�� ��Ÿ�� �� �ִ�.
// ���� ������ ���� ������ �� �ֵ��� ���⼭ ������Ʈ ������ ������ �巯����.

struct Circle : GraphicObject{
    void draw() override{
        std::cout << "Circle"<< std::endl;
    }
};

// ����� ������� ���� ���� �׷��� ��ü�� ������ GhaphicObject�� ������ �� �ִ�.

struct Group : GraphicObject{
    std::string name;

    explicit Group(const std::string& name)
        : name{name}{}
    
    void draw() override {
        std::cout << "Group "<< name.c_str()<< " contains: "<< std::endl;
        for (auto&& o : objects){
            o->draw();
        }
    }

    std::vector<GraphicObject*> objects;
};
// ���� �� ��ü�� �׷� �׷��� ��ü�� draw() �Լ��� �����ϰ� ������ �׸� �� �ִ� �����̴�.
// ���� ������ ���� API�� �̿��� �� �ִ�.

int main(){
    Group root("root");
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);

    root.draw();

    return 0;
}

// ������ ���� ��µȴ�.
/* 
Group root contains:
Circle
Group sub contains:
Circle 
*/
// �� ������ �������� Ŀ���� �������̽� ���ǰ� ���Ǳ�� ������ ���� �ܼ��� ������ ������Ʈ ���� �����̴�.