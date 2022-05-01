#include<iostream>
using namespace std;

#define BUTTON_LEFT 37
#define BUTTON_UP 38
#define BUTTON_RIGHT 39
#define BUTTON_DOWN 40

// temp key define
#define BUTTON_X 65
#define BUTTON_Y 66
#define BUTTON_A 67
#define BUTTON_B 68

class Unit{
public:
    Unit(){ x_ = 0; y_ = 0;}
    Unit(int x, int y) : x_(x), y_(y){}
    void moveTo(int x, int y){
       x_ = x;
       y_ = y; 
    }

    int getX(){ return x_;}
    int getY(){ return y_;}
    void setX(int x){ x_ = x;}
    void setY(int y){ y_ = y;}
private:
    int x_;
    int y_;
};

class GameActor{
public:
    GameActor(){
        unit_ = new Unit(0,0);
    }
    void jump(){
        cout << "����" << endl;
    }
    void fire(){
        cout << "�߻�" << endl;
    }
    Unit* getUnit(){return unit_;}
private:
    Unit* unit_;
};
// �� �� �ִ� �ൿ�� ������ �� �ִ� ���� Ŭ���� Command
class Command{
public:
    virtual ~Command(){}
    virtual void excute(GameActor& actor)=0;
    virtual void undo()=0;
};

// ������ �ൿ�� �ִ� ���� Ŭ������
class JumpCommand : public Command {
public:
    virtual void excute(GameActor& actor){
        actor.jump();
    }
};

class FireCommand : public Command {
    virtual void excute(GameActor& actor){
        actor.fire();
    }
};

class MoveUnitCommand : public Command {
public:
    MoveUnitCommand(Unit* unit, int x, int y)
    : unit_(unit), x_(x), y_(y),
    xBefore_(0), yBefore_(0){}

    virtual void excute(){
        xBefore_ = unit_->getX();
        yBefore_ = unit_->getY();
        unit_->moveTo(x_, y_);
    }
    virtual void undo(){
        unit_->moveTo(xBefore_, yBefore_);
    }
    virtual void excute(GameActor& actor){
        actor.getUnit()->moveTo(x_, y_);
    }
private:
    Unit* unit_;
    int x_, y_;
    int xBefore_, yBefore_;
};


// ���� ��ư�� ���� �ൿ�� ���� �����͸� ������ �ִ� InputHandler
class InputHandler{
public:
    Command* handleInput();
    // ����� ���ε�(bind)�� �޼����..

private:
    Command* buttonX_;
    Command* buttonY_;
    Command* buttonA_;
    Command* buttonB_;
};
Unit* getSelectedUnit(){
    return new Unit();
}
// �Է�ó���� �������� ���ӵȴ�.
bool isPressed(char Button){
    return true;
};
Command* InputHandler::handleInput(){
    if(isPressed(BUTTON_X)) return buttonX_;
    if(isPressed(BUTTON_Y)) return buttonY_;
    if(isPressed(BUTTON_A)) return buttonA_;
    if(isPressed(BUTTON_B)) return buttonB_;
    
    Unit* unit = getSelectedUnit();
       if(isPressed(BUTTON_UP)) {
        int destY = unit->getY() + 1;
        return new MoveUnitCommand(unit, unit->getX(), destY);
    }
    if(isPressed(BUTTON_DOWN)) {
        int destY = unit->getY() - 1;
        return new MoveUnitCommand(unit, unit->getX(), destY);
    }
    if(isPressed(BUTTON_LEFT)) { 
        int destX = unit->getX() - 1;
        return new MoveUnitCommand(unit, destX, unit->getY());
    }
    if(isPressed(BUTTON_RIGHT)) {
        int destX = unit->getX() + 1;
        return new MoveUnitCommand(unit, destX, unit->getY());
    }
    return NULL;
}

int main(){
    GameActor actor;
    InputHandler inputHandler;

	Command* command = inputHandler.handleInput();
    if(command) {
        command->excute(actor);
    }
}