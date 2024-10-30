#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100
#define MAX_CHAR 256

// 노드 구조체 정의
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode* left, * right;
};

// 최소 힙 구조체 정의
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// 새 노드 생성
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// 최소 힙 생성
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// 두 노드 교환
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// 최소 힙화
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 크기가 1인지 확인
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// 최소값 추출
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// 최소 힙에 노드 삽입
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// 최소 힙 빌드
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// 힙 생성
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// 허프만 트리 생성
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode* left, * right, * top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// 허프만 코드 생성 및 표시
void printCodes(struct MinHeapNode* root, int arr[], int top, char codes[256][MAX_TREE_HT]) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1, codes);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1, codes);
    }

    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i) {
            codes[(int)root->data][i] = arr[i] + '0';
            printf("%d", arr[i]);
        }
        codes[(int)root->data][top] = '\0';
        printf("\n");
    }
}

// Huffman Codes 생성 및 복호화
void HuffmanCodes(char data[], int freq[], int size) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    char codes[256][MAX_TREE_HT] = { {0} };

    printCodes(root, arr, top, codes);

    // 압축 해제 예제
    char encodedString[] = "10110010001110101010100";
    printf("Decoded string: ");
    struct MinHeapNode* current = root;
    for (int i = 0; encodedString[i] != '\0'; i++) {
        if (encodedString[i] == '0')
            current = current->left;
        else
            current = current->right;

        if (!current->left && !current->right) {
            printf("%c", current->data);
            current = root;
        }
    }
    printf("\n");
}

// 문자 빈도 계산
void calculateFrequency(FILE* file, int freq[]) {
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch >= 0 && ch < MAX_CHAR) {
            freq[(int)ch]++;
        }
    }
}

int main() {
    FILE* file = fopen("Huffman_input.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return -1;
    }

    int freq[MAX_CHAR] = { 0 };
    calculateFrequency(file, freq);
    fclose(file);

    // 유효한 문자의 빈도와 데이터 배열 생성
    char data[MAX_CHAR];
    int data_freq[MAX_CHAR];
    int size = 0;

    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i] > 0) {
            data[size] = (char)i;
            data_freq[size] = freq[i];
            size++;
        }
    }

    // Huffman Codes 생성 및 복호화
    HuffmanCodes(data, data_freq, size);

    return 0;
}
