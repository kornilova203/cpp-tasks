//
// Created by Liudmila Kornilova on 13.05.17.
// Test for PrioritizedQueue
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PrioritizedQueue.h"

/**
 * Randomly insert or delete element from queue
 * @param queue
 * @param pInsert
 * @param size
 */
void executeFunc(PrioritizedQueue &queue, float pInsert, int &size) {
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
    PrioritizedQueue queue;
    int iterNum = 500; // number of iterations
    float pInsert = 0.8; // probability of insertion

    int size = 0;

    for (int i = 0; i < iterNum; i++) {
        executeFunc(queue, pInsert, size);

        REQUIRE (queue.checkCorrectness() == 1);

        REQUIRE (size == queue.size());
    }
}