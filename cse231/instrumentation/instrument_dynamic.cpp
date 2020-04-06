#include <map>
#include <cstdio>

static std::map<std::string, unsigned int> *opcodeMap = nullptr;
static unsigned int totalCount = 0;

void __count(const char *opcodeName) {
    if (opcodeMap == nullptr) {
        opcodeMap = new std::map<std::string, unsigned int>;
    }

    totalCount++;

    if (opcodeMap->count(opcodeName)) {
        (*opcodeMap)[opcodeName]++;
    } else {
        (*opcodeMap)[opcodeName] = 1;
    }
}

void __printResult() {
    for (auto &pair: *opcodeMap) {
        printf("%s\t%u\n", pair.first.c_str(), pair.second);
    }

    printf("TOTAL\t%u\n", totalCount);

    delete opcodeMap;
}
