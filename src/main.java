
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;



public class main {
    static int currentTime = 0;

    public static void main(String[] args) {
        int n;
        int End=0;

        Scanner sc = new Scanner(System.in);
        n=sc.nextInt();
        ArrayList<process>processes=new ArrayList<process>();
        for(int i=0;i<n;++i)
        {
            System.out.print("Process Name: ");
            String name=sc.next();
            System.out.print("Arrival Time: " );
            int arr=sc.nextInt();
            System.out.print("Burst Time: ");
            int bur=sc.nextInt();
            process p=new process(name,arr,bur,bur,0,0,0);
            End+=bur;
            processes.add(p);
        }

        int last=-1;
        for(int i=0;i<End;i++) {
            Collections.sort(processes, new Comparator<process>() {
                @Override
                public int compare(process o1, process o2) {


                    if(o1.arrival<=currentTime&&o2.arrival<=currentTime)
                    {
                        if(o1.remaining!=0&&o2.remaining!=0&&o1.remaining<o2.remaining)return -1;
                        else if (o1.remaining!=0&&o2.remaining!=0&&o1.remaining>o2.remaining) return 1;
                        else if(o1.remaining>o2.remaining)return -1;
                        else return 1;
                    }
                    else
                    {
                        if(o1.arrival<o2.arrival)return -1;
                        else return 1;
                    }


                }
            });
            System.out.println("Time: "+i);
            for (int j = 0; j < n; j++) {
                System.out.println(processes.get(j).name + " " + processes.get(j).arrival + " " + processes.get(j).remaining);
            }
            System.out.println("------------------------------------------");
            process p=new process(processes.get(0).name,processes.get(0).arrival,processes.get(0).burst,processes.get(0).remaining,processes.get(0).lastEntered,processes.get(0).waitingTime,processes.get(0).TurnAround);
            p.remaining=p.remaining-1;
            if(last!=p.arrival)
            {
                p.lastEntered=i;
                last=p.arrival;
                p.waitingTime=i-p.arrival-(p.burst-(p.remaining+1));
            }
            if(p.remaining==0)
            {
                p.TurnAround=i+1-p.arrival;
            }
            processes.remove(0);
            processes.add(p);
            currentTime++;
        }
        double avgWaiting=0.0,avgTurnaround=0.0;
        for (int j = 0; j < n; j++) {
            System.out.println("Name: "+processes.get(j).name + " Waiting Time: " + processes.get(j).waitingTime + " Turn Around Time: " + processes.get(j).TurnAround);
            avgWaiting+=processes.get(j).waitingTime;
            avgTurnaround+=processes.get(j).TurnAround;
        }
        avgTurnaround/=n;
        avgWaiting/=n;
        System.out.println("Average Waiting Time : "+avgWaiting);
        System.out.println("Average Turn Around Time : "+avgTurnaround);


    }
}
