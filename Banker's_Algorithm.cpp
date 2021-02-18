#include <iostream>
#include <vector>
#include <string>
using namespace std;


int N;	// Process�� ���� 
int M;	// Resource Type�� ����

int Max[200][200];
int Allocation[200][200];
int Need[200][200];
int Available[200];

bool Finish[200];
int Sequence[200];

// ����� ���� �Լ�
void InputValues();
void BANKER();
void PrintChange(int);
void PrintInfo();

int main() {
	cout << "======================================================" << endl;
	cout << "=                  OS Assignment #3                  =" << endl;
	cout << "=               : Banker's Algorithm                 =" << endl;
	cout << "=                                 2016112650 ������  =" << endl;
	cout << "======================================================" << endl;

	// Process���� ������ �Է�
	InputValues();

	// Sequence �Է�
	cout << "\nProcess Sequence[] : ";
	for (int i = 0; i < N; i++) {
		cin >> Sequence[i];
	}

	// Banker's Algorithm �����Լ�
	BANKER();

	int get;
	cout << "Type Anything -> Enter to Exit!" << endl;
	cin >> get;

	return 0; 
}

void InputValues() {
	cout << "<Input>" << endl;
	cout << "Number of Process : ";
	cin >> N;
	cout << "Number of Resource Type : ";
	cin >> M;

	cout << "\nAvailable[] Matrix : " << endl;
	cout << " ex) Available[j] = k : j�� ���ҽ��� k�� Available" << endl;
	for (int j = 0; j < M; j++) {
		cin >> Available[j];
	}

	cout << "\nMax[][] Matrix : " << endl;
	cout << " ex) Max[i][j] = k : i�� ���μ����� j�� ���ҽ��� �ִ� k�� �䱸" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Max[i][j];
		}
	}
	cout << "\nAllocation[][] Matrix : " << endl;
	cout << " ex) Allocation[i][j] = k : i�� ���μ����� j�� ���ҽ��� ���� k�� �Ҵ��" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Allocation[i][j];
		}
	}
	cout << "\nNeed[][] Matrix : Auto Input..." << endl;
	cout << " ex) Allocation[i][j] = k : i�� ���μ����� j�� ���ҽ��� k�� �ʿ���" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			Need[i][j] = Max[i][j] - Allocation[i][j];
			printf("%3d", Need[i][j]);
		}	puts("");
	}

	PrintInfo();
}

void BANKER() {
	int order = 0;

	while (true) {
		// ��� ���μ����� Finish�� Ż��
		bool exit = true;
		for (int i = 0; i < N; i++) {
			if (!Finish[i])
				exit = false;
		}
		if (exit) {
			cout << "SAFE : this sequence works!" << endl;
			return;
		}
		int idx = Sequence[order];
		cout << "\n\n" << endl;
		cout << "======================================================" << endl;
		cout << order + 1 << "��° : Process"<< idx << endl;

		// Need���� �����ǵ��� �Ҵ� ������ �� �˻�
		bool canAlloc = true;
		for (int j = 0; j < M; j++) {
			if (Need[idx][j] > Available[j])
				canAlloc = false;
		}
		
		// �Ҵ� �����ϴٸ�
		if (canAlloc) {
			// 1. Allocation
			PrintChange(idx);	// Need, Available �� ���
			for (int j = 0; j < M; j++) {
				Available[j] -= Need[idx][j];
				Allocation[idx][j] += Need[idx][j];
				Need[idx][j] = 0;
			}
			cout << " �� " << endl;
			cout << " �� (Allocate!)" << endl;
			cout << " �� " << endl;
			cout << " �� " << endl;
			PrintChange(idx);

			// 2. Release
			for (int j = 0; j < M; j++) {
				Available[j] += Allocation[idx][j];  
				Allocation[idx][j] = 0;
				Finish[idx] = true;
			}
			cout << " �� " << endl;
			cout << " �� (Release!)" << endl;
			cout << " �� " << endl;
			cout << " �� " << endl;
			PrintChange(idx);
			cout << "======================================================" << endl;
		}
		// �Ҵ��� �� �ȴٸ�
		else {
			cout << "UNSAFE : this sequence doesn't work!" << endl;
			PrintInfo();
			return;
		}
		// ���� �ε��� �˻�
		order++;
	}
}

void PrintChange(int process) {
	int idx = process;

	printf("Need      : ");
	for (int j = 0; j < M; j++) {
		printf("%3d", Need[idx][j]);
	}
	puts("");
	
	printf("Available : ");
	for (int j = 0; j < M; j++) {
		printf("%3d", Available[j]);
	}
	puts("");
}

void PrintInfo() {
	cout << "\n============================================================================================================" << endl;
	// ù° ��
	printf("%-6s%-30s%-30s%-30s\n", "", "Allocation", "MAX", "Available");

	// ��° ��
	printf("%6s", "");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < M; j++) {
			printf("R%-2d ", j);
		}
		for (int k = 0; k < 30 - 4 * M; k++) {
			printf(" ");
		}
	}
	puts("");
	// ��° �� ~ (N+3)��° ��
	for (int i = 0; i < N; i++) {
		printf(" P%-2d  ", i);
		for (int j = 0; j < M; j++) {
			printf("%-3d ", Allocation[i][j]);
		}
		for (int k = 0; k < 30 - 4 * M; k++) {
			printf(" ");
		}
		for (int j = 0; j < M; j++) {
			printf("%-3d ", Max[i][j]);
		}
		for (int k = 0; k < 30 - 4 * M; k++) {
			printf(" ");
		}
		if (i == 0) {
			for (int j = 0; j < M; j++) {
				printf("%-3d ", Available[j]);
			}
			for (int k = 0; k < 30 - 4 * M; k++) {
				printf(" ");
			}
		}
		puts("");
	}
	cout << "============================================================================================================\n" << endl;
}