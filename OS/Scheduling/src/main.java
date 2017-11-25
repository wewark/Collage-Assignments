import java.util.Scanner;

public class main {


    public static void main(String[] args) {

        while(true)
        {
            System.out.println("1: preemptive Shortest- Job First (SJF) Scheduling");
            System.out.println("2: Round Robin (RR)");
            System.out.println("3: Priority Scheduling");
            System.out.println("4: AG Scheduling");
            System.out.println("5: Exit");
            System.out.print("Input: ");
            Scanner sc = new Scanner(System.in);
            int input=sc.nextInt();
            switch (input) {
                case 1: sjf s=new sjf();
                     s.sjfSimulation();;
                    break;
                case 2:  RR r=new RR();
                      r.rrSimulation();;
                    break;
                case 3:  priority p=new priority();
                    p.prioritySimulation();
                    break;
                case 4:  ;
                    break;
                case 5: return ;
                default: System.out.println("Invalid Input");
                    break;
            }
            for(int i=0;i<13;i++)System.out.println();
        }


    }
}
