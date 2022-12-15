class parent{
public:
int x;
void show(){
std::cout<<x;}
};

class child: public parent{
public:
int y;
void display(){
std::cout<<y;
}
};