//
// Created by Liudmila Kornilova on 13.05.17.
// Test for PriorityQueue
//

// Abstract data type which is based on set.
// It has:
// insert (if item is not in set)
// deleteMin (get element with the least priority (and delete it)
// makeNull

// Priority is a function, specified on set. p(a) is priority of a. Отображения.
// Part-sorted tree

// 1. each node has up to 2 children
// 2. all potentially-possible leafs may be only on the right sight of existing nodes.
// 3. Priority of parent is not bigger than priority of children. delete will always get root.
// - all left nodes will be smaller than right node

// DeleteMin
// 1. Search mort right element on bottom level
// 2. Copy it to root
// 3. Swap nodes till algorithm finds new position for this node. (compare to left nodes. If it is smaller - swap)
// 4. Return deleted root

// Insert
// 1. insert element on most left position on bottom layer. If bottom layer is full. Add new layer.
// 2. Swap element if son has smaller priority

// On array
// a[i] - root
// a[2i] - left child
// a[2i + 1] - right child

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PriorityQueue.h"

/**
 * Randomly insert or delete element from queue
 * @param queue
 * @param pInsert
 * @param size
 */
void executeFunc(PriorityQueue &queue, float pInsert, int &size) {
    float random = ((float) rand() / (RAND_MAX));

    if (random < pInsert) { // insert element
        if (!queue.isFull()) {
            int val = (int) (((float) rand() / RAND_MAX ) * 10);
            int prior = (int) (((float) rand() / RAND_MAX ) * 10);
            if (!queue.hasValue(val)) // if value will be inserted
                size++;
            queue.insert(val, prior);
        }
    }
    else if (!queue.isEmpty()) { // delete element
            queue.deleteMin();
            size--;
    }
}

TEST_CASE("Check prioritized queue") {
    srand((unsigned int) time(NULL));
    PriorityQueue queue;
    int iterNum = 500; // number of iterations
    float pInsert = 0.8; // probability of insertion

    int size = 0;

    for (int i = 0; i < iterNum; i++) {
        executeFunc(queue, pInsert, size);

        REQUIRE (queue.checkCorrectness() == 1);

        REQUIRE (size == queue.size());
    }
}