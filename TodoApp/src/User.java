import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class User {
	String name, mail;
	Account account;
	HashMap<String, TodoList> todoLists = new HashMap<>();

	User(String name, String mail, String password) {
		this.name = name;
		this.mail = mail;
		account = new Account(password);
	}

	public void addTodoList(String listName) {
		todoLists.put(name, new TodoList(listName));
	}

	public void addTodo(String listName, String name, String description, String date) {
		todoLists.get(listName).addTodo(name, description, date);
	}

	public void markAsDone(String listName, String name) {
		todoLists.get(listName).markAsDone(name);
	}

	@Override
	public String toString() {
		StringBuilder ret = new StringBuilder();
		for (Object list : todoLists.entrySet())
			ret.append(list.toString());
		return ret.toString();
	}
}
