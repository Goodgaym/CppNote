#include<iostream>
#include<vector>
#include<memory>
#include<math.h>
using namespace std;

// # �ó�����
// �⺻���� �׸��� ��ü�� ��������.
struct Point{
    int x, y;
};

struct Line{
    Point start, end;
};

// �������� ������ ��� ���� �� �ֵ��� �Ϲ�ȭ �Ѵ�.
// vector<Line>�� ��ӹ޾� ǥ���� ���� ������ ���� ���� �Լ��� ������ ��������.
struct VectorObject{
    virtual vector<Line>::iterator begin() = 0;
    virtual vector<Line>::iterator end() = 0;
};

// ���� �簢�� Rectangle�� �������� ũ�⸦ �Է¹޾� �����ϰ�, 
// �簢���� �����ϴ� ���е��� vector<Line> Ÿ�� �ʵ忡 �����Ͽ� �� �������鸸 �����ϴ� ������� ������ �� �ִ�.

struct VectorRectangle : VectorObject{
    VectorRectangle(int x, int y, int width, int height){
        lines.emplace_back(Line{Point{x,y}, Point{x+width, y}});
        lines.emplace_back(Line{Point{x+width, y}, Point{x+width, y+height}});
        lines.emplace_back(Line{Point{x, y}, Point{x, y+height}});
        lines.emplace_back(Line{Point{x, y+height}, Point{x+width, y+height}});
    }

    vector<Line>::iterator begin() override{
        return lines.begin();
    }

    vector<Line>::iterator end() override{
        return lines.end();
    }

private:
    vector<Line> lines;
};

// ���� �簢�� �׸��� �׸��ٰ� ����. ������ �׷��� �� �� ����. �Ʒ� �������̽��� ���� �Ǿ��ֱ� �����̴�.
// (MFC ���̺귯���� CPaintDC Ŭ����)
/*

void DrawPoints(CPaintDC& dc, std::vector<Point>::iterator start, std::vector<Point>::iterator end){
    for(auto i = start; i!= end; ++i)
        dc.SetPixel(i->x, i->y, 0);
}

// �׸��� �������̽��� ���� ��� �͹ۿ� ������ �츮�� ������ �׷��� �Ѵ�.
*/

// # �����
/* �簢�� ��� �׷��� �Ѵٰ� ��������.
<1:MainCode>
*/

// �� ��ü���� �׸��� ���ؼ��� �簢���� �̷�� ������ ���տ��� ������ ���и��� ���� ���� ���� ��ȯ�Ǿ�� �Ѵ�.
// �̸� ���� ������ Ŭ������ �����.

struct LineToPointAdapter{
    typedef vector<Point> Points;
    LineToPointAdapter(Line& line){
        int left = min(line.start.x, line.end.x);
        int right = max(line.start.x, line.end.x);
        int top = min(line.start.y, line.end.y);
        int bottom = max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;
        
        if(dx == 0){
            for(int y = top; y <= bottom; ++y){
                points.emplace_back(Point{left, y});
            }
        }
        else if(dy == 0){
            for(int x = left; x <= right; ++x){
                points.emplace_back(Point{x, top});
            }
        }
    }

    virtual Points::iterator begin() {return points.begin();}
    virtual Points::iterator end() {return points.end();}
private:
    Points points;
};

//
// <2:MainCode>

int main(){
    /*
    <1>
    vector<shared_ptr<VectorObject>> vectorObjects{
        make_shared<VectorRectangle>(10, 10, 100, 100),
        make_shared<VectorRectangle>(30, 30, 60, 60)
    };
    
    <2>
    for(auto& obj : vectorObjects){
        for(auto line : *obj){
            LineToPointAdapter lpo{line};
            DrawPoints(dc, lpo.begin(), lpo.end());
        }
    }
    */
    return 0;
}
