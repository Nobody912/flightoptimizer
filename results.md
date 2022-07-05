# Results

## Output and Correctness
The BFS and Dijkstra's algorithm follow standard BFS and Dijkstra, respectively, implemented to fit our dataset. The map projection algorithm draws lines on the map according to the path given by either BFS or Dijkstra's and then flood fills the state of the airport.
We first ran small scale data tests on the algorithms to confirm they work before testing with the full dataset. We picked out tests from the dataset with different variables, such as non-stop flight vs multiple-stop flight, and confirmed the algorithms work as intended.

## Leading Question Answer
With the BFS, we found which path would be least number of stops. With Dijkstra's Algorithm, we found which path would be most cost efficient. We then took those two paths and displayed it both in text and graphically.
With this, we can directly answer our question of which are some of the most efficient ways of traveling between two U.S. airports. However, we did have to partly change the leading question from mileage to number of stops due to a lack of data about distance from our dataset.
Because of this lack of data, we also changed from A star heuristic to Dijkstra's Algorithm. Besides this oversight we had in the beginning and after a slight adjustment, we did complete our goal.
It was interesting to see a graphic representation of essentially comfort (number of stops) vs cost when traveling by air in the U.S.
