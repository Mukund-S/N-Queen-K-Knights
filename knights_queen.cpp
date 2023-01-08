//
//  knights_queen.cpp
//
//
//  Mukund Sharma
//  GO1374620
//  CS580
//

#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int N, M, K, Q;

void generateRandomly(vector<vector<int>> &board, vector<vector<int>> &state, vector<vector<int>> &stateQ)
{

    // Seed for the random function
    srand(time(0));

    // Iterating through the
    // column indices
    int p = K;
    int l = Q;
    while (p > 0 || l > 0)
    {
        int i = rand() % N;
        int j = rand() % M;
        //Check for number of remaining knights
        //and addtiton into random board
        if (p > 0 && board[i][j] == 0)
        {
            state[i][j] = 1;
            board[i][j] = 1;
            p--;
            continue;
        }
        //Check for number of remaining queen
        //and addtiton into random board
        if (l > 0 && board[i][j] == 0)
        {
            stateQ[i][j] = 2;
            board[i][j] = 2;
            l--;
            continue;
        }
    }
}

//10 10 10 10 120 abc other

// A utility function that prints
// the 2D array "board".
void printBoard(vector<vector<int>> &board, int &conflict, string filename)
{
    ofstream file(filename);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (board[i][j] == 0)
                file << "E";
            else if (board[i][j] == 1)
                file << "K";
            else if (board[i][j] == 2)
                file << "Q";
        }
        file << "\n";
    }
    file << conflict;
    file.close();
}

//Function calculate number of conflicts for knights
int conflictsForKnightsKnights(vector<vector<int>> &v, int &row, int &col)
{
    int conflict = 0;
    if (row >= 1 && col >= 2 && row < N && col < M && (v[row - 1][col - 2] == 1))
    {
        conflict++;
    }
    if (row >= 1 && row < N && col < M - 2 && (v[row - 1][col + 2] == 1))
    {
        conflict++;
    }
    if (col >= 2 && row < N - 1 && col < M && (v[row + 1][col - 2] == 1))
    {
        conflict++;
    }
    if (row < N - 1 && col < M - 2 && (v[row + 1][col + 2] == 1))
    {
        conflict++;
    }
    if (row >= 2 && col >= 1 && row < N && col < M && (v[row - 2][col - 1] == 1))
    {
        conflict++;
    }
    if (row >= 2 && row < N && col < M - 1 && (v[row - 2][col + 1] == 1))
    {
        conflict++;
    }
    if (col >= 1 && row < N - 2 && col < M && (v[row + 2][col - 1] == 1))
    {
        conflict++;
    }
    if (row < N - 2 && col < M - 1 && (v[row + 2][col + 1] == 1))
    {
        conflict++;
    }

    return conflict;
}

//Function calculate number of conflicts for knights
int conflictsForKnightsQueen(vector<vector<int>> &v, int &row, int &col)
{
    int conflict = 0;
    if (row >= 1 && col >= 2 && row < N && col < M && (v[row - 1][col - 2] == 2))
    {
        conflict++;
    }
    if (row >= 1 && row < N && col < M - 2 && (v[row - 1][col + 2] == 2))
    {
        conflict++;
    }
    if (col >= 2 && row < N - 1 && col < M && (v[row + 1][col - 2] == 2))
    {
        conflict++;
    }
    if (row < N - 1 && col < M - 2 && (v[row + 1][col + 2] == 2))
    {
        conflict++;
    }
    if (row >= 2 && col >= 1 && row < N && col < M && (v[row - 2][col - 1] == 2))
    {
        conflict++;
    }
    if (row >= 2 && row < N && col < M - 1 && (v[row - 2][col + 1] == 2))
    {
        conflict++;
    }
    if (col >= 1 && row < N - 2 && col < M && (v[row + 2][col - 1] == 2))
    {
        conflict++;
    }
    if (row < N - 2 && col < M - 1 && (v[row + 2][col + 1] == 2))
    {
        conflict++;
    }
    return conflict;
}

//Function call for conflicts of knights
int knightConflict(vector<vector<int>> &board)
{
    int c = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (board[i][j] == 1)
                c += conflictsForKnightsKnights(board, i, j);
        }
    }
    //Since we are counting 2 conflicts
    //for the number of knights and it
    //is getting repeated. So we divide it
    //to half.
    c /= 2;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (board[i][j] == 1)
                c += conflictsForKnightsQueen(board, i, j);
        }
    }
    return c;
}

