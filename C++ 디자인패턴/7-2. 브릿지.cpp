#include<iostream>
using namespace std;

// Pimpl ���ʴ� �긴�� ������ Ư���� ��
// Renderer Ŭ������ ����, �����ͷ� �׸� �� �ִٰ� �Ѵ�.
// Renderer ���̽� Ŭ������ ������ ���� �����Ѵ�. 
struct Renderer{
    virtual void render_circle(float x, float y, float radius) = 0;
};

// ������ �׸��� �ʰ� �ֿܼ� �޼����� ����Ѵ�.
struct VectorRenderer : Renderer{
    void render_circle(float x, float y, float radius) override{
        cout << "Drawing a vector circle of radius " <<radius << endl;
    }
};
struct RasterRenderer : Renderer{
    void render_circle(float x, float y, float radius) override{
        cout << "Rasterizing circle of radius " << radius <<endl;
    }
};

// ���ϵ����� ���̽� Ŭ���� Shape�� �������� ���� ������ ������. 
// ���� ������ ��� �Լ� draw�� ���ؼ� �ڱ� �ڽ��� �׸� �� �ִ�. �߰������� ũ�� ������ �� �� �ִ� resize() ��� �Լ��� ������.

struct Shape{
protected:
    Renderer& renderer;
    Shape(Renderer& renderer): renderer{renderer}{}
public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

// renderer�� Renderer Ŭ������ ���� ������ ����Ǿ� �ִ�. ó������ �ǵ����� �ʾ����� �긴�� ������ �����ߴ�.

struct Circle: Shape{
    float x, y, radius;

    void draw() override{
        renderer.render_circle(x, y, radius);
    }

    void resize(float factor) override{
        radius *= factor;
    }
    Circle(Renderer& renderer, float x, float y, float radius)
     : Shape{renderer}, x{x}, y{y}, radius{radius}{}
};

// �긴���� �̿��� Circle�� ������ ������ �����ϴ� �κ��� draw()�ȿ� �����ȴ�. ���⼭ �긴���� Renderer�̴�.
// �������� �ڽ��� �ٷ�°��� Circle���� ���� �𸣰� �ڽ��� ���� ������ ���ٵǰ� �ִٴ� �͵� ���� ���Ѵ�.

int main(){
    RasterRenderer rr;
    Circle raster_circle{rr, 5, 5, 5};
    raster_circle.draw();
    raster_circle.resize(2);
    raster_circle.draw();

    return 0;
}
