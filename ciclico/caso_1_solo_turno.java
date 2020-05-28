package parcial;
import java.util.Random;
import java.util.concurrent.*; 
public class Simulacion01 extends Thread {// se relaiza la extension de la libreria thread
	int plato=10;//se crea un plato con diez fideos global
	int estomago;//se declara el estomago
	Semaphore semaforo;
	int id;
	public Simulacion01(Semaphore sem) {
		this.estomago=100;
		this.semaforo=sem;
		
	}
	public void run() {
		while(plato>0) {//el while termina cuando ya no tegna fideos
		
			
			
			try {
				semaforo.acquire();//se adquiere el permiso
				comer();
				if(this.estomago>=100){
					System.out.println("Filosofo "+this.getName()+" tiene el estomago lleno");
					pensar();
				}
				--plato;//cada que come se disminuye hasta que llegue a 0
				
				
			}
			catch( InterruptedException e) {
				e.printStackTrace();
				System.out.println("se produjo un error");
			}
			pensar();
			semaforo.release();//se libera el permiso

	    }
	}
	public void comer() {
	
			int numero = (int)(1000+Math.random()*2000+1);//estamos haciendo un ramdom del 1000 al 2000
			try {
				this.sleep(numero);
			}
			catch( InterruptedException e) {
				e.printStackTrace();
				System.out.println("se produjo un error");
			}
			this.estomago=this.estomago+25;//cada que come aumenta en 25
			System.out.println(this.getName()+" esta comiendo..."+" su estomago esta en "+this.estomago);
		
		
		
	}
	public void pensar() {
		int numero = (int)(1000+Math.random()*2000+1);//estamos haciendo un ramdom del 1000 al 2000
		long inicio = System.nanoTime();
		try {
			this.sleep(numero);
		}
		catch( InterruptedException e) {
			e.printStackTrace();
			System.out.println("se produjo un error");
		}
		this.estomago=this.estomago-25;//cada que piensa disminuye en 25
		System.out.println(this.getName()+" esta pensando...");
	
		long despues = System.nanoTime();
		
		long tiempo = despues - inicio;
		if(this.estomago<=100 && tiempo>=250000000){
			System.out.println("Filosofo "+this.getName()+" murio de hambre");
		}
		
	}
	public static void main(String[] args)throws InterruptedException {
		int N = 5;
		Semaphore sem = new Semaphore(1);
		for(int i =1;i<=N;i++) {
			new Simulacion01(sem).start();
		}

	}

}