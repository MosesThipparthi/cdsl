/*
 * cdsl_rbtree_test.c
 *
 *  Created on: May 21, 2015
 *      Author: root
 */

#include "cdsl.h"
#include "cdsl_rbtree.h"
#include <stdio.h>

BOOL cdsl_rbtreeDoTest(void){
	rb_treeNode_t* root;
	rb_treeNode_t node_pool[TEST_SIZE];
	int keys[TEST_SIZE];

	root = NULL;
	int i = 0;

	for(i = 0;i < TEST_SIZE;i++){
		keys[i] = rand() % TEST_SIZE;
		cdsl_rbtreeNodeInit(&node_pool[i],keys[i]);
		cdsl_rbtreeInsert(&root,&node_pool[i]);
	}

	rb_treeNode_t* del = NULL;
	for(i = 0;i < TEST_SIZE;i++){
		del = NULL;
		del = cdsl_rbtreeDelete(&root,keys[i]);
		if(!del)
			return FALSE;
	}

	return TRUE;

}