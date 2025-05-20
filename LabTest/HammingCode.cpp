#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int data[4];

    cout << "Enter Data Bits (a3 a2 a1 a0) : ";
    for (int i = 0; i < 4; i++)
    {
        cin >> data[i];
    }

    int redundant[3];

    redundant[2] = data[1] ^ data[2] ^ data[3];
    redundant[1] = data[2] ^ data[1] ^ data[0];
    redundant[0] = data[0] ^ data[3] ^ data[2];

    int codeword[7];

    codeword[0] = data[0];
    codeword[1] = data[1];
    codeword[2] = data[2];
    codeword[3] = data[3];
    codeword[4] = redundant[0];
    codeword[5] = redundant[1];
    codeword[6] = redundant[2];

    cout << "Generated Codeword : ";

    for (int i = 0; i < 7; i++)
    {
        cout << codeword[i];
    }
    cout << endl;

    int recieved[7];

    cout << "Enter the recieved bits (b3 b2 b1 b0 q2 q1 q0) : ";

    for (int i = 0; i < 7; i++)
    {
        cin >> recieved[i];
    }

    vector<int> syndrome(3, 0);

    syndrome[2] = recieved[3] ^ recieved[2] ^ recieved[1] ^ recieved[6];
    syndrome[1] = recieved[0] ^ recieved[2] ^ recieved[1] ^ recieved[5];
    syndrome[0] = recieved[0] ^ recieved[3] ^ recieved[2] ^ recieved[4];

    int error = 0;

    if (syndrome == vector<int>{0, 0, 1})
    {
        error = 7;
    }

    else if (syndrome == vector<int>{0, 1, 0})
    {
        error = 6;
    }

    else if (syndrome == vector<int>{0, 1, 1})
    {
        error = 2;
    }

    else if (syndrome == vector<int>{1, 0, 0})
    {
        error = 5;
    }

    else if (syndrome == vector<int>{1, 0, 1})
    {
        error = 4;
    }

    else if (syndrome == vector<int>{1, 1, 0})
    {
        error = 1;
    }

    else if (syndrome == vector<int>{1, 1, 1})
    {
        error = 3;
    }

    if (error == 0)
    {
        cout << "No error detected.";
    }

    else
    {
        cout << "Error detected at position " << error << endl;
        recieved[error - 1] ^= 1;

        cout << "Corrected Code : ";
        for (int i = 0; i < 7; i++)
        {
            cout << recieved[i];
        }
    }
}
