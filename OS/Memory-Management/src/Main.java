import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	private static ArrayList<Partition> memory = new ArrayList<>();

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int initialSize = sc.nextInt();

		memory.add(new Partition(0, initialSize));

		while (true) {
			int x = sc.nextInt();
			switch (x) {
				case 1:
					int size = sc.nextInt();
					int type = sc.nextInt();
					if (type == 1)
						System.out.println(bestFit(size));
					else if (type == 2)
						System.out.println(worstFit(size));
					else
						System.out.println(firstFit(size));
					break;
				case 2:
					int startAddress = sc.nextInt();
					if (deallocate(startAddress))
						System.out.println("De-allocated successfully");
					else
						System.out.println("De-allocation unsuccessful");
					break;
				case 3:
					type = sc.nextInt();
					defragment(type);
					break;
			}
			print();
		}
	}

	private static int firstFit(int size) {
		for (Partition cur : memory)
			if (!cur.used && cur.size >= size) {
				cur.allocate(size);
				return cur.start;
			}
		return -1;
	}

	private static int worstFit(int size) {
		Partition worst = new Partition(-1, -1);
		for (Partition cur : memory)
			if (!cur.used && cur.size >= size &&
					(worst.start == -1 || cur.size > worst.size))
				worst = cur;
		worst.allocate(size);
		return worst.start;
	}

	private static int bestFit(int size) {
		Partition best = new Partition(-1, -1);
		for (Partition cur : memory)
			if (!cur.used && cur.size >= size &&
					(best.start == -1 || cur.size < best.size))
				best = cur;
		best.allocate(size);
		return best.start;
	}

	private static void defragment(int type) {
		if (type == 1) {
			for (int i = 0; i < memory.size(); ++i) {
				Partition cur = memory.get(i);
				if (cur.used && cur.size > cur.sizeAllocated) {
					int free = cur.size - cur.sizeAllocated;
					cur.size = cur.sizeAllocated;
					memory.add(++i, new Partition(cur.start + cur.size, free));
				}
			}
		}
		else if (type == 2) {
			for (int i = 0; i < memory.size() - 1; ++i) {
				Partition cur = memory.get(i);
				Partition next = memory.get(i + 1);
				if (!cur.used && !next.used) {
					cur.size += next.size;
					memory.remove(i-- + 1);
				}
			}
		}
		else {
			int unused = 0;
			for (int i = 0; i < memory.size(); ++i) {
				if (!memory.get(i).used) {
					unused += memory.get(i).size;
					memory.remove(i--);
				}
				else memory.get(i).start -= unused;
			}

			if (unused > 0) {
				int start = 0;
				if (!memory.isEmpty()) {
					Partition last = memory.get(memory.size() - 1);
					start = last.start + last.size;
				}
				memory.add(new Partition(start, unused));
			}
		}
	}

	private static boolean deallocate(int startAddress) {
		for (Partition cur : memory)
			if (cur.start == startAddress && cur.used) {
				cur.deAllocate();
				return true;
			}
		return false;
	}

	private static void print() {
		System.out.println("Start\tSize\tSize Allocated\tUsed");
		for (Partition cur : memory)
			System.out.println(cur);
	}
}
