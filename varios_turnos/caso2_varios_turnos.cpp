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

int intrupt[tam];//se crea un plato para cada filosofo
void seleccion(){
    for(int i=0; i<tam; i++){
        estomago[i]=100;//se inicializa 100 los estomagos
        intrupt[i]=20;//tendran 20 fideos por cada filosofo
    }
}

void print(string str){
    mutex cout_mutex;
    cout_mutex.lock();
    cout<<str<<endl;
    cout_mutex.unlock();
}

void think(int id){
    time_t instanteInicial, instanteFinal;
    instanteInicial = time(0);
    int num=1000+rand()%(2000-100);//se genera un tiempo ramdon entre 
    this_thread::sleep_for(chrono::milliseconds(num)); //el filosofo piensa un timepo ramdom
    instanteFinal = time(0);
    int a=instanteFinal-instanteInicial;
    print("filosofo " + to_string(id) + " esta pensando.");
    estomago[id]=estomago[id]-25;//se disminuye en 25 el estomago del filosofo
    if(a>=2 and estomago[id]<=100){
      print("filosofo " + to_string(id) + " murio de hambre");
    }
    
}

bool eat(int id, int izquierda, int derecha) { 

    while(1) if (mtx[izquierda].try_lock()) {
        if(estomago[id]>=125){//controlamos que el filosofo que solo comen mayor igual a 125
            return true; //retornraa true y no realiza el proceso de los palillos
        }   
        print("filosofo " + to_string(id) + " tengo el palillo " + to_string(izquierda));

        if (mtx[derecha].try_lock()) {
            int num=1000+rand()%(2000-100);//se genera un tiempo ramdon 
            this_thread::sleep_for(chrono::milliseconds(num));//se espera una catnidad aleatoria de segundos
            print("filosofo " + to_string(id) + " tengo el palillo " + to_string(derecha) + 
                "\nfilosofo " + to_string(id) + " come.");
            estomago[id]=estomago[id]+25;//aumenta su estomago cada que come
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

    while (intrupt[filosofo]-- > 0) {//segun cada platillo se disminuye
        if (eat(filosofo, lIndex, rIndex)) { 
            mtx[lIndex].unlock(); // baja el tenedor derecho
            mtx[rIndex].unlock(); // baja el tenedor izquierdo
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