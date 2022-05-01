#include<iostream>
#include<atomic>
#include<mutex>
using namespace std;
// # ������ü�μ��� �̱���
// �ս��� �����ڰ��� ����� �Ͽ� �ּ� ������ �� �ѹ��� �ν��Ͻ� �ϵ��� �ϴ� ���̴�.
/*
struct Database{
    /** 
     * \brief �� ��ü�� �� �� �̻� �ν��Ͻ�ȭ ���� ���ÿ�.
     */
    /*
    Database(){}
};

// ������ �ǵ����� ���� ������ ������� �����ڰ� ȣ��Ǿ� ���� ���� �ִ�.
// ���� ������ ���̵��� static ���� ��ü�� �δ°��̴�.

static Database database{};

// static ������ü�� �������� ������ ������ ���� ���̳ʸ��鿡�� �ʱ�ȭ ������ ���ǵǾ� ���� �ʴٴ� ���̴�.
// ������ü�� ���� �� ���ȴٸ� ��� �� ��⿡�� ���� ��ü�� ������ �� �� ���� ��ü�� �����ϴ� �� �ٸ� ���� ��ü�� ���� �ʱ�ȭ�� ���°� �ƴ� �� �ִ�.
// �׸��� ����ڰ� ������ü�� �ִٴ� ����� ��� �� �� �ִ��� �ϴ� ������ �ִ�.

Database& get_database(){
    static Database database;
    return database;
}

*/
// �� �Լ��� ȣ���ϸ� �����ͺ��̽��� ������ �� �ִ� ������ ���� �� �ִ�.
// ������ ������ �������� C++11 �̻� ���������� �����ȴ�.
// static ��ü�� �ʱ�ȭ �ϴ� �ڵ� �յڷ� �����Ϸ��� ���� �������ִ��� Ȯ���ؾ� �Ѵ�.
// �̱����� �ٸ� �̱����� �����ص� �Ǵ°�?

// # �������� ����

/*
struct Database{
    Database(){
        static int instance_count{0};
        if (++instance_count > 1){
            throw std::runtime_error("Cannot make >1 database!");
        }
    }
};
*/

// �̷��� �����ϰ� �Ǹ� ����� ���� ���鿡�� �����ڰ� �� �ѹ��� ȣ��Ǿ�� �ϴ� ���� �� �� ����.
// ��������� �����ϴ� ���� ���� ����� �����ڸ� private�� �����ϰ� �ν��Ͻ��� ���Ϲޱ� ���� ��� �Լ��� ����� ���̴�.

struct Database{
protected:
    Database(){
        // ��Ÿ �ʿ��� �۾�
    }
    static atomic<Database*> istc;
    static mutex mtx;

public:
    static Database& get(){
        // C++11 �̻� ���������� ������ ������ ��
        static Database database;
        return database;
    }
    Database(Database const&) = delete;
    Database(Database&&) = delete;
    Database& operator=(Database const&) = delete;
    Database& operator=(Database &&) = delete;  

    // C++11 ���������� �������� ��ŷ ������� �����ڸ� ��ȣ�ؾ� �Ѵ�.
    static Database& instance();   
};

// ��Ƽ ������ �������� ���� �����ڸ� ��ȣ�Ѵ�. (������ boost�� ����ؾ���)
Database& Database::instance(){
    Database* db = istc.load(memory_order_consume);
    if(!db){
        lock_guard<mutex> guard(mtx);
        db = istc.load(memory_order_consume);
        if(!db){
            db = new Database();
            istc.store(db, memory_order_release);
        }
    }
}

// �� �ڵ忡�� �����ڸ� ����� ����/�̵� ������/�����ڸ� �����Ѵ�.
int main(){
    return 0;
}