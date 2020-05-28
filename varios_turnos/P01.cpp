#include <iostream>
#include <mutex>
#include <thread>
#include <ctime>
#include <chrono>
using namespace std;

thread philosphers[5];//se crean los threads
mutex mtx[5];
int comio[5] = {0};
int intrupt = 20; 

void print(string str){
    mutex cout_mutex;
    cout_mutex.lock();
    cout<<str<<endl;
    cout_mutex.unlock();
}

void think(int id){
    this_thread::sleep_for(chrono::milliseconds(600)); 
    print("filosofo " + to_string(id) + " esta pensando.");
}

bool eat(int id, int izquierda, int derecha) { 

    while(1) if (mtx[izquierda].try_lock()) {   
        print("filosofo " + to_string(id) + " tengo el palillo " + to_string(izquierda));

        if (mtx[derecha].try_lock()) {
            print("filosofo " + to_string(id) + " tengo el palillo " + to_string(derecha) + 
                "\nfilosofo " + to_string(id) + " come.");
            return true;
        } else {
            mtx[izquierda].unlock();
            think(id);
        }

    }
    return false;
}



void dinner_started(int filosofo) {

    int lIndex = min(filosofo, (filosofo + 1) % (5));
    int rIndex = max(filosofo, (filosofo + 1) % (5));

    while (intrupt-- > 0) {
        if (eat(filosofo, lIndex, rIndex)) { 
            mtx[lIndex].unlock(); // baja el tenedor derecho
            mtx[rIndex].unlock(); // baja el tenedor izquierdo
            comio[filosofo]++; 
            this_thread::sleep_for(std::chrono::milliseconds(600));
        }    
    }

}

int main() { 
    for (int i = 0; i < 5; ++i) philosphers[i] = std::thread(dinner_started, i);
    for (int i = 0; i <5; ++i) philosphers[i].join();
    
    for (int i = 0; i < 5; ++i){
     cout << i <<" = "<<comio[i]<<endl;
    }   
}