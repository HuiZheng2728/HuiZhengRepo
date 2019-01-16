import java.awt.HeadlessException;
import java.io.PrintWriter;

import org.omg.CORBA.CurrentHolder;

public class HuffmanLinkedList extends ListNode {
	private ListNode listHead;
	private ListNode oldListHead;
	private ListNode dummy;

	public HuffmanLinkedList() {
		super();
		dummy = new ListNode();
		listHead=dummy;
		oldListHead=dummy;
	}

	public ListNode findSpot(ListNode node,ListNode head){
		while(node.getProb()>head.getNext().getProb()){
			head=head.getNext();
			if(head.getNext()==null){
				break;
			}
		}
		return head;
	}
	
	public void listInsert(ListNode spot, ListNode n){
		n.setNext(spot.getNext());
		spot.setNext(n);
	}
	
	public ListNode getFirst() {
		return this.listHead;
	}

	public boolean isEmpty() {
		if(this.listHead.getNext() == dummy)
			return true;
		return false;

	}

	public void insert(String charStr,int c,PrintWriter p) {
		ListNode walker = listHead;
		ListNode newNode = new ListNode(charStr,c);
		
		while(walker.getNext()!=null && walker.getNext().getProb()<newNode.getProb()){
			walker=walker.getNext();
		}
		newNode.setNext(walker.getNext());
		walker.setNext(newNode);	
		p.println(printList(listHead));
	
		
	}
	
	
	public  ListNode listBTNode(PrintWriter p){
		ListNode newHead =listHead.getNext();
		while(newHead.getProb()!=100){
		ListNode newNode = new ListNode();
		newNode.setCharStr(newHead.getCharStr()+newHead.getNext().getCharStr());
		newNode.setLeftNode(newHead);
		newNode.setRightNode(newHead.getNext());
		newNode.setProb(newHead.getProb()+newHead.getNext().getProb());
		p.println(printNode(newNode));
		listInsert(findSpot(newNode, newHead), newNode);
		p.println(printList(newHead));	
		newHead=newHead.getNext().getNext();
		}
		p.println("ListHead --> (dummy, 0, "+newHead.getCharStr()+ ") -->( "+ newHead.getCharStr()+", "+newHead.getProb()+", NULL)");
		return newHead;
	}
	

	public String printList(ListNode head) {
		
		String result = "listHead --> (dummy, 0, " + head.getNext().getCharStr() + ") --> ";
		
		ListNode current = head;
		while (current.getNext()!= null) {			
			result += "(" + current.getCharStr() + ", " + current.getNext().getCharStr()+" "+current.getNext().getProb()+ ") --> ";
			current = current.getNext();
		}
		return result + "(" + current.getCharStr() + "--> NULL)\n";
	}

}
