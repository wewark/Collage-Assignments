import java.util.*;

public class AG {

	public static void agSimulation() {
		int n;
		int End = 0;
		Scanner sc = new Scanner(System.in);
		System.out.print("Number of processes: ");
		n = sc.nextInt();
		ArrayList<QProcess> processes = new ArrayList<>();
		ArrayList<QProcess> original = new ArrayList<>();
		Queue<QProcess> usedbefore = new LinkedList<>(); ;

		ArrayList<String> order = new ArrayList<>();
		for (int i = 0; i < n; ++i) {
			System.out.print("QProcess Name: ");
			String name = sc.next();
			System.out.print("Arrival Time: ");
			int arr = sc.nextInt();
			System.out.print("Burst Time: ");
			int bur = sc.nextInt();
			System.out.print("Quantum: ");
			int qnt = sc.nextInt();
			QProcess p = new QProcess(name, arr, bur, bur, 0, 0, 0);
			p.quantum = qnt;
			End += bur;
			End = Math.max(End, arr + bur);
			processes.add(p);
			original.add(p);
		}

		int last = -1;
		for (int i = 0; i < End; ) {
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
			System.out.println("Time : " + i);
			System.out.print("* Quantum ( ");
			for (int j = 0; j < original.size(); j++) {
				System.out.print(original.get(j).quantum);
				if (j != original.size() - 1) System.out.print(", ");
			}
			System.out.print(" ) -> ceil(50%) = ( ");
			for (int j = 0; j < original.size(); j++) {
				int x = original.get(j).quantum;
				x = (int) Math.ceil(x * 1.0 / 2.0);
				System.out.print(x);
				if (j != original.size() - 1) System.out.print(", ");
			}
			System.out.println(" )");
			if (processes.size() != 0 && processes.get(0).arrival <= i) {
				QProcess p = new QProcess(
						processes.get(0).name,
						processes.get(0).arrival,
						processes.get(0).burst,
						processes.get(0).remaining,
						processes.get(0).lastEntered,
						processes.get(0).waitingTime,
						processes.get(0).TurnAround
				);
				p.quantum = processes.get(0).quantum;
				p.waitingTime = i - p.arrival - (p.burst - p.remaining);
				int halfQuantum = (int) Math.ceil(p.quantum * 1.0 / 2.0);
				if (last != p.arrival) {
					order.add(p.name);
					last = p.arrival;
				}
				i += Math.min(p.remaining, halfQuantum);
				p.remaining -= Math.min(p.remaining, halfQuantum);
				if (p.remaining != 0) {

					Boolean isSmaller = false;
					for (QProcess process : processes) {
						if (process.arrival <= i && process.remaining < p.remaining) {
							isSmaller = true;
							break;
						}
					}
					if (isSmaller) {
						processes.remove(0);
						usedbefore.add(p);
						if (p.burst - p.remaining >= p.quantum)
							p.quantum += 1;
						else p.quantum += p.quantum - halfQuantum;

					}
					else {
						processes.remove(0);
						if (p.burst - p.remaining >= p.quantum) {
							p.quantum += 1;
							usedbefore.add(p);
						}
						else {
							processes.add(p);
						}
					}
				}
				else {
					p.quantum = 0;
					p.TurnAround = i - p.arrival;
					processes.remove(0);
				}
				for (int j = 0; j < original.size(); j++) {
					if (original.get(j).name.equals(p.name)) {
						original.set(j, p);
						break;
					}
				}
			}
			else   //take from the queue
			{
				QProcess p = usedbefore.peek();
				p.waitingTime = i - p.arrival - (p.burst - p.remaining);
				int halfQuantum = (int) Math.ceil(p.quantum * 1.0 / 2.0);
				i += Math.min(p.remaining, halfQuantum);
				p.remaining -= Math.min(p.remaining, halfQuantum);
				if (last != p.arrival) {
					order.add(p.name);
					last = p.arrival;
				}
				if (p.remaining != 0) {
					if (p.burst - p.remaining >= p.quantum)
						p.quantum += 1;
					else p.quantum += p.quantum - halfQuantum;
					usedbefore.remove();
					usedbefore.add(p);
				}
				else {
					p.quantum = 0;
					p.TurnAround = i - p.arrival;
					usedbefore.remove();
				}
				for (int j = 0; j < original.size(); j++) {
					if (original.get(j).name.equals(p.name)) {
						original.set(j, p);
						break;
					}
				}


			}
		}
		double avgWaiting = 0.0, avgTurnaround = 0.0;
		System.out.println("Order of Execution:");
		for (int i = 0; i < order.size(); i++) {
			System.out.print(order.get(i));
			if (i != order.size() - 1) System.out.print("->");
		}
		System.out.println();
		for (QProcess org : original) {
			System.out.println("Name: " + org.name + " Waiting Time: " + org.waitingTime + " Turn Around Time: " + org.TurnAround);
			avgWaiting += org.waitingTime;
			avgTurnaround += org.TurnAround;
		}
		avgTurnaround /= n;
		avgWaiting /= n;
		System.out.println("Average Waiting Time : " + avgWaiting);
		System.out.println("Average Turn Around Time : " + avgTurnaround);
	}
}
