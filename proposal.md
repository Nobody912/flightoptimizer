# CS 225 Final Project Proposal
Erik Ji | David Ho | Ariocie Liang  
March 24, 2022, Revision 1.0  

## Leading Question
**What is the most mileage and cost efficient way to travel from one U.S. airport to another airport?**  

Our final project aims to answer that question by creating software to find the most distance and/or cost efficient way to get from airport to airport by using the A* heuristic algorithm calculated using Euclidean distance and displayed on a image map using a geographical projection algorithm.

## Data Acquisition and Processing
For our project, we will be using the [United States Department of Transportation D1B1 Airline Flight Market Dataset](https://www.transtats.bts.gov/DL_SelectFields.aspx?gnoyr_VQ=FHK&QO_fu146_anzr=b4vtv0%20n0q%20Qr56v0n6v10%20f748rB).

### Data Format
The format is provided to us in a `.csv` format, with the following potentially useful parameters:

1. Flight Year
1. Origin Airport ID (USDOT assigned airport ID)
1. Origin Airport 3-Letter Code
1. Origin Country Code
1. Origin State Code
1. Destination Airport ID (USDOT assigned airport ID)
1. Destination Airport 3-Letter Code
1. Destination Country Code
1. Destination State Code
1. Market Fare
1. Market Distance

We will only need a subset of the data depending on the extent our ability to develop our user interface. The main parameters we need are market fare, distance, and origin/destination airport codes.

### Data Correction
In order to properly parse input data, we will employ the several measure to ensure we have no malformed or blatantly inaccurate data. 

From the initial construction of our working dataset, we will remove any malformed or impossible entries in the case of bad data. The accuracy of the data will be verified in the following ways:

1. Airport codes will be checked against a set of valid U.S. 3-digit airport codes
1. Extraneous distance and flight fares will be omitted as outliers. In the extremely rare case that we do not have accurate flight data for a certain route, we will use average dollar/mile estimates based on previous flight data.

### Data Storage 
To store our processed data, we will utilize directed graphs with weighted edges. This will likely be stored in the form of structs with vector parameters/fields.

Estimated storage size: 65 MB  
Estimated time complexity insert: `O(1)`  
Estimated time complexity remove: `O(1)`  
Estimated routing complexity: `O(V + ElogV)` where `V` is the number of vertices (airports) and `E` is the number of paths (flight itineraries).

## Graph Algorithms

### Breadth First Traversal
To find the origin and destination flights, we will need to use a breadth first traversal to go through our graph and find the optimal flight map based on number of connections. 

#### Function Inputs/Outputs
Parameters for the BFS traversal should include origin airport and destination airport. The output should include the number of connecting flights and order of connecting flights between the origin and destination.

#### Function Efficiency
The efficiency of the BFS Traversal should be approximately `O(V + E)`, where V is the number of vertices and E is the number of edges, as we intend to use an adjacency list rather than an adjacency matrix.
### A* Heuristic Algorithm
We intend to use the A-star heuristic algorthim to complete the weighted-path solving problem, with Euclidean distance being the basis of the heuristic. The nodes will be airports, and the paths will be weighted based on average itinerary price between two given airports.

#### Function Inputs/Outputs
Parameters for our program should include origin airport, destination airport, and certain constraints such as maximum price or maximum distance traveled to allow for some customizability in itinerary.

#### Function Efficiency
Given the generalized runtime efficiency of the A* heuristic algorithm is `O(V + ElogV)`. However, the efficiency will vary with our method of implementation including the exact programmatic structures we use and the efficiency of our code.

### Custom Map Projection Algorithm
The map projection algorithm will assist in drawing the output onto an actual image. This algorithm will traverse our entire graph, drawing every node as well as highlighting the optimal paths based on flight connection and cost considerations.

#### Function Inputs/Outputs
Parameters for the function should include the current graph and the respective optimal paths for connection and price optimized traversals of the graph. The output should be a PNG image showing a map of the U.S. with the final flight routes.

#### Function Efficiency
The function should have an approximately `O(V + E)` efficiency, as the function will have to paint every node and and every edge, as well as the final pathes.

## Timeline
### Data Acquisition
Currently we intend to solely use the USDOT D1B1 Airline Flight Market dataset, but there are other datasets we can utilize for more datapoints and thus more accurate results.

**Deadline: April 9th**

### Data Processing
The data processing phase includes purging/omitting useless, malformed, or outlier data, defining the scope of our inputs/outputs and further cleaning our dataset, and unifying our results in a final dataset.

**Deadline: April 16th**

### Data Organization/Graph Construction
After we have a clean dataset to work with, we need to write code to assemble our data into a storable format to be used to build our graphs. This can then be re-imported upon execution time.

In terms of actuallly constructing the graph, the nodes will be airports available from out datasets, and the weight of the edges will be determined by the average price per flight on a given route from our datasets. 


**Deadline: April 16th**


### Implementing A* Heuristic Algorithm
Next, we will need to implement the actual pathfinding system. Using however we implement our dataset, it is likely we will need time to figure out how to properly interface the algorithm with our data.

**Deadline: April 23rd**
### Implementing the BFS Traversal Algorithm
We will also need to implement the BFS traversal algorithm. This algorithm simply needs to perform the breadth-first search algorithm between the origin and destination airports.

**Deadline: April 18th**

### Implementing the Geographic Projection Algorithm
This algorithm needs to draw the airports of the country, and highlight the routes depending on the cost and number-of-connections optimization.

**Deadline: April 30th**