// A utility function that compares
// two arrays, state1 and state2 and
// returns true if equal
// and false otherwise.
bool stateDifference(vector<vector<int>> &state1,
                     vector<vector<int>> &state2)
{

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            if (state1[i][j] != state2[i][j])
            {
                return false;
            }
    }
    return true;
}

// A utility function that fills
// the 2D array "board" with
// values "value"
void fillBoard(vector<vector<int>> &board, int value)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            board[i][j] = value;
        }
    }
}

int checkQueen(vector<vector<int>> &board)
{
    int attacking = 0, row, col;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (board[i][j] == 2)
            {
                // To the left of same row
                // (row remains constant
                // and col decreases)
                row = i;
                col = j - 1;
                while (col >= 0)
                {
                    if (board[row][col] == 1)
                        break;
                    if (board[row][col] == 2)
                    {
                        attacking++;
                        //break;
                    }
                    col--;
                }
                // To the right of same row
                // (row remains constant
                // and col increases)
                row = i;
                col = j + 1;
                while (col < M)
                {
                    if (board[row][col] == 1)
                        break;
                    if (board[row][col] == 2)
                    {
                        attacking++;
                        //break;//check
                    }
                    col++;
                }
                // Diagonally to the left up
                // (row and col simultaneously
                // decrease)
                row = i - 1;
                col = j - 1;
                while (col >= 0 && row >= 0)
                {
                    if (board[row][col] == 1)
                        break;
                    if (board[row][col] == 2)
                    {
                        attacking++;
                        //break;
                    }
                    col--;
                    row--;
                }
                // Diagonally to the right down
                // (row and col simultaneously
                // increase)
                row = i + 1;
                col = j + 1;
                while (col < M && row < N)
                {
                    if (board[row][col] == 1)
                        break;
                    if (board[row][col] == 2)
                    {
                        attacking++;
                        //break;
                    }
                    col++;
                    row++;
                }

                // Diagonally to the left down
                // (col decreases and row
                // increases)
                row = i + 1;
                col = j - 1;
                while (col >= 0 && row < N)
                {
                    if (board[row][col] == 1)
                        break;
                    if (board[row][col] == 2)
                    {
                        attacking++;
                        //break;
                    }
                    col--;
                    row++;
                }

                // Diagonally to the right up
                // (col increases and row
                // decreases)
                row = i - 1;
                col = j + 1;
                while (col < M && row >= 0)
                {
                    if (board[row][col] == 1)
                        break;
                    if (board[row][col] == 2)
                    {
                        attacking++;
                        //break;
                    }
                    col++;
                    row--;
                }
                //Going UP in same column
                row = i - 1;
                col = j;
                while (row >= 0)
                {
                    if (board[row][col] == 1)
                        break;
                    if (board[row][col] == 2)
                    {
                        attacking++;
                        //break;
                    }
                    row--;
                }

                //Going Down in same column
                row = i + 1;
                col = j;
                while (row < N)
                {
                    if (board[row][col] == 1)
                        break;
                    if (board[row][col] == 2)
                    {
                        attacking++;
                        //break;
                    }
                    row++;
                }
            }
        }
    }
    return attacking;
}

// This function calculates the
// objective value of the
// state(queens attacking each other)
// using the board by the
// following logic.
int calculateConflicts(vector<vector<int>> &board,
                       vector<vector<int>> &state, vector<vector<int>> &stateQ)
{
    // For each queen in a column, we check
    // for other queens falling in the line
    // of our current queen and if found,
    // any, then we increment the variable
    // attacking count.

    // Number of queens attacking each other,
    // initially zero.
    int attacking = 0;

    //check for queen
    attacking += checkQueen(board);
    //check for knights
    attacking /= 2;
    attacking += knightConflict(board);
    // Return pairs.
    return (int)(attacking);
}

// A utility function that
// generates a board configuration
// given the state.
void generateBoard(vector<vector<int>> &board,
                   vector<vector<int>> &state, vector<vector<int>> &stateQ)
{
    fillBoard(board, 0);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (state[i][j] == 1)
                board[i][j] = 1;
            if (stateQ[i][j] == 2)
                board[i][j] = 2;
        }
    }
}
//Copying one State to another
void copyState(vector<vector<int>> &state1, vector<vector<int>> &state2)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            state1[i][j] = state2[i][j];
    }
}

