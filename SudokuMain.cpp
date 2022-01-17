#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int const Dim = 9;
int const boxDim = 3;

void printPuzzle(vector<vector<int> >puzzle){
    for(int i=0; i<Dim; i++){
        for(int j=0; j<Dim; j++){
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
}

bool checkRow(vector<vector<int> > puzzle){
    for(int i=0; i<Dim; i++){
        int arr[Dim];
        for(int j=0; j<Dim; j++)
            arr[j] = puzzle[i][j];

        sort(arr, arr+Dim);
        for(int j=1; j<Dim; j++){
            if(arr[j] == 0) continue;
            if(arr[j] == arr[j-1]) return false;
        }
    }
    return true;
}

bool checkCol(vector<vector<int> > puzzle){
    for(int i=0; i<Dim; i++){
        int arr[Dim];
        for(int j=0; j<Dim; j++)
            arr[j] = puzzle[j][i];

        sort(arr, arr+Dim);
        for(int j=1; j<Dim; j++){
            if(arr[j] == 0) continue;
            if(arr[j] == arr[j-1]) return false;
        }
    }
    return true;
}

bool checkBox(vector<vector<int> > puzzle){
    for(int i=0; i<Dim; i++){
        int arr[Dim];
        for(int j=0; j<Dim; j++)
            arr[j] = puzzle[((i/boxDim)*boxDim)+(j/boxDim)][((i%boxDim)*boxDim)+(j%boxDim)];

        sort(arr, arr+Dim);
        for(int j=1; j<Dim; j++){
            if(arr[j] == 0) continue;
            if(arr[j] == arr[j-1]) return false;
        }
    }
    return true;
}

bool checkPuzzle(vector<vector<int> > puzzle){
    if(checkRow(puzzle) && checkCol(puzzle) && checkBox(puzzle))
        return true;
    else
        return false;
}

int findSpace(vector<vector<int> > puzzle){
    for(int i=0; i<(Dim*Dim); i++){
        if(puzzle[i/Dim][i%Dim] == 0)
            return i;
    }
    return -1;
}

void addPuzzle(vector<vector<int> > &puzzle, int index, int temp){
    puzzle[index/Dim].at(index%Dim) = temp;
}

bool canAddPuzzle(vector<vector<int> > puzzle, int nextSpace, int temp){
    addPuzzle(puzzle, nextSpace, temp);
    if(checkPuzzle(puzzle))
        return true;
    else
        return false;
}

bool solvePuzzle(vector<vector<int> > &puzzle){
    int nextSpace = findSpace(puzzle);
    if(nextSpace == -1)
        return true;
    for(int i=1; i<Dim; i++){
        if(canAddPuzzle(puzzle, nextSpace, i)){
            addPuzzle(puzzle, nextSpace, i);
            if(solvePuzzle(puzzle))
                return true;
            else 
                addPuzzle(puzzle, nextSpace, 0);
        }
    }
    return false;
}

int main()
{
    vector<vector<int> > puzzle(Dim);

    for(int i=0; i<Dim; i++){
        for(int j=0; j<Dim; j++){
            int input;
            cin >> input;
            
            if(input >=0 && input <=Dim)
                puzzle[i].push_back(input);
            else{
                cout << "Input is invalid." << endl;
                return -1;
            }
        }
    }
    
    cout << endl;
    if(solvePuzzle(puzzle))
        printPuzzle(puzzle);
    else
        cout << "This puzzle cannot be solved." << endl;
}