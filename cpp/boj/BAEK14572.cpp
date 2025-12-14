#include<iostream>
#include<algorithm>

using namespace std;

const int MAX_K = 30 + 5, MAX_N = 100'000 + 5;

enum {
    DELETE = -1,
    INSERT = 1,
};

struct Student{
    int alg, ability;
};

int alg_count[MAX_K];
int N, K, D, M, d, A;
Student students[MAX_N];


void groupOperation(int index, int operation){
    for(int i = 0; i < K; i++){
        if((1 << i) & students[index].alg){
            alg_count[i] += operation;
        }
    }
}

void insertStudent(int index){
    groupOperation(index, INSERT);
}
void deleteStudent(int index){
    groupOperation(index, DELETE);
}

int main(){
    //FAST I/O
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    //input
    cin >> N >> K >> D;
    for(int i = 0; i < N; i++){
        cin >> M >> d;
        students[i].ability = d;
        for(int j = 0; j < M; j++){
            cin >> A;
            students[i].alg |= 1 << (A - 1);
        }
    }

    sort(students, students + N, [](const Student& lv, const Student& rv){
        return lv.ability < rv.ability;
    });

    int lo = 0, hi = 0, E = 0;
    //two pointers
    while (hi < N) {
        if(students[hi].ability - students[lo].ability > D){
            deleteStudent(lo);
            lo += 1;
        }
        else{
            insertStudent(hi);
            int efficiency = 0;
            for(int i = 0; i < K; i++){
                if(0 < alg_count[i] && alg_count[i] < (hi - lo + 1)){
                    efficiency += 1;
                }
            }
            E = max(E, efficiency * (hi - lo + 1));
            hi += 1;
        }
    }
    cout << E;
}
