# dsho2-arliang2-erikrj2
Team name: dea

What is the difference between flight paths in comfort (number of stops) vs cost when flying from one airport to another in the U.S.?

## Github Organization

All major code files and parsed data are in the src folder. The raw data is in the Raw Data folder. The progress reports are in the WeeklyReports folder. The presentation video is in the main.

## Usage

The input data is the origin and destination wanted, written as the 3 letter airport code it corresponds to, and the name of the file to output onto. The written output is in the command line, while the image output is in the src folder in file specified, flightpath-out.png file.

The test output is written in the command line with the image output in the src folder under the flightpath-test.png file. Our test suite includes tests for basic non-stop flights and flights with stops. It also tests for when BFS and Dijkstra's Algorithm differ and are the same path. Lastly, it tests for when inputs are invalid and the drawing function.

To run main:
```C++
make main
# Origin and Destination are 3 letter airport codes, filename should be flightpath-out.png
./main [Origin] [Destination] [Filename]
```

To run tests:
```C++
make test
./test
```
