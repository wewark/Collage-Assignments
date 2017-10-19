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

public class App {
	private JPanel panelMain;
	private JButton chooseFileButton;
	private JButton compressButton;
	private JButton decompressButton;
//
//	private LZW compressor = new LZW(100, 100);
//	private JFileChooser fileChooser = new JFileChooser(new File(System.getProperty("user.dir")));
//	private String parentDir;
//
//	public App() {
//		FileNameExtensionFilter filter = new FileNameExtensionFilter(".txt", "txt", "text");
//		fileChooser.setFileFilter(filter);
//
//		chooseFileButton.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				fileChooser.showOpenDialog(null);
//			}
//		});
//		compressButton.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				File file = fileChooser.getSelectedFile();
//				String[] lines = readFile(file.toPath().toString());
//
//				ArrayList<LZW.Tag> tags = compressor.encode(String.join("\n", lines));
//
//				StringBuilder builder = new StringBuilder();
//				for (LZW.Tag tag : tags) {
//					builder.append(tag.toString());
//				}
//
//				parentDir = file.toPath().getParent().toString();
//				writeFile(parentDir + "/compressed.txt", builder.toString());
//			}
//		});
//		decompressButton.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				String[] lines = readFile(parentDir + "/compressed.txt");
//				ArrayList<LZW.Tag> tags = splitTags(String.join("\n", lines));
//				writeFile(parentDir + "/decompressed.txt", compressor.decode(tags));
//			}
//		});
//	}
//
//	private static void writeFile(String pathStr, String text) {
//		List<String> linesList = Arrays.asList(text);
//		Path path = Paths.get(pathStr);
//		try {
//			Files.write(path, linesList);
//		} catch (Exception e) {
//			System.out.println(e);
//		}
//	}
//
//	private static String[] readFile(String pathStr) {
//		ArrayList<String> lines = new ArrayList<String>();
//		Path path = Paths.get(pathStr);
//		try {
//			Files.lines(path).forEach(lines::add);
//		} catch (Exception e) {
//			System.out.println(e);
//		}
//		return lines.toArray(new String[0]);
//}
//
//	private static ArrayList<LZW.Tag> splitTags(String tagsStr) {
//		String[] tagsStrArr = tagsStr
//				.replace("><"," ")
//				.replace("<", "")
//				.replace(">","")
//				.split(" ");
//
//		ArrayList<LZW.Tag> result = new ArrayList<>();
//		for (String tag : tagsStrArr) {
//			result.add(new LZW.Tag(tag));
//		}
//		return result;
//	}

	public static void main(String[] args) {
//		JFrame frame = new JFrame("App");
//		frame.setContentPane(new App().panelMain);
//		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//		frame.pack();
//		frame.setResizable(false);
//		frame.setVisible(true);

		LZW lzw = new LZW();
		int[] res = lzw.encode("ABAABABBAABAABAAAABABBBBBBBB");
		for (int i : res) {
			System.out.print(i + " ");
		}
	}
}
