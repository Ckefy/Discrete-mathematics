import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
        Scanner f1 = new Scanner(new File("lzw.in"), "utf8");
        PrintWriter f2 = new PrintWriter(new File("lzw.out"), "utf8");
        String s = f1.nextLine();
        ArrayList<String> mas = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
            mas.add(new String(String.valueOf((char) ('a' + i))));
        }
        String buffer = new String();
        StringBuilder ans = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            if (mas.indexOf(buffer + s.charAt(i)) == -1) {
                ans.append(mas.indexOf(buffer));
                ans.append(' ');
                mas.add(buffer + s.charAt(i));
                buffer = String.valueOf(s.charAt(i));
            } else {
                buffer += s.charAt(i);
            }
        }
        ans.append(mas.indexOf(buffer));
        f2.write(new String(ans));
        f1.close();
        f2.close();
    }
}
