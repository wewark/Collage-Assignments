public class TodoTask {
	String name, description, date;
	boolean done = false;

	TodoTask(String name, String description, String date) {
		this.name = name;
		this.description = description;
		this.date = date;
	}

	public void markAsDone() {
		done = true;
	}

	@Override
	public String toString() {
		return name + " " + description + " " + date + " " + (done ? "Done" : "Not done") + "\n";
	}
}
