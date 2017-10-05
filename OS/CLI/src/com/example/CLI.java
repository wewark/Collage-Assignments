package com.example;

import java.io.File;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

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
		if(args.length<1||args.length>2)return;
		if(args.length==1)
		{
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
	
	public static void date(String[] args)
	{
		if(!checkArgs(args,1))return;
		
		DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		Date date = new Date();
		System.out.println(dateFormat.format(date));
	}
	
	public static void help(String[] args)
	{
		if(!checkArgs(args,1))return;
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
				case "date":
					date(arguments);
					break;
				case "help":
					help(arguments);
					break;
				case "exit":
					return ;
			}
		}
	}
}
