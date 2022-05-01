#include <iostream>
#include <sstream>
using namespace std;

// ��Ŀ������ ����
// : �̹� �����ϴ� Ÿ�Կ� ���ο� ����� �߰��ϸ鼭�� ���� Ÿ���� �ڵ忡 ������ ���� �� �ְ� ���ش�.

// �ó����� : ������ ��Ÿ���� Shape�� ������ �����ϰ� �ְ� �̸� ��ӹ޾� ������ �ִ� ������ ������ ������ �߰��Ѵ�.
//          ���߿� �ΰ��� �Ӽ��� ��� �ʿ�� �ϴ� ��찡 �߻��Ͽ� �߰��� Ŭ������ ����µ� ��������� �ΰ��� ����� �߰��ϱ� ����
//          Ŭ������ 3�� ����� �ȴ�. �̷����̸� ����� �ϳ� �߰��ɶ����� 7���� Ŭ������ ������ �� ���� �ִ�.
struct Shape{
    virtual string str() const =0;
};

struct Circle: Shape{
    float radius;

    explicit Circle (const float radius)
        : radius{radius} {}
    void resize(float factor){ radius *= factor;}

    string str() const override{
        ostringstream oss;
        oss<< "A circle of radius " << radius;
        return oss.str();
    }
}; // Square ������ ����

struct Square: Shape{
    float length;

    explicit Square (const float length)
        : length{length} {}
    void resize(float factor){ length *= factor;}

    string str() const override{
        ostringstream oss;
        oss<< "A square with side " << length;
        return oss.str();
    }
};
// ����� ������δ� ȿ�������� ���ο� ����� ������ �߰��� ���� ���ٴ� ���� �� �� �ִ�. ���� ���������� Ȱ���Ѵ�.
// �������� : ��Ŀ������ ���Ͽ��� ��ü�鿡 ���ο� ����� Ȯ���Ҷ� Ȱ��Ǵ� ��Ŀ����

// ���� �������� : ������ �ְ�����鼭 ��Ÿ�ӿ� �������� ���𰡸� �ռ��� �� �ְ� �Ѵ�.
// ���� �������� : ���ø��� �̿��Ͽ� ������ ������ �߰������ �ռ��ǰ� �Ѵ�.

// ���� ��Ŀ������

// ������ ���� ������ �Ѵٰ� ��������. ��Ӵ�� ������������ ColoredShape�� ���� �� �ִ�.
struct ColoredShape : Shape{
    Shape& shape;
    string color;

    ColoredShape(Shape& shape, const string& color)
        : shape{shape}, color{color}{}
    
    string str() const override{
        ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};    

// ������ ������ �ϰ� �ʹٸ� ������ ���� ������ �� �ִ�.
struct TransparentShape : Shape{
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape, const uint8_t transparency)
        : shape{shape}, transparency{transparency} {}

    string str() const override{
        ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

// ���� ������ 0..255 ������ �����ϸ� �װ��� �ۼ��������� ������ִ� ���ο� ����� �߰��Ǿ���.
    
// ���ϰ� ColoredShape�� TrnasparentShape�� �ռ��Ͽ� ����� ���� �� ��� ��� ������ ����ǵ��� �� �� �ִ�.

int main(){
    Circle circle{0.5f};
    ColoredShape redCircle{circle, "red"};
    cout << redCircle.str() << endl;
    // ��°�� "A circle of radius 0.5 has the color red"

    Square square{3};
    TransparentShape demiSquare{square, 85};
    cout << demiSquare.str() << endl;
    // ��°�� "A square with side 3 has 33.3333% transparency"

    Circle circle2{23};
    ColoredShape greenCircle{circle2, "green"};
    TransparentShape myCircle{greenCircle, 64};
    cout << myCircle.str() << endl;
    // ��°�� "A circle of radius 23 has the color green has 25.098% transparency"
    return 0;
}