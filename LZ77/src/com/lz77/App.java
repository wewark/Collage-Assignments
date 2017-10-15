package com.lz77;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class App {
	private JPanel panelMain;
	private JButton chooseFileButton;
	private JButton compressButton;
	private JButton decompressButton;

	private JFileChooser fileChooser = new JFileChooser(new File(System.getProperty("user.dir")));

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
				ArrayList<String> lines = new ArrayList<String>();
				try {
					Files.lines(file.toPath()).forEach(lines::add);
				} catch (Exception ex) {
					System.out.println(ex);
				}

				LZ77 compressor = new LZ77(10, 10);
				ArrayList<LZ77.Tag> tags = compressor.encode(String.join("", lines));

				StringBuilder builder = new StringBuilder();
				for (LZ77.Tag tag : tags) {
					builder.append(tag.toString());
				}

				Path path = Paths.get(file.toPath().getParent().toString() + "/compressed.txt");
				List<String> linesList = new ArrayList<String>();
				linesList.add(builder.toString());
				try {
					Files.write(path, linesList, Charset.defaultCharset());
				} catch (Exception ex) {
					System.out.println(ex);
				}
			}
		});
	}

	public static void main(String[] args) {
		JFrame frame = new JFrame("App");
		frame.setContentPane(new App().panelMain);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();
		frame.setResizable(false);
		frame.setVisible(true);
//		LZ77 lz = new LZ77(5, 5);
//		String s = "cabracadabrarrarrad";
//		ArrayList<LZ77.Tag> tags = lz.encode(s);
//		for (LZ77.Tag tag : tags) {
//			System.out.println(tag.toString());
//		}
//		System.out.println(LZ77.decode(tags));
//		if (LZ77.decode(tags).equals(s))
//			System.out.println("Equal!!");
	}
}
