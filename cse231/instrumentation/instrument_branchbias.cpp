#include <map>
#include <cstdio>
#include <unordered_set>

static std::map<const char *, unsigned int> *takenMap = nullptr;
static std::map<const char *, unsigned int> *totalMap = nullptr;
static std::unordered_set<unsigned int> *blockVisited = nullptr;

/**
 * Counts in a conditional branch only if it is taken.
 *
 * @param functionName the name of the given function
 * @param blockID the ID of the given block
 */
void __countTaken(const char *functionName, unsigned int blockID) {
    if (takenMap == nullptr) {
        takenMap = new std::map<const char *, unsigned int>;
    }

    if (blockVisited == nullptr) {
        blockVisited = new std::unordered_set<unsigned int>;
    }

    if (!blockVisited->count(blockID)) {
        if (takenMap->count(functionName)) {
            (*takenMap)[functionName]++;
        } else {
            (*takenMap)[functionName] = 1;
        }

        blockVisited->insert(blockID);
    }
}

/**
 * Counts in a conditional branch.
 *
 * @param functionName the name of the given function
 * @param totalCount the total number of the conditional branches in the given function
 */
void __countTotal(const char *functionName, unsigned int totalCount) {
    if (totalMap == nullptr) {
        totalMap = new std::map<const char *, unsigned int>;
    }

    if (!totalMap->count(functionName)) {
        (*totalMap)[functionName] = totalCount;
    }
}

/**
 * Prints the results.
 */
void __printResult() {
    if (takenMap == nullptr || totalMap == nullptr) {
        printf("ERROR: Instrumentation maps are not initialized.\n");
        return;
    }

    printf("Function Bias Taken Total\n");

    for (auto &pair: *takenMap) {
        const char *functionName = pair.first;
        unsigned int countTaken = pair.second;
        unsigned int countTotal = (*totalMap)[functionName];
        double bias = (double) countTaken / (double) countTotal;

        printf("%s\t%.2f\t%u\t%u\n", functionName, bias, countTaken, countTotal);
    }

    delete takenMap;
    delete totalMap;
    delete blockVisited;
}
