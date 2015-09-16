#!/usr/bin/python

import random
import math

def stoc_walk(p, dr, vol, periods):
    for i in range(periods):
        w = random.gauss(0.0, 1.0)
        p += dr*p + w*vol*p
    return p

s0 = 10.0
drift = 0.001502
volatility = 0.026
r = 0.02
days = 255
N = 100000
zero_trials = 0

k = 12.0

avg = 0.0

for i in range(N):
    temp = stoc_walk(s0, drift, volatility, days)
    if temp > k:
        payoff  = temp - k
        payoff *= math.exp(-r)
        avg    += payoff
    else:
        zero_trials += 1

avg = avg / float(N)

print("MONTE CARLO PLAIN VANILLA CALL OPTION PRICING")
print("Option price: ",avg)
print("Initial price: ",s0)
print("Strike price: ",k)
print("Daily expected drift: ",drift)
print("Daily expected volatility: ",volatility)
print("Total trials: ",N)
print("Zero trials: ",zero_trials)
print("Percentage of total trials: ", 100.0*float(zero_trials)/float(N))

