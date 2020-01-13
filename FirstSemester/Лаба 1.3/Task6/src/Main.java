import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
        ArrayList<String> mas = new ArrayList<>();
        Scanner f1 = new Scanner(new File("vectors.in"));
        BufferedWriter f2 = new BufferedWriter(new FileWriter("vectors.out"));
        int n = f1.nextInt();
        int kek = (int) Math.pow(2, n);
        for (int i = 0; i < kek; i++){
            String s = Integer.toString(i, 2);
            String s1 = new String();
            while (s1.length() + s.length() < n) {
                s1 += '0';
            }
            s1 += s;
            for (int j = 0; j < n - 1; j++){
                if ((s1.charAt(j) == '1') && (s1.charAt(j) == s1.charAt(j+1))){
                    break;
                }
                if (j == n -2 ){
                    mas.add(s1);
                }
            }
        }
        int size = mas.size();
        f2.write(Integer.toString(size));
        f2.newLine();
        for (int i = 0; i < size; i++){
            f2.write(mas.get(i));
            f2.newLine();
        }
        f1.close();
        f2.close();
    }
}
