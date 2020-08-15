import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;


public class Main {
    private static String FILE_PATH = "../data/huffman.txt";

    public static int[] readFile(String FILE_PATH) throws FileNotFoundException {
        Scanner sc = new Scanner(new File(FILE_PATH));
        int nBinaryNode = sc.nextInt();
        int[] bnBuffer = new int[nBinaryNode] ;
        for (int i = 0; i < nBinaryNode; i++){
            bnBuffer[i] = sc.nextInt();
        }
        sc.close();
        return bnBuffer;
    }


    public static void main(String[] args) throws FileNotFoundException {
        // get node weights from assigned txt file
        if (args.length == 1){
            FILE_PATH = args[0];
        }

        int[] nBuffer = readFile(FILE_PATH);
        // sort the array and convert it to binary node's linked list
        Arrays.sort(nBuffer);
        LinkedList<Binary_node> lstBuffer = new LinkedList<Binary_node>();
        for (int value : nBuffer) {
            lstBuffer.add(new Binary_node(value));
        }

        // plan: iterate all nodes in list, merge closest two until one remaining in list
        Binary_node a, b, bnBuffer;
        int weightSum;
        while (lstBuffer.size() > 1)
        {
            // merge closest two nodes to one binary node
            a = lstBuffer.pop();
            b = lstBuffer.pop();
            weightSum = a.getWeight() + b.getWeight();
            bnBuffer = new Binary_node(weightSum);
            if (a.getWeight() >= b.getWeight()){
                bnBuffer.leftChild = a;
                bnBuffer.rightChild = b;
            }
            else{
                bnBuffer.leftChild = b;
                bnBuffer.rightChild = a;
            }
            bnBuffer.setMaxDepth(Math.max(a.getMaxDepth(), b.getMaxDepth()) + 1);
            bnBuffer.setMinDepth(Math.min(a.getMinDepth(), b.getMinDepth()) + 1);

            // insert merged node into appropriate place in lstBuffer, so as not to shuffle sorted list
            int i;
            for (i=0; i<lstBuffer.size(); i++){
                if (weightSum <= lstBuffer.get(i).getWeight()){
                    lstBuffer.add(i, bnBuffer);
                    break;
                }
            }
            if (i == lstBuffer.size()){
                lstBuffer.addLast(bnBuffer);
            }
        }
        System.out.printf("Max depth: %d, min depth: %d\n", lstBuffer.getFirst().getMaxDepth(), lstBuffer.getFirst().getMinDepth());
    }
}
