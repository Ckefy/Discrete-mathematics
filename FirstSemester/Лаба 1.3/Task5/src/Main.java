import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
        Scanner f1 = new Scanner(new File("telemetry.in"));
        BufferedWriter f2 = new BufferedWriter(new FileWriter("telemetry.out"));
        int n = f1.nextInt();
        int k = f1.nextInt();
        ArrayList<String> mas = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            char c = (char) ((int) '0' + i);
            mas.add(Character.toString(c));
        }
        for (int i = 2; i <= n; i++) {
            int size = mas.size();
            for (int j = 0; j < k; j++) {
                if (j == 0) {
                    for (int z = 0; z < size; z++) {
                        mas.set(z, Integer.toString(0) + mas.get(z));
                    }
                    continue;
                }
                if (j % 2 == 0) {
                    for (int z = 0; z < size; z++) {
                        mas.add(Integer.toString(j) + mas.get(z).substring(1));
                    }
                } else {
                    for (int z = size - 1; z >= 0; z--) {
                        mas.add(Integer.toString(j) + mas.get(z).substring(1));
                    }
                }
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