import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class RR {
	public static void rrSimulation() {
		int n;
		int End = 0;
		int Qunt;
		System.out.print("Number of processes: ");
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		System.out.print("Quantum: ");
		Qunt = sc.nextInt();
		ArrayList<process> processes = new ArrayList<process>();
		ArrayList<process> Finished = new ArrayList<process>();
		ArrayList<String> order = new ArrayList<String>();
		for (int i = 0; i < n; ++i) {
			System.out.print("Process Name: ");
			String name = sc.next();
			int arr = i;
			System.out.print("Burst Time: ");
			int bur = sc.nextInt();
			process p = new process(name, arr, bur, bur, 0, 0, 0);
			End += bur;
			processes.add(p);
		}

		int last = -1;
		for (int i = 0; i < End; ) {

			System.out.println("Time: " + i);
			for (int j = 0; j < processes.size(); j++) {
				System.out.println(processes.get(j).name + " " + processes.get(j).remaining);
			}
			System.out.println("------------------------------------------");
			process p = new process(processes.get(0).name, processes.get(0).arrival, processes.get(0).burst, processes.get(0).remaining, processes.get(0).lastEntered, processes.get(0).waitingTime, processes.get(0).TurnAround);
			p.waitingTime = i - (p.burst - (p.remaining));
			i += Math.min(Qunt, p.remaining);
			p.remaining = Math.max(0, p.remaining - Qunt);
			if (last != p.arrival) {
				order.add(p.name);
				p.lastEntered = i;
				last = p.arrival;
			}
			processes.remove(0);
			if (p.remaining == 0) {
				p.TurnAround = i;
				Finished.add(p);
			}
			else {
				processes.add(p);
			}
		}
		double avgWaiting = 0.0, avgTurnaround = 0.0;
		System.out.println("Order of Execution:");
		for (int i = 0; i < order.size(); i++) {
			System.out.print(order.get(i));
			if (i != order.size() - 1) System.out.print("->");
		}
		System.out.println();
		for (int j = 0; j < n; j++) {
			System.out.println("Name: " + Finished.get(j).name + " Waiting Time: " + Finished.get(j).waitingTime + " Turn Around Time: " + Finished.get(j).TurnAround);
			avgWaiting += Finished.get(j).waitingTime;
			avgTurnaround += Finished.get(j).TurnAround;
		}
		avgTurnaround /= n;
		avgWaiting /= n;
		System.out.println("Average Waiting Time : " + avgWaiting);
		System.out.println("Average Turn Around Time : " + avgTurnaround);
	}
}
