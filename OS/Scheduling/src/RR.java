import java.util.ArrayList;
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
		ArrayList<QProcess> processes = new ArrayList<>();
		ArrayList<QProcess> Finished = new ArrayList<>();
		ArrayList<String> order = new ArrayList<>();
		for (int i = 0; i < n; ++i) {
			System.out.print("QProcess Name: ");
			String name = sc.next();
			int arr = i;
			System.out.print("Burst Time: ");
			int bur = sc.nextInt();
			QProcess p = new QProcess(name, arr, bur, bur, 0, 0, 0);
			End += bur;
			processes.add(p);
		}

		int last = -1;
		for (int i = 0; i < End; ) {

			System.out.println("Time: " + i);
			for (QProcess process : processes) {
				System.out.println(process.name + " " + process.remaining);
			}
			System.out.println("------------------------------------------");
			QProcess p = new QProcess(processes.get(0).name, processes.get(0).arrival, processes.get(0).burst, processes.get(0).remaining, processes.get(0).lastEntered, processes.get(0).waitingTime, processes.get(0).TurnAround);
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
		for (QProcess finish : Finished) {
			System.out.println("Name: " + finish.name + " Waiting Time: " + finish.waitingTime + " Turn Around Time: " + finish.TurnAround);
			avgWaiting += finish.waitingTime;
			avgTurnaround += finish.TurnAround;
		}
		avgTurnaround /= n;
		avgWaiting /= n;
		System.out.println("Average Waiting Time : " + avgWaiting);
		System.out.println("Average Turn Around Time : " + avgTurnaround);
	}
}
