package com.example;

import java.io.File;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

public class CLI {
	static String currentDir = System.getProperty("user.dir");

	public static boolean isPath(String path) {
		File file = new File(path);

		if (!file.isAbsolute())
			file = new File(currentDir + "/" + path);

		if (!file.exists()) {
			System.out.println("Directory doesn't exist");
			return false;
		}
		else if (!file.isDirectory()) {
			System.out.println("This is not a directory");
			return false;
		}
		return true;
	}

	public static String removeDots(String path) {
		path = path.replaceAll("([.])", "");
		return path;
	}

	public static boolean checkArgs(String[] args, int desiredSize) {
		if (args.length > desiredSize) {
			System.out.println("Too many arguments!");
			return false;
		}
		if (args.length < desiredSize) {
			System.out.println("Too few arguments!");
			return false;
		}
		return true;
	}

	public static void cd(String[] args) {
		if (!checkArgs(args, 2)) return;

		if (!isPath(args[1])) return;

		Path path = Paths.get(args[1]);
		if (!path.isAbsolute())
			path = Paths.get(currentDir + "/" + args[1]);

		path = path.normalize();
		path = Paths.get(removeDots(path.toString()));
		currentDir = path.toString();
		System.setProperty("user.dir", currentDir);
	}

	public static void ls(String[] args) {
		if (!checkArgs(args, 1)) return;

		File file = new File(currentDir);
		String[] results = file.list();
		for (String result : results)
			System.out.println(result);
	}

	public static void main(String[] args) {
		while (true) {
			System.out.print(currentDir + ": ");
			Scanner scan = new Scanner(System.in);
			String cmd = scan.nextLine();

			String[] arguments = cmd.split(" ");

			switch (arguments[0]) {
				case "cd":
					cd(arguments);
					break;
				case "ls":
					ls(arguments);
					break;
			}
		}
	}
}
