import java.io.*;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
        Scanner f1 = new Scanner(new File("antigray.in"));
        BufferedWriter f2 = new BufferedWriter(new FileWriter("antigray.out"));
        int n = Integer.parseInt(f1.nextLine());
        int kek = (int) Math.pow(3, n - 1);
        for (int i = 0; i < kek; i++) {
            String s = Integer.toString(i, 3);
            String s1 = new String();
            while (s1.length() + s.length() < n) {
                s1 += '0';
            }
            s1 += s;
            f2.write(s1);
            f2.newLine();
            for (int j = 0; j < s1.length(); j++) {
                if (s1.charAt(j) == '0') {
                    f2.write('1');
                } else if (s1.charAt(j) == '1') {
                    f2.write('2');
                } else {
                    f2.write('0');
                }
            }
            f2.newLine();
            for (int j = 0; j < s1.length(); j++) {
                if (s1.charAt(j) == '0') {
                    f2.write('2');
                } else if (s1.charAt(j) == '1') {
                    f2.write('0');
                } else {
                    f2.write('1');
                }
            }
            f2.newLine();
        }
        f1.close();
        f2.close();
    }
}
