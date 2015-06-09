#!/usr/bin/env python3

"""
This is a simple Python implementation of the (mu/mu_I, lambda)-sigmaSA-ES
as discussed in 
http://www.scholarpedia.org/article/Evolution_Strategies
Based on
https://homepages.fhv.at/hgb/downloads/mu_mu_I_lambda-ES.oct
"""

import math
import numpy as np
import matplotlib.pyplot as plt
import random


MU = 3                    # number of parents
LAMBDA = 12               # number of offspring

X_INIT = np.ones(24)       # initial parent vector 
#X_INIT = np.ones(2)       # initial parent vector 
SIGMA_INIT = 1            # initial global mutation strength sigma 

SIGMA_MIN = 1e-10         # ES stops when sigma is smaller than sigma_min

gen_index = 0
indiv_index = 0

###########################################################

# Function to be optimized (sphere test function as an example)
# individual: the individual to evaluate
def sphere_function(indiv):
    x = indiv.x
    assert x.shape == X_INIT.shape, x
    y = -np.dot(x, x)
    return y

def robudog(indiv):
    param_file_name = "gen" + str(gen_index) + "_indiv" + str(indiv_index)
    score_file_name = param_file_name + ".score"

    score = None

    # check the argument
    x = indiv.x
    assert x.shape == X_INIT.shape, x

    # write params file
    with open(param_file_name, "w") as fd:
        for xi in x:
            print(xi, end=' ', file=fd)

    # run botsim.org
    # TODO

    # retrive the score
    with open(score_file_name, "r") as fd:
        score = float(fd.read())

    return score

fitness = robudog

###########################################################

# The individual class
# x: the individual's value
# sigma: the individual's sigma
class Individual():
    def __init__(self, x, sigma):
        self.x = x
        self.sigma = sigma
        self.reward = fitness(self)

    def __str__(self):
        return "{0} {1} {2}".format(self.x, self.sigma, self.reward)

###########################################################

# This sorts the population according to the individuals' fitnesses
# pop: a list of Individual objects
def select_individuals(pop):
    pop.sort(key=lambda indiv: indiv.reward, reverse=True)
    return pop[:MU]

# This performs intermediate (multi-) recombination
# parents: a list of Individual objects
def recombine_individuals(parents):
    parents_y = np.array([indiv.x for indiv in parents])
    parents_sigma = np.array([indiv.sigma for indiv in parents])
    recombinant = Individual(parents_y.mean(axis=0), parents_sigma.mean())
    return recombinant

###########################################################

def main():

    global gen_index
    global indiv_index

    # Initialization
    n = X_INIT.shape[0]         # determine search space dimensionality n   
    tau = 1. / math.sqrt(2.*n)  # self-adaptation learning rate

    # Initializing individual population
    parent_pop = [Individual(X_INIT, SIGMA_INIT) for i in range(MU)]

    # Evolution loop of the (mu/mu_I, lambda)-sigma-SA-ES
    while parent_pop[0].sigma > SIGMA_MIN:
        gen_index += 1
        print("Generation", gen_index)

        offspring_pop = []
        recombinant = recombine_individuals(parent_pop) # TODO: BUG ? this statement may be in the next line
        for i in range(1, LAMBDA):
            indiv_index = i

            offspring_sigma = recombinant.sigma * math.exp(tau * random.normalvariate(0,1))
            offspring_y = recombinant.x + offspring_sigma * np.random.normal(size=n)
            offspring = Individual(offspring_y, offspring_sigma)
            offspring_pop.append(offspring)

            print(" Individual", indiv_index, "score", offspring.reward)
        parent_pop = select_individuals(offspring_pop)

        print(" Best individual", parent_pop[0].x, "score", parent_pop[0].reward)
        #print(parent_pop[0])

# Remark: Final approximation of the optimizer is in "parent_pop[0].x"
#         corresponding fitness is in "parent_pop[0].reward" and the final 
#         mutation strength is in "parent_pop[0].sigma"

if __name__ == "__main__":
    main()
