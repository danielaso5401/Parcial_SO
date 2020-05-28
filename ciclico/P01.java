package filofos_turno;

public class Filosofo extends Thread {// se relaiza la extension de la libreria thread


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

		System.out.println(this.getName()+" esta comiendo...");
		
	}
	public void pensar() {

		System.out.println(this.getName()+" esta pensando...");
		
	}
	public static void main(String[] args)throws InterruptedException {
		Filosofo  N=new Filosofo();
		N.start();
	}

}
