#include <cstdio>
using namespace std;
#define EPSILON 0.0001

// ���� ���͸� ǥ���ϴ� ����ü�� �����մϴ�.
struct Vector2{
double x, y;
//������
Vector2(double _x, double _y){
x = _x, y = _y;
}
//����
double cross(const Vector2& other) const{
return x*other.y-y*other.x;
}

/* ������ �����ε��� ���� ���� ������ ������ �����մϴ�. */

//������ �Ǽ���
Vector2 operator * (double r) const{
	return Vector2(x*r, y*r);
}
//������ ����
Vector2 operator + (Vector2 other) const{
	return Vector2(x + other.x, y + other.y);
}
//������ ����
Vector2 operator - (Vector2 other) const{
	return Vector2(x - other.x, y - other.y);
}
//�� ������ ��
bool operator == (Vector2 other) const{
	return x == other.x && y == other.y;
}
bool operator < (Vector2 other) const{
	return x < other.x && y < other.y;
}
};

bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x){
	double det = (b - a).cross(d - c);
	// �� ���� ������ ���
}