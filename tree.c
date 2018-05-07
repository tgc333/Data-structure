#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

FILE *fp;

typedef struct info {
	char name[15];
	char phone[15];
}info;

typedef struct TreeNode {
	info human;
	struct TreeNode *left, *right;
	struct TreeNode *parent;
}TreeNode;

void insert_node(TreeNode **root, char key[], char phone[]) {
	TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
	TreeNode *temp = *root;
	if (new_node == NULL) return;

	strcpy(new_node->human.name, key);
	strcpy(new_node->human.phone, phone);
	new_node->right = NULL;
	new_node->left = NULL;

	if (temp == NULL) {
		(*root) = new_node;
		return;
	}

	while (temp != NULL) {
		new_node->parent = temp;
		if (temp->human.name[0] >= key[0])
			temp = temp->left;
		else
			temp = temp->right;
	}

	if (new_node->parent->human.name[0] >= key[0])
		new_node->parent->left = new_node;
	else
		new_node->parent->right = new_node;
}

TreeNode *search_node(TreeNode *root, char key[]) {
	TreeNode *temp = root;
	while (temp != NULL && strcmp(key, temp->human.name)) {
		if (temp->human.name[0] >= key[0])
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}

void delete_node(TreeNode **root, char key[]) {
	TreeNode *remove = search_node(*root, key);

	if (remove == NULL) {
		printf("지울 노드 없음");
		return;
	}

	if (remove->left == NULL && remove->right == NULL) {
		if (remove == (*root))
			(*root) = NULL;
		else if (remove->parent->human.name[0] > key[0])
			remove->parent->left = NULL;
		else
			remove->parent->right = NULL;
		free(remove);
	}

	else if (remove->left == NULL)
	{
		strcpy(remove->human.name, remove->right->human.name);
		strcpy(remove->human.phone, remove->right->human.phone);
		delete_node(&remove->right, remove->right->human.name);
	}
	else if (remove->right == NULL)
	{
		strcpy(remove->human.name, remove->left->human.name);
		strcpy(remove->human.phone, remove->left->human.phone);
		delete_node(&remove->left, remove->left->human.name);
	}
	else {
		TreeNode *temp = remove;
		remove = remove->right;

		while (remove->left != NULL)
			remove = remove->left;

		strcpy(temp->human.name, remove->human.name);
		strcpy(temp->human.phone, remove->human.phone);
		delete_node(&temp->right, remove->human.name);
	}
}


void LVR(TreeNode *root)   // 중위
{
	if (root) {
		LVR(root->left);
		printf("\n이름 : %s\n", root->human.name);
		printf("전화번호 : %s\n", root->human.phone);
		LVR(root->right);
	}
}

void save_file(TreeNode *root)   // 중위
{
	if (root) {
		save_file(root->left);
		fputs(root->human.name, fp);
		fputc('\n', fp);
		fputs(root->human.phone, fp);
		fputc('\n', fp);
		save_file(root->right);
	}
}

TreeNode *open_file()
{
	TreeNode *temp = NULL;
	char name[15];
	char phone[15];
	char buf[100];
	int i = 0;
	fp = fopen("test.txt", "rt");
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		switch (i) {
		case 0:
			strcpy(name, buf); i++;
			for (int i = 0; i < sizeof(name); i++)
				if (name[i] == '\n')
					name[i] = '\0';
			break;
		case 1:
			strcpy(phone, buf); i++;
			for (int i = 0; i < sizeof(phone); i++)
				if (phone[i] == '\n')
					phone[i] = '\0';
			i = 0;
			insert_node(&temp, &name, &phone);
			break;
		}
	}
	printf("불러오기 완료\n");
	fclose(fp);
	return temp;
}

void printMenu(void)
{
	system("cls");
	printf("******************************\n");
	printf("[Phone Book Program by 20130992]\n");
	printf("           - Menu -           \n");
	printf("   1. Input Phone             \n");
	printf("   2. Delete Phone             \n");
	printf("   3. Print Phone            \n");
	printf("   4. Search Phone            \n");
	printf("   5. Save Phone Book           \n");
	printf("   6. Load Phone Book           \n");
	printf("   0. Quit                    \n");
	printf("   => Input your choice: ");
}

int main(void)
{
	TreeNode *root = NULL;
	int input;
	int data;
	char name[15];
	char phone[15];

	while (1) {
		printMenu();
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("이름 >> ");
			scanf("%s", &name);
			printf("전화번호 >> ");
			scanf("%s", &phone);
			insert_node(&root, &name, &phone);
			break;
		case 2:
			printf("이름 >> ");
			scanf("%s", &name);
			delete_node(&root, &name);
			break;
		case 3:
			LVR(root);
			printf("\n");
			break;
		case 4:
			printf("이름 >> ");
			scanf("%s", &name);
			TreeNode *temp = search_node(root, &name);
			printf("이름 : %s\n", temp->human.name);
			printf("전화번호 : %s\n", temp->human.phone);
			break;
		case 5:
			fp = fopen("test.txt", "w+t");
			save_file(root);
			printf("저장 완료\n");
			fclose(fp);
			break;
		case 6:
			root = open_file();
			break;
		case 0:
			return 1;
		}
		getch();
	}
	return 0;
}