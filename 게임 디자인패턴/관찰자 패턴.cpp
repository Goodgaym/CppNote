#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define MAX_OBSERVERS 10

enum State{
    IDLE, MOVE, GRAVITY};
enum Event{
    EVENT_START_FALL
};
enum Achivement{
    ACHIVEMENT_FELL_OF_BRIDGE
};

class Unit{
public:
    Unit(int x, int y) : x_(x), y_(y){}
    int x_, y_;
};

class Entity{
public:
    Entity(Unit* unit): unit(unit){}
    bool isOnSurface(){
        if(this->unit->y_==0)
            return true;
        else 
            return false;
    }
    void accelerate(State id){
        switch(id){
        case GRAVITY:
            unit->y_ -= 1;
        }
    }
    void update(){

    }
    bool isHero(){return true;}
private:
    Unit* unit;
};

class Observer{
public:
    virtual void onNotify(Entity& entity, Event event) = 0;
};

class Achivements : public Observer{
public:
    Achivements():heroIsOnBridge_{true}{}
    ~Achivements(){}
    void onNotify(Entity& entity, Event event) override{
        switch(event){
        case EVENT_START_FALL:
            if(entity.isHero() && heroIsOnBridge_)
                unlock(ACHIVEMENT_FELL_OF_BRIDGE);
            break;
        // �� �� �ٸ� �̺�Ʈ�� ó���ϰ�..
        // heroIsOnBridge_ ���� ������Ʈ �Ѵ�. 
        default:
            break;
        }
    }
    
private:
    void unlock(Achivement achivement){
        // ���� ������ ����ִٸ� ��������Ѵ�.
        switch(achivement){
        case ACHIVEMENT_FELL_OF_BRIDGE:
            cout << "�ٸ����� �������� ���� ����" << endl;
            break;
        default:
            break;
        }
    }
    bool heroIsOnBridge_;    
};

class Subject{
public: 
    void addObservers(Observer* observer){
        if(find(begin(observers_), end(observers_), observer) == end(observers_))
            observers_.push_back(observer); 
    } 
    void removeObservers(Observer* observer){
        if (observers_.empty()) return;
		for (auto it = observers_.begin(); it != observers_.end(); ++it){
			if (*it == observer){
				*it = nullptr; // �׳� nullptr�� ǥ���Ѵ�
			}
		}
    }
protected:
    void notify(Entity& entity, Event event){
        for(auto ob : observers_){
            ob->onNotify(entity, event);
        }
    }
private:
    vector<Observer*> observers_;
};

class Physics : public Subject{
public:
    void updateEntity(Entity& entity);
};

void Physics::updateEntity(Entity& entity){
    bool wasOnSurface = entity.isOnSurface();
    entity.accelerate(GRAVITY);
    entity.update();

    if(wasOnSurface && !entity.isOnSurface()){
        notify(entity, EVENT_START_FALL);
    }
}

int main(){
    Entity hero{new Unit(0,0)};
    
    Achivements cpfall;
    Physics heroPhy;
    heroPhy.addObservers(&cpfall);
    heroPhy.updateEntity(hero);
    return 0;
}