int neighbourCal(vector<vector<int>> &NeighbourBoard, vector<vector<int>> &NeighbourState, vector<vector<int>> &NeighbourStateQ, int opObjective,
                 vector<vector<int>> &opState, vector<vector<int>> &opStateQ, vector<vector<int>> &opBoard)
{
    // Calculating the objective
    // value of the neighbour.

    int temp = calculateConflicts(
        NeighbourBoard,
        NeighbourState, NeighbourStateQ);

    // Comparing temporary and optimal
    // neighbour objectives and if
    // temporary is less than optimal
    // then updating accordingly.

    if (temp <= opObjective)
    {
        opObjective = temp;

        copyState(opState,
                  NeighbourState);

        copyState(opStateQ,
                  NeighbourStateQ);

        generateBoard(opBoard,
                      opState, opStateQ);
    }
    cout << "Conflicts = " << opObjective << endl;
    return opObjective;
}

int findNeighbour(vector<vector<int>> &board,
                  vector<vector<int>> &state, vector<vector<int>> &stateQ)
{
    // Declaring and initializing the
    // optimal board and state with
    // the current board and the state
    // as the starting point.

    vector<vector<int>> opBoard(N, vector<int>(M, 0));
    vector<vector<int>> opState(N, vector<int>(M, 0));
    vector<vector<int>> opStateQ(N, vector<int>(M, 0));

    copyState(opState,
              state);
    copyState(opStateQ,
              stateQ);
    generateBoard(opBoard,
                  opState, opStateQ);
    // Initializing the optimal
    // objective value

    int opObjective = calculateConflicts(opBoard,
                                         opState, opStateQ);

    // Declaring and initializing
    // the temporary board and
    // state for the purpose
    // of computation.

    vector<vector<int>> NeighbourBoard(N, vector<int>(M, 0));
    vector<vector<int>> NeighbourState(N, vector<int>(M, 0));
    vector<vector<int>> NeighbourStateQ(N, vector<int>(M, 0));

    copyState(NeighbourState,
              state);
    copyState(NeighbourStateQ,
              stateQ);
    generateBoard(NeighbourBoard,
                  NeighbourState, NeighbourStateQ);
    // Iterating through all
    // possible neighbours
    // of the board.

    srand(time(0));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (board[i][j] == 0)
            {
                int r = rand() % N;
                int c = rand() % M;
                while (!board[r][c])
                {
                    r = rand() % N;
                    c = rand() % M;
                }
                if (board[r][c] == 1)
                {
                    NeighbourState[i][j] = 1;
                    NeighbourBoard[i][j] = 1;
                    NeighbourState[r][c] = 0;
                    NeighbourBoard[r][c] = 0;
                    opObjective = neighbourCal(NeighbourBoard, NeighbourState, NeighbourStateQ, opObjective,
                                               opState, opStateQ, opBoard);
                    NeighbourState[i][j] = 0;
                    NeighbourBoard[i][j] = 0;
                    NeighbourState[r][c] = 1;
                    NeighbourBoard[r][c] = 1;
                }
                if (board[r][c] == 2)
                {
                    NeighbourStateQ[i][j] = 2;
                    NeighbourBoard[i][j] = 2;
                    NeighbourStateQ[r][c] = 0;
                    NeighbourBoard[r][c] = 0;
                    opObjective = neighbourCal(NeighbourBoard, NeighbourState, NeighbourStateQ, opObjective,
                                               opState, opStateQ, opBoard);
                    NeighbourStateQ[i][j] = 0;
                    NeighbourBoard[i][j] = 0;
                    NeighbourStateQ[r][c] = 2;
                    NeighbourBoard[r][c] = 2;
                }
            }
        }
    }

    // Copying the optimal board and
    // state thus found to the current
    // board
    copyState(state, opState);
    copyState(stateQ, opStateQ);
    fillBoard(board, 0);
    generateBoard(board, state, stateQ);
    return opObjective;
}

void EmptyBoard(vector<vector<int>> &board,
                vector<vector<int>> &state, vector<vector<int>> &stateQ)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            board[i][j] = 0;
            state[i][j] = 0;
            stateQ[i][j] = 0;
        }
    }
}

