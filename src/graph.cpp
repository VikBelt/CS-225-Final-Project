#include "graph.h"

int count_g = 67662;
namespace mtv{

    /* PUBLIC METHODS */

    // Graph Constructors
    Graph::Graph(){ 
        vector<vector<double>> vec(mat_t, vector<double> (mat_t, NO_EDGE));
        vector<Vertex> vec_air(mat_t, Vertex());
        adjMat = vec;
        airports = vec_air;
    }

    Graph::Graph(int edgeSize){
        vector<vector<double>> vec(edgeSize, vector<double> (edgeSize, NO_EDGE));
        vector<Vertex> vec_air(edgeSize, Vertex());   
        adjMat = vec;
        airports = vec_air;
    }

    void Graph::parseRoutes(string fname){

        std::ifstream routesFile(fname);
        if(!routesFile.is_open())   
            throw graph_excepts::route_parse_error("NOT OPEN, IDIOTS");

        string line, item;
        parseRoutesHelper(routesFile,line,item);
        routesFile.close();
    }

    void Graph::printFirstXVertices(int x){
        for(int i = 0; i < x; i++){
            for(const auto& elem : adjMat[i]){
                std::cout<<elem;
            }
            std::cout<<"\n";
        }
    }

    bool Graph::checkAdjacency(int srcID, int destID){

        unsigned long src = (unsigned long) srcID;
        unsigned long dest = (unsigned long) destID;

        // check bounds on input IDs
        if(src > adjMat.size() || dest > adjMat.size()){
            return false;
        }
        //  
        return adjMat.at(srcID).at(destID) >= 0.0;
    }

    vector<int> Graph::getEdges(int srcID){
        vector<int> edges;
        //edges.reserve(std::floor(loadFactor * mat_t));
        for(size_t i = 0; i < adjMat.at(srcID).size(); i++){
            if(adjMat.at(srcID).at(i) >= 0.0){
                edges.push_back(i);
            }
        }
        return edges;
    }

    void Graph::storeAirports(string filename) {
        std::ifstream airportFile(filename);
        //if not open throw an exception
        if(!airportFile.is_open())
            throw graph_excepts::airport_parse_error("NOT OPEN, IDIOTS");
        
        std::string line;
        storeAirportsHelper(airportFile,line);
    }

    double Graph::getEdgeWeight(Vertex source, Vertex dest) {
        //call method in utility.h to get the distane between two points
        double distance = calculateDistance(source.latitude,source.longitude,dest.latitude,dest.longitude);
        return distance;
    }

    vector<Vertex> Graph::getVerticies() const {
        return airports;
    }

    //Implements Dijkstras Algorithm then retrives the shortest path =b
    bool Graph::shortestPath(Vertex source, Vertex dest, vector<Vertex>& path){
        
        //if destination and source are equal do nothing
        if(source == dest) {
            return true;
        }

       /**
        * Need Min Heap - Default aka "std::priority_queue<type> max_heap" for MAX HEAP.
        * Min Heap defined like this in constructor:
        * "std::priority_queue <Type, vector<Type>, ComparisonType > for min_heap"
        */

        //distance vector where all airport IDs are infinity away from the start - start is 0 away
        vector<double> dist(airports.size(),-1.0);
        vector<Vertex> prev(airports.size());

        //lambda to create custom comparator for use in the queue - captures vars by ref
        //required in order to make a min heap in stl
        //using a lambda since creating a comaparator struct would'nt make sense in this context
        //primarilly because the comparison depends on the dist array

        auto comp = [&] (Vertex lhs, Vertex rhs) {
            if(dist.empty()){
                return false;
            }
            return (dist[lhs.airportId] > dist[rhs.airportId]);
        };

        //create minHeap as specfied above
        priority_queue<Vertex,vector<Vertex>,decltype(comp)> Q(comp);
        for(size_t i = 0; i < airports.size(); i++){
            //push 0 distance to the start
            if(airports.at(i).airportId == -1){continue;}
            if(source.airportId == (int)i){
                dist.at(i) = 0;
                prev.at(i) = Vertex();
            }
            //all other distances should be infinity - to start with 
            else {
                dist.at(i) = INF;
            }
            //add into the queue
            //prev.at(i) = Vertex();
            Q.push(airports[i]);
        }
        

        while(!Q.empty()) {
            Vertex u = Q.top();
            Q.pop();
            if(u == dest){
                double dist = 0.0;
                Vertex cur = u;
                if(cur == source || prev.at(cur.airportId).airportId != -1){
                    while(prev.at(cur.airportId).airportId != source.airportId){
                        path.push_back(cur);
                        Vertex pre = prev.at(cur.airportId);
                        dist += getEdgeWeight(cur,pre);
                        cur = pre;
                    }
                    path.push_back(cur);
                    dist += getEdgeWeight(cur,source);
                    path.push_back(source);
                    reverse(path.begin(),path.end());
                    return true;
                } 
            }

            if(dist.at(u.airportId) < INF){
                //go through the indicies of the adj verticies
                vector<int> neighbors = getEdges(u.airportId);
                //for each neighbor of vertex u
                for(size_t i = 0; i < neighbors.size(); i++) {
                    Vertex v = airports.at(neighbors.at(i));
                    //do the relaxation
                    if((dist[u.airportId] + getEdgeWeight(u,v) < dist[v.airportId])) {
                        dist[v.airportId] = getEdgeWeight(u,v) + dist[u.airportId];
                        Q.push(v);
                        prev[v.airportId] = u;
                        
                    }
                }
            }
        }

        return false;
    }

