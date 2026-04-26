/*#include <iostream>
using namespace std;
class student{
    public:
        string name;
        student(string n){
            name=n;
        }
        student(const student &s){
            name=s.name;
        }
        void display(){
            cout<<name<<endl;
        }
};
int main(){
    student s1("owais`");
    student s2=s1;
    s2.display();
    s1.display();

}*/

#include <iostream>
using namespace std;
class student{
    public:
        string name;
        int age;
         student(string n ,int a){
             name=n;
            age=a;
        }
        student(const student &s){
            name=s.name;
            age=s.age;
        }
        void display(){
            cout<<name<<endl;
            cout<<age<<endl;
        }
};
int main(){
    student s1("owais",19);
    student s2=s1;
    s1.display();
    s2.display();
}
