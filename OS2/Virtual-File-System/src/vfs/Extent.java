package vfs;

import java.io.Serializable;

public class Extent implements Serializable {
	int startLocation;
	int size;
	Extent next = null;

	public Extent(int startLocation) {
		this.startLocation = startLocation;
	}
}