    vector<Vertex> Graph::landmarkPath(Vertex start, Vertex mid, Vertex end){

        /*
         * To solve this problem this method be using the shortest path algorithm to find the shortest
         * path from start to mid and from mid to end
         */

        vector<Vertex> path1;
        vector<Vertex> path2;
        vector<Vertex> path;

        if(shortestPath(start, mid, path1)){
            if(shortestPath(mid, end, path2)){
                path.insert(path.end(), path1.begin(), path1.end());
                path.insert(path.end(), path2.begin()+1, path2.end());
            }

            else {return path;}
        }

        else {return path;}
            
        return path;
    }

    void Graph::DFS(int start, vector<bool>& visited){
        if((airports.at(start)).airportId > -1)
        if(visited[(airports.at(start)).airportId] == false){
            visited[(airports.at(start)).airportId] = true;
            std::cout << (airports.at(start).airportName);
 
            for (int i = 0; i < (int)adjMat.size(); i++) {
                if((airports.at(i)).airportId>-1){
                    if (adjMat[(airports.at(start)).airportId][(airports.at(i)).airportId]>-1 && (!visited[(airports.at(i)).airportId])) {
			            std::cout<<"->";//<<(airports.at(i)).airportId<<"\n";                
			            DFS((airports.at(i)).airportId, visited);
                    }
                }
            }
		}
    }

    void Graph::DFS()
    {
      vector<bool> visited(airports.size(),false);
      std::ofstream* myfile = new std::ofstream();
      myfile->open ("traversals.txt");
      for(auto V : airports){
          
          if(V.airportId != -1 && visited.at(V.airportId) == false){
              
              DFS(V, visited,myfile);
          }
      }
      myfile->close();
      delete myfile;  
    }
    
    void Graph::DFS(Vertex start, vector<bool>& visited, std::ofstream* myfile)
    {
        // std::ofstream myfile;
        // myfile.open ("traversals.txt", std::ios::app);
        (*myfile)<<std::endl;
        stack<Vertex> s;
        vector<int> neighbors;
        s.push(start);

        while(!s.empty()){
            Vertex cur = s.top();
            s.pop();
            if(cur.airportId != -1 && visited.at(cur.airportId) == false){
                (*myfile) << cur.airportId << "->"; 
                visited.at(cur.airportId) = true;
                neighbors = getEdges(cur.airportId);
                for(int neighbor: neighbors){
                    s.push(airports.at(neighbor));
                }
            }
        }

    }

    /**
     * PRIVATE HELPER FUNCTIONS
     */

    //helper for parseRoutes
    void Graph::parseRoutesHelper(std::ifstream& routesFile, string& line, string& item) {
        int colCounter;
        // open file and get the line
        while(std::getline(routesFile, line)){
            // get the line and make it a str stream
            std::stringstream ss(line);
            colCounter = 0;
            int srcId = 0; int destId = 0;
            // get each bit until comma and add into item
            while(std::getline(ss,item,',')){
                // we check which column we are on
                // column 3 - source ID, column 5 - destiID
                // column 8 - last column
                switch(colCounter)
                {
                    case 0:
                        srcId = atoi(item.c_str());
                        break;
                    case 1:
                        destId = atoi(item.c_str());
                        break;
                }
                colCounter++;

                //check if coor are valid
                unsigned long src = static_cast<unsigned long>(srcId);
                unsigned long dest = static_cast<unsigned long> (destId);
                if(srcId != 0 && destId != 0){
                    if(src < adjMat.size() && dest < adjMat.size()) {adjMat.at(srcId).at(destId) = 0.0;}
                }
            }    
        }
    }

    //Parse Airport Helper
    void Graph::storeAirportsHelper(std::ifstream& airportFile, string& line) {
        while (std::getline(airportFile, line)){
            //file parsing
            std::stringstream ss(line);
            string skip;
            string ID, fname, lname, country, iata, icao;
            string number1, number2, number3;
            std::getline(ss, ID, ',');
            std::getline(std::getline(ss, skip, '"'), fname, '"');
            std::getline(ss, lname, ',');
            std::getline(std::getline(ss, skip, '"'), lname, '"');
            std::getline(ss, country, ',');
            std::getline(std::getline(ss, skip, '"'), country, '"');
            std::getline(ss, iata, ',');
            std::getline(std::getline(ss, skip, '"'), iata, '"');
            std::getline(ss, icao, ',');
            std::getline(std::getline(ss, skip, '"'), icao, '"');
            std::getline(ss, number1, ',');
            std::getline(ss, number2, ',');
            std::getline(ss, number3, ',');
            //vector fields
            Vertex newAirport(stoi(ID),fname,iata,icao,stod(number2),stod(number3));
            airports.at(newAirport.airportId) = newAirport;
        }
    }

} //namespace mtv
