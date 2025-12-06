#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& workerShifts, size_t day, size_t col, std::set<Worker_T>& alreadyWorking);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    //need something to count each day and such
    std::vector<size_t> workerShifts(avail[0].size(), 0);
    //reintialize sched after the sched.clear
    size_t temp = avail.size();
    for (size_t i = 0; i < temp; i++){
        std::vector<Worker_T> tempRow(dailyNeed, INVALID_ID);
        sched.push_back(tempRow);
    }
    std::set<Worker_T> alreadyWorking;
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, 0, 0, alreadyWorking);


}
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& workerShifts, size_t day, size_t col, std::set<Worker_T>& alreadyWorking){
    //move to the next day if the col is out of bounds
    if (col >= sched[day].size()){
        alreadyWorking.clear();
        scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day + 1, 0, alreadyWorking);
        return false;
    }
    //this is the base case
    if (day >= sched.size()){
        return true;
    }
    for (Worker_T w = 0; w < avail[0].size(); w++){
        if (avail[day][w] == true && workerShifts[w] < maxShifts){
            if (alreadyWorking.count(w) == 0){
                alreadyWorking.insert(w);
                workerShifts[w]++;
                sched[day][col] = w;
                if (scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day, col + 1, alreadyWorking)){
                    return true;
                }
                sched[day][col] = INVALID_ID;
                workerShifts[w]--;
            }
        }
    }
    return false;
}
