

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

static std::vector<int> container = { 1,2,3,4,5 };
static int maxForContainer = container.size();                      //In static memory because they're not tied down to any particular state of the permutation.
static std::vector<int> remainderHolder;                            //and are needed for the entire program, rather than just a function or something short-lived.
static std::vector<std::unordered_set<int>> spotChecker(maxForContainer);
#define LAST_IMPORTANT_SPOT (container.size() - 2)
#define MAXIMUM_NUMBER_FOR_SPOT (maxForContainer - stage)           //macros are a bit redudant as they could just be variables, but I could
#define LAST_ELEMENT remainderHolder.size() - 1                     //mess up changing it so I thought it fine to keep it this way
int counter = 1;


//the general algorithm is that for any state (where a state consist a spot in the general container), we can solve it by doing all the necessary permutations for anything preceding it (right to left)
//and then moving onto the next number for that spot until we fill out a certain amount for that spot. (the numbers for that spot always remain the same, as there is a pattern to it)
//for example, the second to last number and the last number can be filled out with just one permutation for both (meaning two states but only one permutation is needed via a std::swap)
//and then the third number is going to be three numbers completed for that spot, and then the fourth spot is four numbers for that spot, and then so on and so on.
void printContainer() {
    for (int i = 0; i < container.size(); i++) {
        if (i == container.size() - 1) {
            std::cout << container[i] << '\t' << counter << '\n';
        }
        else {
            std::cout << container[i] << ", ";
        }
    }
    counter++;
}

void checkAvailability(int stage) {
    auto i = std::find_if(remainderHolder.begin(), remainderHolder.end(), [stage](int i) {
        return spotChecker[stage].find(i) == spotChecker[stage].end();
        });
    if (i != remainderHolder.end()) {
        std::swap(*i, remainderHolder[LAST_ELEMENT]);
        container[stage] = remainderHolder[LAST_ELEMENT];
        remainderHolder.pop_back();
    }
}

void permuter(int stage) {
    if (stage == LAST_IMPORTANT_SPOT) {
        printContainer();
        std::swap(container[stage], container[stage + 1]);
        printContainer();
        for (int j = 1; j >= 0; j--) {
            remainderHolder.push_back(container[j + stage]);
            container.pop_back();
        }
        return;
    }
    while (spotChecker[stage].size() != MAXIMUM_NUMBER_FOR_SPOT) {
        permuter(stage + 1);
        spotChecker[stage].insert(container[stage]);
        remainderHolder.push_back(container[stage]);
        checkAvailability(stage);
        for (int j = 0; j < remainderHolder.size() && spotChecker[stage].size() != MAXIMUM_NUMBER_FOR_SPOT; j++) {
            container.push_back(remainderHolder[j]);
        }
        if (spotChecker[stage].size() != MAXIMUM_NUMBER_FOR_SPOT) {
            remainderHolder.clear();
        }
    }
    container.pop_back();
    spotChecker[stage].clear();
}

int main()
{
    permuter(0);
}


