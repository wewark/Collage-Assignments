package com.example;

import com.sun.org.apache.xpath.internal.res.XPATHErrorResources_ja;

import java.io.File;
import java.nio.file.Files;
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

	public static void cd(String[] args) {
		if (args.length != 2) {
			System.out.println("Too many arguments!");
			return;
		}
		if (!isPath(args[1])) return;

		Path path = Paths.get(args[1]);
		if (!path.isAbsolute())
			path = Paths.get(currentDir + "/" + args[1]);

		path = path.normalize();
		path = Paths.get(removeDots(path.toString()));
		currentDir = path.toString();
		System.setProperty("user.dir", currentDir);
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
			}
		}
	}
}
