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
	private JTextField bitsTextField;
	private JPanel containerPanel;

	private JFileChooser fileChooser = new JFileChooser(new File(System.getProperty("user.dir")));
	private String parentDir;

	private App() {
		FileNameExtensionFilter filter = new FileNameExtensionFilter(".txt", "txt", "text");
		fileChooser.setFileFilter(filter);
		fileChooser.setSelectedFile(new File("E:\\Projects\\Collage-Individual-Assignments\\Scalar-Quantization/test.txt"));

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
				parentDir = file.toPath().getParent().toString();
				String[] lines = readFile(file.toPath().toString());
				lines = lines[0].split(" ");

				ArrayList<Integer> arr = stringArraytoIntegerList(lines);
				int bits = Integer.parseInt(bitsTextField.getText());
				ArrayList<ArrayList<Integer>> result = ScalarQuantization.encode(arr, bits);

				writeFile(parentDir + "/compressed.txt", ScalarQuantization.toString(arr, result));
			}
		});

//		decompressButton.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				String[] lines = readFile(parentDir + "/compressed.txt");
//
//				writeFile(parentDir + "/decompressed.txt", "");
//			}
//		});
	}

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

	private static ArrayList<Integer> stringArraytoIntegerList(String[] strArr) {
		ArrayList<Integer> ret = new ArrayList<>();
		for (String str : strArr)
			ret.add(Integer.parseInt(str));
		return ret;
	}

	public static void main(String[] args) {
		JFrame frame = new JFrame("App");
		frame.setContentPane(new App().panelMain);
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		frame.pack();
		frame.setResizable(false);
		frame.setVisible(true);
		frame.setLocationRelativeTo(null);

//		ArrayList<Integer> arr = new ArrayList<>(Arrays.asList(6, 15, 17, 60, 100, 90, 66, 59, 18, 3, 5, 16, 14,67, 63, 2, 98, 92));
//		ArrayList<ArrayList<Integer>> result = ScalarQuantization.encode(arr, 2);
//
//		int c = 0;
//		for (ArrayList<Integer> curArr : result) {
//			System.out.print(c++ + " " + ScalarQuantization.average(curArr) + ":");
//			for (Integer i : curArr)
//				System.out.print(" " + i);
//			System.out.println();
//		}
//
//		for (Integer anArr : arr) {
//			boolean found = false;
//			for (int j = 0; j < result.size() && !found; ++j)
//				for (int k = 0; k < result.get(j).size(); ++k)
//					if (result.get(j).get(k).equals(anArr)) {
//						System.out.print(j + " ");
//						found = true;
//						break;
//					}
//		}
	}
}
