import java.util.ArrayList;
import java.util.Scanner;


public class Main {

    public static void main(String[] args) {
        Scanner f1 = new Scanner(System.in);
        boolean flag0 = false, flag1 = false, flagS = false, flagM = false, flagL = false;
        int n = Integer.parseInt(f1.nextLine());
        for (int i = 0; i < n; i++) {
            int k = f1.nextInt();
            String s = f1.nextLine().substring(1);
            if (!flag0) {
                if (s.charAt(0) == '1') {
                    flag0 = true;
                }
            }
            if (!flag1) {
                if (s.charAt(s.length() - 1) == '0') {
                    flag1 = true;
                }
            }
            if (!flagS) {
                int count0 = 0, count1 = 0;
                for (int j = 0; j < Math.pow(2, k); j++) {
                    if (s.charAt(j) == '0') {
                        count0++;
                    } else {
                        count1++;
                    }
                }
                if (count0 != count1) {
                    flagS = true;
                }
            }
            if (!flagM) {
                int step = (int) Math.pow(2, k - 1);
                while (step > 0) {
                    int j = 0;
                    while (j < s.length()) {
                        for (int z = j; z < j + step; z++) {
                            if (s.charAt(z) > s.charAt(z + step)) {
                                flagM = true;
                                break;
                            }
                        }
                        j += 2 * step;
                        if (flagM){
                            break;
                        }
                    }
                    if (flagM){
                        break;
                    }
                    step/=2;
                }
            }
            if (!flagL) {
                ArrayList<Integer> num = new ArrayList<>();
                ArrayList<Integer> ans = new ArrayList<>();
                for (int j = 0; j < s.length(); j++) {
                    num.add(Character.digit(s.charAt(j), 10));
                }
                for (int z = 0; z < Math.pow(2, k); z++) {
                    ans.add(num.get(0));
                    for (int j = 0; j < Math.pow(2, k) - z - 1; j++) {
                        num.set(j, (num.get(j) + num.get(j + 1)) % 2);
                    }
                }
                for (int j = 0; j < s.length(); j++) {
                    if (ans.get(j) == 0) {
                        continue;
                    }
                    if (Integer.bitCount(j) > 1) {
                        flagL = true;
                        break;
                    }
                }
            }
        }
        if (flag0 && flag1 && flagS && flagM && flagL) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }
    }
}

