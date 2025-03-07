import java.util.Iterator;


public class printDaySo extends Thread  {
    private String name;
    public printDaySo (String name) {
        this.name = name;
    }

    public void run (){
        for (int i = 0; i<=10; i++){
            System.out.println (this.name + i);
        }
    }
    public static void main (String[] args) {
        printDaySo A = new printDaySo("A");
        printDaySo B = new printDaySo("B");
        printDaySo C = new printDaySo("C");
    
        A.start();
        B.start();
        C.start();
    
    }
}

