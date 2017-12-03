import java.util.HashMap;

public class TodoApplication {
	HashMap<String, User> users = new HashMap<>();
	String currentUser = "";

	public void addUser(String name, String mail, String password) {
		users.put(name, new User(name, mail, password));
	}

	public boolean login(String name, String password) {
		return users.get(name).account.password.equals(password);
	}
}
