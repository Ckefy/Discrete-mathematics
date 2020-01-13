import java.sql.SQLOutput;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner f1 = new Scanner(System.in);
        int n = Integer.parseInt(f1.nextLine());
        ArrayList<String> mas = new ArrayList<>();
        ArrayList<Integer> num = new ArrayList<>();
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < Math.pow(2, n); i++) {
            mas.add(f1.nextLine());
            num.add(Character.digit(mas.get(i).charAt(n + 1), 10));
        }
        for (int i = 0; i < Math.pow(2, n); i++) {
            ans.add(num.get(0));
            for (int j = 0; j < Math.pow(2, n) - i - 1; j++) {
                num.set(j, (num.get(j) + num.get(j + 1)) % 2);
            }
        }
        for (int i = 0; i < mas.size(); i++) {
            System.out.print(mas.get(i).substring(0, mas.get(i).length()-1));
            System.out.println(Integer.toString(ans.get(i)));
        }
    }
}
