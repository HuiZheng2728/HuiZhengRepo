import java.awt.List;
import java.io.PrintWriter;

public class HuffmanBinaryTree extends ListNode{
	
	private ListNode Head;
	private ListNode Dummy;
	
	public HuffmanBinaryTree(){
		super();
		Dummy = new ListNode();
		Head = Dummy;
	}
	public ListNode constructHBT(ListNode treeNode,String code,PrintWriter writeCharCode){
		if(treeNode==null){
			
		}else if (isLeaf(treeNode)){
			writeCharCode.print(treeNode.getCharStr()+" ");
			treeNode.setCode(code);
			writeCharCode.println(treeNode.getCode());
		}else {
			constructHBT(treeNode.getLeftNode(), code+"0",writeCharCode);
			constructHBT(treeNode.getRightNode(), code+"1",writeCharCode);
			
		}
		return treeNode;
	}
	public  void inOrder(ListNode Node,PrintWriter p){	
		if(Node==null){
			
		}else{
			inOrder(Node.getLeftNode(),p);
			p.println(printNode(Node));
			inOrder(Node.getRightNode(),p);
		}
	}
	public void preOrder(ListNode Node,PrintWriter p){
		if(Node==null){	
			
		}else{
			p.println(printNode(Node));
			preOrder(Node.getLeftNode(),p);
			preOrder(Node.getRightNode(),p);
		}
	}
	public void postOrder(ListNode Node,PrintWriter p){
		if(Node==null){
		}else{
			postOrder(Node.getLeftNode(),p);
			postOrder(Node.getRightNode(),p);
			p.println(printNode(Node));
		}
	}
	
	public boolean isLeaf(ListNode Node){
		if(Node.getLeftNode()==null && Node.getRightNode()==null){
			return true;
		}
		return false;	 
	}
}