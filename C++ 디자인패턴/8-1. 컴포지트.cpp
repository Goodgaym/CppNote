#include<iostream>
#include<array>     // array �ڷᱸ��
#include<numeric>   // accumulate �Լ�
#include<algorithm> // max_element �Լ�
using namespace std;

// ������Ʈ ����
// : � ��ü���� ���տ� ���� ���� �������̽��� �����ϰ� ������ �� �ְ� �ϴ� ��

/* 
class Creature {
    int strength, agility, intelligence;
public:
    int get_strength() const{
        return strength;
    }
    
    void set_strength(int strength){
        Creature::strength = strength;
    }

    // �ٸ� get/set ��� �Լ���...
};
*/

// ��踦 ������ �ܼ��ϰ� ������ ���� ������ �Ѵ�. ������ �ٶ������� �ʴ�...

/* 
class Creature{
    int strength, agility, intelligence;
    // �ٸ� �����...
    int sum() const {
        return strength + agility + intelligence;
    }
    double average() const {
        return sum() / 3.0;
    }
    int max() const {
        return ::max(::max(strength, agility), intelligence);
    }
} 
*/

// ������ ���� ������ �ٶ������� �ʴ�.
// - ��ü �հ踦 ����� �� �ʵ� �� �ϳ��� ���߸��� ����.
// - ����� ����� �� ����� 3.0�� ���ǰ� �ִ�. �� ���� �ʵ��� ������ �ٲ𶧸��� �ٲ��� �ؼ� �ǵ�ġ���� ���Ӽ��� �߱��Ѵ�.
// - �ִ� ���� ���� �� ��� �ʵ� �� �ָ��� std::max()�� �ݺ� ȣ���ؾ� �Ѵ�.

// ���� ������� �迭��� �Ӽ��� �ִ�.

class Creature {
    enum Abilities{ str, agl, intl, count};
    array<int, count> abilities;

    // ���� ��, ������ �� ���� get/set ��� �Լ��� ������ �� �ִ�.
    int get_strength() const { return abilities[str]; }
    void set_strength(int value) { abilities[str] = value;}
    // �ٸ� �Ӽ��鵵 ���� ������� get/set ����...

    // ���� sum(), average(), max()�� ������ ����� ��������.
    int sum() const{
        return accumulate(abilities.begin(), abilities.end(), 0);
    }
    
    double average() const {
        return sum() / (double)count;
    }

    int max() const{
        return *max_element(abilities.begin(), abilities.end());
    }
};