import java.util.HashMap;

public class TodoList {
	String name;
	HashMap<String, TodoTask> todos = new HashMap<>();

	TodoList(String name) {
		this.name = name;
	}

	public void addTodo(String name, String description, String date) {
		todos.put(
				name,
				new TodoTask(name, description, date)
		);
	}

	public void markAsDone(String name) {
		todos.get(name).markAsDone();
	}

	@Override
	public String toString() {
		StringBuilder ret = new StringBuilder(name + '\n');
		for (Object todo : todos.entrySet())
			ret.append(todo.toString()).append('\n');
		return ret.toString();
	}
}
