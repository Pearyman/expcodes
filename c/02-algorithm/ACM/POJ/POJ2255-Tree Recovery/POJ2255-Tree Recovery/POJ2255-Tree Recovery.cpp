/*
	Author:     Exp
	Date:       2017-12-01
	Code:       POJ 2255
	Problem:    Tree Recovery
	URL:		http://poj.org/problem?id=2255
*/

/*
	���������
	  ����һ�ö�������ǰ������������������������.
	  ���ж������ɲ��ظ��Ĵ�д��ĸ��ɣ�ÿ���ڵ�һ����ĸ.

	����˼·��
	 �� ǰ������ĵ�һ����ĸ���� ��
	 �� �������������ĸ�����ҳ� ����ĸ����ô����ĸ�������ߵ��ַ����ͷֱ���������������
	 �� ��������������ֻ��26����˿������õݹ��Ϣ٢ڸ�ԭ������
	 �� �Ը�ԭ�Ķ�����ʹ��DFS�������������

	 ע��
	  �Զ������� ǰ����������������������� ������ʹ��DFS������
	  �������϶��¡��������ұ������������ڴ�ӡ�ڵ��ʱ����ͬ��
	  [ǰ�����] �Ӹ��ڵ����ʱ��ӡ��ǰ�ڵ�
	  [�������] ������������ʱ��ӡ��ǰ�ڵ�
	  [�������] ������������ʱ��ӡ��ǰ�ڵ�
*/

#include <memory.h>
#include <iostream>
using namespace std;

const static int STR_LEN = 27;
const static char NULL_CHAR = '\0';

class Node {
	public:
		char name;
		Node* left;
		Node* right;

		Node(): name(NULL_CHAR), left(NULL), right(NULL) {}

		bool operator == (const Node& other) {
			return (this == &other || this->name == other.name);
		}

		bool operator != (const Node& other) {
			return !(operator == (other));
		}
};


Node* createTree(char* preOrder, char* inOrder);
void dfs(Node* node, char* _out_postOrder);

int main(void) {
	char preOrder[STR_LEN] = { NULL_CHAR };
	char inOrder[STR_LEN] = { NULL_CHAR };

	while(cin >> preOrder >> inOrder) {
		Node* root = createTree(preOrder, inOrder);
		char postOrder[STR_LEN] = { NULL_CHAR };
		dfs(root, postOrder);
		cout << postOrder << endl;

		memset(preOrder, STR_LEN, sizeof(char) * STR_LEN);
		memset(inOrder, STR_LEN, sizeof(char) * STR_LEN);
	}
	return 0;
}


Node* createTree(char* preOrder, char* inOrder) {
	const int LEN = strlen(preOrder);
	if(LEN <= 0) {
		return NULL;
	}

	Node* root = new Node();
	root->name = *preOrder;	// ǰ������ĵ�һ���ڵ�ض�������

	char* leftPreOrder = new char[LEN + 1];		// ������ǰ����
	char* leftInOrder = new char[LEN + 1];		// ������������
	char* rigntPreOrder = new char[LEN + 1];	// ������ǰ����
	char* rigntInOrder = new char[LEN + 1];		// ������������
	strcpy(leftPreOrder, preOrder);
	strcpy(leftInOrder, inOrder);
	strcpy(rigntPreOrder, preOrder);
	strcpy(rigntInOrder, inOrder);

	// ���ݸ��ڵ����������е�λ�ã���������������ǰ�����к��������з�Χ
	for(int i = 0; *(inOrder + i) != NULL_CHAR; i++) {
		if(root->name == *(inOrder + i)) {
			*(leftInOrder + i) = NULL_CHAR;
			int leftLen = strlen(leftInOrder);
			*(leftPreOrder + leftLen + 1) = NULL_CHAR; 

			Node* leftTree = createTree((leftPreOrder + 1), leftInOrder);
			Node* rightTree = createTree((rigntPreOrder + leftLen + 1), (rigntInOrder + i + 1));
			root->left = leftTree;
			root->right = rightTree;
			break;
		}
	}

	delete[] leftPreOrder;
	delete[] leftInOrder;
	delete[] rigntPreOrder;
	delete[] rigntInOrder;
	return root;
}

void dfs(Node* node, char* _out_postOrder) {
	if(node == NULL) {
		return;
	}

	dfs(node->left, _out_postOrder);
	dfs(node->right, _out_postOrder);

	*(_out_postOrder + strlen(_out_postOrder)) = node->name;
}