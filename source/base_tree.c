/*
 * base_tree.c
 *
 *  Created on: Nov 15, 2015
 *      Author: innocentevil
 */

#include "base_tree.h"
#include "cdsl.h"
#include <stdio.h>


#define PRINT 	printf

static int calc_max_depth_rc(base_treeNode_t** root);
static int calc_size_rc(base_treeNode_t** root);
static void print_rc(base_treeNode_t* current,cdsl_generic_printer_t prt,int depth);
static int traverse_incremental_rc(base_treeNode_t* current,int* current_order,base_tree_callback_t cb);
static int traverse_decremental_rc(base_treeNode_t* current,int* current_order,base_tree_callback_t cb);
static void print_tab(int cnt);

void tree_traverse(base_treeRoot_t* rootp, base_tree_callback_t cb,int order)
{
	if((cb == NULL) || (rootp == NULL) || (rootp->entry == NULL))
		return;
	int i = 0;
	if(order == ORDER_DEC)
		traverse_decremental_rc(rootp->entry,&i,cb);
	else
		traverse_incremental_rc(rootp->entry,&i,cb);
}

int tree_size(base_treeRoot_t* rootp)
{
	if(rootp == NULL)
		return 0;
	return calc_size_rc(&rootp->entry);
}

void tree_print(base_treeRoot_t* rootp,cdsl_generic_printer_t print)
{
	if(rootp == NULL)
		return;
	print_rc(rootp->entry,print,0);
}

int tree_max_depth(base_treeRoot_t* rootp)
{
	if(rootp == NULL)
		return 0;
	return calc_max_depth_rc(&rootp->entry);
}



static int calc_size_rc(base_treeNode_t** root)
{
	int cnt = 0;
	if((root == NULL) || (*root == NULL))
		return 0;
	if((*root))
		cnt = 1;
	if(!(*root)->left && !(*root)->right) return cnt;
	if((*root)->left)
		cnt += calc_size_rc(&(*root)->left);
	if((*root)->right)
		cnt += calc_size_rc(&(*root)->right);
	return cnt;
}


static int calc_max_depth_rc(base_treeNode_t** root)
{
	if((root == NULL) || (*root == NULL))
		return 0;
	int max = 0;
	int temp = 0;
	if(max < (temp = calc_max_depth_rc(&(*root)->left)))
		max = temp;
	if(max < (temp = calc_max_depth_rc(&(*root)->right)))
		max = temp;
	return max + 1;
}

static void print_rc(base_treeNode_t* current,cdsl_generic_printer_t print,int depth)
{
	if(!current)
		return;
	print_rc(current->right,print,depth + 1);
	print_tab(depth); if(print) print(current);
	print_rc(current->left,print,depth + 1);
}

static void print_tab(int cnt)
{
	while(cnt--)
		PRINT("\t");
}

static int traverse_incremental_rc(base_treeNode_t* current, int* current_order, base_tree_callback_t cb)
{
	if(current == NULL)
		return 0;
	if(traverse_incremental_rc(current->left,current_order,cb) == MSG_BREAK_TRAVERSE)
		return MSG_BREAK_TRAVERSE;
	*current_order += 1;
	if(cb(*current_order,current) == MSG_BREAK_TRAVERSE)
		return MSG_BREAK_TRAVERSE;
	return traverse_incremental_rc(current->right,current_order,cb);
}

static int traverse_decremental_rc(base_treeNode_t* current, int* current_order, base_tree_callback_t cb)
{
	if(current == NULL)
		return 0;
	if(traverse_decremental_rc(current->right,current_order,cb) == MSG_BREAK_TRAVERSE)
		return MSG_BREAK_TRAVERSE;
	*current_order += 1;
	if(cb(*current_order,current) == MSG_BREAK_TRAVERSE)
		return MSG_BREAK_TRAVERSE;
	return traverse_decremental_rc(current->left,current_order,cb);
}