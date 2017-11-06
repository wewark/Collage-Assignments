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

//	private ArithmaticCoding compressor = new ArithmaticCoding();
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
//		compressButton.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				File file = fileChooser.getSelectedFile();
//				String[] lines = readFile(file.toPath().toString());
//
//				Huffman.HashResult hash = compressor.encode(String.join("\n", lines));
//
//				StringJoiner hashStr = new StringJoiner(",");
//				for (Huffman.Pair row : hash.codeTable) {
//					hashStr.add(row.letter).add(row.code);
//				}
//				hashStr.add(hash.code);
//
//				parentDir = file.toPath().getParent().toString();
//				writeFile(parentDir + "/compressed.txt", hashStr.toString());
//			}
//		});
//		decompressButton.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				String[] lines = readFile(parentDir + "/compressed.txt");
//
//				String[] hashStr = String.join("\n", lines).split(",");
//				Huffman.HashResult hash = new Huffman.HashResult();
//				hash.code = hashStr[hashStr.length - 1];
//				hash.codeTable = new Huffman.Pair[(hashStr.length - 1) / 2];
//				for (int i = 0; i < hashStr.length - 1; i += 2) {
//					hash.codeTable[i / 2] = new Huffman.Pair(hashStr[i], hashStr[i + 1]);
//				}
//
//				writeFile(parentDir + "/decompressed.txt", compressor.decode(hash));
//			}
//		});
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
//		JFrame frame = new JFrame("App");
//		frame.setContentPane(new App().panelMain);
//		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//		frame.pack();
//		frame.setResizable(false);
//		frame.setVisible(true);

		ArrayList<Character> symbols = new ArrayList<>();
		ArrayList<Double> probs = new ArrayList<>();
		symbols.add('A');
		symbols.add('B');
		symbols.add('C');
		probs.add(0.8);
		probs.add(0.02);
		probs.add(0.18);

		ArithmaticCoding ar = new ArithmaticCoding(symbols, probs);
		String rs = ar.encode("ACBA");
		System.out.println(rs);
	}
}
