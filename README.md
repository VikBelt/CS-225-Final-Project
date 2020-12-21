# Graph Algorithms in C++ - with Open Flights 
Data Analysis of Open Flights Data using a weighted, directed Graph. <br/>
Team Members: Mois Bourla, Vikram Belthur, Tanmay Goyal. <br/>
Doxygen: https://vikrambelthur.com/cs_225_final_project_docs/
## Building and Running
This project can be built on most Linux Systems and on Windows. <br/>
### Running on Linux (and EWS)
To build and run this project on EWS and Linux you can use the included Makefile. <br/>

```
$ make
$ ./main
```
### Running on Windows
In order to run this project on Windows, make sure you have WSL setup on your PC. <br/>
Link Here: https://docs.microsoft.com/en-us/windows/wsl/install-win10 <br/>
Run the program in the same way as in Linux

```
$ make
$ ./main
```
## Project Description
### Data Usage
We used the airports.dat file and the routes.dat file from https://openflights.org/data.html <br/>
### Project Functionality
The project is designed to do Four Main things <br/>
- Construct a directed, weighted graph out of the aforementioned data files.
- Traverse this airport-route graph using Depth First Search (DFS). 
    - Our project does this both iteratively (stack) and using recursion. 
- Find the shortest path between two airports, based on Dijkstras Algorithm. 
- Find the a "landmark-path",the shortest path between two airports, including a midway destination

