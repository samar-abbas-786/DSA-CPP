#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>

using namespace std;

// Define the NFA structure
class EpsilonNFA
{
public:
    set<string> states;                             // Q
    set<char> alphabet;                             // Σ
    map<string, map<char, set<string>>> transition; // δ
    map<string, set<string>> epsilonTransitions;    // ϵ transitions
    string startState;                              // q0
    set<string> finalStates;                        // F

    // Load NFA from file
    void loadFromFile(string filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Error opening file.\n";
            return;
        }

        int numStates, numFinalStates, numTransitions, numEpsilonTransitions;
        file >> numStates;

        // Read states
        for (int i = 0; i < numStates; ++i)
        {
            string state;
            file >> state;
            states.insert(state);
        }

        // Read alphabet
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
            transition[from][symbol].insert(to);
        }

        // Read epsilon transitions
        file >> numEpsilonTransitions;
        for (int i = 0; i < numEpsilonTransitions; ++i)
        {
            string from, to;
            file >> from >> to;
            epsilonTransitions[from].insert(to);
        }

        // Read start state
        file >> startState;

        // Read final states
        file >> numFinalStates;
        for (int i = 0; i < numFinalStates; ++i)
        {
            string state;
            file >> state;
            finalStates.insert(state);
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

            if (epsilonTransitions.find(current) != epsilonTransitions.end())
            {
                for (const string &nextState : epsilonTransitions[current])
                {
                    if (closure.find(nextState) == closure.end())
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
        q.push(make_pair(startClosure, vector<string>()));

        bool accepted = false;
        vector<vector<string>> acceptingPaths;

        while (!q.empty())
        {
            pair<set<string>, vector<string>> frontElement = q.front();
            set<string> currentStates = frontElement.first;
            vector<string> path = frontElement.second;
            q.pop();

            // If we consumed the entire input, check if we reached an accepting state
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

            // Move for each character in input
            if (path.size() < input.size())
            {
                char symbol = input[path.size()];
                set<string> nextStates;

                for (const string &state : currentStates)
                {
                    if (transition[state].find(symbol) != transition[state].end())
                    {
                        nextStates.insert(transition[state][symbol].begin(), transition[state][symbol].end());
                    }
                }

                // Apply epsilon-closure
                nextStates = epsilonClosure(nextStates);

                if (!nextStates.empty())
                {
                    vector<string> newPath = path;
                    newPath.push_back(string(1, symbol));
                    q.push(make_pair(nextStates, newPath));
                }
            }
        }

        // Output result
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
        {
            break;
        }
        nfa.simulate(testString);
    }

    return 0;
}