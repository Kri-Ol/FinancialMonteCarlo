#include <iostream>
#include <random>
#include <cmath>
#include <chrono>

using namespace std;

std::default_random_engine generator;

double stoc_walk(double p,double dr,double vol,int periods)
{
    double mean = 0.0;
    double stdv = 1.0;

    std::normal_distribution<double> distribution(mean, stdv);

    for(int i=0; i < periods; i++)
    {
        double w = distribution(generator);
        p += dr*p + w*vol*p;
    }
    return p;
}

int main()
{
    //Initialize variables
    double s0 = 10.0;           //Initial price
    double drift = 0.001502;    //daily drift
    double volatility = 0.026;  //volatility (daily)
    double r = 0.02;            //Risk free yearly rate
    int days = 255;             //Days
    int N = 100000;             //Number of Monte Carlo trials
    double zero_trials = 0.0;

    double k = 12.0;             //Strike price

    //Calculate N payoffs
    double avg = 0.0;
    for(int j=0; j < N; j++)
    {
        double temp = stoc_walk(s0, drift, volatility, days);
        if(temp > k)
        {            
            double payoff  = temp - k;
            payoff *= exp(-r);
            avg += payoff;
        }
        else
        {
            zero_trials += 1;
        }
    }

    //Average the results
    avg /= (double)N;

    //Print results
    cout << "MONTE CARLO PLAIN VANILLA CALL OPTION PRICING" << endl;
    cout << "Option price: " << avg << endl;
    cout << "Initial price: " << s0 << endl;
    cout << "Strike price: " << k << endl;
    cout << "Daily expected drift: " << drift*100 << "%" << endl;
    cout << "Daily volatility: " << volatility*100 << "%" << endl;
    cout << "Total trials: " << N << endl;
    cout << "Zero trials: " << zero_trials << endl;
    cout << "Percentage of total trials: " << zero_trials/N*100 << "%" << std::endl;

    return 0;
}
