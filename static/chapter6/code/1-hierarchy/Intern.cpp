#include "Intern.h"

#include <cstdio>
#include <random>

Intern::Intern(std::string name, std::string surname, unsigned int salary, bool is_clumsy)
    : _name{std::move(name)}, _surname{std::move(surname)}, _salary{salary}, _is_clumsy{is_clumsy}
{
}

void Intern::increase_salary(unsigned int raise)
{
    _salary += raise;
}

void Intern::fetch_coffee()
{
    std::random_device rd;
    std::mt19937 gen{rd()};

    const auto probability = _is_clumsy ? 0.4f : 0.1f;
    std::bernoulli_distribution break_cup_dist{probability};

    while (break_cup_dist(gen))
    {
        std::printf("%s %s (Intern): \"Oups......\"\n", get_name().c_str(), get_surname().c_str());
        ++_nb_broken_cups;
    }

    std::printf("%s %s (Intern): \"Here's your coffee Sir.\"\n", get_name().c_str(), get_surname().c_str());
}
