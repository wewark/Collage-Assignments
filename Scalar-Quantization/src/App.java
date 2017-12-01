import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.nio.file.*;
import java.util.*;

public class App {
	private JPanel panelMain;
	private JButton chooseFileButton;
	private JButton compressButton;
	private JButton decompressButton;

//	private ArithmaticCoding compressor;
//	private JFileChooser fileChooser = new JFileChooser(new File(System.getProperty("user.dir")));
//	private String parentDir;
//
//	public App() {
//		FileNameExtensionFilter filter = new FileNameExtensionFilter(".txt", "txt", "text");
//		fileChooser.setFileFilter(filter);
//
//		ArrayList<Character> symbols = new ArrayList<>();
//		ArrayList<Double> probs = new ArrayList<>();
//		symbols.add('A');
//		symbols.add('B');
//		symbols.add('C');
//		probs.add(0.8);
//		probs.add(0.02);
//		probs.add(0.18);
//
//		compressor = new ArithmaticCoding(symbols, probs);
//
//		chooseFileButton.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				fileChooser.showOpenDialog(null);
//			}
//		});
//
//		compressButton.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				File file = fileChooser.getSelectedFile();
//				parentDir = file.toPath().getParent().toString();
//				String[] lines = readFile(file.toPath().toString());
//
//				String hash = compressor.encode(String.join("\n", lines));
//				hash = compressor.txtSize + "\n" + hash;
//
//				writeFile(parentDir + "/compressed.txt", hash);
//			}
//		});
//
//		decompressButton.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				String[] lines = readFile(parentDir + "/compressed.txt");
//				compressor.txtSize = Integer.parseInt(lines[0]);
//				lines = Arrays.copyOfRange(lines, 1, lines.length);
//
//				String decoded = compressor.decode(String.join("\n", lines));
//
//				writeFile(parentDir + "/decompressed.txt", decoded);
//			}
//		});
//	}

	private static void writeFile(String pathStr, String text) {
		List<String> linesList = Collections.singletonList(text);
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
//		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
//		frame.pack();
//		frame.setResizable(false);
//		frame.setVisible(true);

	}
}
