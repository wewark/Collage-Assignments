import java.util.Scanner;

public class Main {
	static TodoApplication app = new TodoApplication();

	public static void main(String[] args) {
		System.out.println("login or signup?");
		Scanner sc = new Scanner(System.in);
		String res;
		res = sc.nextLine();

		if (res.equals("signup")) {
			String name, mail, password;
			System.out.print("Name: "); name = sc.nextLine();
			System.out.print("Mail: "); mail = sc.nextLine();
			System.out.print("Password: "); password = sc.nextLine();
			app.addUser(name, mail, password);
			app.login(name, password);
		}
		else {
			String name, password;
			System.out.print("Name: "); name = sc.nextLine();
			System.out.print("Password: "); password = sc.nextLine();
			app.login(name, password);
		}

		while (true) {
			// TODO:
		}
	}
}
