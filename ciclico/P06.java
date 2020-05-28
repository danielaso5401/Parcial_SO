package filofos_turno;
import java.util.Random;
public class Filosofo extends Thread {// se relaiza la extension de la libreria thread

	int estomago;//se declara el estomago
	public Filosofo() {
		this.estomago=100;
	}
	public void run() {
		while(true) {
			
			comer();
			if(this.estomago>=100){//verifica que su estomago no pase de 100
				System.out.println("Filosofo "+this.getName()+" tiene el estomago lleno");
				pensar();//lo manda a pensar para que baje de peso
			}
			try {
				this.sleep(1000);
			}
			catch( InterruptedException e) {
				e.printStackTrace();
				System.out.println("se produjo un error");
			}
			pensar();
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
		try {
			this.sleep(numero);
		}
		catch( InterruptedException e) {
			e.printStackTrace();
			System.out.println("se produjo un error");
		}
		this.estomago=this.estomago-25;//cada que piensa disminuye en 25
		System.out.println(this.getName()+" esta pensando...");
		
	}
	public static void main(String[] args)throws InterruptedException {
		int N = 5;

		for(int i =1;i<=N;i++) {
			new Filosofo().start();
		}

	}

}
