import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class priority {
    public static void prioritySimulation()
    {
        int n;
        int End=0;
        System.out.print("Number of processes: ");
        Scanner sc = new Scanner(System.in);
        n=sc.nextInt();
        ArrayList<process> processes=new ArrayList<process>();
        ArrayList<process> Finished=new ArrayList<process>();
        ArrayList<String>order=new ArrayList<String>();
        for(int i=0;i<n;++i)
        {
            System.out.print("Process Name: ");
            String name=sc.next();
            int arr=i;
            System.out.print("Burst Time: ");
            int bur=sc.nextInt();
            System.out.print("Priority: ");
            int pr=sc.nextInt();
            process p=new process(name,arr,bur,bur,0,0,0);
            p.priority=pr;
            End+=bur;
            processes.add(p);
        }

        int last=-1;
        for(int i=0;i<End;) {
            Collections.sort(processes, new Comparator<process>() {
                @Override
                public int compare(process o1, process o2) {
                    if (o1.priority < o2.priority) return -1;
                    else return 1;
                }
            });
            System.out.println("Time: " + i);
            for (int j = 0; j < processes.size(); j++) {
                System.out.println(processes.get(j).name + " " + processes.get(j).remaining + " " + processes.get(j).priority);
            }
            System.out.println("------------------------------------------");
            process p = new process(processes.get(0).name, processes.get(0).arrival, processes.get(0).burst, processes.get(0).remaining, processes.get(0).lastEntered, processes.get(0).waitingTime, processes.get(0).TurnAround);
            p.priority = processes.get(0).priority;
            p.waitingTime = i;
            i += p.burst;
            order.add(p.name);
            processes.remove(0);
            p.TurnAround = i - p.arrival;
            Finished.add(p);
            for (int j =0; j < processes.size(); j++)
            {
                process element = new process(processes.get(j).name, processes.get(j).arrival, processes.get(j).burst, processes.get(j).remaining, processes.get(j).lastEntered, processes.get(j).waitingTime, processes.get(j).TurnAround);
                element.priority = processes.get(j).priority-1;
                processes.set(j,element);
            }

        }
        double avgWaiting=0.0,avgTurnaround=0.0;
        System.out.println("Order of Execution:");
        for(int i=0;i<order.size();i++)
        {
            System.out.print(order.get(i));
            if(i!=order.size()-1)System.out.print("->");
        }
        System.out.println();
        for (int j = 0; j < n; j++) {
            System.out.println("Name: "+Finished.get(j).name + " Waiting Time: " + Finished.get(j).waitingTime + " Turn Around Time: " + Finished.get(j).TurnAround);
            avgWaiting+=Finished.get(j).waitingTime;
            avgTurnaround+=Finished.get(j).TurnAround;
        }
        avgTurnaround/=n;
        avgWaiting/=n;
        System.out.println("Average Waiting Time : "+avgWaiting);
        System.out.println("Average Turn Around Time : "+avgTurnaround);
    }
}
