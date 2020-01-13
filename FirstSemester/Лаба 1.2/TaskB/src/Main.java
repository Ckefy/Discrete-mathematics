import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
        Scanner f1 = new Scanner(new File("bwt.in"), "utf8");
        PrintWriter f2 = new PrintWriter(new File("bwt.out"), "utf8");
        ArrayList<String> massive = new ArrayList<>();
        String s = f1.nextLine();
        massive.add(s);
        int len = s.length();
        for (int i = 1; i < len; i++) {
            s = massive.get(i - 1);
            String s1 = s.substring(len - 1, len) + s.substring(0, len - 1);
            massive.add(s1);
        }
        Collections.sort(massive);
        for (int i = 0; i < massive.size(); i++){
            f2.write(massive.get(i).charAt(len-1));
        }
        f1.close();
        f2.close();
    }
}