int hillClimbing(vector<vector<int>> &board, vector<vector<int>> &state, vector<vector<int>> &stateQ)
{

    // Declaring and initializing the
    // neighbour board and state with
    // the current board and the state
    // as the starting point.

    vector<vector<int>> neighbourBoard(N, vector<int>(M, 0));
    vector<vector<int>> neighbourState(N, vector<int>(M, 0));
    vector<vector<int>> neighbourStateQ(N, vector<int>(M, 0));

    copyState(neighbourState, state);
    copyState(neighbourStateQ, stateQ);
    generateBoard(neighbourBoard, neighbourState, neighbourStateQ);
    do
    {

        // Copying the neighbour board and
        // state to the current board and
        // state, since a neighbour
        // becomes current after the jump.
        copyState(state, neighbourState);
        copyState(stateQ, neighbourStateQ);
        generateBoard(board, state, stateQ);
        // Getting the optimal neighbour

        int c = findNeighbour(neighbourBoard, neighbourState, neighbourStateQ);

        if (c == 0 || (stateDifference(state, neighbourState) && stateDifference(stateQ, neighbourStateQ)))
        {

            // If neighbour and current are
            // equal then no optimal neighbour
            // exists and therefore output the
            // result and break the loop.
            if (c == 0)
            {
                copyState(state, neighbourState);
                copyState(stateQ, neighbourStateQ);
                generateBoard(board, state, stateQ);
            }
            //            cout<<"Final Ans:\n";
            //            printBoard(board);
            break;
        }
        else if (calculateConflicts(board, state, stateQ) == calculateConflicts(
                                                                 neighbourBoard, neighbourState, neighbourStateQ))
        {

            // If neighbour and current are
            // not equal but their objectives
            // are equal then we are either
            // approaching a shoulder or a
            // local optimum, in any case,
            // jump to a random neighbour
            // to escape it.

            EmptyBoard(neighbourBoard, neighbourState, neighbourStateQ);
            generateRandomly(neighbourBoard, neighbourState, neighbourStateQ);
        }

    } while (true);

    return calculateConflicts(board, state, stateQ);
}

int SimulatedAnnealing(vector<vector<int>> &board,
                       vector<vector<int>> &state, vector<vector<int>> &stateQ)
{

    // Declaring and initializing the
    // neighbour board and state with
    // the current board and the state
    // as the starting point.

    vector<vector<int>> neighbourBoard(N, vector<int>(M, 0));
    vector<vector<int>> neighbourState(N, vector<int>(M, 0));
    vector<vector<int>> neighbourStateQ(N, vector<int>(M, 0));
    srand(time(0));
    copyState(neighbourState, state);
    copyState(neighbourStateQ, stateQ);
    generateBoard(neighbourBoard, neighbourState, neighbourStateQ);

    double temperature = 4000; //temperature
    double val = 0.99;
    while (temperature > 0)
    {

        // Copying the neighbour board and
        // state to the current board and
        // state, since a neighbour
        // becomes current after the jump.

        temperature = temperature * val;
        int conflictBoard = calculateConflicts(board, state, stateQ);

        // Getting the optimal neighbour

        int conflictNeighbour = findNeighbour(neighbourBoard, neighbourState, neighbourStateQ);

        double cost = conflictNeighbour - conflictBoard;
        if (cost < 0)
        {
            copyState(state, neighbourState);
            copyState(stateQ, neighbourStateQ);
            generateBoard(board, state, stateQ);
            conflictBoard = conflictNeighbour;
        }
        else
        {
            double prob = exp(-cost / temperature);
            if (rand() / double(RAND_MAX) < prob)
            {
                copyState(state, neighbourState);
                copyState(stateQ, neighbourStateQ);
                generateBoard(board, state, stateQ);
                conflictBoard = conflictNeighbour;
            }
        }

        if (conflictBoard == 0)
        {
            break;
        }
    }

    return calculateConflicts(board, state, stateQ);
}

