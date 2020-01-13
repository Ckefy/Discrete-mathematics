import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner f1 = new Scanner(System.in);
        int n = f1.nextInt();
        int maxbytes = 64;
        ArrayList<StringBuilder> column = new ArrayList<>();
        ArrayList<Long> numbers = new ArrayList<>();
        for (int i = 0; i < maxbytes; i++) {
            column.add(new StringBuilder());
        }
        for (int i = 0; i < n; i++) {
            long nowLong = f1.nextLong();
            numbers.add(nowLong);
            String s1 = Long.toString(nowLong, 2);
            String s = new String();
            while (s.length() + s1.length() < maxbytes) {
                s += 0;
            }
            for (int z = 0; z < s1.length(); z++) {
                s += s1.charAt(z);
            }
            for (int j = 0; j < maxbytes; j++){
                column.get(j).append(s.charAt(j));
            }
        } //есть столбики битов всех слов друг за другом
        long needLong = f1.nextLong();
        if (needLong == 0) {
            System.out.println("1&~1");
        }
        //если у всех чисел два столбца битов равны, но результат разный, то проиграли
        //собрали нужную единицу - то есть сделали в столбце все 1 и перемножили
        //если еще где-то образовалась единица - то значит у нас было два одинаковых столбика и разные результаты
        //а мы их вычеркнули
        for (int i = 0; i < n; i++) {
            if (numbers.get(i) == needLong) {
                System.out.println(i + 1);
                return;
            }
        }
        String need1 = Long.toString(needLong, 2);
        String need = new String();
        while (need.length() + need1.length() < maxbytes) {
            need += 0;
        }
        for (int i = 0; i < need1.length(); i++) {
            need += need1.charAt(i);
        }
        for (int i = 0; i < maxbytes; i++) {
            for (int j = i + 1; j < maxbytes; j++) {
                if ((new String(column.get(i)).equals(new String(column.get(j)))) && (need.charAt(i)) != need.charAt(j)) {
                    System.out.println("Impossible");
                    return;
                }
            }
        }
        boolean flag = true;
        for (int i = 0; i < need.length(); i++) {
            if (need.charAt(i) == '1') {
                if (!flag) {
                    System.out.print('|');
                }
                for (int j = 0; j < n; j++) {
                    if (j != 0) {
                        System.out.print('&');
                    }
                    if (column.get(i).charAt(j) == '1') {
                        System.out.print(j + 1);
                    } else {
                        System.out.print('~');
                        System.out.print(j + 1);
                    }
                }
                flag = false;
            }
        }
    }
}
