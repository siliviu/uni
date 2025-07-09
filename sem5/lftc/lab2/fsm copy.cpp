#include <bits/stdc++.h>

using namespace std;

template<class T = string, class U = char>
class FSM {
    vector<T> states, finalStates;
    vector<U> alphabet;
    T initialState;
    unordered_map<T, unordered_map<U, vector<T>>> transitions;
public:
    FSM(const vector<U>& _alphabet, const vector<T>& _states, T _initialState, const vector<T>& _finalStates, const vector<tuple<T, T, U>>& _transitions)
        : alphabet(_alphabet), states(_states), initialState(_initialState), finalStates(_finalStates) {
        for (auto& [from, to, symbol] : _transitions)
            transitions[from][symbol].emplace_back(to);
    }
    vector<U> getAlphabet() {
        return alphabet;
    }
    vector<T> getStates() {
        return states;
    }
    vector<T> getFinalStates() {
        return finalStates;
    }
    vector<tuple<T, T, U>> getTransitions() {
        vector<tuple<T, T, U>> answer;
        for (auto& [from, x] : transitions)
            for (auto& [symbol, y] : x)
                for (auto& to : y)
                    answer.emplace_back(from, to, symbol);
        return answer;
    }
    bool isDeterministic() {
        for (auto& [from, x] : transitions)
            for (auto& [symbol, y] : x)
                if (y.size() > 1)
                    return false;
        return true;
    }
    bool isAccepted(vector<U> input) {
        T curState = initialState;
        for (auto& symbol : input) {
            if (!transitions[curState].count(symbol))
                return false;
            curState = transitions[curState][symbol][0];
        }
        return find(finalStates.begin(), finalStates.end(), curState) != finalStates.end();
    }
    vector<U> getLongestAccepted(vector<U> input) {
        T curState = initialState;
        vector<U> answer, current;
        for (auto& symbol : input) {
            if (!transitions[curState].count(symbol))
                break;
            curState = transitions[curState][symbol][0];
            current.emplace_back(symbol);
            if (find(finalStates.begin(), finalStates.end(), curState) != finalStates.end())
                answer = current;
        }
        return answer;

    }
};