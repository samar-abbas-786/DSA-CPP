#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>

using namespace std;

class EpsilonNFA
{
public:
    set<string> states;
    set<char> alphabet;
    map<string, map<char, set<string>>> transition;
    map<string, set<string>> epsilonTransitions;
    string startState;
    set<string> finalStates;

    void loadFromFile(string filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Error opening file: " << filename << "\n";
            return;
        }

        int numStates, numFinalStates, numTransitions, numEpsilonTransitions;
        file >> numStates;

        for (int i = 0; i < numStates; ++i)
        {
            string state;
            file >> state;
            states.insert(state);
        }

        int alphabetSize;
        file >> alphabetSize;
        for (int i = 0; i < alphabetSize; ++i)
        {
            char symbol;
            file >> symbol;
            alphabet.insert(symbol);
        }

        // Read transitions
        file >> numTransitions;
        for (int i = 0; i < numTransitions; ++i)
        {
            string from, to;
            char symbol;
            file >> from >> symbol >> to;
            if (states.count(from) && states.count(to) && alphabet.count(symbol))
            {
                transition[from][symbol].insert(to);
            }
            else
            {
                cerr << "Invalid transition: " << from << " --" << symbol << "--> " << to << "\n";
            }
        }

        // Read epsilon transitions
        file >> numEpsilonTransitions;
        for (int i = 0; i < numEpsilonTransitions; ++i)
        {
            string from, to;
            file >> from >> to;
            if (states.count(from) && states.count(to))
            {
                epsilonTransitions[from].insert(to);
            }
            else
            {
                cerr << "Invalid epsilon transition: " << from << " -> " << to << "\n";
            }
        }

        // Read start state
        file >> startState;
        if (!states.count(startState))
        {
            cerr << "Invalid start state: " << startState << "\n";
            return;
        }

        // Read final states
        file >> numFinalStates;
        for (int i = 0; i < numFinalStates; ++i)
        {
            string state;
            file >> state;
            if (states.count(state))
            {
                finalStates.insert(state);
            }
            else
            {
                cerr << "Invalid final state: " << state << "\n";
            }
        }

        file.close();
    }

    // Compute epsilon-closure of a state
    set<string> epsilonClosure(string state)
    {
        set<string> closure;
        stack<string> stack;
        stack.push(state);
        closure.insert(state);

        while (!stack.empty())
        {
            string current = stack.top();
            stack.pop();

            if (epsilonTransitions.count(current))
            {
                for (const string &nextState : epsilonTransitions[current])
                {
                    if (!closure.count(nextState))
                    {
                        closure.insert(nextState);
                        stack.push(nextState);
                    }
                }
            }
        }
        return closure;
    }

    // Compute epsilon-closure of a set of states
    set<string> epsilonClosure(set<string> states)
    {
        set<string> closure;
        for (const string &state : states)
        {
            set<string> stateClosure = epsilonClosure(state);
            closure.insert(stateClosure.begin(), stateClosure.end());
        }
        return closure;
    }

    // Simulate the NFA
    void simulate(string input)
    {
        queue<pair<set<string>, vector<string>>> q;
        set<string> startClosure = epsilonClosure(startState);
        q.push({startClosure, {}});

        bool accepted = false;
        vector<vector<string>> acceptingPaths;

        while (!q.empty())
        {
            pair<set<string>, vector<string>> front = q.front();
            set<string> currentStates = front.first;
            vector<string> path = front.second;
            q.pop();

            if (path.size() == input.size())
            {
                for (const string &state : currentStates)
                {
                    if (finalStates.count(state))
                    {
                        accepted = true;
                        acceptingPaths.push_back(path);
                    }
                }
            }

            if (path.size() < input.size())
            {
                char symbol = input[path.size()];
                set<string> nextStates;

                for (const string &state : currentStates)
                {
                    if (transition.count(state) && transition[state].count(symbol))
                    {
                        nextStates.insert(transition[state][symbol].begin(), transition[state][symbol].end());
                    }
                }

                nextStates = epsilonClosure(nextStates);

                if (!nextStates.empty())
                {
                    vector<string> newPath = path;
                    newPath.push_back(string(1, symbol));
                    q.push({nextStates, newPath});
                }
            }
        }

        cout << "Input: " << input << " -> ";
        if (accepted)
        {
            cout << "Accepted\n";
            cout << "Paths:\n";
            for (const auto &path : acceptingPaths)
            {
                for (const auto &step : path)
                {
                    cout << step << " -> ";
                }
                cout << "(final state)\n";
            }
        }
        else
        {
            cout << "Rejected\n";
        }
    }
};

// Driver function
int main()
{
    EpsilonNFA nfa;
    string filename = "nfa_input.txt";

    // Load NFA from file
    nfa.loadFromFile(filename);

    // Get user input for test strings
    cout << "Enter test strings (type 'exit' to stop):\n";
    string testString;
    while (true)
    {
        cout << "Test string: ";
        cin >> testString;
        if (testString == "exit")
            break;
        nfa.simulate(testString);
    }

    return 0;
}