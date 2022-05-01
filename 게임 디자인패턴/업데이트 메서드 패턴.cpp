#include <iostream>
using namespace std;

#define MAX_ENTITIES 256

// �ൿ�� ������ �ִ� ���𰡸� ������ Entity Ŭ����
class Entity {
public:
    Entity() : x_(0), y_(0) {}
    virtual ~Entity(){}
    virtual void Update() =0;

    double x() const{ return x_;}
    double y() const{ return y_;}
    
    void setX(double x) {x_ = x;}
    void setY(double y) {y_ = y;}

private:
    double x_;
    double y_;
};

// ������ ������ �ִ� ���� Ŭ����
class World {
public:
    World() : numEntities_(0) {}
    void gameLoop();

private:
    Entity* entities_[MAX_ENTITIES];
    int numEntities_;
};

// ���� ����
void World::gameLoop(){
    while(true){
        // ���� �Է� ó��

        // Entity ���� ������� ������Ʈ ���ش�.
        for(int i=0; i<numEntities_; i++){
            entities_[i]->Update();
        }

        // ����, ������
    }
}

int main(){


    return 0;    
}