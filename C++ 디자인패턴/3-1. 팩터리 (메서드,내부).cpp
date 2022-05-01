#include<iostream>
#define _USE_MATH_DEFINES
#include<math.h>
using namespace std;

/* # �ó����� 
    ���� ��ǥ���� ��ǥ�� ������ �����Ϸ� �Ѵٰ� �ϸ� �Ʒ��� ���� ������ ���̴�.

    ������ǥ�谡 �ƴ� ����ǥ���� ��ǥ������ �����Ѵٰ� �ϸ� ������ �ȴ�.
    ���� �����ϸ� ����ǥ��� �����ڸ� �߰��ϸ� ���� ������ ������ ���� ��ǥ���� �����ڿ� ������ �Ұ����ϴ�.

struct Point{
    // ���� ��ǥ�� ������
    Point(const float x, const float y)
        : x{x}, y{y} {} 

    // �� ��ǥ�� ������
    Point(const float r, const float theta){
        x = r * cos(theta);
        y = r * sin(theta);
    }

    // �ΰ��� ������ �����ε��� ��ģ��... (float, float)

    float x, y; // ���� ��ǥ�� ��ǥ��
}

    �Ѱ��� �ܼ��� ����� ��ǥ�� ������ �����ϴ� enum Ÿ���� �����ϰ�
    
enum class PointType{
    cartesian,
    polar
};

    ��ǥ�� �����ڿ� ��ǥ�� ������ �����ϴ� �Ķ���͸� �߰��Ѵ�.

    Point(float a, float b, PointType type = PointType::cartesian){
        if(type == PointType::cartesian){
            x = a; y = b;
        }
        else {
            x = r * cos(theta);
            y = r * sin(theta);
        }
    }

    �̷��� ���� ����ϸ� �������� �Ķ���� �̸��� a b�� �Ǿ� ������ ������ ���������� ���
    ������ �ϴ� �Ķ�������� �ǹ̸� �����ϱ� ��ƴ�.
*/

/* # ���͸� �޼���

struct Point{
    float x, y;
protected:
    Point(const float x, const float y)
        : x{x}, y{y} {}
public:
    static Point NewCartesian(float x, float y){
        return {x, y};
    }
    static Point NewPolar(float r, float theta){
        return {r* cos(theta), r* sin(theta)};
    }
};

 ���⼭ static �Լ����� ���͸� �޼����� �θ���.
 �̷��� �޼��尡 �ϴ����� Point ��ü�� �����Ͽ� �����ϴ� �� ���̴�.
 ���� ��ǥ���� ����Ҷ� ������ ���� ��Ȯ�ϰ� �� �� �ִ�.
 <1><main code>
*/

/* # ���͸�
//  ������ ���������� Point�� �����ϴ� �Լ����� ������ Ŭ������ ���� ���� �� �ִµ� �׷��� Ŭ������ ���͸���� �θ���.
//  ���� Point Ŭ������ ������ ���� �����Ѵ�.

struct Point {
    float x,y;
    friend class PointFactory;
private:
    Point(float x, float y) : x(x), y(y) {}
};
    �����ܺ� �κ��� �ΰ��� �ִ�.
    - Point�� �����ڴ� private�� ����Ǿ� ����ڰ� ���� �����ڸ� ȣ���� �� ���� �Ѵ�.
    - Point�� PointFactory�� frined Ŭ������ �����Ѵ�. �̺κ��� ���͸��� Point�� �����ڿ� ������ �� �ְ� �Ϸ��� �ǵ��̴�.

 ���� ������ Ŭ���� PointFactory�� New-() �Լ����� �����ϱ⸸ �ϸ� �ȴ�.
struct PointFactory{
    static Point NewCartesian(float x, float y){
        return Point{x, y};
    }
    static Point NewPolar(float r, float theta){
        return Point{r* cos(theta), r* sin(theta)};
    }
};

 ���� ������ ���� �ν��Ͻ��� ������ �� �ִ�.
 <2><main code>
*/
/* # �������͸�
    ���� ���͸��� ������ Ÿ���� ���� Ŭ�����μ� �����ϴ� ������ ���͸��� ���Ѵ�.
    C#, �ڹ� �� friend Ű���忡 �ش��ϴ� ������ ���� ���α׷��� ���鿡���� ���� ���͸��� ���ϰ� ����Ѵ�.

 ���� ���͸��� ������ ������ Ÿ���� ���� Ŭ�����̱� ������ private ����鿡 �����ο� ���� ������ �����ٴ� ���̴�.
*/
struct Point{
private:
    Point(float x, float y) : x{x}, y{y} {}
    struct PointFactory{
    private:
        PointFactory(){}

    public:
        static Point NewCartesian(float x, float y){
            return Point{x, y};
        }
        static Point NewPolar(float r, float theta){
            return Point{r* cos(theta), r* sin(theta)};
        }
    };

public: 
    float x, y;
    static PointFactory Factory;
};

// �̷��� ����� ���͸��� �����ؾ��� Ŭ������ �� �������϶� ���������� 
// ����Ÿ���� Ȱ���Ͽ� ��ü�� �����ؾ� �Ѵٸ� ���� ���͸� ������ �������� �ʴ�.
// <3><main code>

// :: �� .�� ����ų� Point�� �ߺ��Ǽ� �ԷµǴ� ���� ������ �������� �ʴ´ٸ�
// ���͸��� public���� �ΰų� typedef�� ����ϸ� �ȴ�.

int main(){
    /* 
    <1>
    auto p = Point::NewPolar(5, M_PI_4);

    <2>
    auto my_point = PointFactory::NewCartesian(3, 4);
    */
    auto pp = Point::Factory.NewCartesian(2,3);
    
    //
    return 0;
}