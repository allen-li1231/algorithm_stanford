import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashSet;
import java.util.Scanner;

public class Main {

    public static long[] readFile(String FILE_PATH) throws FileNotFoundException {
        Scanner sc = new Scanner(new File(FILE_PATH));
        int nBinaryNode = sc.nextInt();
        long[] nBuffer = new long[nBinaryNode] ;
        for (int i = 0; i < nBinaryNode; i++){
            nBuffer[i] = sc.nextInt();
        }
        sc.close();
        return nBuffer;
    }
    public static void main(String[] args) throws FileNotFoundException{
        String FILE_PATH;
        if (args.length == 1){
            FILE_PATH= args[0];
        }
        else{
            FILE_PATH = "../data/mwis.txt";
        }

        long[] nBuffer = readFile(FILE_PATH);
        long[] nResult = new long[nBuffer.length];
        nResult[0] = nBuffer[0];
        nResult[1] = Math.max(nBuffer[0], nBuffer[1]);
        HashSet<Integer> sResult = new HashSet<Integer>();
        for (int i = 2; i < nResult.length; i++)
        {
            nResult[i] = Math.max(nResult[i - 2] + nBuffer[i], nResult[i - 1]);
        }
        for (int i = nResult.length-1; i >= 1; i--)
        {
            if (nResult[i] != nResult[i - 1]){
                sResult.add(i + 1);
                i--;
            }
        }
        if (nResult[0] != nResult[1]) {
            sResult.add(1);
        }

        int[] nQidx = {1, 2, 3, 4, 17, 117, 517, 997};
        for (int i: nQidx)
        {
            if (sResult.contains(i)){
                System.out.print(1);
            }
            else{
                System.out.print(0);
            }
        }

    }
}
