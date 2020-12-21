#include "../catch/catch.hpp"
#include "../src/utility.h"
#include "../src/vertex.h"
#include "../src/graph.h"

using namespace mtv;

TEST_CASE ("Dummy Test") {
    string testString = "test";
    REQUIRE( testString == "test");
}

/**
 * Test Cases for Shortest Path using Dijkstra's Algorithm
 * Test Will be performed on Toy Data - a subset of the original data
 */

