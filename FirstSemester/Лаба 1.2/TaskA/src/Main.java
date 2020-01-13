import java.io.*;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner f1 = new Scanner(new File("huffman.in"));
        PrintWriter f2 = new PrintWriter(new File("huffman.out"));
        int n = Integer.parseInt(f1.nextLine());
        long inf = 1000000000000L;
        ArrayList<Long> mas1 = new ArrayList<>(), mas2 = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            mas1.add(f1.nextLong());
            mas2.add(inf);
        }
        Collections.sort(mas1);
        for (int i = n; i < n + 2; i++) {
            mas1.add(inf);
            mas2.add(inf);
        }
        int fir = 0, sec = 0;
        long ans = 0;
        for (int i = 0; i < n - 1; i++) {
            long m11 = mas1.get(fir), m12 = mas1.get(fir + 1);
            long m21 = mas2.get(sec), m22 = mas2.get(sec + 1);
            if ((m12 <= m21) && (m11 + m12 <= m21 + m22)) {
                mas2.set(i, m11 + m12);
                ans += mas2.get(i);
                fir += 2;
                continue;
            }
            if ((m21 <= m12) && (m11 <= m22)) {
                mas2.set(i, m11 + m21);
                ans += mas2.get(i);
                fir++;
                sec++;
                continue;
            }
            if ((m21 + m22 <= m11 + m12) && (m22 <= m11)) {
                mas2.set(i, m21 + m22);
                ans += mas2.get(i);
                sec += 2;
            }
        }
        f2.write(Long.toString(ans));
        f1.close();
        f2.close();
    }
}
