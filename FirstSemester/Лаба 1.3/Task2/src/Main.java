import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
        Scanner f1 = new Scanner(new File("gray.in"));
        BufferedWriter f2 = new BufferedWriter(new FileWriter("gray.out"));
        int n = Integer.parseInt(f1.nextLine());
        ArrayList<String> mas = new ArrayList<>();
        mas.add("0");
        mas.add("1");
        for (int i = 2; i <= n; i++) {
            int kek = (int) Math.pow(2, i);
            for (int j = 0; j < kek / 2; j++) {
                String s = "0";
                s += mas.get(j);
                mas.set(j, s);
            }
            for (int j = kek / 2; j < kek; j++) {
                String s = "1";
                s += mas.get(kek - j - 1).substring(1);
                mas.add (s);
            }
        }
        for (int i = 0; i < mas.size(); i++){
            f2.write(mas.get(i));
            f2.newLine();
        }
        f1.close();
        f2.close();
    }
}
