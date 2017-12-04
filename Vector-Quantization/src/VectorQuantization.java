import java.util.ArrayList;

public class VectorQuantization {
	int vectorSize;
	int codebookSize;
	ArrayList<ArrayList<ArrayList<Integer>>> block;

	VectorQuantization(int vectorSize, int codebookSize) {
		this.vectorSize = vectorSize;
		this.codebookSize = codebookSize;
	}

	public void encode(int[][] img) {
		for (int bi = 0; bi < img.length / vectorSize; ++bi) {
			for (int bj = 0; bj < img.length / vectorSize; ++bj) {
				ArrayList<ArrayList<Integer>> cur = new ArrayList<>();

				for (int i = bi * vectorSize; i < bi * vectorSize + vectorSize; ++i) {
					cur.add(new ArrayList<>());
					for (int j = bj * vectorSize; j < bj * vectorSize + vectorSize; ++j) {
						cur.get(cur.size() - 1).add(img[i][j]);
					}
				}

				block.add(cur);
			}
		}

		ArrayList<ArrayList<Integer>> avg = new ArrayList<>();
		for (int i = 0; i < avg.size(); ++i)
			avg.add(new ArrayList<>(img.length / vectorSize));

		for (ArrayList<ArrayList<Integer>> aBlock : block)
				for (int i = 0; i < aBlock.size(); ++i)
					for (int j = 0; j < aBlock.get(i).size(); ++j)
						avg.get(i).set(j, avg.get(i).get(j) + aBlock.get(i).get(j));

		for (int i = 0; i < vectorSize; ++i)
			for (int j = 0; j < vectorSize; ++j)
				avg.get(i).set(j, avg.get(i).get(j) / block.size());
	}

	private static ArrayList<ArrayList<Integer>> average(ArrayList<ArrayList<Integer>> arr) {

	}
}
