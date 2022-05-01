#include <iostream>
#include <sstream>
using namespace std;

struct Shape {
    virtual string str() const = 0;
};

struct Circle : Shape {
    float radius;
 
    Circle(){}

    explicit Circle(const float radius)
        : radius{ radius } {}
    void resize(float factor) { radius *= factor; }

    string str() const override {
        ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape {
    float size;
    
    Square(){}

    explicit Square(const float size)
        : size{ size } {}
    void resize(float factor) { size *= factor; }

    string str() const override {
        ostringstream oss;
        oss << "A square with side " << size;
        return oss.str();
    }
};

// resize() ��� �Լ��� Shape �������̽��� ���谡 ���� ������ ��Ŀ�����Ϳ��� ȣ���� �� ����.
// ������ ��� ��� MixIn ����̶� �Ҹ��� ����� �̿��Ѵ�.

// static_assert�� �̿��� Shape�̿��� Ÿ���� �����Ǵ� ���� ���´�.

template <typename T> struct ColoredShape : T {
    static_assert(is_base_of<Shape, T>::value,
        "template argument must be a Shape");

    string color;

    ColoredShape(){}

    template <typename...Args>
    ColoredShape(const string& color, Args ...args)
        : T(std::forward<Args>(args)...), color{ color }{}
    // ���⼭ ���̽� Ŭ������ �Ҹ��ڸ� ȣ���� ���� ����.
    // �ֳĸ� �Ҹ��ڸ� �� ���� ���� �����̴�.

    string str() const override {
        ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};  // TransparentShape<T>�� ������ ����...

// ������ ��� �����ڸ� �ѹ��� ���ϰ� ȣ�� �ϴ� �κ��� �Ҿ���.

// ��Ŀ���̼��� �ϼ��ϱ� ���� ColoredShape�� TransparentShape�� �����ڸ� �����Ѵ�. �� �����ڵ��� �� ������ ���ڸ� �޴´�. 
// ù��° ���ڵ��� ������ ���ø� Ŭ������ ����Ǵ� �͵��̰� �ι�° ���ڵ��� �θ� Ŭ������ ���޵� ���׸� �Ķ���� ���̴�.

template <typename T> struct TransparentShape : T {
    static_assert(is_base_of<Shape, T>::value,
        "template argument must be a Shape");

    uint8_t transparency;

    TransparentShape(){}

    template<typename...Args>
    TransparentShape(const uint8_t transparency, Args ...args)
        : T(std::forward<Args>(args)...), transparency{ transparency }{}

    string str() const override {
        ostringstream oss;
        oss << T::str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

int main() {
    // ����Ʈ �����ڰ� ������ �������� �ʴ´�.
    ColoredShape<TransparentShape<Square>> square{ "blue" };
    square.size = 2;
    square.transparency = 50;
    cout << square.str() << endl;
    // ���� square�� � ����� ���� ����
    square.resize(3);
    
    // ���� �����ڴ� ���� ������ ������ ���ڸ� ���� �� �ִ�. ���� ������ �̿��غ���.
    ColoredShape<TransparentShape<Square>> sq = { "red", 51, 5 };
    cout << sq.str() << endl;
    // ��°�� "A square with side 5 has 20% transparency has the color red"

    return 0;
}