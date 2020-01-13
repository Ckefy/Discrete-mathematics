import java.io.*;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
        //Scanner f1 = new Scanner(System.in);
        Scanner f1 = new Scanner(new File("allvectors.in"));
        BufferedWriter f2 = new BufferedWriter(new FileWriter("allvectors.out"));
        int n = Integer.parseInt(f1.nextLine());
        int k = (int) Math.pow(2, n);
        for (int i = 0; i < k; i++) {
            String s = Integer.toString(i, 2);
            int s1 = 0;
            while (s1 + s.length() < n) {
                s1++;
                f2.write('0');
            }
            f2.write(s);
            f2.newLine();
        }
        f1.close();
        f2.close();
    }
}
