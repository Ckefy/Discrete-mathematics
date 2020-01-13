import java.io.*;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
        Scanner f1 = new Scanner(new File("mtf.in"), "utf8");
        PrintWriter f2 = new PrintWriter(new File("mtf.out"), "utf8");
        String s = f1.nextLine();
        StringBuilder smth = new StringBuilder();
        for (int i = 0; i < 26; i++) {
            smth.append((char) ('a' + i));
        }
        String mas = new String(smth);
        int len = s.length();
        StringBuilder ans = new StringBuilder();
        for (int i = 0; i < len; i++) {
            int pos = mas.indexOf(s.charAt(i));
            ans.append(Integer.toString(pos + 1));
            ans.append(' ');
            mas = mas.charAt(pos) + mas.substring(0, pos) + mas.substring(pos + 1);
        }
        f2.write(new String(ans));
        f1.close();
        f2.close();
    }
}
