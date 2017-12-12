public class Partition {
	int start, size;
	private int sizeAllocated;
	boolean used = false;

	Partition(int start, int size, int sizeAllocated) {
		this.start = start;
		this.size = size;
		this.sizeAllocated = sizeAllocated;
	}

	public boolean allocate(int size) {
		if (!used) {
			this.sizeAllocated = size;
			this.used = true;
			return true;
		}
		return false;
	}

	public int sizeFree() {
		return size - sizeAllocated;
	}

	@Override
	public String toString() {
		return start + "\t" + size + "\t" + sizeAllocated + "\t" + (used ? "used" : "not used");
	}
}
