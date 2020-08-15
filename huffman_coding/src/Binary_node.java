import javax.lang.model.type.NullType;

public class Binary_node {
    private int weight;
    private int maxDepth = 0;
    private int minDepth = 0;

    Binary_node leftChild = null;
    Binary_node rightChild = null;

    Binary_node(int weight)
    {
        this.weight = weight;
    }

    public Binary_node setLeftChild(int weight)
    {
        this.leftChild = new Binary_node(weight);
        return this.leftChild;
    }

    public Binary_node setRightChild(int weight)
    {
        this.rightChild = new Binary_node(weight);
        return this.rightChild;
    }

    public void setChildren(int leftWeight, int rightWeight)
    {
        setLeftChild(leftWeight);
        setRightChild(rightWeight);
    }

    public int getWeight(){
        return this.weight;
    }

    public void setMaxDepth(int n){
        this.maxDepth = n;
    }

    public int getMaxDepth(){
        return this.maxDepth;
    }

    public void setMinDepth(int n){
        this.minDepth = n;
    }

    public int getMinDepth(){
        return this.minDepth;
    }
}
