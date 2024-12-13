#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//비교횟수, 탐색횟수 전역 변수
int compareCount = 0;
int searchCount = 0;

typedef struct Node { //트리 노드 구조체
	int key;
	struct Node* left;
	struct Node* right;
	int height;
} Node;

Node* createNode(int key) { //새로운 노드 생성 함수
	Node* nptr = (Node*)malloc(sizeof(Node));
	nptr->key = key;
	nptr->left = NULL;
	nptr->right = NULL;
	nptr->height = 1; //초기 높이를 1로 설정한다
	return nptr;
}

int getHeight(Node* nptr) { //높이 반환 함수
	if (nptr == NULL) return 0;
	else return nptr->height;
}

int getBalance(Node* nptr) { //균형 계산 함수
	if (nptr == NULL) return 0;
	return getHeight(nptr->left) - getHeight(nptr->right);
}

Node* rotateRight(Node* y) { //오른쪽 회전 함수
	Node* x = y->left;
	Node* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
	x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

	return x; //회전된 노드 반환
}

Node* rotateLeft(Node* x) { //왼쪽 회전 함수
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));
	y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));

	return y; //회전된 노드 반환
}

Node* AVLinsertNode(Node* root, int key) { //AVL 트리 삽입 함수
	if (root == NULL) return createNode(key); //노드가 NULL일 시, 새 노드 생성
	if (root->key > key) root->left = AVLinsertNode(root->left, key); //키 값이 작으면 왼쪽 노드에 삽입
	else if (root->key < key) root->right = AVLinsertNode(root->right, key); //키 값이 크면 오른쪽 노드에 삽입
	else return root;

	root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right)); //현재 노드의 높이 업데이트

	int balance = getBalance(root);

	//균형을 맞추기 위해 회전 처리
	if (balance > 1 && key < root->left->key) return rotateRight(root); // LL
	if (balance < -1 && key > root->right->key) return rotateLeft(root); // RR
	if (balance > 1 && key > root->left->key) { // LR
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	if (balance < -1 && key < root->right->key) { // RL
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	return root;
}

Node* BSTinsertNode(Node* root, int key) { //이진 탐색 트리 삽입 함수
	if (root == NULL) return createNode(key); //노드가 NULL일 시, 새 노드 생성
	if (root->key > key) root->left = BSTinsertNode(root->left, key); //키 값이 작으면 왼쪽 노드에 삽입
	else if (root->key < key) root->right = BSTinsertNode(root->right, key); //키 값이 크면 오른쪽 노드에 삽입
	return root;
}

Node* getMinValueNode(Node* node) { // 트리에서 최소값 노드 찾기
	Node* current = node;
	while (current->left)
		current = current->left;
	return current;
}

Node* AVLdeleteNode(Node* root, int key) { //AVL 트리 삭제 함수
	if (root == NULL) return root;
	if (key < root->key) root->left = AVLdeleteNode(root->left, key);
	else if (key > root->key) root->right = AVLdeleteNode(root->right, key);
	else {
		// 노드 삭제
		if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		}
		// 오른쪽 서브트리에서 최소값 노드 찾기
		Node* temp = getMinValueNode(root->right);
		root->key = temp->key; // 키값만 복사함
		root->right = AVLdeleteNode(root->right, temp->key); // 이제 그 최소값을 가진 노드 삭제
	}

	root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right)); //현재 노드의 높이 업데이트

	int balance = getBalance(root); //균형 계산

	if (balance > 1 && getBalance(root->left) >= 0) return rotateRight(root);  // LL
	if (balance < -1 && getBalance(root->right) <= 0) return rotateLeft(root); // RR
	if (balance > 1 && getBalance(root->left) < 0) {                           // LR
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	if (balance < -1 && getBalance(root->right) > 0) { // RL
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	return root;
}

Node* BSTdeleteNode(Node* root, int key) { //이진 탐색 트리 삭제 함수
	if (root == NULL) return root;
	if (key < root->key) root->left = BSTdeleteNode(root->left, key);
	else if (key > root->key) root->right = BSTdeleteNode(root->right, key);
	else {
		// 노드 삭제
		if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		}
		// 오른쪽 서브트리에서 최소값 노드 찾기
		Node* temp = getMinValueNode(root->right);
		root->key = temp->key; // 키값만 복사함
		root->right = BSTdeleteNode(root->right, temp->key); // 이제 그 최소값을 가진 노드 삭제
	}
	return root;
}

Node* searchNode(Node* root, int key) { //트리에서 주어진 키를 검색하는 함수
	if (root == NULL) { 
		compareCount++;  
		return NULL;
	}

	compareCount++;  
	if (key == root->key)
		return root;

	if (key < root->key) {
		compareCount++;  
		return searchNode(root->left, key);
	}
	compareCount++; 
	return searchNode(root->right, key);
}


void doAVLBatch(Node* root) { //AVL Tree Batch 수행 함수
	searchCount = 0;
	int A, B;
	for (int i = 0; i < 2000; i++) {
		A = rand() % 3; //0, 1, 2 중 선택
		B = rand() % 1000;

		switch (A) {
			case 0: //삽입
				root = AVLinsertNode(root, B);
				break;
			case 1: //삭제
				root = AVLdeleteNode(root, B);
				break;
			case 2: //탐색
				searchCount++;
				searchNode(root, B);
				break;
		}
	}
}

void doBinaryBatch(Node* root) { //Binary Search Tree Batch 수행 함수
	searchCount = 0;
	int A, B;
	for (int i = 0; i < 2000; i++) {
		A = rand() % 3; //0, 1, 2 중 선택
		B = rand() % 1000;

		switch (A) {
			case 0: //삽입
				root = BSTinsertNode(root, B);
				break;
			case 1: //삭제
				root = BSTdeleteNode(root, B);
				break;
			case 2: //탐색
				searchCount++;
				searchNode(root, B);
				break;
		}
	}
}

void freeTree(Node* root) { //메모리 해제 함수
	if (root == NULL) return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

int main(int argc, char* argv[]) {
	Node* root = NULL; //루트 노드 초기화
	srand(time(NULL));
	float allCount = 0.0; //평균 비교 횟수 저장

	//AVL에 대한 2000회 Batch 작업을 수행한다.
	doAVLBatch(root);
	allCount = (float)compareCount / searchCount; //평균 비교 횟수 계산
	printf("average AVL compare count: %.2f\n", allCount); //그 결과 출력

	freeTree(root); // 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
	root = NULL; //루트 노드 초기화
	compareCount = allCount = 0; //비교 횟수 초기화

	//Binary Search Tree에 대한 2000회 Batch를 수행한다.
	doBinaryBatch(root);
	allCount = (float)compareCount / searchCount; //평균 비교 횟수 계산
	printf("average Bin compare count: %.2f\n", allCount); //그 결과 출력

	//메모리 해제 후 프로그램 종료
	freeTree(root); 
	return 0;
}
