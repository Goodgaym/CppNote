#include<iostream>

// �ӽ� Ű
#define PRESS_B 'B'
#define PRESS_DOWN 40
#define RELEASE_DOWN 41

// ���¸� ���������� ����
enum State{
    STATE_STANDING,
    STATE_JUMPING,
    STATE_DUCKING,
    STATE_DIVING
};

// �ӽ� Ű �Է��� ���� �ӽ� Ŭ����
struct Input{
    bool operator==(char&& input){
        if(input == key)
            return true;
        else
            return false;
    }
private:
    char key;
};

// ���¸� ����� Heroine Ŭ����
struct Heroine{
    Heroine(int maxCharge, int jumpVelocity)
     : MAX_CHARGE(maxCharge),
       JUMP_VELOCITY(jumpVelocity){} 

    void superBomb();
    
    virtual void handleInput(Input);
    virtual void update();

    const int MAX_CHARGE;
    const int JUMP_VELOCITY;

    HeroineState state_;
private:
};

// ���¸� ������ �� ȣ���ϴ� handleInput �Լ�
void Heroine::handleInput(Input input){
    // ���� ������ input�� ���� ���°� ����ȴ�.
    HeroineState* state = state_->handleInput(*this, input);
    if(state != NULL){
        delete state_;
        state_ = state;
    }
}
void Heroine::update(){
    state_->update(*this);
}

// ���� �������̽�
class HeroineState{
public:
    virtual ~HeroineState(){}
    virtual HeroineState* handleInput(Heroine& heroine,Input input){}
    virtual void update(Heroine& heroine){}

    static StandingState standing;
    static DuckingState ducking;
    static JumpingState jumping;
    static DivingState diving;
};

///////////////////////////////////////////////////////////////
// �Ʒ��� ���� �������̽��� ��ӹ޴� ���µ�

class DuckingState: public HeroineState {
public:
    DuckingState() : chargeTime_{0}{}

    virtual HeroineState* handleInput(Heroine&, Input);
    virtual void update(Heroine&);
private:
    int chargeTime_;
};

HeroineState* DuckingState::handleInput(Heroine& heroine, Input input){
    if(input == RELEASE_DOWN){
        heroine.state_ = &HeroineState::standing;
        //heroine.setGraphics(IMAGE_STAND);
    }
}

void DuckingState::update(Heroine& heroine){
    chargeTime_++;
    if(chargeTime_ > heroine.MAX_CHARGE){
        heroine.superBomb();
    }
}
//////////////////////////////////////////////////////////////////
class StandingState: public HeroineState {
public:
    StandingState(){}

    virtual HeroineState* handleInput(Heroine&, Input);
    virtual void update(Heroine&);
private:
};
HeroineState* StandingState::handleInput(Heroine& heroine, Input input){}
void StandingState::update(Heroine& heroine){}

//////////////////////////////////////////////////////////////////
class JumpingState: public HeroineState {
public:
    JumpingState(){}

    virtual HeroineState* handleInput(Heroine&, Input);
    virtual void update(Heroine&);
private:
};
HeroineState* JumpingState::handleInput(Heroine& heroine, Input input){}
void JumpingState::update(Heroine& heroine){}

//////////////////////////////////////////////////////////////////
class DivingState: public HeroineState {
public:
    DivingState(){}

    virtual HeroineState* handleInput(Heroine&, Input);
    virtual void update(Heroine&);
private:
};
HeroineState* DivingState::handleInput(Heroine& heroine, Input input){}
void DivingState::update(Heroine& heroine){}
