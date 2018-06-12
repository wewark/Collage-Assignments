package vfs;

public class MemoryManager {
	private static boolean memory[];

	public static void initialize(int memorySize, Directory root) {
		memory = new boolean[memorySize];
		initialize(root);
	}

	private static void initialize(Directory cur) {
		for (File file : cur.files.values()) {
			reallocate(file);
		}
		for (Directory directory : cur.directories.values()) {
			initialize(directory);
		}
	}

	public static void allocateExtent(File file) {
		int allocated = 0;
		Extent extent = null;
		for (int i = 0; i < memory.length && allocated < file.size; ++i) {
			if (!memory[i]) {
				if (extent == null) {
					file.firstExtent = new Extent(i);
					extent = file.firstExtent;
				}
				else {
					extent.next = new Extent(i);
					extent = extent.next;
				}
				while (!memory[i] && allocated < file.size) {
					memory[i++] = true;
					extent.size++;
					allocated++;
				}
			}
		}
	}

	public static void allocateBestFit(File file) {
		int start = 0, mn = (int) 1e9, mnStart = -1;
		for (int i = 0; i < memory.length; ++i) {
			if (!memory[i] && (i == 0 || memory[i - 1])) {
				start = i;
			}
			if (memory[i] && i > 0 && !memory[i - 1] &&
					i - start >= file.size && i - start < mn) {
				mn = i - start;
				mnStart = start;
			}
		}
		if (!memory[memory.length - 1] &&
				memory.length - start >= file.size &&
				memory.length - start < mn) {
			mnStart = start;
		}

		for (int i = mnStart; i < mnStart + file.size; ++i) {
			memory[i] = true;
		}
		file.blockCount = file.size;
		file.startLocation = mnStart;
	}

	public static void allocateIndexed(File file) {
		file.allocatedBlocks = new int[file.size];
		for (int i = 0, cnt = 0;
		     i < memory.length && cnt < file.size;
		     ++i) {
			if (!memory[i]) {
				file.allocatedBlocks[cnt++] = i;
				memory[i] = true;
			}
		}
	}

	private static void reallocate(File file) {
		if (file.allocationMethod == AllocationMethod.EXTENT) {
			Extent extent = file.firstExtent;
			while (extent != null) {
				for (int i = extent.startLocation; i < extent.startLocation + extent.size; ++i) {
					memory[i] = true;
				}
				extent = extent.next;
			}
		}
		else if (file.allocationMethod == AllocationMethod.BESTFIT) {
			for (int i = file.startLocation; i < file.startLocation + file.size; ++i) {
				memory[i] = true;
			}
		}
		else {
			for (int i : file.allocatedBlocks) {
				memory[i] = true;
			}
		}
	}

	public static void deallocate(File file) {
		if (file.allocationMethod == AllocationMethod.EXTENT) {
			Extent extent = file.firstExtent;
			while (extent != null) {
				for (int i = extent.startLocation; i < extent.startLocation + extent.size; ++i) {
					memory[i] = false;
				}
				extent = extent.next;
			}
		}
		else if (file.allocationMethod == AllocationMethod.BESTFIT) {
			for (int i = file.startLocation; i < file.startLocation + file.size; ++i) {
				memory[i] = false;
			}
		} else {
			for (int i : file.allocatedBlocks) {
				memory[i] = false;
			}
		}
	}

	public static void printDiskStatus() {
		int allocated = 0;
		int start = 0;

		for (int i = 0; i < memory.length; ++i) {
			if (!memory[i] && (i != 0 && memory[i - 1])) {
				System.out.println("+ " + start + " " + (i - 1));
				start = i;
			}
			if (memory[i] && i > 0 && !memory[i - 1]) {
				System.out.println("- " + start + " " + (i - 1));
				start = i;
			}
			if (memory[i]) allocated++;
		}

		if (!memory[memory.length - 1]) {
			System.out.println("- " + start + " " + (memory.length - 1));
		}

		System.out.println("Empty space: " + (memory.length - allocated));
		System.out.println("Allocated space: " + allocated);
	}
}
