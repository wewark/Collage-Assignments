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

			PredictiveCoding pc = new PredictiveCoding(6);
			PredictiveCoding.HashResult hash = pc.encode(pixels);
			pixels = pc.decode(hash);

			writeFile(parentDir + "/compressed.txt", hash.toString());
		});

		decompressButton.addActionListener(e -> {
			ImageClass.writeImage(pixels, fileName.substring(0, fileName.length() - 4) + "_out2.jpg");
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

	public static void main(String[] args) {
		JFrame frame = new JFrame("App");
		frame.setContentPane(new App().panelMain);
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		frame.pack();
		frame.setResizable(false);
		frame.setVisible(true);
		frame.setLocationRelativeTo(null);
	}
}