int localBeamSearch(vector<vector<int>> &board,
                    vector<vector<int>> &state, vector<vector<int>> &stateQ)
{

    // Declaring and initializing the
    // neighbour board and state with
    // the current board and the state
    // as the starting point.

    vector<vector<int>> neighbourBoard(N, vector<int>(M, 0));
    vector<vector<int>> neighbourState(N, vector<int>(M, 0));
    vector<vector<int>> neighbourStateQ(N, vector<int>(M, 0));
    int conflicts = calculateConflicts(board, state, stateQ);
    int k = N;
    vector<vector<vector<int>>> localBoard(k + 1, vector<vector<int>>(N, vector<int>(M, 0)));
    vector<vector<vector<int>>> localneighbourState(k + 1, vector<vector<int>>(N, vector<int>(M, 0)));
    vector<vector<vector<int>>> localneighbourStateQ(k + 1, vector<vector<int>>(N, vector<int>(M, 0)));
    for (int i = 0; i <= k; i++)
    {
        EmptyBoard(neighbourBoard, neighbourState, neighbourStateQ);
        generateRandomly(neighbourBoard, neighbourState, neighbourStateQ);
        int c = calculateConflicts(neighbourBoard, neighbourState, neighbourStateQ);
        copyState(localneighbourState[i], neighbourState);
        copyState(localneighbourStateQ[i], neighbourStateQ);
        generateBoard(localBoard[i], localneighbourState[i], localneighbourStateQ[i]);
        if (c < conflicts)
        {
            copyState(state, neighbourState);
            copyState(stateQ, neighbourStateQ);
            generateBoard(board, state, stateQ);
            conflicts = c;
        }
    }

    int flag = 0, s = 0;

    while (conflicts > 0)
    {
        //work with K generated Random Neighbours
        //at a time.
        for (int i = 0; i <= k; i++)
        {
            //assign states from localneighbourState to neighbourstate
            copyState(neighbourState, localneighbourState[i]);
            copyState(neighbourStateQ, localneighbourStateQ[i]);
            //generate neighbourBoard for the same
            generateBoard(neighbourBoard, localneighbourState[i], localneighbourStateQ[i]);
            //find the next neigbour
            //and return the conflicts
            int c1 = findNeighbour(neighbourBoard, neighbourState, neighbourStateQ);
            //compare with optimal state conflicts
            if (c1 < conflicts)
            {
                //if number of conflicts are less
                //then changing the localneighbour
                //to make it new neighbour
                copyState(localneighbourState[i], neighbourState);
                copyState(localneighbourStateQ[i], neighbourStateQ);
                //Since the number of conflicts are best
                //Assigning the neighbour state to
                //original state
                copyState(state, neighbourState);
                copyState(stateQ, neighbourStateQ);
                generateBoard(board, state, stateQ);
                conflicts = c1;
            }
            //If number of conflicts are reduced to 0
            //then breaking from the loop
            if (conflicts == 0)
                break;
            //If neighbour state and localNeighbourState is same
            //and it is not the first loop
            //Then assigning flag to 0
            //and breaking from the loop
            if ((stateDifference(neighbourState, localneighbourState[i]) || stateDifference(neighbourStateQ, localneighbourStateQ[i])) && s != 0)
            {
                flag = 1;
                break;
            }
        }
        //If flag value is assigned 0
        //then breaking from the loop
        if (flag == 1)
            break;
        //Increase the number of loop counts
        // in order to keep track
        s++;
    }
    //Returning the number of conflicts
    return conflicts;
}

int main(int argc, char *argv[])
{

    string filename, method;
    int t; //tmax
    cout << "KnightsAndQueens ";
    cin >> N;
    cin >> M;
    cin >> Q;
    cin >> K;
    cin >> t;
    cin >> filename;
    cin >> method;
    vector<vector<int>> state(N, vector<int>(M, 0));
    vector<vector<int>> stateQ(N, vector<int>(M, 0));
    vector<vector<int>> board(N, vector<int>(M, 0));
    int conflict = 0;
    //Adding extension of file to filename
    filename += ".txt";
    char a;
    //converting the value of method to lower
    for (int i = 0; i < method.size(); i++)
    {
        a = tolower(method[i]);
        method[i] = a;
    }
    //Generating Random Board
    generateRandomly(board, state, stateQ);
    //Applying the method specified by user
    if (method == "hc")
        conflict = hillClimbing(board, state, stateQ);
    else if (method == "sa")
        conflict = SimulatedAnnealing(board, state, stateQ);
    else if (method == "other")
        conflict = localBeamSearch(board, state, stateQ);
    printBoard(board, conflict, filename);
    return 0;
}
