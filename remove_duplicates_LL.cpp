#include<iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int v):val(v),next(nullptr){}
};

/**
 * Computes the size of a linked list
 * @param   *head -> A pointer to the head of a linked list
 * @returns size_t -> The size of the linked list
 */
size_t compute_size(ListNode* head)
{
	size_t size = 0;
	
	for(ListNode* iterator = head; iterator!=nullptr ; size++, iterator = iterator->next);

	return size;
}

/**
 * Splits a linked list into two parts(left & right)
 * @param   *head -> A pointer to the head of a linked list
 * @param   n -> The number of nodes the left part should contain
 * @returns *ListNode -> The right part
 */
ListNode* split(ListNode *head, size_t n){

	for(size_t i = 1; i < n && head!=nullptr; head = head->next, i++);
	
	if(head == nullptr)
		return head;

	ListNode *divided_list = head->next;
	head->next = nullptr;
	return divided_list;
}

/**
 * Merges two linked lists in ascending order into a third list
 * @param   *l1 -> A pointer to the head of linked list 1
 * @param   *l2 -> A pointer to the head of linked list 2
 * @param   *head -> A pointer to the head of the result linked list
 * @returns *ListNode -> linked list
 */
ListNode* merge(ListNode* l1, ListNode* l2, ListNode* head){
	ListNode* iterator = head;
	while(l1!=nullptr && l2!=nullptr)
	{
		if(l1->val > l2->val)
		{
			iterator->next = l2;
			iterator = l2;
			l2 = l2->next;
		}
		else
		{
			iterator->next = l1;
			iterator = l1;
			l1 = l1->next;
		}
	}
	iterator->next = (l1!=nullptr ? l1 : l2);

	for(;iterator->next!=nullptr; iterator = iterator->next);

	return iterator;
}

/**
 * A function that implements merge sort for a linked list
 * @param   *head -> A pointer to the head of the linked list
 * @returns *ListNode -> A sorted linked list
 */
ListNode* sort_list(ListNode *head)
{
	if(head == nullptr || head->next == nullptr)
		return head;
	
	size_t size = compute_size(head);
	
	ListNode dummy(0);
	dummy.next = head;
	ListNode *left, *right, *tail;

	for(size_t step = 1; step < size; step*=2 )
	{
		ListNode* iterator = dummy.next;
		tail = &dummy;
		while(iterator)
		{
			left = iterator;
			right = split(left, step);
			iterator = split(right,step);
			tail = merge(left, right, tail);
		}
	}
	return dummy.next;
}

/**
 * Deletes duplicate nodes from a linked list. 
 * Sorts the list before deletion
 * @Time_Complexity -> O(n log n)
 * @param   *head -> A pointer to the head the linked list
 * @returns *ListNode -> linked list
 */
ListNode* delete_duplicates_reorder_list(ListNode* head)
{
	if(head == nullptr)
		return head;
		
	head = sort_list(head);
	ListNode dummy(0);
	dummy.next = head;

	for(ListNode *iterator = head, *next = nullptr; iterator!=nullptr && iterator->next!=nullptr; iterator=iterator->next)
	{
		next = iterator->next;
		if(iterator->val == next->val)
		{
			while(next!=nullptr && iterator->val == next->val)
			{
				ListNode* temp = next->next;
				delete next;
				iterator->next = temp;
				next = iterator->next;
			}
		}
	}
	return dummy.next;
}

/**
 * Deletes duplicate nodes from a linked list. 
 * Preserves the original ranking.
 * @Time_Complexity -> O(n^2)
 * @param   *head -> A pointer to the head the linked list
 * @returns *ListNode -> linked list
 */
ListNode* delete_duplicates_list(ListNode* head)
{
	if(head == nullptr)
		return head;
		
	ListNode dummy(0);
	dummy.next = head;
	for(ListNode *iterator = head; iterator!=nullptr && iterator->next!=nullptr; iterator=iterator->next)
	{
		for(ListNode* prev = iterator, *next = iterator->next; next!=nullptr; next = next->next)
		{
			if(next->val == iterator->val)
			{
				ListNode* temp = next->next;
				delete next;
				prev->next = temp;
				next = prev;
			}
			else
				prev = prev->next;
		}
		
	}
	return dummy.next;
}

int main()
{
	ListNode* head_1 = new ListNode(1);
	ListNode* tail_1 = head_1;

	for(int i=0; i<10; tail_1=tail_1->next, i++)
		tail_1->next = new ListNode(i);

	for(int i = 7; i>=-2; tail_1=tail_1->next, i--)
		tail_1->next = new ListNode(i);

	ListNode* head_2 = new ListNode(head_1->val);
	for(ListNode* iterator = head_1->next, *tail_2 = head_2; iterator!= nullptr; tail_2 = tail_2->next, iterator = iterator->next)
		tail_2->next = new ListNode(iterator->val);
	
	cout<<"original values in list 1"<<endl;
	for(ListNode* iterator = head_1; iterator!= nullptr; iterator = iterator->next)
		cout<<iterator->val<<" ";

	cout<<endl<<"Delete duplicates with reordering"<<endl;
	head_1 = delete_duplicates_reorder_list(head_1);
	for(ListNode* iterator = head_1; iterator!= nullptr; iterator = iterator->next)
		cout<<iterator->val<<" ";

	cout<<endl<<endl<<"original values in list 2"<<endl;
	for(ListNode* iterator = head_2; iterator!= nullptr; iterator = iterator->next)
		cout<<iterator->val<<" ";

	cout<<endl<<"Delete duplicates without reordering"<<endl;
	head_2 = delete_duplicates_list(head_2);
	for(ListNode* iterator = head_2; iterator!= nullptr; iterator = iterator->next)
		cout<<iterator->val<<" ";
}