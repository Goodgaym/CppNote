#include<iostream>

// 모노스테이트는 싱글턴의 변형이다.
// 겉보기엔 일반 클래스 같지만 싱글턴처럼 동작한다.

class Printer{
    static int id;

public:
    int get_id() const{ return id;}
    void set_id(int value) { id = value;}
};

// static 데이터를 이용하여 get/set 멤버함수가 구현되어 있다.
// 문제는 사용자가 일반 클래스로 알고 인스턴스를 만들어 다른 ID를 부여하지만 두 객체의 ID는 모두 같아진다.
/* 모노스테이트의 장단점
    장점
    - 상속받기 쉬워 다형성을 활용할 수 있다.
    - 생존 주기가 적절히 잘 정의된다.
    - 시스템에서 사용 중인 이미 존재하는 객체를 수정하여 이용할 수 있다.

    단점
    - 코드 깊숙이 손을 댄다. (일반 객체를 모노스테이트로 변환하는 것은 간단하지 않다.)
    - static 멤버를 사용하기 때문에 실제 객체가 인스턴스화되어 사용되는지와 관계없이 항상 메모리를 차지한다.
    - 클래스의 필드들이 항상 get/set 멤버 함수를 통해서만 접근되는 것으로 가정한다.
*/
int main(){
    Printer p;

    return 0;
}