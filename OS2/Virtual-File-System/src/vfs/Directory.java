package vfs;

import java.util.HashMap;

class Directory {
	private String path;
	private String name;
	HashMap<String, File> files;
	HashMap<String, Directory> directories;

	Directory(String path, String name) {
		this.path = path;
		this.name = name;
	}

	Directory() {

	}
}
