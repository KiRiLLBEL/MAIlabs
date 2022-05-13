#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../Downloads/tree1.h"

int main()
{
	
	Tree tree = NULL;
    int root = 0, ver = 0, parent = 0, count= 0;
	while(1)
	{
		printf("Введите число.\n1 Создание корня дерева    2 добавление элементов  3 удаление элементов   4  печать дерева    5 Подсчет вершин   6  Выход\n");
		int n=0;
		scanf("%d",&n);
		switch(n){
			case(1):
				if(tree != NULL)
		            	printf("Tree already exists\n");
		        	else 
		        	{
					printf("Введите значение корня дерева:\n");
                			scanf("%d", &root);
                			tree = tree_create(root);
					printf("Tree created\n");
				}
				break;
			case(2):
				printf("Введите родителя и ребенка\n");
				scanf("%d%d", &parent, &ver);
                		tree_add_node(tree, parent, ver);
				break;
			case(3):
				if(!tree) printf("Дерева не существует\n");
			    	else 
			    	{
					printf("Введите вершину, которую хотите удалить\n");
					scanf("%d", &ver);
					tree_del_node(tree, ver);
			    	}
				break;
			case(4):
				if (!tree) printf("Дерева не существует\n");
				else 
				{
					printf("\n\n");
					tree_print(tree);
					printf("\n\n");
				}
				break;
			case(5):
				l(tree,&count);
				break;
			case(6):
				tree_del_node(tree,root);
				printf("End program\n");
                exit(0);
                break;
			default:
				printf("Некорректный ввод данных\n");
		}
	}
}
