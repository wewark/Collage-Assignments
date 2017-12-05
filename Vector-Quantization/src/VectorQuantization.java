import java.awt.*;
import java.util.ArrayList;

public class VectorQuantization {
	private ArrayList<Group> groups;
	private ArrayList<ArrayList<Integer>> sortedBlocks;
	private int vectorSize, codebookSize;
	private int labelsHeight, labelsWidth;

	VectorQuantization(int vectorSize, int codebookSize) {
		this.vectorSize = vectorSize;
		this.codebookSize = codebookSize;
	}

	public HashResult encode(int[][] img) {
		groups = new ArrayList<>();
		groups.add(new Group());
		labelsHeight = labelsWidth = img.length / vectorSize;

		for (int bi = 0; bi < labelsHeight; ++bi) {
			for (int bj = 0; bj < labelsWidth; ++bj) {
				ArrayList<Integer> cur = new ArrayList<>();

				for (int i = bi * vectorSize; i < bi * vectorSize + vectorSize; ++i) {
					for (int j = bj * vectorSize; j < bj * vectorSize + vectorSize; ++j) {
						cur.add(img[i][j]);
					}
				}

				groups.get(0).addChild(cur);
			}
		}
		sortedBlocks = groups.get(0).children;

		while (groups.size() < codebookSize)
			groups = Group.split(groups, true);

		ArrayList<Group> tmp = groups;
		do {
			groups = tmp;
			tmp = Group.split(groups, false);
		} while (!equals(tmp, groups));

		return new HashResult();
	}


		static ArrayList<Group> split(ArrayList<Group> groups, boolean intoTwo) {
			ArrayList<Group> ret = new ArrayList<>();
			for (Group group : groups) {
				ArrayList<Integer> avg = group.average();
				if (intoTwo) {
					ret.add(new Group(calc(avg, -1)));
					ret.add(new Group(calc(avg, 1)));
				}
				else ret.add(new Group(calc(avg, 0)));
			}

			for (Group group : groups)
				for (ArrayList<Integer> child : group.children) {
					int mn = (int) 1e5, mni = -1;
					for (int i = 0; i < ret.size(); ++i) {
						int dist = distance(child, ret.get(i).avg);
						if (dist < mn) {
							mn = dist;
							mni = i;
						}
					}

					ret.get(mni).addChild(child);
				}

			return ret;
		}

		static ArrayList<Integer> calc(ArrayList<Integer> arr, int change) {
			ArrayList<Integer> ret = new ArrayList<>();
			for (Integer anArr : arr) ret.add(anArr + change);
			return ret;
		}

		static int distance(ArrayList<Integer> a, ArrayList<Integer> b) {
			int ret = 0;
			for (int i = 0; i < a.size(); ++i)
				ret += (int)Math.pow(a.get(i) - (b.isEmpty() ? 0 : b.get(i)), 2);
			return (int)Math.sqrt(ret);
		}

		void addChild(ArrayList<Integer> child) {
			children.add(child);
		}

		ArrayList<Integer> average() {
			ArrayList<Integer> avg = new ArrayList<>();
			if (children.isEmpty()) return avg;

			for (int i = 0; i < children.get(0).size(); ++i)
				avg.add(0);

			for (ArrayList<Integer> aBlock : children)
				for (int i = 0; i < aBlock.size(); ++i)
					avg.set(i, avg.get(i) + aBlock.get(i));

			for (int i = 0; i < avg.size(); ++i)
				avg.set(i, avg.get(i) / children.size());
			return avg;
		}

		public boolean equals(Group obj) {
			return children.equals(obj.children);
		}
	}

	class HashResult {
		ArrayList<ArrayList<Integer>> codeBook;
		ArrayList<ArrayList<Integer>> codeLabels;

		HashResult() {
			codeBook = new ArrayList<>();
			codeLabels = new ArrayList<>();

			for (Group group : groups)
				codeBook.add(group.average());

			for (ArrayList<Integer> block : sortedBlocks) {
				int mn = (int) 1e5, mni = -1;
				for (int i = 0; i < codeBook.size(); ++i) {
					int dist = Group.distance(block, codeBook.get(i));
					if (dist < mn) {
						mn = dist;
						mni = i;
					}
				}

				if (codeLabels.isEmpty() || codeLabels.get(codeLabels.size() - 1).size() == labelsWidth) {
					codeLabels.add(new ArrayList<>());
				}
				codeLabels.get(codeLabels.size() - 1).add(mni);
			}
		}

		@Override
		public String toString() {
			StringBuilder ret = new StringBuilder();
			for (ArrayList<Integer> arr : codeBook) {
				for (Integer i : arr)
					ret.append(i).append(" ");
				ret.append("\n");
			}
			ret.append("\n");

			for (ArrayList<Integer> arr : codeLabels) {
				for (Integer i : arr)
					ret.append(i).append(" ");
				ret.append("\n");
			}

			return ret.toString();
		}
	}
}
