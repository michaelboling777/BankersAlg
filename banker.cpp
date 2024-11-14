//********************************************************************
//
// Michael Boling
// Operating Systems
// Programming Project #5: Banker's Algorithm
// March 26, 2023
// Instructor: Dr. Siming Liu
//
//********************************************************************

#include <iostream>
#include <stdio.h>
#include <fstream> //to read from .txt file
#include <vector>

using namespace std;

// formatting functions:
void alphabet();
void alphabet_nonindent();
void req_format();

// global variable(s):
char alph;

int main(int argc, char *argv[])
{
    // # of processes and # of rescource type
    int n = 0; // # processes
    int m = 0; // # rescources

    // variables needed... g-i
    int test_safe = 0;
    int need_itr = 0;
    bool req_rescource = true;
    int read_no;
    char read_sem;

    string txt_file = argv[1];
    txt_file = txt_file.c_str();

    // testing if cml arg is passed
    if (argc != 2)
    {
        cout << "Please enter the .txt file as a command line argument.\n"
             << endl;
    }
    ifstream Read_File;

    Read_File.open(txt_file);
    if (Read_File.is_open())
    {
        Read_File >> n;
        Read_File >> m;
    }

    cout << "\nThere are " << n << " processes in the system.\n\n"; // a
    cout << "There are " << m << " resource types.\n\n";            // b

    // matrices:
    vector<vector<int>> allocate(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<vector<int>> avail(1, vector<int>(m));
    vector<int> check(m);
    vector<int> done_arr(n, 0);
    vector<vector<int>> request(1, vector<int>(m));
    vector<int> safe(n, 0);

    // Now, we read the allocation matrix:

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < m; j++)
        {

            Read_File >> allocate[i][j];
        }
    }

    // print allocate matrix
    // c

    cout << "The Allocation Matrix is...\n";
    alphabet();
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << ":"
             << " ";
        for (int j = 0; j < m; j++)
        {
            cout << allocate[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    //===================================================
    //===================================================

    // Now, we read max matrix

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < m; j++)
        {

            Read_File >> max[i][j];
        }
    }

    // printing max matrix:
    // d

    cout << "The Max Matrix is...\n";
    alphabet();
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << ":"
             << " ";
        for (int j = 0; j < m; j++)
        {
            cout << max[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    //===================================================
    //===================================================

    // Now, we compute and print "need" matrix
    // e

    cout << "The Need Matrix is...\n";
    alphabet();
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << ":"
             << " ";
        for (int j = 0; j < m; j++)
        {
            // we know need matrix to simply be max - allocate at appropriate iteration(s)
            need[i][j] = max[i][j] - allocate[i][j];
            cout << need[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    //===================================================
    //===================================================

    // Now, we read availability vector:

    for (int i = 0; i < 1; i++)
    {

        for (int j = 0; j < m; j++)
        {

            Read_File >> avail[i][j];
        }
    }

    // printing avail vector:
    // f

    cout << "The Available Vector is...\n";
    alphabet_nonindent();
    cout << endl;
    for (int i = 0; i < 1; i++)
    {

        for (int j = 0; j < m; j++)
        {
            cout << avail[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    //===================================================
    //===================================================

    // initializing check[] array
    for (int i = 0; i < m; i++)
    {

        check[i] = avail[0][i];
    }

    // checking if safe...
    // g

    while (test_safe < n)
    {
        bool notify = false;

        // testing the length of done_arr
        for (int i = 0; i < n; i++)
        {

            // there is an index "i" that is false: (condition met)
            if (done_arr[i] == false)
            {
                for (need_itr = 0; need_itr < m; need_itr++)
                {
                    // if this condition is met then break out of the loop
                    // if not, then keep trying to find a condition that will
                    // meet this standard
                    if ((check[need_itr] < need[i][need_itr]))
                    {
                        break;
                    }
                    // all iteration reached, we conclude need[i] <= check
                }
                // this condition ensure that it hasnt been broken out of the loop:
                //(all the previous iterations have indeed been exhausted)
                if (need_itr == m)
                {
                    for (int r = 0; r < m; r++)
                    {
                        // Now, we can safetly get the new rescource allocation:
                        check[r] = check[r] + allocate[i][r];
                    }
                    // if that passed, we set that iteration of i of done_arr to true
                    done_arr[i] = true;
                    notify = true;
                    // for breaking out of loop:
                    safe[test_safe++] = i;
                }
            }
        }

        // notify will only need to be false once to be not safe for all processes
        if (notify == false)
        {
            cout << "Error, your system is NOT in a safe state!\n";
            break;
        }
    }
    // if the while loop was indeed exhausted w/o breaks that caused test_safe != n then ...test:
    if (test_safe == n)
    {
        cout << "THE SYSTEM IS IN A SAFE STATE!\n\n";
    }

    //===================================================
    //===================================================

    Read_File >> read_no;
    Read_File >> read_sem;

    // reading request vector:
    for (int i = 0; i < 1; i++)
    {

        for (int j = 0; j < m; j++)
        {
            Read_File >> request[i][j];
        }
    }

    // printing request vector:
    // h
    cout << "The Request Vector is...\n";
    req_format();
    cout << endl;

    for (int i = 0; i < 1; i++)
    {
        cout << read_no << read_sem;
        for (int j = 0; j < m; j++)
        {
            cout << request[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    //===================================================
    //===================================================

    // compute if request can be granted:
    // i
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // ensuring these conditions are NOT met in order to release rescources:
            if ((need[read_no][j] < request[i][j]) || (request[i][j] > avail[i][j]))
            {
                req_rescource = false;
                break;
            }
        }
        break;
    }
    if (req_rescource == true)
    {
        cout << "THE REQUEST CAN BE GRANTED!\n\n";
    }
    else
    {
        cout << "Error, the request could NOT be granted!\n\n";
    }

    //===================================================
    //===================================================

    // computing new available vector:
    // j
    for (int i = 0; i < 1; i++)
    {

        for (int j = 0; j < m; j++)
        {
            // it is simply availability matrix - request matrix (at right iterations)

            avail[i][j] = avail[i][j] - request[i][j];
        }
    }
    // printing the new available vector:

    cout << "The Available Vector is...\n";
    alphabet_nonindent();
    cout << endl;
    for (int i = 0; i < 1; i++)
    {

        for (int j = 0; j < m; j++)
        {
            cout << avail[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

//=======================================================================
//=======================================================================

//********************************************************************
//
// alphabet Function
//
// This function is used to format the allocation, max, and need matrices
// as well as providing ample indentation for the matrices that are to be printed
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary       n/a
//*******************************************************************
void alphabet()
{
    alph = 'A';
    cout << "   ";
    for (int i = 0; i < 4; i++)
    {

        cout << alph << " ";
        alph++;
    }
}

//********************************************************************
//
// alphabet_nonindent Function
//
// This function is used to format the "avail" matrix
// It has no indentation for proper formatting when wanting to print the
// avail matrix
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary       n/a
//*******************************************************************
void alphabet_nonindent()
{
    alph = 'A';

    for (int i = 0; i < 4; i++)
    {

        cout << alph << " ";
        alph++;
    }
}

//********************************************************************
//
// req_format Function
//
// This function is used to format the "request" matrix
// It has proper indentation when wanting to print the "request" matrix out
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary       n/a
//*******************************************************************

void req_format()
{
    alph = 'A';
    cout << "  ";

    for (int i = 0; i < 4; i++)
    {

        cout << alph << " ";
        alph++;
    }
}
