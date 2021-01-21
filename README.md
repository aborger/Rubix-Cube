# RubixBot
RubixBot was started as a class project to create an 3D printed 6 axis arm to complete a task. Me being the overacheiver I am decided we were going to make our arm solve a rubix cube. Note most of this work was done in 2019, my freshman year of college. The first program I created uses the F2L method. This is the method most people learn when solving a rubix cube by hand. This method worked great except it took 100 moves on average to solve it and I wanted our robotic arm to do it faster. I decided I needed to use AI to solve the cube in less moves. The Genetic Rubix Solver was my first attempt at using artificial intelligence for anything. I hadn't even taken a class on it yet, so my knowledge came 100% from google and youtube. The Genetic Rubix Solver did not use any kind of neural network, instead it used a genetic algorithm to generate a list of moves that will complete the cube (That was the idea). Then I discovered Neural Networks and decided to make an implementation of the NEAT (NeuroEvolution of Augmenting Topologies). This method is able to complete the cube when it is scrambled by only one move, but development stopped while adding the ability to use more moves.


# How they work

## 1. CFOP Method
This method is the most popular amongst speed cubers. It solves the white cross first, then the white face, the first two layers (Hence F2L), it orientates the last layer (OLL), then permutates the last layer (PLL). This creates the acronym CFOP(Cross,F2L,OLL, PLL). The algorithm is pretty rudamentary and involves mostly if then statements. If the cube is in this state, then perform this move and so on. The algorithm follows CFOP very closely. You can learn more about the CFOP algorithm [here.](https://ruwix.com/the-rubiks-cube/advanced-cfop-fridrich/white-cross/)

## 2. Genetic Algorithm Method
The idea behind this method was every rubix cube can be solved in less than 20 moves. When I learned about genetic algorithms I decided to implement one to solve a rubix cube. The "genes" are rubix cube moves (Ex: turning the left side). Each member of the population is made up of a list of genes/moves. Each member was given a fitness score to see how they did. These scores started from 0 to 100, with a score of 100 meaning the cube has been solved. There are three main functions responsible for the reproduction of members. The fitness function (reponsible for seeing how well a member does), the cross-over function (responsible for creating new members from old parent members), and the mutation function (responsible for adding randomness, new moves, and not letting every member endup with the same moves).

### The Fitness Function:
There are four sections to the fitness method.

1. Cubies on the correct side
    - One point was added to the score for each cubie on the correct side.
    - Ex: A blue cubie on the blue side.
    - There are 54 possible points in this section.

2. Adjacent pieces of the same color
    - One point was added for each adjacent peice of the same color.
    - Ex: A blue side piece next to the blue center.
    - There are 72 possible points in this section.

3. Completed row
    - One point was added for each row done.
    - Ex: 3 blue's in a row.
    - There are 18 possible points in this section.

4. Completed face
    - One point was added for each face done.
    - There are 6 possible points in this section.

Now you may notice that doesn't add up to 100. It adds up to 150 then I just divided by 1.5, also more points should've been given for a completed face then a cubie on the correct side. This was fixed in the NEAT algorithm version.

### The Cross Over Function:
The cross over method used in the algorithm could've used lots of improvement. It was very basic. Two members were picked from the population to be "breeded" (Named parents). Two new members were created (Name children) and a cross point was selected. The cross point is a random number between 0 and 20 because each member has a list of 20 moves. Child 1 gets the moves before the cross point from parent 1 and the moves after the cross point from parent 2. Child 2 gets the moves before from parent 2 and the moves after from parent 1.

### The Mutation Function
When a new population is created every member has a chance to be mutated. If a random number from 0 to 100 is less than the mutation rate (I used 7) then that member is getting mutated. When a member is being mutated a random gene(move) is replaced with a new random move.

This method had several issues. Everytime the robot would solve the cube it would have to go through the genetic algorithm whose main principle is to use randomness and fitness to get better. However, there are about 43 quintillion possible configurations for a rubix cube and using a method that has no concept of strategy or the fact that one move is applied before the next did not work very well. It was able to solve a completely scrambled cube a few times if the algorithm was ran for about 5 hours. Also occasionally an out of bounds issue occured with the move array generating a move that wasn't one of the possible moves. I decided to move onto the next and better method instead of solving this issue.


## 1. NEAT Algorithm Method
This method taught me the most about AI and Machine Learning even though it did not work super well. The algorithm was implemented as planned, but during the course of development I was only able to generate one move to use. I did at one point generate a list of moves by performing one move, performing it and then using that as the input to the algorithm, but it was never able to solve it. This was before I learned about Recurrent Neural Networks while working on my AI stock trader. None the less, this is how this algorithm works.

This method also uses a genetic algorithm except each member contains a neural network. The neural network does not have a set structure, instead it starts as 54 input nodes (1 for each cubie, 13 output nodes (1 for each possible move), and a connection (takes the input, multiplies it by a weight, and gives it to the output). These members can reproduce and mutate to add more nodes or connections. Nodes and connection weights can also be changed. This algorithm is repeated until a member is found that can complete the starting cube.

Note: If I were to redo this today I would've implemented a Deep Q Network (DQN) like the method I used in KaraV2, the second version of the AI stock trader I am still working on. This would allow it to look at states and perform moves that provide the best reward from each state.

### Reproduction
The functions in this method responsible for reproduction are again the fitness function and mutation function. However, I could not figure out a good crossover function for the networks so I used a different selection method to create new members instead.

#### Fitness Function

There are 5 parts to this fitness function, while it is better than the genetic algorithm fitness function, it still could be a lot better.

1. Complete
    - 100 points if the cube is complete
  
2. Completed Side
    - 4 points for each side completed
    - 6 possible sides so 24 possible points
    
3. Full Rows
    - 3 points for an entire horizontal or vertical row around the cube being completed
    - 6 possible rows (3 horizontal and 3 vertical) so 18 possible points
    
4. Crosses
    - 2 points for each cross created
    - 6 possible crosses (1 on each side) so 12 possible points
    
5. Rows on sides completed
    - 1 point for each row completed
    - 6 rows per side (3 horizontal and 3 vertical) and 6 sides so 36 possible points
    
I didn't really plan out the fitness score on this as they add up to 90, but I just needed some way to see if it's making progress. I check to see if it's completed before the rest to award it the full 100 points.
    
#### Mutation Function

In this mutation function every member has a possibility of getting mutated like the last one. They are selected if a random value from 0 to 100 is less than the mutation percentage. If they are selected their network will either be trained or modified. A value can be set for how likely training is I usually used 90%. If the network is trained then a random weight or bias is selected to be modified. That weight or bias's value is multiplied by a value close to 1 and between .5 and 1.5. If the network is selected to be modified there are 4 options.
1. Add a Node
    - A node with a random bias will be added to an existing connection
2. Remove a Node
    - A random node will be selected to be removed, all input connections will now output directly to the output of any output connections.
3. Add a connection
    - A connection will be added from a random node to another random node. It checks to make sure the input is upstream from the output
4. Remove a connection
    - A random connection is picked to be removed.
    
#### Selection Function
The selection function keeps the top performing members of the population and generates new members to keep the population size the same. To get any real success out of this algorithm I would've needed to make a crossover function instead.


Those are the three best methods I used for solving a rubix cube. These were all going to be implemented in a robot that solves the cube using an arduino, a color sensor, and servos. The first version of the robot was not good as it was designed to be a 6 axis arm which could not maneuver well enough around the cube to be functional. The second version which is included in the repository worked great, but I never implemented code into it because I started working on my AI stock trader instead.

