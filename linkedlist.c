#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
int size=0;
struct node{
    int int_v,pos;
    struct node *next;
};
struct node *insert(struct node *,int,int);
void delete(struct node *,int);
struct node *find(struct node *,int);
int delete_helper(struct node*,int);
void position_reload_insert(struct node*);
void position_reload_delete(struct node*);
//void swap(struct node*,struct node*);
void display(struct node*);
struct node *insert(struct node *root,int position,int value){
	if(position==0){
		struct node *duplicate_head=(struct node*)malloc(sizeof(struct node));
		struct node *copy_next=(*root).next;
		(*duplicate_head).int_v=(*root).int_v;
		(*duplicate_head).pos=2;
		(*root).int_v=value;
		(*root).next=duplicate_head;
		(*duplicate_head).next=copy_next;
		return root;
	}
    struct node *selected_trv=root;
	while((*selected_trv).pos!=position-1){
		selected_trv=(*selected_trv).next;
	}
	if((*selected_trv).next==NULL){
		(*selected_trv).next=(struct node*)malloc(sizeof(struct node));
		selected_trv=(*selected_trv).next;
		(*selected_trv).int_v=value;
		size++;
		(*selected_trv).pos=size;
		(*selected_trv).next=NULL;
		return selected_trv;
	}
	struct node *temp=&(*(*selected_trv).next);
	(*selected_trv).next=(struct node*)malloc(sizeof(struct node));
	selected_trv=(*selected_trv).next;
	(*selected_trv).int_v=value;
	(*selected_trv).next=temp;
	size++;
	(*selected_trv).pos=size;
	position_reload_insert(selected_trv);
	return selected_trv;
}
void delete(struct node *head, int pos){
	if(pos==0){
		struct node *copy_next_next=(*(*head).next).next;
		(*head).int_v=(*(*head).next).int_v;
		free((*head).next);
		(*head).next=copy_next_next;
		return;
	}
	struct node *n1=head;
	while((*n1).pos!=pos-1){
		n1=(*n1).next;
	}
	struct node *save_nd=(*n1).next;
	(*n1).next=(*save_nd).next;
	free(save_nd);
    size--;
}
struct node *find(struct node *head, int value){
	struct node *selected=head;
	while(selected!=NULL){
		if((*selected).int_v==value){
			return selected;
		}
		selected=(*selected).next;
	}
	return NULL;
}
int delete_helper(struct node *head, int value){
	struct node *find_output=find(head,value);
	if(find_output!=NULL){
		position_reload_delete(find_output);
		//printf("position_reload_delete successful\n");
		delete(head,(*find_output).pos);
		return 1;
	}
	return 0;
}
void position_reload_insert(struct node *new){
	struct node *trv=(*new).next;
	while(trv!=NULL){
		(*trv).pos++;
		trv=(*trv).next;
	}
}
void position_reload_delete(struct node *deleted){
	struct node *trv=(*deleted).next;
	while(trv!=NULL){
		(*trv).pos--;
		trv=(*trv).next;
	}
}
/*void swap(struct node *node1,struct node *node2,struct node *node1_prev,struct node *node2_forw){
	(*node2).next=node1;
    (*node1_prev).next=node2;
    (*node1).next=node2_forw;
}*/
/*void swap(struct node *node1,struct node *node2){
	int temp_data=(*node1).int_v;
	(*node1).int_v=(*node2).int_v;
	(*node2).int_v=temp_data;
}*/
void display(struct node *head){
	struct node *selected=head;
	while(selected!=NULL){
		printf("%d ",(*selected).int_v);
		selected=(*selected).next;
	}
}
int main(void){
    struct node *head;
    head=(struct node*)malloc(sizeof(struct node));
	(*head).pos=size;
	(*head).next=NULL;
    int user_in,user_choice_in,insert_pos=0;
    printf("\nEnter head value:");
    scanf("%d",&user_in);
    (*head).int_v=user_in;
    printf("\nEnter 1 to insert data\nEnter 2 to delete data\nEnter 3 to see if a value exists in the linked list.\nEnter 4 to display the linked list\nEnter 5 to delete with position.\nEnter 6 to exit.\n");
	while(user_choice_in!=6){
		printf("Choice:");
		scanf("%d",&user_choice_in);
		switch(user_choice_in){
			case 1:
			 printf("\nEnter value:");
			 scanf("%d",&user_in);
			 printf("\nenter position:");
			 scanf("%d",&insert_pos);
			 insert(head,insert_pos-1,user_in);
			 break;
			case 2:
			 printf("\nValue(Duplicate values will continue to exist):");
			 scanf("%d",&user_in);
			 delete_helper(head,user_in);
			 break;
			case 3:
			 printf("\nValue:");
			 scanf("%d",&user_in);
			 printf("\n%s\n",find(head,user_in)?"Yes.":"No.");
			 break;
			case 4:
			 display(head);
			 printf("\n");
			 break;
			case 5:
			 printf("\nEnter position:");
			 scanf("%d",&user_in);
			 delete(head,user_in-1);
		}
	}
	return 0;
}