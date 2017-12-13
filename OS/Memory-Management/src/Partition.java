public class Partition {
	int start, size, sizeAllocated;
	boolean used = false;

	Partition(int start, int size) {
		this.start = start;
		this.size = size;
	}

	public void allocate(int size) {
		this.sizeAllocated = size;
		this.used = true;
	}

	public void deAllocate() {
		this.sizeAllocated = 0;
		this.used = false;
	}

	@Override
	public String toString() {
		return start + "\t" + size + "\t" + sizeAllocated + "\t" + (used ? "used" : "not used");
	}
}
