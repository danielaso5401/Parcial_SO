package filofos_turno;

public class Filosofo extends Thread {// se relaiza la extension de la libreria thread

	int estomago;//se declara el estomago
	public Filosofo() {
		this.estomago=100;//se asigna a cada hilo un total de 100
	}
	public void run() {
		while(true) {
			
			comer();
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

		System.out.println(this.getName()+" esta comiendo..."+" su estomago esta en "+this.estomago);//se imprime el estomago
		
	}
	public void pensar() {

		System.out.println(this.getName()+" esta pensando...");
		
	}
	public static void main(String[] args)throws InterruptedException {
		int N = 5;

		for(int i =1;i<=N;i++) {
			new Filosofo().start();
		}

	}

}
