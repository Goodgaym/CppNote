#include<iostream>
#include<vector>
#include<memory>
#include<math.h>

#include<boost/container_hash/hash.hpp>
using namespace std;
using namespace boost;

// ���� �ڵ�� ������ �Ǵ� ��Ȳ�� �ִ�. ȭ���� ������Ʈ �ɶ����� DrawPoints()�� �Ҹ��� ��츦 �����Ѵ�.
// ���� �ٲ� ���� ������ ������ ���е��� ����Ϳ� ���� �ݺ������� ������ ��ȯ�ȴ�.
// ��ȿ������ �ߺ� �۾��� ���ϱ� ���� ĳ���� �̿��Ѵ�.

// ��� ���ø����̼��� �⵿�� �� �̸� ����͸� �̿��� ������ �ΰ� ��Ȱ���ϴ� ���̴�.
// <3:MainCode>


struct Point{
    int x, y;
    
    friend size_t hash_value(const Point& obj){
        size_t seed = 0x725C686F;
        boost::hash_combine(seed, obj.x);
        boost::hash_combine(seed, obj.y);
        return seed;
    }
};

struct Line{
    Point start, end;
    
    friend size_t hash_value(const Point& obj){
        size_t seed = 0x725C686F;
        boost::hash_combine(seed, obj.x);
        boost::hash_combine(seed, obj.y);
        return seed;
    }
};

struct VectorObject{
    virtual vector<Line>::iterator begin() = 0;
    virtual vector<Line>::iterator end() = 0;
};

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
//<2:MainCode>

int main(){
    
    // <1>
    vector<shared_ptr<VectorObject>> vectorObjects{
        make_shared<VectorRectangle>(10, 10, 100, 100),
        make_shared<VectorRectangle>(30, 30, 60, 60)
    };
    /*
    // <2>
    for(auto& obj : vectorObjects){
        for(auto line : *obj){
            LineToPointAdapter lpo{line};
            DrawPoints(dc, lpo.begin(), lpo.end());
        }
    }
    */

    // <3>
    vector<Point> points;
    for(auto& o : vectorObjects){
        for(auto& l : *o){
            LineToPointAdapter lpo{l};
            for(auto& p : lpo){
                points.push_back(p);
            }
        }
    }

	//DrawPoints(hdc, points.begin(), points.end());

    return 0;
}
