#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define LT 0
#define RT 1
#define LTI(ni) tree[ni].child[0]
#define RTI(ni) tree[ni].child[1]
#define MAXN 100007
#define INF 10000007
using namespace std;
// LT < node < RT
struct Node {
	//  ֵ�� �Ѽ���������ţ�ͬ����ֵ�������� ���Լ�Ϊ�������Ĵ�С
	int value, aux, child[2], cnt, size;
} tree[MAXN];
int root = 0, ttop = 1;
void init() {
	srand(20021104);
	tree[root].aux = RAND_MAX; // rand(): 0 ~ RAND_MAX
	tree[root].size = 0;
}
inline void update_size(int ni) {
	tree[ni].size = tree[tree[ni].child[LT]].size + tree[ni].cnt
	                + tree[tree[ni].child[RT]].size;
}

// ���԰�����rotateͳһ����
inline void rotate(int& xi, int type) {
	int yi = tree[xi].child[type];
	/* ----------------- key -------------------- */
	tree[xi].child[type] = tree[yi].child[1-type];
	tree[yi].child[1-type] = xi;
	/* ----------------- key -------------------- */
	update_size(xi), update_size(yi); // ����һ��
	xi = yi; // �޸Ĵ���xi�����ֶԵ�ǰ������
}

// ����ݹ����
void _insert (int& xi, int value) {
	//*
	if (xi == 0) { // û�����ֵ�Ľڵ�(xiΪ0ʱ���������)
		xi = ++ttop; // �޸Ĵ����ָ�룡����Ҳ�����޸�root
		tree[xi].value = value;
		tree[xi].cnt = 1;
		tree[xi].aux = rand();
		tree[xi].child[LT] = tree[xi].child[RT] = 0;
	} else if (tree[xi].value == value) { // �����ֵ�Ľڵ�
		tree[xi].cnt++;
	} else { // ����Ҫ�ݹ�
		int type = tree[xi].value < value; // BST������
		_insert(tree[xi].child[type], value); // �ݹ�
		// ���ƻ��˶Ѿ�תһת
		if (tree[tree[xi].child[type]].aux < tree[xi].aux)
			rotate(xi, type);
	}
	update_size(xi);
	//printf("DEBUG(last xi, value):%d %d\n", xi, value);
}
inline void insert(int value) {
	_insert(root, value);
}

// ����ݹ�ɾ��
void _erase(int& xi, int value) {
	if (xi == 0) return;
	if (tree[xi].value == value) { // �������ڵ�
		if (tree[xi].cnt > 1) { // ����һ��
			tree[xi].cnt--;
		} else { // ֻ��һ���Ļ���Ҫȥ����ڵ���
			if (!tree[xi].child[LT] && !tree[xi].child[RT]) { //�����������յĻ�
				xi = 0;  // ֱ��ɾ��, �Ź�, ֱ��ȥ��������������
				return;
			}
			// �����߼���ʵ�е㸴��
			/*
			 * ���û��RT��Leftת
			 * ���û��LT��Rightת
			 * �����Ǳ�auxС���Ǳ�ת
			 */
			// ���ڿյĽڵ�ָ���tree[0].auxΪ-1�϶�С, ����ֻҪ����aux�ͺ�
			int type =
			    tree[tree[xi].child[LT]].aux > tree[tree[xi].child[RT]].aux;
			rotate(xi, type);
			// ת���˾ͼ�������ɾ��ֱ�����
			_erase(xi, value);
		}
	} else { // �����û�ҵ���ڵ�, �ͼ�����BST����������
		_erase(tree[xi].child[value > tree[xi].value], value);
	}
	update_size(xi);
}
inline void erase(int value) {
	_erase(root, value);
}

int _getKth(int& xi, int k) {
	//printf("DEBUG(getKth:xi, k)%d %d\n", xi, k);
	// ���k��LT��size��С����ô��k���һ����LT����
	if (k <= tree[tree[xi].child[LT]].size)
		return _getKth(tree[xi].child[LT], k);

	// �����k��ȥ�Լ�ǰ��ĺ��Լ�������
	k -= tree[tree[xi].child[LT]].size + tree[xi].cnt;
	// ��Ϊǰ���ж���k��LT��size, ��������Ϊ����Ψһ���ܾ��ǵ�k�����ǵ�ǰֵ
	if (k <= 0)
		return tree[xi].value;
	// ���k����, ˵����RT�Ǳ�
	else return _getKth(tree[xi].child[RT], k);
}
inline int getKth(int k) {
	return _getKth(root, k);
}
Node& _find(int& xi, int value) {
	//printf("DEBUG(find:xi) %d\n", xi);
	if (tree[xi].value == value)
		return tree[xi];
	else if (value < tree[xi].value)
		return _find(tree[xi].child[LT], value);
	else if (value > tree[xi].value)
		return _find(tree[xi].child[RT], value);
}
Node& find(int value) {
	return _find(root, value);
}
int _get_rank(int xi, int value) {
	if (xi == 0) return 1;
	if (value <= tree[xi].value) return _get_rank(LTI(xi), value);
	else return _get_rank(RTI(xi), value) + tree[LTI(xi)].size + tree[xi].cnt; 
}
inline int get_rank(int value){
	return _get_rank(root, value);
}
int _front(int xi, int value) {
	int best;
	while(xi){
		if (tree[xi].value < value)
			(best = tree[xi].value), (xi = RTI(xi));
		else xi = LTI(xi);
	}
	return best;
}
inline int front(int value) {
	return _front(root, value);
}
int _next(int xi, int value) {
	int best;
	while (xi){
		if (tree[xi].value > value)
			(best = tree[xi].value), (xi = LTI(xi));
		else xi = RTI(xi);
	}
	return best;
}
inline int next(int value) {
	return _next(root, value);
}
int main() {
	int n, opt, v;
	scanf("%d", &n);
	init();
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &opt, &v);
		switch (opt) {
			case 1:
				insert(v);
				break;
			case 2:
				erase(v);
				break;
			case 3:
				printf("%d\n", get_rank(v));
				break;
			case 4:
				printf("%d\n", getKth(v));
				break;
			case 5:
				printf("%d\n", front(v));
				break;
			case 6:
				printf("%d\n", next(v));
				break;
			default:
				break;
		}
	}
	return 0;
}
