#include<iostream>
#include<memory>
#include<map>
#include<functional>
using namespace std;

// # �߻����͸�
// �׵��� ��ü �Ѱ��� �����ϴ� ��츦 ����ô�. �幰���� ���� ������ ������ ��ü�� �����ؾ� �� ��쵵 �ִ�.
// �߻� ���͸��� �׷��� ��츦 ���� �����̴�.

// �߰ſ� ���� Ŀ�Ǹ� �Ǹ��ϴ� ī�並 ��ؾ��Ѵٰ� ����������, �� ������� �ٸ� ��� �̿��� ���������.
// ������ ���� �߰ſ� ���Ḧ �߻�ȭ�ϴ� HotDrink�� �����Ѵ�.
struct HotDrink{
    virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink{
    void prepare(int volume) override{
        cout << "Take tea bag, boil water, pour "<< volume <<"ml, add some lemon" << endl;
    }
};

struct Coffee : HotDrink{
    void prepare(int volume) override{
        cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!" << endl;
    }
};

// make_drink �Լ��� ������ ����� ����.
/*
unique_ptr<HotDrink> make_drink(string type){
    unique_ptr<HotDrink> drink;
    if(type == "tea"){
        drink = make_unique<Tea>();
        drink->prepare(200);
    }
    else{
        drink = make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}
*/
// �׷��� ���� Ŀ�Ǹ� ����� ���� �ٸ���. ���� ���͸��� ������ �Ѵ�.

struct HotDrinkFactory{
    virtual unique_ptr<HotDrink> make() const = 0;
};
// �� ���͸��� �߻� ���͸��̴�.
// � Ư�� �������̽��� �����ϰ� ������ ���� Ŭ������ �ƴ� �߻� Ŭ�����̴�.

// �Ʒ��� ���� �ڽ� Ŭ������ ����Ŭ�����μ� ���� �� �ִ�.

struct TeaFactory : HotDrinkFactory{
    unique_ptr<HotDrink> make() const override{
        return make_unique<Tea>();
    }
};

struct CoffeeFactory : HotDrinkFactory{
    unique_ptr<HotDrink> make() const override{
        return make_unique<Coffee>();
    }
};
// ���� �� �� ���� ���ؿ��� �ٸ� ������ ���Ḧ ������ �Ѵٰ� ������ ����
// �߰ſ� ���� �Ӹ� �ƴ϶� ������ ���ᵵ ���� �� �־�� �Ѵ�.
// �̸� ���� DrinkFactory�� �ξ� ��� ������ �پ��� ���͸��鿡 ���� ������ ���ο��� �������� �� �� �ִ�.

class DrinkFactory{
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory(){
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
        hot_factories["Tea"] = make_unique<TeaFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string& name){
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};

// # �Լ��� ���͸�
// ���͸���� ���Ҷ� �� ���� �� �ϳ��� �ǹ��Ѵ�.
// - ��ü�� ��� �����ϴ��� �˰� �ִ� � Ŭ����
// - ȣ������ �� ��ü�� �����ϴ� �Լ�
// 2��°�� ���� ���͸� �޼����� ������ ���� ������ ���͸���� �θ���. �޼���� ��ü�� ����Լ��� �ǹ��Ѵ�.

// �Լ��� ������ ����� �� �ִ�. ��, ���͸��� �����͸� �����ϴ� ��� ��ſ� 200ml�� ���Ḧ �����ϴ� ���� ��ü�� ���͸��� �����ϰ� �� �� �ִ�.
class DrinkWithVolumeFactory{
    map<string, function<unique_ptr<HotDrink>()>> factories;
public:
    DrinkWithVolumeFactory(){
        factories["tea"] = []{
            auto tea = make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };
        factories["coffee"] = []{
            auto coffee = make_unique<Coffee>();
            coffee->prepare(50);
            return coffee;
        };
    }
    unique_ptr<HotDrink> make_drink(const string& name);
};

// ����� ���͸��� ���� ȣ���ϴ� ������ ������ ���� ���� �� �� �ִ�.
inline unique_ptr<HotDrink> DrinkWithVolumeFactory::make_drink(const string& name){
    return factories[name]();
}
// �� �ڵ�� �����ϰ� ����ڰ� �̿��� �� �ִ�.
int main(){
    DrinkFactory df;
    df.make_drink("Tea");

    DrinkWithVolumeFactory dv;
    dv.make_drink("coffee");
    return 0;
}