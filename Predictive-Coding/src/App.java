import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class App {
	private JPanel panelMain;
	private JButton chooseFileButton;
	private JButton compressButton;
	private JButton decompressButton;
	private JPanel containerPanel;

	private JFileChooser fileChooser = new JFileChooser(new File(System.getProperty("user.dir")));
	private String parentDir, fileName;
	private int[][] pixels;

	private App() {
		FileNameExtensionFilter filter = new FileNameExtensionFilter(".jpg", "jpg", "JPG");
		fileChooser.setFileFilter(filter);
		fileChooser.setSelectedFile(new File("E:\\Projects\\Collage-Individual-Assignments\\Predictive-Coding/lena.jpg"));

		chooseFileButton.addActionListener(e -> {
			fileChooser.showOpenDialog(null);
		});

		compressButton.addActionListener(e -> {
			File file = fileChooser.getSelectedFile();
			parentDir = file.toPath().getParent().toString();
			fileName = file.getName();
			pixels = ImageClass.readImage(fileName);

			PredictiveCoding pc = new PredictiveCoding(8);
			PredictiveCoding.HashResult hash = pc.encode(pixels);
			pixels = pc.decode(hash);

			writeFile(parentDir + "/compressed.txt", hash.toString());
		});

		decompressButton.addActionListener(e -> {
			ImageClass.writeImage(pixels, fileName.substring(0, fileName.length() - 4) + "_out.jpg");
		});
	}

	private static void writeFile(String pathStr, String text) {
		List<String> linesList = Collections.singletonList(text);
		Path path = Paths.get(pathStr);
		try {
			Files.write(path, linesList);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private static String[] readFile(String pathStr) {
		ArrayList<String> lines = new ArrayList<String>();
		Path path = Paths.get(pathStr);
		try {
			Files.lines(path).forEach(lines::add);
		} catch (Exception e) {
			e.printStackTrace();
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

//		int[][] pixels = ImageClass.readImage("lenaTest3.jpg");
//
//		VectorQuantization vq = new VectorQuantization(2, 50);
//		VectorQuantization.HashResult hash = vq.encode(pixels);
//		pixels = vq.decode(hash);
//
//		ImageClass.writeImage(pixels, "lenaTest3_out.jpg");


//		VectorQuantization vq = new VectorQuantization(2, 4);
//		int[][] arr = {
//				{1, 2, 7, 9, 4, 11},
//				{3, 4, 6, 6, 12, 12},
//				{4, 9, 15, 14, 9, 9},
//				{10, 10, 20, 18, 8, 8},
//				{4, 3, 17, 16, 1, 4},
//				{4, 5, 18, 18, 5, 6}
//		};
//		VectorQuantization.HashResult hash = vq.encode(arr);
//		System.out.println(hash);
//
//		int[][] result = vq.decode(hash);
//		for (int[] aResult : result) {
//			for (int i : aResult)
//				System.out.print(i + " ");
//			System.out.println();
//		}
	}
}
