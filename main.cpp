#include <simlib.h>
#include <list>
#include <iostream>
#include <fstream>

#define POPULATION 1000
#define TIME_PERIOD 100

int main()
{
    // Number of contacts per day (input argument) * probability of transmission
    double infection_rate = 0.4;
    // 1 / (average time of recovery)
    double recovery_rate = 0.035;
    // Death rate = (number of deaths / number of cases) / time of recovery
    double death_rate = 0.005;
    // Vaccination rate = number of vaccines per time / number of susceptible
    double vaccination_rate = 5;

    //SIRD
    double population = POPULATION;
    double infected = 3.f;
    double susceptible = population - infected;
    double vaccinated = 0.f;
    double total_recovered = 0.f;
    double total_deceased = 0.f;

    std::list<double> infected_list = {};
    std::list<double> susceptible_list = {};
    std::list<double> recovered_list = {};
    std::list<double> deceased_list = {};
    std::list<double> vaccinated_list = {};

    for (int i = 0; i <= TIME_PERIOD; ++i)
    {
        double infected_daily = ((infection_rate * susceptible * infected) / population);
        total_deceased = total_deceased + death_rate * infected;
        total_recovered = total_recovered + recovery_rate * infected;
        infected = infected + (infected_daily - recovery_rate * infected - death_rate * infected);
        vaccinated = vaccinated + vaccination_rate > population ? population : vaccinated + vaccination_rate;
        susceptible = susceptible - infected_daily - vaccination_rate;
        if (susceptible < 0)
            susceptible = 0;


        population = population - death_rate * infected;

        infected_list.push_back(infected);
        susceptible_list.push_back(susceptible);
        recovered_list.push_back(total_recovered);
        deceased_list.push_back(total_deceased);
        vaccinated_list.push_back(vaccinated);

//        printf("Day #%d\n"
//               "Susceptible = %f\n"
//               "Infected = %f\n"
//               "Recovered = %f\n"
//               "Deceased = %f\n"
//               "Population = %f\n"
//               "--------------------", i, susceptible, infected, total_recovered, total_deceased, population);
    }

    //printf("Total infected = %f\n", total_infected);
    std::ofstream output;
    output.open("output.out");
    for (auto i: susceptible_list)
    {
        output << i << ':';
    }
    output << std::endl;

    for (auto i: infected_list)
    {
        output << i << ':';
    }
    output << std::endl;

    for (auto i: recovered_list)
    {
        output << i << ':';
    }
    output << std::endl;

    for (auto i: deceased_list)
    {
        output << i << ':';
    }
    output << std::endl;

    for (auto i: vaccinated_list)
    {
        output << i << ':';
    }
    output << std::endl;
    output.close();

}