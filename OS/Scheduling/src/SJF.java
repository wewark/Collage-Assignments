import java.util.ArrayList;
import java.util.Scanner;

public class SJF {

	public static void sjfSimulation() {
		int n;
		int End = 0;
		Scanner sc = new Scanner(System.in);
		System.out.print("Number of processes: ");
		n = sc.nextInt();
		ArrayList<QProcess> processes = new ArrayList<>();
		ArrayList<String> order = new ArrayList<>();
		for (int i = 0; i < n; ++i) {
			System.out.print("QProcess Name: ");
			String name = sc.next();
			System.out.print("Arrival Time: ");
			int arr = sc.nextInt();
			System.out.print("Burst Time: ");
			int bur = sc.nextInt();
			QProcess p = new QProcess(name, arr, bur, bur, 0, 0, 0);
			End += bur;
			End = Math.max(End, arr + bur);
			processes.add(p);
		}

		int last = -1;
		for (int i = 0; i < End; i++) {
			int finalI = i;
			processes.sort((o1, o2) -> {
				if (o1.arrival <= finalI && o2.arrival <= finalI) {
					if (o1.remaining != 0 && o2.remaining != 0 && o1.remaining < o2.remaining) return -1;
					else if (o1.remaining != 0 && o2.remaining != 0 && o1.remaining > o2.remaining) return 1;
					else if (o1.remaining > o2.remaining) return -1;
					else return 1;
				}
				else {
					if (o1.arrival < o2.arrival) return -1;
					else return 1;
				}


			});
			System.out.println("Time: " + i);
			for (QProcess process : processes) {
				System.out.println(process.name + " " + process.arrival + " " + process.remaining);
			}
			System.out.println("------------------------------------------");
			QProcess p = new QProcess(
					processes.get(0).name,
					processes.get(0).arrival,
					processes.get(0).burst,
					processes.get(0).remaining,
					processes.get(0).lastEntered,
					processes.get(0).waitingTime,
					processes.get(0).TurnAround
			);
			if (p.arrival <= i) {
				p.remaining = p.remaining - 1;
				if (last != p.arrival) {
					order.add(p.name);
					p.lastEntered = i;
					last = p.arrival;
					p.waitingTime = i - p.arrival - (p.burst - (p.remaining + 1));
				}
				if (p.remaining == 0) {
					p.TurnAround = i + 1 - p.arrival;
				}
				processes.remove(0);
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
		for (QProcess process : processes) {
			System.out.println("Name: " + process.name + " Waiting Time: " + process.waitingTime + " Turn Around Time: " + process.TurnAround);
			avgWaiting += process.waitingTime;
			avgTurnaround += process.TurnAround;
		}
		avgTurnaround /= n;
		avgWaiting /= n;
		System.out.println("Average Waiting Time : " + avgWaiting);
		System.out.println("Average Turn Around Time : " + avgTurnaround);
	}
}
