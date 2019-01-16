import java.awt.List;

public class ListNode {

	private String charStr;
	private int prob;
	private ListNode next;
	private ListNode leftNode;
	private ListNode rightNode;
	private String code;

	public ListNode() {
		this.next = null;
		this.leftNode=null;
		this.rightNode=null;
	}
	public  String printNode(ListNode Node) {
		String pNode="";
		pNode+="char  " + Node.getCharStr()+"  "+ "Prob "+ Node.getProb()+" ";
		if (Node.getNext()==null) {
			pNode+=Node.getNext()+" ";
			
		}else{
			pNode+=" " +Node.getNext().getCharStr()+" ";		
		}
		
		if(Node.getLeftNode()==null){
			pNode+=" left "+Node.getLeftNode()+" ";
			
		}else{
			pNode+=" left "+ Node.getLeftNode().getCharStr()+" " + Node.getLeftNode().getProb()+ " ";
		}
		if(Node.getRightNode()==null){
			pNode+= " right " + Node.getRightNode()+ " ";
			
		}else{
			pNode+=" right " + Node.getRightNode().getCharStr()+" "+ Node.getRightNode().getProb()+ " ";
		}
		
		return pNode;
	}
	
	
	public String getCode(){
		return this.code;
	}
	public void setCode(String code){
		this.code=code;
	}

	public ListNode(String data,int count) {
		this.prob=count;
		this.charStr = data;
		this.next = null;
	}
	
	public ListNode getLeftNode(){
		return this.leftNode;
	}
	public void setLeftNode(ListNode leftNode){
		this.leftNode=leftNode;
	}
	
	
	public ListNode getRightNode(){
		return this.rightNode;
	}
	public void setRightNode(ListNode rightNode){
		this.rightNode=rightNode;
	}
	
	
	
	public int getProb(){
		return this.prob;
	}
	public void setProb(int count){
		this.prob=count;
	}

	public String getCharStr() {
		return this.charStr;
	}
	public void setCharStr(String charStr) {
		this.charStr = charStr;
	}

	public ListNode getNext() {
		return next;
	}

	public void setNext(ListNode next) {
		this.next = next;
	}
}
