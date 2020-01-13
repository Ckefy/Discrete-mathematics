import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
        Scanner f1 = new Scanner(new File("chaincode.in"));
        BufferedWriter f2 = new BufferedWriter(new FileWriter("chaincode.out"));
        int n = f1.nextInt();
        ArrayList<String> mas = new ArrayList<>();
        String s = new String();
        for (int i = 0; i < n; i++) {
            s += '0';
        }
        mas.add(s);
        ArrayList<Boolean> check = new ArrayList<>();
        int maxn = (int) Math.pow(2, 16);
        for (int i = 0; i < maxn; i++) {
            check.add(false);
        }
        check.set(0, true);
        while (true) {
            String now = mas.get(mas.size() - 1);
            String now1 = now.substring(1) + '1';
            String now0 = now.substring(1) + '0';
            boolean flag1 = false, flag0 = false;
            if (check.get(Integer.parseInt(now1, 2))) {
                flag1 = true;
            }
            if (flag1) {
                if (check.get(Integer.parseInt(now0, 2))) {
                    flag0 = true;
                }
                if (!flag0) {
                    mas.add(now0);
                    check.set(Integer.parseInt(now0, 2), true);
                } else {
                    break;
                }
            } else {
                mas.add(now1);
                check.set(Integer.parseInt(now1, 2), true);
            }
        }
        for (int i = 0; i < mas.size(); i++) {
            f2.write(mas.get(i));
            f2.newLine();
        }
        f1.close();
        f2.close();
    }
}
