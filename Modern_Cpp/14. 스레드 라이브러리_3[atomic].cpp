#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

//atomic ��ü�� ����ϸ� �� �ٸ� ����ȭ �۾����� �����ڿ��� ����� �� �ִ�.
void func(atomic<int> &a, int t, int n){
    for(int i =0; i<t; i++){
        cout << "thread" << n <<" :" << a++ <<endl;
        this_thread::sleep_for(1s);
    }
}

int main(){
    atomic<int> a(1); // atomic�� Ŭ�����̴�. ������ �ʱ�ȭ, ������ �ʱ�ȭ ����

    thread t1(func, ref(a), 5, 1);
    thread t2(func, ref(a), 5, 2);
    thread t3(func, ref(a), 5, 3);
    
    t1.join();
    t2.join();
    t3.join();
}