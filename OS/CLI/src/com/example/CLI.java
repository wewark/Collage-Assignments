package com.example;

import java.io.File;
import java.nio.file.*;
import java.util.Scanner;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

public class CLI {
	static String currentDir = System.getProperty("user.dir");

	// Returns the absolute path (e.g "C:\myparent\myfile.txt")
	// instead of the relative path (e.g "myfile.txt" when the current directory is "C:\myparent")
	public static String makeAbsolute(String path) {
		File file = new File(path);
		if (!file.isAbsolute())
			return currentDir + "/" + path;
		return path;
	}

	public static boolean isPath(String path) {
		File file = new File(path);

		if (!file.isAbsolute())
			file = new File(currentDir + "/" + path);

		if (!file.exists()) {
			System.out.println("Directory doesn't exist");
			return false;
		} else if (!file.isDirectory()) {
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

	public static void clear(String[] args) {
		// :'D
		for (int i = 0; i < 20; i++) {
			System.out.println("\n");
		}
	}

	public static void cd(String[] args) {
		if (args.length < 1 || args.length > 2) return;
		if (args.length == 1) {
			Path path = Paths.get("C:\\");
			path = path.normalize();
			path = Paths.get(removeDots(path.toString()));
			currentDir = path.toString();
			System.setProperty("user.dir", currentDir);
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

	public static void ls(String[] args) {
		if (!checkArgs(args, 1)) return;

		File file = new File(currentDir);
		String[] results = file.list();
		for (String result : results)
			System.out.println(result);
	}

	public static void cp(String[] args) {
		args[1] = makeAbsolute(args[1]);
		args[2] = makeAbsolute(args[2]);
		Path oldPath = Paths.get(args[1]);
		Path newPath = Paths.get(args[2]);
		try {
			Files.copy(oldPath, newPath, StandardCopyOption.REPLACE_EXISTING);
		} catch (Exception e) {
			System.out.println(e);
		}
	}

	public static void date(String[] args) {
		if (!checkArgs(args, 1)) return;

		DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		Date date = new Date();
		System.out.println(dateFormat.format(date));
	}

	public static void mv(String[] args) {
		cp(args);
		rm(new String[]{args[0], args[1]});
	}

	public static void rm(String args[]) {
		if (!checkArgs(args, 2)) return;
		File file = new File(currentDir + "/" + args[1]);
		if (file.delete()) return;
		else System.out.println("File not found");
	}

	public static void mkdir(String args[]) {
		if (!checkArgs(args, 2)) return;
		File file = new File(currentDir + "/" + args[1]);
		file.mkdir();

	}

	public static void rmdir(String args[]) {
		if (!checkArgs(args, 2)) return;
		if (!isPath(args[1])) return;
		File file = new File(currentDir + "/" + args[1]);
		file.delete();
	}

	public static void cat(String[] args) {
		for (int i = 1; i < args.length; i++) {
			Path path = Paths.get(args[i]);
			try {
				Files.lines(path).forEach(s -> System.out.println(s));
			} catch (Exception e) {
				System.out.println(e);
			}
		}
	}

	public static void more(String[] args) {
		// TODO
	}

	public static void pwd(String[] args) {
		System.out.println(currentDir);
	}

	public static void help(String[] args) {
		if (!checkArgs(args, 1)) return;
		System.out.println("args:");
		System.out.println("clear");
		System.out.println("cd");
		System.out.println("ls");
		System.out.println("cp");
		System.out.println("mv");
		System.out.println("rm");
		System.out.println("mkdir");
		System.out.println("rmdir");
		System.out.println("cat");
		System.out.println("more");
		System.out.println("pwd");
		System.out.println();
		System.out.println("date");
		System.out.println("exit");
	}

	// When '?' is written before a command
	public static void helpCmd(String[] args) {
		// TODO
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		while (true) {
			System.out.print(currentDir + ": ");
			String cmd = scan.nextLine();

			String[] arguments = cmd.split(" ");

			switch (arguments[0]) {
				case "clear":
					clear(arguments);
					break;
				case "cd":
					cd(arguments);
					break;
				case "ls":
					ls(arguments);
					break;
				case "cp":
					cp(arguments);
					break;
				case "mv":
					mv(arguments);
					break;
				case "rm":
					rm(arguments);
					break;
				case "mkdir":
					mkdir(arguments);
					break;
				case "rmdir":
					rmdir(arguments);
					break;
				case "cat":
					cat(arguments);
					break;
				case "date":
					date(arguments);
					break;
				case "help":
					help(arguments);
					break;
				case "pwd":
					pwd(arguments);
					break;
				case "exit":
					return;
				default:
					System.out.println("'" + arguments[0] + "' is not recognized as an internal or external command,\n" +
							"operable program or batch file.");
			}
		}
	}
}
