#include <iostream>
#include <mutex>
#include <thread>
#include <ctime>
#include <chrono>
using namespace std;
const int tam=5;//se define la cantidad de filosofos
thread philosphers[tam];// se generan los threads
mutex mtx[tam];
int estomago[tam];//se crea un array de estomagos dela misma cantidad de filosofos
int intrupt=20;
void seleccion(){
    for(int i=0; i<tam; i++){
        estomago[i]=100;//se inicializa 100 los estomagos
    }
}

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
            estomago[filosofo]--; 
            this_thread::sleep_for(std::chrono::milliseconds(600));
        }    
    }

}

int main() { 
    seleccion();// se llama a la funcion para llenar los estomagos
    for (int i = 0; i < 5; ++i) philosphers[i] = std::thread(dinner_started, i);
    for (int i = 0; i <5; ++i) philosphers[i].join();
    
    for (int i = 0; i < 5; ++i){
     cout << i <<" = "<<estomago[i]<<endl;
    }   
}