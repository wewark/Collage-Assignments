package com.lzw;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.StringJoiner;

public class App {
	private JPanel panelMain;
	private JButton chooseFileButton;
	private JButton compressButton;
	private JButton decompressButton;

	private LZW compressor = new LZW();
	private JFileChooser fileChooser = new JFileChooser(new File(System.getProperty("user.dir")));
	private String parentDir;

	public App() {
		FileNameExtensionFilter filter = new FileNameExtensionFilter(".txt", "txt", "text");
		fileChooser.setFileFilter(filter);

		chooseFileButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				fileChooser.showOpenDialog(null);
			}
		});
		compressButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				File file = fileChooser.getSelectedFile();
				String[] lines = readFile(file.toPath().toString());

				int[] hash = compressor.encode(String.join("\n", lines));

				StringJoiner hashStr = new StringJoiner(",");
				for (int i : hash) {
					hashStr.add(Integer.toString(i));
				}

				parentDir = file.toPath().getParent().toString();
				writeFile(parentDir + "/compressed.txt", hashStr.toString());
			}
		});
		decompressButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				String[] lines = readFile(parentDir + "/compressed.txt");

				String[] hashStr = String.join("\n", lines).split(",");
				int[] hash = new int[hashStr.length];
				for (int i = 0; i < hashStr.length; ++i) {
					hash[i] = Integer.parseInt(hashStr[i]);
				}

				writeFile(parentDir + "/decompressed.txt", compressor.decode(hash));
			}
		});
	}

	private static void writeFile(String pathStr, String text) {
		List<String> linesList = Arrays.asList(text);
		Path path = Paths.get(pathStr);
		try {
			Files.write(path, linesList);
		} catch (Exception e) {
			System.out.println(e);
		}
	}

	private static String[] readFile(String pathStr) {
		ArrayList<String> lines = new ArrayList<String>();
		Path path = Paths.get(pathStr);
		try {
			Files.lines(path).forEach(lines::add);
		} catch (Exception e) {
			System.out.println(e);
		}
		return lines.toArray(new String[0]);
}

	public static void main(String[] args) {
		JFrame frame = new JFrame("App");
		frame.setContentPane(new App().panelMain);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();
		frame.setResizable(false);
		frame.setVisible(true);

//		LZW lzw = new LZW();
//		int[] res = lzw.encode("ABAABABBAABAABAAAABABBBBBBBB");
//		for (int i : res) {
//			System.out.print(i + " ");
//		}
//		System.out.println();
//		System.out.println(lzw.decode(res));
	}
}
