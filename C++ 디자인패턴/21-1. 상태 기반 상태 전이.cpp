#include<iostream>

// # ���� ��� ���� ����
// ���� ����ġ�� �𵨸��غ���. ���� ���� �ٸ� ���·� ������ ������ ������ �ȴ�.
class State{
    virtual void on(LightSwitch *ls){
        std::cout << "Light is already on\n";
    }
    virtual void off(LightSwitch *ls){
        std::cout << "Light is already off\n";
    }
};

class OffState:public State{};
class OnState:public State{};

class LightSwitch{
    State *state;
public:
    LightSwitch(){
        state = new OffState();
    }
    void set_state(State* state){
        this->state = state;
    }
};

