package vfs;

public class Main {
	private static Directory root = new Directory();

	public static void main(String[] args) {
		// TODO
	}

	private static void createFile(String pathStr, int size) {
		String[] path = pathStr.split("/");
		if (!valid(path)) {
			System.out.println("invalid path");
			return;
		}

		Directory cur = getParent(path);
		String filename = path[path.length - 1];
		if (cur.files.containsKey(filename)) {
			System.out.println("file already exists");
			return;
		}

		cur.files.put(filename, new File(pathStr, filename, size));
	}

	private static void createFolder(String pathStr) {
		String[] path = pathStr.split("/");
		if (!valid(path)) {
			System.out.println("invalid path");
			return;
		}

		Directory cur = getParent(path);
		String dirname = path[path.length - 1];
		if (cur.directories.containsKey(dirname)) {
			System.out.println("directory already exists");
			return;
		}

		cur.directories.put(dirname, new Directory(pathStr, dirname));
	}

	private static void deleteFile(String pathStr) {
		String[] path = pathStr.split("/");
		if (!valid(path)) {
			System.out.println("invalid path");
			return;
		}

		Directory cur = getParent(path);
		String filename = path[path.length - 1];
		if (!cur.files.containsKey(filename)) {
			System.out.println("file doesn't exist");
			return;
		}

		cur.files.remove(filename);
	}

	private static void deleteFolder(String pathStr) {
		String[] path = pathStr.split("/");
		if (!valid(path)) {
			System.out.println("invalid path");
			return;
		}

		Directory cur = getParent(path);
		String dirname = path[path.length - 1];
		if (cur.directories.containsKey(dirname)) {
			System.out.println("directory doesn't exist");
			return;
		}

		cur.directories.remove(dirname);
	}

	private static boolean valid(String[] path) {
		if (!path[0].equals("root")) return false;
		Directory cur = root;
		for (int i = 1; i < path.length - 1; ++i) {
			if (!cur.directories.containsKey(path[i]))
				return false;
			cur = cur.directories.get(path[i]);
		}

		return true;
	}

	private static Directory getParent(String[] path) {
		Directory ret = root;
		for (int i = 1; i < path.length - 1; ++i) {
			ret = ret.directories.get(path[i]);
		}
		return ret;
	}
}
