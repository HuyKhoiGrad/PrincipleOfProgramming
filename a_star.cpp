#include <iostream>
#include<bits/stdc++.h>

using namespace std;


// Create and define status for the Farmer, wolf, goat and cabbage
struct status {
    // Inittially, all atom are in the same bank so define the status for all as 1 
    int farmer = 1;
    int wolf = 1; 
    int goat = 1;
    int cab = 1; 

    // Init the f, g, h for a* algorithm
    int g = 0;
    int h = 0;
    int f = 0;

    // Initialize the previous status 
    struct status* prev = NULL;
    bool operator<(const status& n) const {
        return f > n.f; // for the priority queue to order nodes by lowest f_cost
    }
};

// Define the unavailable status 
bool false_status (status curr_status) {
    if (curr_status.farmer != curr_status.goat){
        if (curr_status.goat == curr_status.wolf) return false;
        if (curr_status.goat == curr_status.cab) return false;
    }
    return true;
}

// Define 4 action in the puzzle 
status move_wolf (status curr_status) {
    curr_status.farmer = 1 - curr_status.farmer;
    curr_status.wolf = 1 - curr_status.wolf;

    return curr_status;
}

status move_goat (status curr_status) {
    curr_status.farmer = 1 - curr_status.farmer;
    curr_status.goat = 1 - curr_status.goat;

    return curr_status;
}

status move_cab (status curr_status) {
    curr_status.farmer = 1 - curr_status.farmer;
    curr_status.cab = 1 - curr_status.cab;

    return curr_status;
}

status move_nothing (status curr_status) {
    curr_status.farmer = 1 - curr_status.farmer;

    return curr_status;
}

// Calculate the heuristic cost to move object 
int cal_h(status curr_status) {
    return curr_status.farmer + curr_status.wolf + curr_status.goat + curr_status.cab;
}

// Calculate f cost of the current status 
status cal_f(status curr_status, status prev_status) {
    curr_status.prev = new status;
    *curr_status.prev = prev_status;
    curr_status.g = prev_status.g + 1;
    curr_status.h = cal_h(curr_status);
    curr_status.f = curr_status.g + curr_status.h;

    return curr_status;
}

// Check fiinshed status 
bool isGoal(status curr_status){
    return curr_status.farmer + curr_status.wolf + curr_status.goat + curr_status.cab == 0;
}

bool checkExistInOpen (priority_queue<status>& pq, status& node) {
    priority_queue<status> temp_pq = pq;
    while (!temp_pq.empty()) {
        if (temp_pq.top().farmer == node.farmer &&
            temp_pq.top().wolf == node.wolf &&
            temp_pq.top().goat == node.goat &&
            temp_pq.top().cab == node.cab)
            return true;
        temp_pq.pop();
    }
    return false;
}

bool checkExistInClose (vector<status> vt, status curr_status) {
    for (int i = 0; i < vt.size(); i++) {
        if (vt[i].farmer == curr_status.farmer &&
            vt[i].wolf == curr_status.wolf &&
            vt[i].goat == curr_status.goat &&
            vt[i].cab == curr_status.cab)
            return true;
    }
    return false;
}

vector<status> getNeighbors(status curr_status) {
    vector<status> vt_temp;

    if (curr_status.farmer == curr_status.wolf) {
        status temp = move_wolf(curr_status);
        temp = cal_f(temp, curr_status);
        if (false_status(temp)){
            vt_temp.push_back(temp);
        }
    }
    if (curr_status.farmer == curr_status.goat) {
        status temp = move_goat(curr_status);
        temp = cal_f(temp, curr_status);
        if (false_status(temp)){
            vt_temp.push_back(temp);
        }
    }
    if (curr_status.farmer == curr_status.cab) {
        status temp = move_cab(curr_status);
        temp = cal_f(temp, curr_status);
        if (false_status(temp)){
            vt_temp.push_back(temp);
        }
    }
    if (1 == 1) {
        status temp = move_nothing(curr_status);
        temp = cal_f(temp, curr_status);
        if (false_status(temp)){
            vt_temp.push_back(temp);
        }
    }
    return vt_temp;

}

void print(status* goal){
    cout << goal->farmer << " " << goal->wolf << " " << goal->goat << " " << goal->cab << endl;
    do {
        goal = goal->prev;
        cout << goal->farmer << " " << goal->wolf << " " << goal->goat << " " << goal->cab << endl;
    } while (goal->prev != NULL); 
}

template <typename T>
void astar(T curr_status, vector<T> (*getNeighbors)(T), bool (*isGoal)(T), void (*print)(T*)) {
    priority_queue <T> open;
    vector<T> close;
    open.push(curr_status);

    T* goal = new T;
    int isOut = false;

    while(open.size() > 0) {
        curr_status = open.top();

        open.pop();

        vector<T> vt_temp = getNeighbors(curr_status);

        for (T i: vt_temp) {
            if (isGoal(i)) {
                goal = &i;
                isOut = true;
                break;
            }
        }

        if (isOut)
            break;

        for (T i: vt_temp) {
            if (!checkExistInClose(close, i) && !checkExistInOpen(open, i)) {
                open.push(i);
            }
        }
        close.push_back(curr_status);
    }


    print(goal);
}

int main() {
    status curr_status;
    curr_status.farmer = 1;
    curr_status.wolf = 1; 
    curr_status.goat = 1; 
    curr_status.cab = 1; 

    astar(curr_status, &getNeighbors, &isGoal, &print);

    return 0;
}