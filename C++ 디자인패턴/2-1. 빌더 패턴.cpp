#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<memory>
using namespace std;

struct HtmlBuilder;

// ���� ������ ������ ��ٷο� ��ü�� ���� ó���ϱ� ���� �����̴�.
// ��, ������ ȣ�� �ڵ� �� �� �ٷ� ������ �� ���� ��ü�� �ٷ��.

/* �ó�����
    �� �������� �׸������� ������Ʈ���� �����ؾ� �Ѵٰ� �Ҷ� 
    ������ HtmlElement�� �����ϴ� ������ ����ȭ �Ѵ�.
*/
/*
struct HtmlElement{
    string name;
    string text;
    vector<HtmlElement> elements;

    string str(int indent = 0) const{
        // �������� ��Ŀ� ���߾� ���
    }
   
    HtmlElement(){}
    HtmlElement(const string& name, const string& text) 
        : name(name), text(text){}

};
*/
// - �ܼ��� ����
// ���� ������ �ܼ��ϰ� ���� ��ü�� ������ ������ �ٸ� Ŭ������ �����Ѵ�.
/*
struct HtmlBuilder{
    HtmlElement root;

    HtmlBuilder(string root_name) {root.name = root_name;}

    *//*
    void add_child(string child_name, string child_text){
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
    }
    *//*
    HtmlBuilder& add_child(string child_name, string child_text){
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);

        return *this;
    }
    
    string str() {return root.str();}
};
*/
// HtmlBuilder�� HTML ��������� �������� �����ϴ� Ŭ�����̴�.
// add_child()�� ���� ��ҿ� �ڽĿ�Ҹ� �߰��ϴ� �������� ���ȴ�.
// �� Ŭ������ ��ºκ� �Ʒ��� ���� ���ȴ�.
// <1><main code>
// add_child()�� ���ϰ��� ���Ǵ°��� ���µ� ���ϰ��� Ȱ���� ���� �帧�� �������̽� ��Ÿ���� ���� �� �ִ�.

// - �帧�� ����
// ������ ���� ���� �ڱ� �ڽ��� �����ϵ��� �����Ѵ�.
// <HtmlBuilder Code>
// ���� �ڱ��ڽ��� ���ϵǱ� ������ ������ ���� �޼������ ������ ���� ȣ���� ����������.
// �̷��� ���·� ȣ���ϴ� ���� �帧�� �������̽���� �θ���.
// <2><main code>
// ������ �����ͷ� ���� ������ ������ �������� ������δ�.

// - �ǵ� �˷��ֱ�
// ����ڰ� ���� Ŭ������ ����ؾ� �Ѵٴ� ���� �˰��ϱ� ���ؼ� ������ ������� ������ ��ü������ �Ұ����ϰ� �Ѵ�.
class HtmlElement{
public:
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    string str(int indent = 0) const{
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (text.size() > 0)
            oss << string(indent_size*(indent + 1), ' ') << text << endl;

        for (const auto& e : elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }

    static unique_ptr<HtmlBuilder> build(const string& root_name){
        return make_unique<HtmlBuilder>(root_name);
    }
    friend HtmlBuilder;
protected:
    HtmlElement(){}
    HtmlElement(const string& name, const string& text) 
        : name(name), text(text){}
    int num = 10;

};

class HtmlBuilder{
public:
    HtmlBuilder(string root_name){
        root.name = root_name;
    }
    
    HtmlBuilder* add_child(string child_name, string child_text){
        HtmlElement e{child_name, child_text};
        
        root.elements.emplace_back(e);

        return this;
    }
    string str() { return root.str();}
    
    operator HtmlElement() const {return root;}
    HtmlElement root;
    
};

int main(){
    /* ���� HtmlElement�� �����ϰ� ����ϴ� �κ� ���� ������ �� ������ ������ �ٸ� Ŭ������ �����Ѵ�.
    string words[] = {"hello", "world"};
    HtmlElement list{"ul", ""};
    for(auto w : words)
        list.elements.emplace_back(HtmlElement{"li", w});
    printf(list.str().c_str());
    
    <1>
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello");
    builder.add_child("li", "world");
    cout << builder.str() << endl;
    
    <2>
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    cout << builder.str() << endl;
    */

    auto builder = HtmlElement::build("ul")
    ->add_child("li","Hello")->add_child("li","World");
    cout << builder->str() << endl;

    return 0;
}