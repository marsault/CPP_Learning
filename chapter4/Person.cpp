#include <iostream>
#include <string>

class Person
{
public:
    Person(const std::string &name, const std::string &surname)
        : _name{name}, _surname{surname}
    {
    }

    void wait(unsigned int years) { _age += years; }

    friend std::ostream& operator<<(std::ostream& o, Person p) {
      std::cout << "A person named \"" << p._name << " " << p._surname
                << "\" with age " << p._age << ".";
      return o;
    }
private:
    std::string _name;
    std::string _surname;
    unsigned int _age = 0u;
};

int main()
{
    Person batman{"Bruce", "Wayne"};
    batman.wait(23);
    std::cout << batman << std::endl;

    return 0;
}
